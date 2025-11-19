# Touchless-Gesture-UI

A **touchless user interface system** that allows users to navigate menus using **hand gestures**.  
The system uses **Python (OpenCV + MediaPipe)** for gesture detection and an **ESP32 with OLED display** for real-time UI feedback.

---

## Features

- **Hand gesture detection** for touchless interaction.
- **Hover and pinch-based click** system for selecting menu options.
- **Dynamic UI panel** with:
  - Header
  - Topic for each page
  - Content section
  - Buttons with hover & click visual feedback
- Adjustable **hover time** to avoid accidental clicks.
- OLED display mirrors the computer screen interface.

---

## Hardware Required

- ESP32 DevKit
- 128x64 OLED Display (SSD1306)
- USB cable for programming
- PC with Python 3.x and webcam

---

## Software Requirements

- Python 3.x
- OpenCV
- MediaPipe
- PySerial
- Arduino IDE (for ESP32 code upload)

Install Python dependencies using pip:

## pin Diagram
ESP32      OLED SSD1306
-----------------------
3.3V   -> VCC
GND    -> GND
D21    -> SDA
D22    -> SCL
