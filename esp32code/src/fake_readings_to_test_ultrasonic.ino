#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"

// ================= CONFIGURATION =================
#define WIFI_SSID     "RMK"
#define WIFI_PASSWORD "135792468"

// Firebase credentials — DO NOT CHANGE
#define API_KEY      "AIzaSyDixq5gmWhy2QVSKwlDwraBNvu1yY-cCrM"
#define DATABASE_URL "https://hospital-dashboard-d5d1b-default-rtdb.asia-southeast1.firebasedatabase.app/"

// ================= DEVICE ID =================
// This must match the "Device ID" you enter in the website when assigning a patient
#define DEVICE_ID "3270756"

// ================= ULTRASONIC PINS =================
#define TRIG_PIN 18
#define ECHO_PIN 19

// ================= IV BAG CALIBRATION (1000ml bag) =================
// Adjust these distances based on your physical setup
#define DIST_FULL   5.0    // cm when bag is FULL  (sensor close to full bag)
#define DIST_EMPTY  30.0   // cm when bag is EMPTY (sensor far from empty bag)

// Weight calibration for 1000ml IV bag
// Full bag  (~1000ml) = ~1.061 kg  (1000ml * 1.006 density / 1000 + 0.055 bag weight)
// Empty bag (0ml)     = ~0.055 kg  (just the bag/tube weight)
#define WEIGHT_FULL  1.061  // kg when bag is full (1000ml)
#define WEIGHT_EMPTY 0.055  // kg when bag is empty

// ================= UPLOAD SETTINGS =================
const unsigned long LATEST_INTERVAL  = 1000;   // Push "latest" every 1 second (live updates)
const unsigned long HISTORY_INTERVAL = 15000;  // Push history entry every 15 seconds

// ================= GLOBALS =================
FirebaseData fbdo;
FirebaseData fbdoHistory;
FirebaseAuth auth;
FirebaseConfig config;

unsigned long lastLatestMs  = 0;
unsigned long lastHistoryMs = 0;

// =========================================================
// SETUP
// =========================================================
void setup() {
  Serial.begin(115200);
  delay(1000);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  Serial.println("\n=== Smart-IV ESP32 Starting ===");
  Serial.println("Device ID : " + String(DEVICE_ID));

  // ── WiFi ──
  Serial.print("Connecting to WiFi: ");
  Serial.println(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(300);
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected!");
  Serial.print("IP Address : ");
  Serial.println(WiFi.localIP());

  // ── Firebase RTDB ──
  config.api_key      = API_KEY;
  config.database_url = DATABASE_URL;

  if (Firebase.signUp(&config, &auth, "", "")) {
    Serial.println("Firebase Auth  : OK");
  } else {
    Serial.println("Firebase Auth  : FAILED — " + String(config.signer.signupError.message.c_str()));
  }

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

  Serial.println("=== Setup Complete ===\n");
}

// =========================================================
// MEASURE DISTANCE
// =========================================================
float measureDistanceCm() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 30000); // 30ms timeout
  if (duration == 0) return -1; // No echo received

  return duration * 0.034 / 2.0;
}

// =========================================================
// CONVERT DISTANCE TO WEIGHT (for 1000ml bag)
// =========================================================
float distanceToWeight(float distance) {
  // Linear interpolation:
  // DIST_FULL  cm → WEIGHT_FULL  kg (1000ml full)
  // DIST_EMPTY cm → WEIGHT_EMPTY kg (0ml empty)
  float weight = WEIGHT_FULL - ((distance - DIST_FULL) / (DIST_EMPTY - DIST_FULL))
                               * (WEIGHT_FULL - WEIGHT_EMPTY);

  // Clamp to valid range
  weight = max((float)WEIGHT_EMPTY, min((float)WEIGHT_FULL, weight));
  return weight;
}

// =========================================================
// LOOP
// =========================================================
void loop() {
  if (!Firebase.ready()) {
    Serial.println("Firebase not ready...");
    delay(1000);
    return;
  }

  unsigned long now = millis();

  // ── Measure ──
  float distance = measureDistanceCm();

  if (distance < 0) {
    Serial.println("Ultrasonic: No echo — check wiring");
    delay(500);
    return;
  }

  float weight = distanceToWeight(distance);

  // Calculate percentage
  float pct = ((weight - WEIGHT_EMPTY) / (WEIGHT_FULL - WEIGHT_EMPTY)) * 100.0;
  pct = max(0.0f, min(100.0f, pct));

  // Estimated volume remaining (mL)
  float volumeMl = pct * 10.0; // 100% = 1000ml

  // ── Serial Monitor Output ──
  Serial.println("─────────────────────────────────");
  Serial.print("Distance   : "); Serial.print(distance, 1); Serial.println(" cm");
  Serial.print("Weight     : "); Serial.print(weight, 3);   Serial.println(" kg");
  Serial.print("Volume     : "); Serial.print(volumeMl, 1); Serial.println(" mL remaining");
  Serial.print("Percentage : "); Serial.print(pct, 1);      Serial.println(" %");

  // ── Status label ──
  String status;
  if (pct > 50)      { status = "NORMAL"; }
  else if (pct > 20) { status = "LOW";    }
  else               { status = "CRITICAL"; }
  Serial.print("Status     : "); Serial.println(status);

  // ── Push LATEST (every 1 second for live dashboard updates) ──
  if (now - lastLatestMs >= LATEST_INTERVAL || lastLatestMs == 0) {
    lastLatestMs = now;

    String latestPath = "/devices/" + String(DEVICE_ID) + "/latest";

    FirebaseJson latestJson;
    latestJson.set("weight",   weight);
    latestJson.set("pct",      pct);
    latestJson.set("distance", distance);
    latestJson.set("volumeMl", volumeMl);
    latestJson.set("status",   status.c_str());
    latestJson.set("ts",       (long long)millis()); // Use millis as timestamp

    if (Firebase.RTDB.setJSON(&fbdo, latestPath.c_str(), &latestJson)) {
      Serial.println("Firebase Latest: OK");
    } else {
      Serial.println("Firebase Latest: FAILED — " + fbdo.errorReason());
    }
  }

  // ── Push HISTORY entry (every 15 seconds for chart/log) ──
  if (now - lastHistoryMs >= HISTORY_INTERVAL || lastHistoryMs == 0) {
    lastHistoryMs = now;

    String histPath = "/devices/" + String(DEVICE_ID) + "/readings";

    FirebaseJson histJson;
    histJson.set("weight",   weight);
    histJson.set("pct",      pct);
    histJson.set("distance", distance);
    histJson.set("volumeMl", volumeMl);
    histJson.set("status",   status.c_str());
    histJson.set("ts",       (long long)millis());

    if (Firebase.RTDB.pushJSON(&fbdoHistory, histPath.c_str(), &histJson)) {
      Serial.println("Firebase History: OK (pushed new entry)");
    } else {
      Serial.println("Firebase History: FAILED — " + fbdoHistory.errorReason());
    }
  }

  Serial.println("─────────────────────────────────\n");
  delay(500); // Small delay between readings
}
