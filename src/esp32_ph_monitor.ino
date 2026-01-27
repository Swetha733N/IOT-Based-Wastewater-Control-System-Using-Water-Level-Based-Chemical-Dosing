/************************************************************
   IoT-Based Water pH Monitoring System
   ESP32 + pH Sensor + Blynk IoT

   - Reads pH value using ESP32 ADC (GPIO 36)
   - Sends real-time pH value to Blynk (Virtual Pin V0)
   - Sends mobile alert if pH is out of safe range
   - Alert is sent only ONCE until pH returns to normal

   Author: Swetha N
 ************************************************************/

// -------- BLYNK TEMPLATE DETAILS --------
// ⚠️ Replace these with your own Blynk credentials
#define BLYNK_TEMPLATE_ID   "YOUR_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "Wastewater pH Monitoring"
#define BLYNK_AUTH_TOKEN    "YOUR_BLYNK_AUTH_TOKEN"

// Enable Serial Monitor printing
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

// -------- WIFI CREDENTIALS --------
// ⚠️ Replace with your WiFi name and password
char ssid[] = "YOUR_WIFI_NAME";
char pass[] = "YOUR_WIFI_PASSWORD";

// -------- pH SENSOR PIN --------
#define PH_PIN 36   // GPIO 36 (ADC1)

// -------- pH VARIABLES --------
float voltage = 0.0;
float pHValue = 0.0;

// -------- SAFE pH RANGE --------
float PH_LOW  = 6.5;
float PH_HIGH = 8.5;

// -------- ALERT CONTROL FLAG --------
bool alertSent = false;

// Blynk Timer
BlynkTimer timer;

/************************************************************
   Function: readPH()
   Reads pH sensor, sends data to Blynk,
   and triggers alert if pH is unsafe
 ************************************************************/
void readPH() {

  // Read raw ADC value
  int adcValue = analogRead(PH_PIN);

  // Convert ADC value to voltage (ESP32: 12-bit ADC)
  voltage = adcValue * (3.3 / 4095.0);

  // Approximate pH calculation formula
  pHValue = 7 + (2.5 - voltage) * 3.5;

  // -------- SERIAL MONITOR OUTPUT --------
  Serial.print("ADC Value: ");
  Serial.print(adcValue);
  Serial.print(" | Voltage: ");
  Serial.print(voltage, 2);
  Serial.print(" V | pH Value: ");
  Serial.println(pHValue, 2);

  // -------- SEND pH VALUE TO BLYNK --------
  Blynk.virtualWrite(V0, pHValue);

  // -------- ALERT LOGIC --------
  if ((pHValue < PH_LOW || pHValue > PH_HIGH) && !alertSent) {
    Blynk.logEvent("ph_alert", "⚠️ Alert: pH Level Out of Safe Range!");
    alertSent = true;   // Prevent repeated alerts
  }

  // Reset alert flag when pH returns to normal
  if (pHValue >= PH_LOW && pHValue <= PH_HIGH) {
    alertSent = false;
  }
}

/************************************************************
   SETUP FUNCTION
 ************************************************************/
void setup() {

  Serial.begin(9600);
  delay(1000);

  // Set ESP32 ADC resolution to 12 bits (0–4095)
  analogReadResolution(12);

  // Connect to Blynk Cloud
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // Read pH value every 2 seconds
  timer.setInterval(2000L, readPH);
}

/************************************************************
   LOOP FUNCTION
 ************************************************************/
void loop() {
  Blynk.run();
  timer.run();
}
