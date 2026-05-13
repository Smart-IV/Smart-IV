# Live Demo

https://smart-iv.github.io/Smart-IV/

**Demo mode is enabled for hackathon evaluation.** Login is temporarily bypassed in the live dashboard flow so judges can access and review features quickly.

# Smart-IV

Smart-IV is an IoT IV-fluid monitoring platform combining ESP32 hardware and a Firebase-backed web dashboard for ward-level clinical monitoring.

## Core Features

- Real-time IV fluid monitoring
- ESP32 integration for bedside telemetry
- Firebase RTDB synchronization
- OLED display monitoring
- Ultrasonic fluid level sensing
- Live dashboard monitoring
- Alert system for low/critical IV levels
- Ward/patient assignment system
- Nurse monitoring workflow
- Demo dashboard access for evaluation

## System Flow

1. **ESP32 nodes** read ultrasonic measurements, compute fluid levels, and publish updates.
2. **Firebase (RTDB + Firestore)** synchronizes telemetry and dashboard data.
3. **Web dashboard** supports assignment, monitoring, alerts, and review workflows.

## Quick Setup

### ESP32

1. Copy `hardware/esp32/current/config.example.h` to `hardware/esp32/current/config.h`.
2. Add local credentials in `config.h`.
3. Open the required `.ino` sketch in Arduino IDE and upload.

### Web Dashboard

1. Copy:
   - `local.config.example.js` -> `local.config.js`
   - `web/archive/local.config.example.js` -> `web/archive/local.config.js`
2. Fill Firebase and local nurse credentials in each `local.config.js`.
3. Open `index.html` (or deploy repository root).

## GitHub Pages Deployment

Deploy from:

- **Branch:** `main`
- **Folder:** `/(root)`

The active dashboard is now served from repository root. `web/archive/` is preserved as the legacy version.

## Security Notes

- Never commit real credentials.
- Keep sensitive values only in ignored local config files.
- Validate Firebase security rules before production use.

## License

MIT License. See [LICENSE](./LICENSE).
