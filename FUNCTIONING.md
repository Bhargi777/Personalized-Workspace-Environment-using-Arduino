# Smart Workspace Monitor - System Functioning 🔄

## Overview

The Smart Workspace Monitor is an intelligent Arduino-based system designed to promote healthy work habits by monitoring user presence, environmental conditions, and encouraging regular posture breaks. The system operates autonomously to create an optimal workspace environment while protecting user health.

## Core System Functions

### 1. User Presence Detection 👤

**How it Works:**
- Uses HC-SR04 ultrasonic sensor to detect user presence within 50cm range
- Continuously measures distance using sound wave reflection
- Triggers different system modes based on presence/absence

**Implementation:**
```cpp
// Distance calculation using ultrasonic sensor
duration = pulseIn(ULTRASONIC_ECHO_PIN, HIGH);
distance = (duration / 2) / 29.1;

if (distance < settings.presenceDistanceCm && distance > 0) {
    // User present - activate working mode
} else {
    // User away - activate power saving mode
}
```

### 2. Posture Break Management ⏰

**Functionality:**
- Tracks continuous working time using `millis()` function
- Triggers break reminders after configurable time limit (default: 10 seconds)
- Forces break period with audio alerts and environmental changes
- Automatically returns to normal mode after break completion

**Break Cycle:**
1. **Working Phase**: Timer starts when user detected
2. **Alert Phase**: Buzzer sounds when time limit reached
3. **Break Phase**: Countdown timer displayed, reduced environmental controls
4. **Reset Phase**: Return to working mode, timer resets

**Code Logic:**
```cpp
void checkPosture(WorkspaceState *currentState) {
    if (!currentState->onBreak && 
        (millis() - currentState->postureStartTime > settings.postureTimeLimit)) {
        // Trigger break mode
        tone(BUZZER_PIN, 500);
        currentState->onBreak = true;
        currentState->breakEndTime = millis() + settings.breakDuration;
    }
    
    if (currentState->onBreak && millis() > currentState->breakEndTime) {
        // End break mode
        currentState->onBreak = false;
        noTone(BUZZER_PIN);
        currentState->postureStartTime = millis();
    }
}
```

### 3. Temperature-Based Fan Control 🌡️

**Smart Climate Control:**
- LM35 temperature sensor provides real-time temperature readings
- Fan speed automatically adjusts based on ambient temperature
- Temperature range: 20°C to 35°C mapped to PWM values 0-255
- Energy efficient operation with gradual speed changes

**Temperature Processing:**
```cpp
void controlFan() {
    int tempValue = analogRead(TEMP_SENSOR_PIN);
    float voltage = (tempValue / 1024.0) * 5.0;
    float temperatureC = CALCULATE_CELSIUS(voltage);
    
    int fanSpeed = map(temperatureC, 20, 35, 0, 255);
    fanSpeed = constrain(fanSpeed, 0, 255);
    analogWrite(FAN_PIN, fanSpeed);
}
```

**Temperature Conversion Macro:**
```cpp
#define CALCULATE_CELSIUS(voltage) ((voltage - 0.5) * 100)
```

### 4. Adaptive Lighting System 💡

**Ambient Light Response:**
- LDR (Light Dependent Resistor) monitors ambient light levels
- LED brightness inversely proportional to ambient light
- Bright environment = dim LED, dark environment = bright LED
- Threshold values configurable for different lighting conditions

**Light Control Logic:**
```cpp
void controlLight() {
    int ldrValue = analogRead(LDR_PIN);
    int ledBrightness = map(ldrValue, settings.ldrLowThreshold, 
                           settings.ldrHighThreshold, 255, 0);
    ledBrightness = constrain(ledBrightness, 0, 255);
    analogWrite(LIGHT_INTENSITY_LED_PIN, ledBrightness);
}
```

### 5. Real-time Status Display 📺

**LCD Information System:**
- 16x2 character LCD provides continuous status updates
- Dynamic content based on current system state
- Clear, informative messages for user guidance

**Display States:**
- **Away Mode**: "Status: Away" + "Power Saving..."
- **Working Mode**: "Status: Working"
- **Break Mode**: "Break Time: Xs" with countdown

## System States and Transitions

### State 1: Away Mode (Power Saving) 🔋

**Activation Conditions:**
- No user detected within presence range
- Distance sensor reads > 50cm or invalid reading

**System Behavior:**
- Fan motor: OFF (0 PWM)
- LED: Minimum brightness (30 PWM)
- Buzzer: Silent
- LCD: Shows away status
- Posture timer: Inactive

### State 2: Working Mode (Active Monitoring) 💼

**Activation Conditions:**
- User detected within presence range
- Not currently in break mode

**System Behavior:**
- Fan: Temperature-controlled operation
- LED: Ambient light-controlled brightness
- Posture timer: Active and counting
- LCD: Shows working status
- Environmental controls: Fully active

### State 3: Break Mode (Health Alert) 🚨

**Activation Conditions:**
- User present continuously for time limit duration
- Posture timer exceeds threshold

**System Behavior:**
- Buzzer: 500Hz tone alert
- Fan: Reduced speed (50 PWM)
- LED: Moderate brightness (50 PWM)
- LCD: Break countdown display
- Timer: Counts down break duration

## Advanced Features

### Memory Management
- Dynamic memory allocation for startup messages
- Proper memory cleanup with `free()` function
- Efficient string handling with `strcpy()` and `sprintf()`

### Recursive Programming
- Factorial calculation demonstration
- Shows advanced programming concepts
- Educational value for code structure

### Data Structure Organization
- Custom structures for settings and state management
- Clean separation of configuration and runtime data
- Pointer-based function parameters for efficiency

```cpp
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
```

## System Timing and Performance

### Update Cycle
- Main loop executes every 200ms
- Sensor readings processed in real-time
- State transitions immediate when conditions met

### Response Times
- Presence detection: ~200ms
- Temperature adjustment: Real-time
- Light adjustment: Real-time
- Break alert: Immediate when timer expires

### Power Efficiency
- Automatic power saving when user away
- PWM control for efficient motor and LED operation
- Minimal standby current consumption

## Configuration and Customization

### Adjustable Parameters
```cpp
const WorkspaceSettings settings = {
    10000,  // Posture time limit (10 seconds)
    5000,   // Break duration (5 seconds)
    50,     // Presence distance (50cm)
    6,      // LDR low threshold
    679     // LDR high threshold
};
```

### Calibration Requirements
- LDR thresholds based on lighting environment
- Temperature ranges for fan control
- Presence distance for workspace size
- Break timing for user preferences

## Health and Ergonomics Benefits

### Posture Management
- Regular break reminders prevent prolonged sitting
- Configurable timing for different work styles
- Audio alerts ensure user awareness

### Environmental Comfort
- Automatic temperature regulation
- Optimal lighting conditions
- Reduced eye strain and thermal stress

### Productivity Enhancement
- Distraction-free operation when away
- Immediate comfort adjustment when present
- Clear status information for peace of mind

## Error Handling and Reliability

### Sensor Validation
- Distance readings validated for reasonable ranges
- Temperature sensor voltage conversion with bounds checking
- LDR readings constrained to valid PWM ranges

### System Recovery
- Automatic state reset when user leaves and returns
- Timer synchronization prevents stuck states
- Memory allocation error handling

This intelligent system combines multiple sensors and control mechanisms to create a responsive, health-conscious workspace environment that adapts to user behavior and environmental conditions.