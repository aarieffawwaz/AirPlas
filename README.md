# AirPlas: IoT-Integrated Multi-Spectral Smartphone Microscope

**AirPlas** is a frontier technology project developed by the **ADA World Class IoT Developer Team**. It is a specialized mobile sensing platform designed for the **detection and classification of microplastics** in environmental samples. By combining custom optics with a cloud-synchronized lighting system, AirPlas allows users to perform field-level analysis that previously required laboratory-grade equipment.

## 🌟 Core Concept: The Microplastic Problem

Microplastics (<5mm) are notoriously difficult to distinguish from organic matter under standard white light. **AirPlas V1** introduces **Multi-Spectral Cloud Synchronization** to solve this. By cycling through specific light wavelengths in real-time coordination with a smartphone capture sequence, AirPlas highlights the unique reflective and refractive properties of synthetic polymers (like PET, PE, and PS), making them stand out against biological backgrounds.

## 🛠 Technical Specifications

### Hardware Architecture
* **Microcontroller:** Seeed Studio XIAO ESP32-C3 (RISC-V Single-Core).
* **Lighting Array:** 8x WS2812B NeoPixel Addressable LEDs (12mm ID).
* **Power System:** 110mAh LiPo Battery (LP501225) with USB-C Charging support.
* **Input Interface:** Single 4-pin tactile switch connected to **GPIO D1** (Deep Sleep Wakeup).
* **Optical System:** 12mm glass lens optimized for **micro-polymer morphology**.

### Synchronized State Machine (Microplastic Identification Logic)
The firmware reacts to integer triggers from the Flutter app to change the "Spectral Signature" of the sample:

| State | Color | Microplastic Application |
| :--- | :--- | :--- |
| **0** | **AirPlas Blue** | Standby / Device Status |
| **1** | **Neutral White** | General morphology and size measurement |
| **2** | **Red (625nm)** | Highlighting surface degradation and cracks in weathered plastic |
| **3** | **Green (525nm)** | Filtering out chlorophyll and organic algae interference |
| **4** | **Blue (470nm)** | **High-Energy Visible (HEV) Contrast**: Triggers auto-fluorescence in certain synthetic fibers and fragments |

## 📐 Mechanical & 3D Design

The housing is engineered for **Field Stability**:
* **Universal Bracket:** A dual-rail sliding carriage ensures the lens remains centered over the camera even during heavy outdoor usage.
* **Dead-bug Wiring:** Optimized for a minimal internal footprint to keep the device portable for environmental researchers.

## 🚀 Deployment (R&D Phase)

1.  **Environment:** Open project in VS Code (PlatformIO).
2.  **Configuration:** Update `WIFI_SSID`, `WIFI_PASSWORD`, `API_KEY`, and `DATABASE_URL` in `src/main.cpp`.
3.  **Compilation:** Click **Build** (Checkmark).
4.  **Flashing:** Click **Upload** (Arrow) to flash the ESP32-C3.

## 🔋 Power Management
* **System Boot:** Short-press D1 to wake from sleep.
* **Deep Sleep:** Long-press (**2 seconds**) to enter low-power mode, preserving battery during field treks.

## 📜 Credits
Developed by **ADA World Class IoT Developer Team**.
