#  System Architecture

## Overview
The system architecture describes the flow of data from the pH sensor to the mobile application using IoT.

## Architecture Flow
1. The pH sensor measures the acidity/alkalinity of water.
2. The sensor outputs an analog voltage.
3. ESP32 reads the analog value using its ADC pin.
4. The ESP32 processes the value and converts it to pH.
5. The processed pH value is sent to the Blynk Cloud via WiFi.
6. The Blynk mobile application displays the pH value in real time.
7. If the pH value exceeds the safe range, a mobile alert notification is triggered.

## Components Involved
- pH Sensor Module
- ESP32 Microcontroller
- WiFi Network
- Blynk Cloud Server
- Blynk Mobile Application

## Data Flow Diagram (Textual)
 ph Sensor-> ESP32 -> Wifi ->Blynk Cloud ->Mobile App

## Advantages
-Real-time monitoring
-Remote access
-Mobile alerts
-Low-Cost IOT solution
