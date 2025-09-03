# 3-Phase Power Metering and Monitoring System  

A complete system for real-time measurement, display, and control of three-phase power. This project combines **low-cost sensors**, **relay protection**, and **dual firmware paths**—STM32 HAL (C) and Arduino IDE (C++)—making it suitable for both **academic learning** and **industrial prototyping**.  



## 📌 Features
- Measure voltage, current, and calculate power for each phase.  
- Display results in real time on an OLED screen.  
- Relay-based load protection with configurable thresholds.  
- Two firmware options:  
  - **STM32F411CEU6 (C, STM32CubeIDE + HAL drivers)**  
  - **Arduino IDE (C++)**  
- Modular hardware design with terminal blocks for safe and flexible connections.  



## ⚡ Quick Start  

### Hardware Required
- **MCU**: STM32F411CEU6 (Black Pill) or Arduino-compatible board  
- **Sensors**: 3× ZMPT101B (voltage), 3× ACS712 (current)  
- **Display**: OLED SSD1306 (128×64, I²C)  
- **Relays**: 3-channel module (5V control, 250V AC rated)  
- **Power**:  
  - 12V DC (relays)  
  - 5V/3.3V regulated supply (MCU, sensors, display)  

⚠️ **Safety Note**: The system interfaces with 3-phase AC (400V). Always test with proper isolation, protective enclosures, and safety procedures.  



### Firmware Options  

#### 1️⃣ STM32 (C, HAL Drivers)  
- Open `firmware/stm32/` in **STM32CubeIDE**.  
- Ensure ADC, I²C, and GPIO peripherals are configured.  
- Build and flash to the STM32F411CEU6.  

#### 2️⃣ Arduino IDE (C++)  
- Open `firmware/arduino/` in **Arduino IDE**.  
- Install required libraries:  
  - `Adafruit_GFX`  
  - `Adafruit_SSD1306`  
- Select your board → upload the sketch.  



## 🔄 System Workflow
1. Initialize OLED display and relays.  
2. Read voltage and current from each phase.  
3. Compute per-phase power.  
4. Display results on OLED.  
5. Apply relay logic if thresholds are exceeded.  
6. Repeat continuously.  



## 📊 Example OLED Output

Phase A: 220V 2.3A 506W

Phase B: 218V 2.1A 458W

Phase C: 221V 2.4A 530W



## 🚀 Future Extensions
- Network integration (Wi-Fi / Ethernet) for remote monitoring.  
- Advanced sensor calibration for higher accuracy.  
- Fault detection and predictive analytics.  
- Cloud-based logging and dashboards.  
