# Smart-IV: IoT-Based Intelligent IV Fluid Monitoring System

<div align="center">

![Smart-IV Logo](https://img.shields.io/badge/Smart--IV-Healthcare%20IoT-blue)
![License](https://img.shields.io/badge/License-MIT-green)
![Status](https://img.shields.io/badge/Status-Active%20Development-orange)

**Automated real-time monitoring of intravenous fluid levels with intelligent alerts and decision support**

[Features](#features) • [Quick Start](#quick-start) • [Tech Stack](#tech-stack) • [Architecture](#architecture) • [Future Scope](#future-scope) • [Contributing](#contributing)

</div>

---

## 🏥 The Problem

Manual IV fluid monitoring is prone to human error, leading to:
- **Delayed response times** when bottles run empty
- **Risk of reverse blood flow** when bags deplete
- **Inconsistent care quality** in resource-constrained settings
- **Burden on healthcare workers** in understaffed wards
- **Particularly dangerous** for elderly and vegetative state patients who cannot self-report

**Smart-IV automates this critical task.**

---

## 💡 What is Smart-IV?

Smart-IV is an **IoT-enabled real-time fluid monitoring system** that:
- 🔍 **Continuously measures** IV bag weight using precision load cells
- 📊 **Converts weight to percentage** (0-100% remaining)
- 🚨 **Triggers intelligent alerts** (Normal → Low → Critical)
- 📈 **Monitors vital signs** (SpO2, Heart Rate, Temperature)
- 📱 **Streams data to cloud** for remote monitoring and historical analysis
- 🤖 **Provides AI-powered decision support** via Groq LLaMA chatbot
- 🎯 **Prevents reverse blood flow** with automatic servo-controlled pinch mechanism
- 💰 **Hospital-deployable at <Rs. 5,000** per unit

---

## ✨ Current Features (Prototype)

### Hardware Monitoring
- ✅ HX711 load cell integration (calibration factor: 287836.24)
- ✅ Real-time weight measurement & percentage calculation
- ✅ Status classification: Normal (>30%) | Low (10-30%) | Critical (<10%)
- ✅ MAX30102 non-contact sensor for SpO2 & Heart Rate
- ✅ MLX90614 infrared temperature sensor (no probe needed)

### User Interface & Alerts
- ✅ OLED display for local real-time visualization
- ✅ LED status indicators (Green/Yellow/Red)
- ✅ Buzzer alerts for Low/Critical thresholds
- ✅ 3.5" TFT LCD display (320×480) with full UI

### Cloud & Remote Monitoring
- ✅ Firebase Realtime Database for instant updates (<100ms latency)
- ✅ Firestore for historical data & global configuration
- ✅ Web dashboard (Netlify-hosted) for caregiver access
- ✅ Real-time data sync across multiple care environments

### Intelligence
- ✅ Groq AI chatbot (LLaMA 3.3-70B) for decision support
- ✅ Context-aware recommendations based on patient vitals & fluid status

---

## 🛠️ Tech Stack

| Layer | Technology |
|-------|-----------|
| **Microcontroller** | ESP32 DOIT DEVKIT V1 |
| **Sensors** | HX711, MAX30102, MLX90614 |
| **Real-time DB** | Firebase (RTDB + Firestore) |
| **Display** | 3.5" TFT SPI LCD |
| **Power** | 1000mAh LiPo + TP4056 USB-C charger |
| **Web Dashboard** | HTML5, JavaScript, Chart.js, Bootstrap |
| **Cloud Platform** | Netlify (frontend) + Firebase (backend) |
| **AI Engine** | Groq API (LLaMA 3.3-70B) |

---

## 🚀 Quick Start

### Hardware Setup
1. **Assemble components** per BOM (see `/hardware/BOM.md`)
2. **Calibrate load cell** with known weights
3. **Wire sensors** to ESP32 (I2C: SDA=GPIO21, SCL=GPIO22)
4. **3D-print enclosure** from `/hardware/3d-models/`

### Firmware Setup
1. Clone this repository
2. Open `firmware/main.ino` in Arduino IDE
3. Install required libraries:
```bash
   - Firebase Arduino Client Library for ESP32
   - Adafruit_MAX30105
   - Adafruit_MLX90614
   - U8g2 (OLED) or Adafruit_SSD1306
   - HX711_ADC
```
4. Update `config.h` with your WiFi & Firebase credentials
5. Upload to ESP32

### Web Dashboard Setup
1. Navigate to `/web-dashboard/`
2. Update `js/config.js` with your Firebase credentials
3. Deploy to Netlify:
```bash
   git push  # Netlify auto-deploys on push
```
4. Access dashboard at your Netlify domain

---

## 📐 System Architecture

┌─────────────────────────────────────────────────────────────┐
│                    Smart-IV System                           │
├─────────────────────────────────────────────────────────────┤
│                                                               │
│  SENSORS (Bedside)          PROCESSING (ESP32)  CLOUD        │
│  ├─ Load Cell ──┐           ┌─ WiFi ─────────→ Firebase RTDB │
│  ├─ MAX30102 ───┼─ I2C ────→│ Real-time calc └─ Firestore    │
│  └─ MLX90614 ──┘           │ & alerts       └─ Groq AI      │
│                             └─ SPI ─────────→ 3.5" TFT       │
│                                                │               │
│                                                ↓               │
│                                           Web Dashboard       │
│                                         (Remote Monitor)      │
│                                                               │
└─────────────────────────────────────────────────────────────┘

See `/docs/ARCHITECTURE.md` for detailed system design.

---

## 📁 Project Structure

smart-iv/
├── README.md (this file)
├── LICENSE
├── .gitignore
│
├── firmware/
│   ├── main.ino (setup + loop)
│   ├── sensors.ino (sensor operations)
│   ├── firebase.ino (cloud sync)
│   ├── display.ino (UI rendering)
│   ├── alerts.ino (notification logic)
│   └── config.h (credentials - .gitignored)
│
├── web-dashboard/
│   ├── index.html
│   ├── css/ (style.css, theme.css, responsive.css)
│   ├── js/ (config.js, firebase.js, app.js, etc.)
│   └── assets/
│
├── hardware/
│   ├── BOM.md (bill of materials)
│   ├── 3d-models/ (STL files for 3D printing)
│   └── schematics/ (circuit diagrams)
│
├── docs/
│   ├── SETUP.md (detailed installation)
│   ├── ARCHITECTURE.md (system design)
│   ├── API.md (Firebase schema)
│   └── CONTRIBUTING.md (how to contribute)
│
└── mobile-app/ (coming soon)

---

## 🔮 Future Scope (Post-MVP)

### Phase 2: Enhanced Monitoring
- **Raspberry Pi 5 local server** (Mosquitto MQTT, Node.js/Express, PostgreSQL)
  - Replace cloud dependency with on-premise control
  - Reduce latency for critical alerts
  - Enable offline operation in connectivity-challenged areas

### Phase 3: Expanded Deployment
- **LoRaWAN integration** (SX1276 module)
  - Long-range, low-power communication
  - Rural healthcare centers without WiFi
  - Hospital-wide mesh network

### Phase 4: Advanced Features
- **Servo-controlled auto-stop mechanism**
  - Automatically pinches IV tube when bag runs empty
  - Prevents dangerous reverse blood flow
  - Fail-safe design (opens if power lost)

- **Voice alerts** (DFPlayer Mini speaker)
  - Multilingual voice prompts
  - Status announcements (Power on, WiFi connected, Critical alert)

- **Mobile app** (iOS/Android native)
  - Push notifications for alerts
  - Quick-access metrics dashboard
  - Offline sync when WiFi unavailable

- **Compact clip-on module** (<Rs. 1,000/unit)
  - Portable across wards
  - Quick attach/detach from IV stand
  - Battery life: 6+ hours per charge

---

## 🧪 Testing & Validation

- ✅ Load cell calibration tested with known weights
- ✅ Real-time Firebase latency: <100ms
- ✅ Sensor accuracy: ±2-3% (clinical acceptable)
- ✅ Hardware tested on hospital-standard IV stands
- ⏳ Mobile app testing (Q3 2024)
- ⏳ Large-scale deployment trial (Q4 2024)

---

## 🤝 Contributing

We welcome contributions! Please see [CONTRIBUTING.md](./docs/CONTRIBUTING.md) for:
- How to report bugs
- How to suggest features
- How to submit pull requests
- Code style guidelines

**Current needs:**
- Backend developers (Node.js/Express for RPi server)
- Mobile app developers (React Native)
- UX/UI designers
- Healthcare domain experts for requirements validation

---

## 📜 License

This project is licensed under the **MIT License** - see [LICENSE](./LICENSE) file for details.

---

## 🙏 Acknowledgments

- Built during **WitchHunt Hackathon** (Health & Wellbeing theme)
- Mentorship from healthcare professionals at R.M.K. Engineering College
- Community feedback from nurses and hospital administrators
- Open-source libraries: Firebase, Chart.js, Bootstrap, Arduino ecosystem

---

## 📞 Support & Contact

- **Documentation**: See `/docs/` folder
- **Issues**: Report bugs via GitHub Issues
- **Questions**: Open a Discussion or reach out to team leads
- **Demo**: Check out our [video submission](link-to-video)

---

## 🎯 Roadmap

| Phase | Timeline | Focus |
|-------|----------|-------|
| Phase 1 (Current) | Apr-Jun 2024 | Core prototype, Firebase integration |
| Phase 2 | Jul-Sep 2024 | RPi5 local server, offline capability |
| Phase 3 | Oct-Dec 2024 | LoRaWAN, rural deployment testing |
| Phase 4 | 2025+ | Mobile app, enterprise features |

---

**Made with ❤️ for healthcare innovation**
