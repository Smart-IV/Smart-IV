#include <WiFi.h>
#include "HX711.h"
#include "ThingSpeak.h"

// ================= VARIABLES =================
float D = 0;                 // Weight in kg
float B = 420.0;             // Calibration factor
float C = 1.0;               // Reference full bag (kg) – adjust if needed
float percentage = 0.0;
bool isMuted = false;

// ================= PINS =================
#define DT 18
#define SCK 19
#define LED_GREEN 15
#define LED_RED 2
#define BUZZER 4

// ================= WIFI =================
const char* ssid = "Wokwi-GUEST";
const char* password = "";

WiFiClient client;

unsigned long channelID = 3270756;
const char* writeAPIKey = "8N5WGZK0XIEGD081";

HX711 scale;

// ===== Blink Control (Non-blocking) =====
unsigned long previousBlink = 0;
const int blinkInterval = 300;
bool redState = false;

// =========================================================

void setup() {

  Serial.begin(115200);
  delay(2000);

  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_RED, LOW);
  noTone(BUZZER);

  // HX711 Setup
  scale.begin(DT, SCK);
  delay(2000);
  scale.set_scale(B);

  Serial.println("Ensure scale is EMPTY...");
  delay(5000);
  scale.tare();

  Serial.println("System Ready");

  // WiFi Setup
  WiFi.begin(ssid, password);
  Serial.print("Connecting");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi Connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  ThingSpeak.begin(client);
}

// =========================================================

void loop() {

  // -------- Read Weight --------
  if (scale.is_ready()) {
    D = max(0.0f, scale.get_units(20));
  }

  percentage = (D / C) * 100.0;

  Serial.print("Weight: ");
  Serial.print(D, 3);
  Serial.print(" kg  |  Percentage: ");
  Serial.print(percentage, 1);
  Serial.println(" %");

  // =========================================================
  //                FINAL LED + ALARM LOGIC
  // =========================================================

  if (D >= 1.0) {
    // NORMAL
    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(LED_RED, LOW);
    noTone(BUZZER);
    isMuted = false;
  }

  else if (D >= 0.5) {
    // LOW
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_RED, HIGH);
    noTone(BUZZER);
  }

  else {
    // CRITICAL
    digitalWrite(LED_GREEN, LOW);

    unsigned long currentMillis = millis();

    if (currentMillis - previousBlink >= blinkInterval) {
      previousBlink = currentMillis;
      redState = !redState;
      digitalWrite(LED_RED, redState);
    }

    if (!isMuted) {
      tone(BUZZER, 1000);
    }
  }

  // =========================================================
  //                ThingSpeak Upload
  // =========================================================

  if (WiFi.status() == WL_CONNECTED) {

    ThingSpeak.setField(1, D);   // Send weight in kg

    int status = ThingSpeak.writeFields(channelID, writeAPIKey);

    if (status == 200) {
      Serial.println("Uploaded ✔");
    } else {
      Serial.print("ThingSpeak Error: ");
      Serial.println(status);
    }
  }

  delay(15000);  // ThingSpeak minimum interval
}
