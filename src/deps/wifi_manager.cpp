#include <Arduino.h>
#include <WiFi.h>
#include "config.h"

void setupWiFiStation() {
  WiFi.mode(WIFI_STA);
  Serial.println("Connecting to Wi-Fi: " WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 20) {
    delay(1000);
    Serial.print(".");
    attempts++;
  }
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("\nFailed to connect to Wi-Fi!");
    while (true);
  }
  Serial.println("\nWi-Fi Connected");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void setupWiFiAP() {
  const char* ssid = "Espresso";
  const char* password = "12345678";

  WiFi.mode(WIFI_AP);
  Serial.println("Starting Wi-Fi AP...");
  if (!WiFi.softAP(ssid, password, 6)) {
    Serial.println("Failed to start Wi-Fi AP!");
    while (true);
  }
  delay(2000);
  Serial.println("Access Point Started");
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());
  Serial.print("Wi-Fi Status: ");
  Serial.println(WiFi.status());
}