# Smart Workspace Monitor - Pin Connections & Wiring 

## Arduino Pin Assignment Table

| Component | Signal | Arduino Pin | Pin Type | Voltage | Notes |
|-----------|--------|-------------|----------|---------|-------|
| **LCD Display (16x2)** |
| | RS (Register Select) | 12 | Digital Output | 5V | Command/Data selection |
| | EN (Enable) | 11 | Digital Output | 5V | Enable signal |
| | D4 (Data Bit 4) | 5 | Digital I/O | 5V | 4-bit mode |
| | D5 (Data Bit 5) | 4 | Digital I/O | 5V | 4-bit mode |
| | D6 (Data Bit 6) | 3 | Digital I/O | 5V | 4-bit mode |
| | D7 (Data Bit 7) | 2 | Digital I/O | 5V | 4-bit mode |
| **Ultrasonic Sensor (HC-SR04)** |
| | Trigger | 8 | Digital Output | 5V | Ultrasonic pulse trigger |
| | Echo | 7 | Digital Input | 5V | Echo pulse input |
| **Temperature Sensor (LM35)** |
| | Signal Output | A0 | Analog Input | 0-5V | Temperature voltage |
| **Light Sensor (LDR)** |
| | Signal Output | A1 | Analog Input | 0-5V | Light level voltage |
| **Fan Motor** |
| | PWM Control | 6 | PWM Output | 0-5V | Speed control signal |
| **LED Light** |
| | PWM Control | 9 | PWM Output | 0-5V | Brightness control |
| **Buzzer** |
| | Control Signal | 13 | Digital Output | 5V | Audio alert |

## Detailed Wiring Connections

### 1. LCD Display (16x2) Wiring 

**LCD Pin Layout:**
```
LCD Pin | Function | Arduino Connection | Notes
--------|----------|-------------------|-------
1 (VSS) | Ground   | GND               | Common ground
2 (VDD) | Power    | 5V                | Main power supply
3 (V0)  | Contrast | Potentiometer     | 10kΩ pot for contrast
4 (RS)  | Register | Pin 12            | Command/Data select
5 (RW)  | Read/Write| GND              | Always write mode
6 (EN)  | Enable   | Pin 11            | Enable pulse
7-10    | Data 0-3 | Not Connected     | Using 4-bit mode
11 (D4) | Data 4   | Pin 5             | Data bit 4
12 (D5) | Data 5   | Pin 4             | Data bit 5
13 (D6) | Data 6   | Pin 3             | Data bit 6
14 (D7) | Data 7   | Pin 2             | Data bit 7
15 (A)  | Backlight| 5V via 220Ω      | Backlight anode
16 (K)  | Backlight| GND               | Backlight cathode
```

**Connection Steps:**
1. Connect VSS (pin 1) to Arduino GND
2. Connect VDD (pin 2) to Arduino 5V
3. Connect V0 (pin 3) to center pin of 10kΩ potentiometer
4. Connect potentiometer outer pins to 5V and GND
5. Connect RS (pin 4) to Arduino pin 12
6. Connect RW (pin 5) to Arduino GND
7. Connect EN (pin 6) to Arduino pin 11
8. Skip pins 7-10 (not used in 4-bit mode)
9. Connect D4-D7 (pins 11-14) to Arduino pins 5,4,3,2 respectively
10. Connect backlight A (pin 15) to 5V through 220Ω resistor
11. Connect backlight K (pin 16) to GND

### 2. HC-SR04 Ultrasonic Sensor Wiring 

**Sensor Pin Configuration:**
```
HC-SR04 Pin | Function | Arduino Connection | Wire Color (Suggested)
------------|----------|-------------------|---------------------
VCC         | Power    | 5V                | Red
GND         | Ground   | GND               | Black
Trig        | Trigger  | Pin 8             | Yellow
Echo        | Echo     | Pin 7             | Green
```

**Important Notes:**
- Requires stable 5V power supply (minimum 15mA)
- Maximum detection range: 4 meters
- Minimum detection range: 2 cm
- Operating frequency: 40kHz
- Trigger pulse must be 10µs HIGH signal

### 3. LM35 Temperature Sensor Wiring 

**LM35 Pin Configuration:**
```
LM35 Pin | Function | Arduino Connection | Description
---------|----------|-------------------|-------------
1 (+Vs)  | Power    | 5V                | Power supply (4V-30V)
2 (Vout) | Output   | A0                | Voltage output (10mV/°C)
3 (GND)  | Ground   | GND               | Ground reference
```

**Voltage Calculation:**
- Output: 10mV per degree Celsius
- 0°C = 0V, 25°C = 250mV, 100°C = 1V
- Arduino reads: (ADC_value / 1024) * 5V
- Temperature = (Voltage - 0.5V) * 100

### 4. LDR (Light Sensor) Circuit Wiring 

**LDR Voltage Divider Circuit:**
```
5V ----[LDR]----+----[10kΩ]---- GND
                 |
                 +---- A1 (Arduino)
```

**Circuit Analysis:**
- Forms voltage divider with 10kΩ fixed resistor
- LDR resistance varies: ~1kΩ (bright) to ~10MΩ (dark)
- Voltage at A1: Vout = 5V * (10kΩ) / (LDR + 10kΩ)
- Bright light: Low LDR resistance → Higher voltage
- Dark conditions: High LDR resistance → Lower voltage

### 5. Fan Motor Driver Circuit 

**Motor Control Setup:**
```
Arduino Pin 6 (PWM) ----[1kΩ]---- Base (NPN Transistor)
                                     |
5V ----[Fan Motor]---- Collector ----+
                                     |
GND ------------------- Emitter -----+
                         |
                     [Flyback Diode]
```

**Components Required:**
- NPN Transistor (2N2222 or similar)
- 1kΩ base resistor
- Flyback diode (1N4007) across motor terminals
- DC fan motor (5V, <500mA recommended)

**Safety Notes:**
- Flyback diode prevents voltage spikes
- Transistor handles motor current, Arduino provides control signal
- PWM frequency: ~490Hz (Arduino default)

### 6. LED Circuit Wiring 

**LED Driver Circuit:**
```
Arduino Pin 9 (PWM) ----[220Ω]---- LED Anode
                                     |
                                   LED Cathode ---- GND
```

**Circuit Specifications:**
- Current limiting resistor: 220Ω
- LED forward voltage: ~2V (red), ~3.3V (white/blue)
- LED current: ~20mA maximum
- PWM frequency: ~490Hz

### 7. Buzzer Connection 

**Active Buzzer Wiring:**
```
Arduino Pin 13 ---- Buzzer Positive (longer leg)
GND --------------- Buzzer Negative (shorter leg)
```

**Passive Buzzer Alternative:**
```
Arduino Pin 13 ----[100Ω]---- Buzzer Positive
GND -------------------------- Buzzer Negative
```

## Power Supply Requirements ⚡

### Total Power Consumption Analysis

| Component | Voltage | Current | Power |
|-----------|---------|---------|-------|
| Arduino Uno | 5V | ~50mA | 250mW |
| LCD Display | 5V | ~20mA | 100mW |
| HC-SR04 | 5V | ~15mA | 75mW |
| LM35 | 5V | ~60µA | 0.3mW |
| Fan Motor | 5V | 0-200mA | 0-1W |
| LED | 5V | 0-20mA | 0-100mW |
| Buzzer | 5V | ~30mA | 150mW |
| **Total** | **5V** | **~355mA** | **~1.7W** |

### Recommended Power Supply
- **USB Power**: Adequate for development and testing
- **External Adapter**: 5V, 2A minimum for reliable operation
- **Battery Operation**: 4x AA batteries (6V) with voltage regulator

## PCB Layout Considerations 

### Component Placement Tips
1. **Keep analog circuits away from digital switching**
2. **Place bypass capacitors near power pins**
3. **Use thick traces for power and ground**
4. **Keep crystal oscillator close to microcontroller**
5. **Separate analog and digital ground planes if possible**

### Signal Integrity
- Use twisted pairs for long sensor cables
- Add pull-up resistors on I2C lines (if expanded)
- Include decoupling capacitors (100nF ceramic, 10µF electrolytic)
- Consider shielding for sensitive analog signals

## Troubleshooting Connection Issues 

### Common Wiring Problems

**LCD Not Working:**
- Check all 6 data connections (RS, EN, D4-D7)
- Verify contrast potentiometer setting
- Ensure proper power supply connections
- Test with simple "Hello World" code

**Ultrasonic Sensor Issues:**
- Swap Trig and Echo pins if not working
- Check 5V power supply stability
- Verify timing in code (10µs trigger pulse)
- Test with known working sensor

**Temperature Reading Errors:**
- Check LM35 orientation (flat side facing out)
- Verify 5V supply voltage accuracy
- Test with multimeter on sensor output
- Calculate expected voltage for room temperature

**LDR Not Responding:**
- Check voltage divider circuit
- Test LDR resistance with multimeter
- Verify pull-down resistor value (10kΩ)
- Calibrate threshold values in code

**Fan/LED Control Problems:**
- Verify PWM-capable pins (3,5,6,9,10,11)
- Check transistor connections for fan
- Test with simple analogWrite() commands
- Measure voltages with multimeter

### Testing Individual Components

**Step-by-Step Testing:**
1. **Power Test**: Verify 5V and GND on all components
2. **Digital I/O**: Test with simple digitalWrite/digitalRead
3. **Analog Input**: Monitor with analogRead and Serial.println
4. **PWM Output**: Test with analogWrite and oscilloscope/LED
5. **Integration**: Combine tested components gradually

**Debug Code Examples:**
```cpp
// Test LCD
lcd.print("LCD Test OK");

// Test ultrasonic
Serial.println(distance);

// Test temperature
Serial.println(temperatureC);

// Test LDR
Serial.println(analogRead(LDR_PIN));

// Test fan PWM
analogWrite(FAN_PIN, 128); // 50% speed

// Test LED PWM
analogWrite(LIGHT_INTENSITY_LED_PIN, 128); // 50% brightness
```

This comprehensive wiring guide ensures proper connections and reliable operation of all system components.