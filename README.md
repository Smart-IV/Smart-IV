# IV Fluid Monitoring System

An IoT-based system designed to monitor IV fluid levels in real-time using weight measurement and provide alerts when levels drop below defined thresholds.

## Overview
This project uses a load cell to continuously measure the weight of an IV fluid bottle and converts it into percentage levels. Based on the remaining fluid, the system categorizes the status into Normal, Low, and Critical, triggering alerts accordingly.

## Features
- Real-time IV fluid level monitoring (weight → percentage)
- Threshold-based classification:
  - Normal
  - Low
  - Critical
- Visual alerts using LEDs
- Audio alert using buzzer
- Live data display on OLED screen
- Data transmission to web/app (Firebase)
- Initial testing with ThingSpeak

## Hardware Used
- ESP32
- Load Cell + HX711 Amplifier
- OLED Display
- Buzzer
- LEDs

## System Architecture
Sensor (Load Cell) → HX711 → ESP32 →  
→ OLED Display (local output)  
→ Firebase (remote monitoring)  

## Working
1. The load cell measures the weight of the IV fluid bottle.
2. HX711 converts analog signals into digital values.
3. ESP32 processes the data and calculates percentage remaining.
4. Based on thresholds, the system determines status:
   - Normal: Safe level
   - Low: Attention required
   - Critical: Immediate action needed
5. Alerts are triggered using LEDs and buzzer.
6. Data is displayed locally and sent to Firebase for remote access.

## Challenges Faced
- **Weight Calibration:** Required multiple trials to achieve accurate readings.
- **Noise & Unstable Data:** Sensor readings were inconsistent and required smoothing.
- **Data Delay:** Latency in ESP32 → web communication was observed and optimized.

## Improvements Made
- Stabilized sensor readings through calibration adjustments
- Reduced noise and improved consistency
- Optimized data transfer for faster updates

## Future Improvements
- Improved mobile app integration
- More accurate prediction of fluid depletion time
- Battery backup system

## Repository Contents
- Source code for ESP32
- Wokwi simulation file (diagram.json)

## Note
This project was built as a practical solution to monitor IV fluid levels and reduce manual checking in healthcare settings.
