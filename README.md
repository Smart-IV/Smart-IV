# Smart-IV

Smart-IV is an IoT IV-fluid monitoring system with ESP32 firmware and a Firebase-backed web dashboard for real-time patient monitoring.

## Features

- Real-time IV fluid monitoring
- Firebase RTDB integration
- OLED display monitoring
- Ultrasonic sensor level detection
- Web dashboard monitoring
- ESP32-based IoT architecture
- Alert/notification system

## Architecture

1. **ESP32 firmware** reads sensor data, computes fluid metrics, and uploads updates.
2. **Firebase (RTDB + Firestore)** stores device streams and dashboard application data.
3. **Web dashboard** visualizes live status, patient registry, alerts, and reports.

## Setup

### ESP32 setup

1. Copy `hardware/esp32/current/config.example.h` to `hardware/esp32/current/config.h`.
2. Fill your local credentials in `config.h`.
3. Open the required `.ino` sketch in Arduino IDE and upload.

### Web setup

1. Copy:
   - `web/current-site/local.config.example.js` -> `web/current-site/local.config.js`
   - `web/archive/local.config.example.js` -> `web/archive/local.config.js`
2. Fill local Firebase and nurse credential values in each `local.config.js`.
3. Serve/deploy the web folder as usual.

### Optional env reference

Use `.env.example` as a reference list of required values. Do not commit `.env` or `.env.local`.

## Deployment (Netlify)

For current dashboard deployment, publish from:

- `web/current-site`

This preserves the existing path and behavior compatibility.

## Folder Structure

```text
Smart-IV/
├── README.md
├── LICENSE
├── .gitignore
├── .env.example
├── app/
│   └── apk/
│       └── app.apk
├── docs/
│   ├── architecture.md
│   ├── features.md
│   └── setup_guide.md
├── hardware/
│   └── esp32/
│       ├── README.md
│       ├── archive/
│       │   └── smart_iv_thingspeak_old.ino
│       ├── current/
│       │   ├── smart_iv_firebase.ino
│       │   ├── config.example.h
│       │   └── config.h (ignored)
│       ├── diagrams/
│       │   └── diagram.json
│       └── test_data/
│           └── fake_readings_to_test_ultrasonic.ino
├── web/
│   ├── current-site/
│   │   ├── index.html
│   │   ├── local.config.example.js
│   │   └── local.config.js (ignored)
│   └── archive/
│       ├── index.html
│       ├── local.config.example.js
│       └── local.config.js (ignored)
```

## Security Notes

- No real credentials should be committed.
- Keep all sensitive values only in ignored local config files.
- Rotate previously exposed secrets (WiFi, Firebase keys, ThingSpeak keys, nurse passwords) before production use.
- Validate Firebase and database security rules before public deployment.

## License

MIT License. See [LICENSE](./LICENSE).
