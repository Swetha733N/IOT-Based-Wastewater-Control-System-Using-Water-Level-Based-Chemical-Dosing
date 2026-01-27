# 🔌 Hardware Connections

This section explains how the pH sensor module is connected to the ESP32 development board.

---

## 📟 pH Sensor to ESP32 Connections

| pH Sensor Pin | ESP32 Pin | Description |
|--------------|-----------|-------------|
| VCC | 3.3V | Power supply |
| GND | GND | Ground |
| AO | GPIO 36 (ADC1) | Analog output |

---

## 🧠 Connection Explanation

- The **pH sensor probe** is connected to the **pH sensor module**
- The module converts chemical activity into an **analog voltage**
- ESP32 reads this voltage using its **ADC pin (GPIO 36)**
- ESP32 processes the value and sends data to the mobile app

---

## ⚠️ Important Notes

- Use **ADC1 pins only** (GPIO 32–39) for stable readings
- Do not connect the sensor output to digital pins
- Ensure proper grounding to avoid noise in readings
