#include <LiquidCrystal.h>
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

// --- Pin Definitions ---
const int RS = 12, EN = 11, D4 = 5, D5 = 4, D6 = 3, D7 = 2;
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

const int TEMP_SENSOR_PIN = A0;
const int LDR_PIN = A1;
const int ULTRASONIC_TRIG_PIN = 8;
const int ULTRASONIC_ECHO_PIN = 7;
const int FAN_PIN = 6;
const int LIGHT_INTENSITY_LED_PIN = 9;
const int BUZZER_PIN = 13;

#define CALCULATE_CELSIUS(voltage) ((voltage - 0.5) * 100)

struct WorkspaceSettings {
  const long postureTimeLimit;
  const long breakDuration;
  const int presenceDistanceCm;
  const int ldrLowThreshold;
  const int ldrHighThreshold;
};

struct WorkspaceState {
  bool userPresent;
  long postureStartTime;
  bool onBreak;
  long breakEndTime;
};

// --- Global Objects and Variables ---
WorkspaceState state;
const WorkspaceSettings settings = {10000, 5000, 50, 6, 679};

// --- Function Prototypes ---
void checkPosture(WorkspaceState *currentState);
void updateLcdDisplay(const WorkspaceState *currentState);
void controlFan();
void controlLight();
long recursiveFactorial(int n);

long recursiveFactorial(int n) {
  if (n <= 1) { return 1; }
  return n * recursiveFactorial(n - 1);
}

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  
  pinMode(ULTRASONIC_TRIG_PIN, OUTPUT);
  pinMode(ULTRASONIC_ECHO_PIN, INPUT);
  pinMode(FAN_PIN, OUTPUT);
  pinMode(LIGHT_INTENSITY_LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  state.userPresent = false;
  state.onBreak = false;
  state.postureStartTime = 0;
  state.breakEndTime = 0;
  
  char *startupMessage = (char*) malloc(20 * sizeof(char));
  if (startupMessage != NULL) {
    strcpy(startupMessage, "Workspace Ready!");
    lcd.print(startupMessage);
    Serial.println(startupMessage);
    free(startupMessage);
  }

  Serial.print("Demonstrating Recursion: Factorial of 5 is ");
  Serial.println(recursiveFactorial(5));
}

void loop() {
  long duration;
  long distance;

  digitalWrite(ULTRASONIC_TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(ULTRASONIC_TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(ULTRASONIC_TRIG_PIN, LOW);
  
  duration = pulseIn(ULTRASONIC_ECHO_PIN, HIGH);
  distance = (duration / 2) / 29.1;

  if (distance < settings.presenceDistanceCm && distance > 0) { // User is present
    if (!state.userPresent) {
      state.userPresent = true;
      state.postureStartTime = millis();
    }
    
    checkPosture(&state); 

    if (!state.onBreak) {
      controlFan();
      controlLight();
    }
  } else { // User is away
    if (state.userPresent) {
      state.userPresent = false;
    }
    state.onBreak = false;
    
    analogWrite(FAN_PIN, 0);
    analogWrite(LIGHT_INTENSITY_LED_PIN, 30);
    noTone(BUZZER_PIN);
  }

  updateLcdDisplay(&state);
  delay(200);
}

void checkPosture(WorkspaceState *currentState) {
  if (!currentState->onBreak && (millis() - currentState->postureStartTime > settings.postureTimeLimit)) {
    tone(BUZZER_PIN, 500);
    currentState->onBreak = true;
    currentState->breakEndTime = millis() + settings.breakDuration;
    
    analogWrite(FAN_PIN, 50);
    analogWrite(LIGHT_INTENSITY_LED_PIN, 50);
  }

  if (currentState->onBreak && millis() > currentState->breakEndTime) {
    currentState->onBreak = false;
    noTone(BUZZER_PIN);
    currentState->postureStartTime = millis();
  }
}

void controlFan() {
  int tempValue = analogRead(TEMP_SENSOR_PIN);
  float voltage = (tempValue / 1024.0) * 5.0;
  float temperatureC = CALCULATE_CELSIUS(voltage);
  
  int fanSpeed = map(temperatureC, 20, 35, 0, 255);
  fanSpeed = constrain(fanSpeed, 0, 255);
  analogWrite(FAN_PIN, fanSpeed);
}

void controlLight() {
  int ldrValue = analogRead(LDR_PIN);
  int ledBrightness = map(ldrValue, settings.ldrLowThreshold, settings.ldrHighThreshold, 255, 0);
  ledBrightness = constrain(ledBrightness, 0, 255);
  analogWrite(LIGHT_INTENSITY_LED_PIN, ledBrightness);
}

void updateLcdDisplay(const WorkspaceState *currentState) {
  lcd.clear();

  char line1[17];
  char line2[17];
  
  if (currentState->onBreak) {
    int secondsLeft = (currentState->breakEndTime - millis()) / 1000;
    sprintf(line1, "Break Time: %ds", secondsLeft + 1);
    strcpy(line2, ""); 
  } else if (!currentState->userPresent) {
    strcpy(line1, "Status: Away");
    strcpy(line2, "Power Saving...");
  } else {
    strcpy(line1, "Status: Working");
    strcpy(line2, "");
  }

  lcd.setCursor(0, 0);
  lcd.print(line1);
  lcd.setCursor(0, 1);
  lcd.print(line2);
} 