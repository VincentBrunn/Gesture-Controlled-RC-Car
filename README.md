# Gesture-Controlled Car

## Overview
This project features a gesture-controlled car, leveraging a transmitter and receiver system. The transmitter interprets hand gestures, transmitting commands to a receiver module in the car. The receiver processes these commands to control the car's movements (e.g., forward, backward, left, right, stop).

## Project Components
1. **Transmitter Module:**
   - Utilizes an **APDS-9960** gesture sensor to detect hand gestures.
   - Converts sensor readings into control signals and sends them via an RF transmitter.
   - Includes an **ESP32** for processing and signal transmission.

2. **Receiver Module:**
   - Equipped with an RF receiver to capture signals from the transmitter.
   - Interprets control signals to drive motors.
   - Operates using an **ESP32** connected to an H-bridge motor driver.

## Features
- Real-time gesture detection and control.
- Bi-directional movement with smooth transitions.
- Compact, low-power hardware design.

## Hardware Requirements
- **ESP32** (2 units: one for the transmitter, one for the receiver).
- **APDS-9960 Gesture Sensor.**
- L298N Motor Driver.
- DC Motors (2-4, depending on design).
- Power Supply (Lipo Battery).
- Chassis for the car (A custom chassis was designed, 3D printed, and decaled in my project).

## Software Requirements
- Arduino IDE or PlatformIO for ESP32 programming.
- Libraries: `Wire.h`, `SoftwareSerial.h`, `SparkFun_APDS9960.h`.

## Code Description
### Transmitter Code
The transmitter code interprets hand gestures using the **APDS-9960** sensor. Specific gestures correspond to predefined commands (e.g., swiping up sends a "move forward" command). It utilizes serial communication to send commands to the RF module.

### Receiver Code
The receiver code decodes incoming RF signals and maps them to motor operations via the L298N driver. It ensures smooth transitions between movements for stable operation.

## Setup Instructions
1. **Assemble the Transmitter:**
   - Connect the **APDS-9960 Gesture Sensor** to the ESP32.
   - Upload the provided transmitter code to the ESP32 using the Arduino IDE or PlatformIO.

2. **Assemble the Receiver:**
   - Wire the L298N motor driver to the ESP32 and DC motors.
   - Upload the provided receiver code to the ESP32 using the Arduino IDE or PlatformIO.

3. **Power the Modules:**
   - Ensure both transmitter and receiver ESP32 modules have adequate power supplies.

4. **Test and Debug:**
   - Verify the transmitter outputs the correct signals for each gesture.
   - Confirm the receiver processes signals and controls the motors accordingly.

## How to Use
1. Power up the transmitter and receiver modules.
2. Perform hand gestures in front of the transmitter:
   - Swipe up: Move forward.
   - Swipe down: Move backward.
   - Swipe left: Turn left.
   - Swipe right: Turn right.
   - Hold hand still: Stop.
3. Observe the car responding to your gestures in real time.

## Customization
- Modify gesture mappings in the transmitter code for custom gestures.
- Adjust motor control logic in the receiver code for different car configurations.

## Troubleshooting
- **No Response from Car:**
  - Verify transmitter and receiver ESP32 modules are powered.
- **Erratic Movement:**
  - Recalibrate the **APDS-9960 Gesture Sensor**.
  - Ensure stable power supply to motors.

## Future Enhancements
- Integrate Bluetooth or Wi-Fi control using the ESP32's built-in connectivity.
- Add obstacle detection using ultrasonic sensors.
- Implement a more robust communication protocol.

## Acknowledgments
This project is built upon foundational ESP32 and robotics concepts, combining gesture recognition and motor control for an intuitive user experience.
