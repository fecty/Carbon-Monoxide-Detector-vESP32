# CODEC-v2: Carbon Monoxide Detector & Decorative Night Light

## Project Overview

CODEC-v2 is an intelligent carbon monoxide (CO) detection system built on the Seeed XIAO ESP32-S3 microcontroller. It combines real-time CO concentration monitoring with an interactive visual interface, featuring an OLED display for data visualization and NeoPixel RGB LEDs that provide color-coded safety indicators.

## Features

- **Real-time CO Monitoring**: Uses the Winsen ZE07-CO electrochemical CO sensor module for accurate CO concentration measurement in ppm (parts per million)
- **OLED Display**: 128x64 SSD1306 OLED screen displaying:
  - Current CO concentration levels
  - Real-time graphical representation of concentration trends
- **RGB LED Indicators**: 16 NeoPixel LEDs providing color-coded safety feedback:
  - 🟢 **Green** (≤50 ppm): Safe
  - 🟡 **Yellow** (51-100 ppm): Caution
  - 🔴 **Red** (>100 ppm): Danger
- **Dual UART Communication Modes**: Supports both Mode 1 (Initiative Upload) and Mode 2 (Q&A) protocols for the ZE07-CO sensor

## Hardware Requirements

- **Microcontroller**: Seeed XIAO ESP32-S3
- **CO Sensor**: Winsen ZE07-CO Electrochemical Sensor Module
- **Display**: Adafruit SSD1306 128x64 OLED Display (I2C)
- **LEDs**: 16x Adafruit NeoPixel RGB LEDs (WS2812B compatible)
- **Pins**:
  - LED Pin: D2 (NeoPixel data)
  - Read Flag Pin: D1
  - OLED: I2C (Wire)
  - CO Sensor: UART Serial

## Software Stack

- **Platform**: PlatformIO
- **Framework**: Arduino
- **Key Libraries**:
  - Adafruit NeoPixel (v1.12.3) - for RGB LED control
  - Adafruit SSD1306 (v2.5.13) - for OLED display management
  - Adafruit GFX - graphics library
  - ZE7_CO - custom sensor communication library

## Project Structure

```
CODEC-v2/
├── src/
│   └── main.cpp           # Main application logic
├── lib/
│   └── ZE7_CO/
│       ├── ZE7_CO.h       # Sensor library header
│       └── ZE7_CO.cpp     # Sensor library implementation
├── include/               # Additional header files
├── test/                  # Test directory
├── platformio.ini         # PlatformIO configuration
└── README.md              # This file
```

## How It Works

1. **Initialization**: The system initializes the OLED display, NeoPixel LEDs, and CO sensor in Mode 1 (Initiative Upload mode)
2. **Data Collection**: CO sensor continuously provides concentration data via UART
3. **Display Update**: Real-time CO levels are displayed on the OLED with a scrolling graph
4. **LED Feedback**: NeoPixel array changes color based on concentration thresholds
5. **Serial Output**: Concentration data is logged to serial monitor for debugging and monitoring

## Usage

1. Flash the firmware to the Seeed XIAO ESP32-S3 using PlatformIO
2. Power on the device
3. Monitor CO concentration on the OLED display
4. Observe LED color changes for safety status:
   - Green: Normal operation
   - Yellow: Moderate CO levels detected
   - Red: Dangerous CO levels - evacuate area

## Safety Information

- This device is designed for CO detection in residential environments
- CO is a colorless, odorless gas that can be lethal in high concentrations
- For critical safety applications, consult professional safety standards
- Regular sensor calibration is recommended for accuracy

## Sensor Specifications

- **Sensor Model**: Winsen ZE07-CO
- **Measurement Range**: 0-1000 ppm
- **Communication**: UART (9600 baud)
- **Response Time**: Mode 1 and Mode 2 protocols supported
- **Documentation**: [ZE07-CO Sensor Manual](https://www.winsen-sensor.com/sensors/co-sensor/ze07-co.htm)

## Author

**Zurain Nazir**  
Email: nazirzurain@gmail.com    
Date: December 2024

## License

This project is licensed under the GNU General Public License v3.0 (GPLv3). See individual source files for copyright and license details.

## References

- ZE07-CO Sensor Library (Original): [tweenietomatoes/ZE07CO](https://github.com/tweenietomatoes/ZE07CO)
- Adafruit Libraries Documentation
- [PlatformIO Documentation](https://docs.platformio.org/)

## Contributing

For improvements, bug reports, or feature requests, please contact the author.
