#include <Arduino.h>
#include "wifi_manager.h"
#include "web_server.h"
#include "ota_manager.h"

// LED pin (GPIO 2)
const int ledPin = 2;

// Blinking state
bool isBlinking = true;

void setup() {
  Serial.begin(115200);
  delay(2000);
  Serial.println("Booting...");

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  Serial.println("LED initialized on GPIO 2");

  setupWiFi();
  setupWebServer();
  setupOTA();
}

void loop() {
  handleWebServer();
  handleOTA();
}