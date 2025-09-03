#include <Arduino.h>
#include <WiFi.h>

void setupWiFi() {
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