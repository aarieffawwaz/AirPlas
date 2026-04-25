# AIRPLAS V1: IoT-Integrated Multi-Spectral Smartphone Microscope

AIRPLAS is a frontier technology project developed by ADA World Class IoT Developer Team. It transforms a standard smartphone into a professional-grade microscope by combining custom optics with an IoT-driven lighting system. This repository contains the firmware for the **XIAO ESP32-C3** and the documentation for the Cloud-to-Hardware integration.

## 🌟 Core Concept

Traditional smartphone microscopes rely on ambient light or static LEDs. AIRPLAS V1 introduces **Multi-Spectral Cloud Synchronization**. By utilizing Firebase as a bridge, the lighting system adjusts its wavelength (color) in real-time coordination with the smartphone camera's capture sequence, allowing for automated, high-contrast, and biological-grade imaging.

## 🛠 Technical Specifications

### Hardware Architecture
- **Microcontroller:** Seeed Studio XIAO ESP32-C3 (RISC-V architecture).
- **Lighting:** 8x WS2812B NeoPixel Addressable LEDs (12mm Internal Diameter).
- **Power:** 110mAh LiPo Battery (LP501225) with USB-C Charging.
- **Switching:** 4-pin tactile switch connected to GPIO D1 with internal pull-up.
- **Optics:** 12mm glass microscope/macro lens (10x-100x magnification).

### Connectivity & IoT Logic
- **Protocol:** WiFi (802.11 b/g/n) for Cloud communication.
- **Backend:** Firebase Realtime Database (RTDB) via Stream Callback.
- **Discovery:** Bluetooth Low Energy (BLE) for initial WiFi provisioning (R&D Phase).

## 📂 Software Infrastructure (PlatformIO)

The project is managed via **PlatformIO** for robust dependency management and C++ compilation.

### Dependency List
- `adafruit/Adafruit NeoPixel`: For high-speed LED timing.
- `mobizt/Firebase ESP Client`: For the low-latency Stream Callback listener.

### State Machine Logic
The firmware operates on a **Synchronized State Machine**. It "subscribes" to a Firebase path and reacts to integer states sent by the Flutter mobile application:

| State | Color | Use Case |
| :--- | :--- | :--- |
| `0` | AIRPLAS Blue | Device Standby / Navigation Mode |
| `1` | Pure White | Standard high-detail microscopic capture |
| `2` | Vivid Red | High-contrast texture and surface depth |
| `3` | Deep Green | Enhanced visualization of biological chlorophyll |
| `4` | Electric Blue | UV-simulated fluorescence/specialized staining |

## 📐 Mechanical & 3D Design

The design focuses on **Ergonomics** and **Stability**.
- **Universal Bracket:** A sliding carriage system on twin guide rails allows the lens to align with any smartphone camera array (iPhone, Samsung, etc.).
- **Material:** Optimized for high-resolution 3D printing (0.1mm layer height recommended).
- **Electronics Housing:** "Dead-bug" wiring layout to maintain a thickness of less than 15mm.

## 🚀 Getting Started (R&D Testing)

1.  **Clone the Repo:** Open the folder in VS Code with PlatformIO.
2.  **Config:** Update `WIFI_SSID`, `WIFI_PASSWORD`, `API_KEY`, and `DATABASE_URL` in `src/main.cpp`.
3.  **Build:** Click the **PlatformIO: Build** (Checkmark) to verify headers.
4.  **Flash:** Connect the XIAO ESP32-C3 via USB-C and click **PlatformIO: Upload** (Arrow).
5.  **Monitor:** Click the **Serial Monitor** (Plug) to confirm "WiFi Connected" and "Stream Active."

## 🔋 Power Operations
- **Power On:** Single press of the tactile button (D1).
- **Power Off:** Hold the tactile button for **2 seconds**. This puts the ESP32 into **Deep Sleep** mode to preserve battery life while maintaining the ability to wake up on the next press.

## 📜 Credits & License
Developed by **ADA World Class IoT Developer Team**.
