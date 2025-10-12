# Smart Workspace Monitor 

An intelligent Arduino-based workspace monitoring system that promotes healthy work habits through automated environmental controls and posture break reminders.

## TinkerCad Link 
- **The link for the circuit:** -## [TinkerCad](https://www.tinkercad.com/things/iUn9QdFoEgi-personalized-workspace-environment-using-arduino)
 
##  Features

- ** Smart Presence Detection** - Ultrasonic sensor automatically detects when you're at your desk
- ** Posture Break Reminders** - Configurable alerts to encourage healthy work habits
- ** Temperature Control** - Automatic fan speed adjustment based on ambient temperature
- ** Adaptive Lighting** - LED brightness adapts to ambient light conditions
- ** Real-time Display** - LCD shows current status and break countdown
- ** Power Saving** - Reduces power consumption when workspace is unoccupied
- ** Audio Alerts** - Gentle buzzer reminders for break time

##  Quick Start

### Prerequisites

- Arduino IDE (1.8+ or 2.0+)
- Basic electronics knowledge
- Soldering skills (optional, breadboard works fine)

### Hardware Requirements

| Component | Quantity | Purpose |
|-----------|----------|---------|
| Arduino Uno/Nano | 1 | Main controller |
| 16x2 LCD Display | 1 | Status display |
| HC-SR04 Ultrasonic | 1 | Presence detection |
| LM35 Temperature Sensor | 1 | Temperature monitoring |
| LDR (Light Sensor) | 1 | Ambient light detection |
| DC Fan/Motor | 1 | Temperature control |
| LED | 1 | Adaptive lighting |
| Buzzer | 1 | Audio alerts |
| Resistors & Wires | Various | Circuit connections |

### Installation

1. **Clone the Repository**
   ```bash
   git clone https://github.com/yourusername/smart-workspace-monitor.git
   cd smart-workspace-monitor
   ```

2. **Hardware Setup**
   - Follow the detailed wiring guide in [PIN-CONNECTIONS.md](PIN-CONNECTIONS.md)
   - Connect all components according to the pin assignment table
   - Double-check all connections before powering on

3. **Software Setup**
   - Open `workspace_monitor.ino` in Arduino IDE
   - Install required libraries (LiquidCrystal is usually pre-installed)
   - Select your Arduino board and port
   - Upload the code

4. **Configuration**
   - Modify settings in the code if needed:
   ```cpp
   const WorkspaceSettings settings = {
       10000,  // Posture time limit (ms)
       5000,   // Break duration (ms)
       50,     // Presence distance (cm)
       6,      // LDR low threshold
       679     // LDR high threshold
   };
   ```

## 📋 Documentation

| Document | Description |
|----------|-------------|
| [ PROJECT-OVERVIEW.md](PROJECT-OVERVIEW.md) | Complete project background, goals, and vision |
| [ FUNCTIONING.md](FUNCTIONING.md) | Detailed explanation of how the system works |
| [ PIN-CONNECTIONS.md](PIN-CONNECTIONS.md) | Comprehensive wiring guide and circuit diagrams |

##  Usage

### System States

** Away Mode**
- Activates when no user detected
- Powers down fan and dims LED
- Shows "Status: Away" on LCD

** Working Mode**
- Activates when user is present
- Environmental controls active
- Posture timer running
- Shows "Status: Working" on LCD

** Break Mode**
- Triggered after prolonged sitting
- Buzzer sounds reminder
- Shows countdown timer
- Reduced environmental controls

### Quick Controls

- **Power On**: Connect to USB or external power
- **Reset**: Press Arduino reset button
- **Calibration**: Adjust LDR thresholds in code for your lighting conditions

##  Customization

### Timing Settings
```cpp
// Adjust these values in the code
postureTimeLimit = 10000;  // 10 seconds (change to 30 minutes: 1800000)
breakDuration = 5000;      // 5 seconds (change to 2 minutes: 120000)
```

### Detection Range
```cpp
presenceDistanceCm = 50;   // Adjust detection distance
```

### Environmental Thresholds
```cpp
ldrLowThreshold = 6;       // Calibrate for your lighting
ldrHighThreshold = 679;    // Adjust based on environment
```

##  System Specifications

| Specification | Value |
|---------------|-------|
| **Operating Voltage** | 5V DC |
| **Power Consumption** | ~350mA (max with fan) |
| **Detection Range** | 2cm - 4m (configurable) |
| **Temperature Range** | 20°C - 35°C (for fan control) |
| **Response Time** | <500ms |
| **Update Frequency** | 200ms |

##  Troubleshooting

### Common Issues

**LCD not displaying:**
- Check all 6 connection pins (RS, EN, D4-D7)
- Adjust contrast potentiometer
- Verify 5V power supply

**Presence detection not working:**
- Verify ultrasonic sensor connections (Trig→8, Echo→7)
- Check for obstacles blocking sensor
- Ensure stable 5V power supply

**Temperature readings incorrect:**
- Verify LM35 orientation and connections
- Check room temperature with external thermometer
- Ensure sensor has proper 5V supply

**Fan/LED not responding:**
- Confirm PWM pins are used (6 for fan, 9 for LED)
- Check transistor circuit for fan motor
- Test with simple analogWrite() commands

### Debug Mode

Add this to your setup() function for serial debugging:
```cpp
Serial.begin(9600);
// Add Serial.println() statements throughout code to monitor values
```

##  License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

