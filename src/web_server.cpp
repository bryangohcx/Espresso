#include <Arduino.h>
#include <WebServer.h>

// LED pin (GPIO 2)
const int ledPin = 2;

// Blinking state (extern to share with main.cpp)
extern bool isBlinking;

// Create web server on port 80
WebServer server(80);

// Function definitions
void toggleBlink() {
  isBlinking = !isBlinking;
}

String getBlinkStatus() {
  return isBlinking ? "Blinking" : "Stopped";
}

// HTML webpage
String htmlPage = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <title>ESP32 OTA Test</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    body { font-family: Arial; text-align: center; padding: 20px; }
    h1 { color: #333; }
    .button { padding: 15px 30px; font-size: 18px; cursor: pointer; margin: 10px; }
    .on { background-color: #4CAF50; color: white; }
    .off { background-color: #f44336; color: white; }
  </style>
</head>
<body>
  <h1>ESP32 OTA Test</h1>
  <p>Wi-Fi and OTA are running.</p>
  <button class="button" onclick="toggleLED()">Toggle LED</button>
  <p>LED Status: <span id="status">Unknown</span></p>
  <script>
    function toggleLED() {
      fetch('/toggle').then(response => response.text()).then(data => {
        document.getElementById('status').innerText = data;
      });
    }
    fetch('/status').then(response => response.text()).then(data => {
      document.getElementById('status').innerText = data;
    });
  </script>
</body>
</html>
)rawliteral";

void setupWebServer() {
  server.on("/", []() {
    server.send(200, "text/html", htmlPage);
  });
  server.on("/toggle", []() {
    digitalWrite(ledPin, !digitalRead(ledPin));
    String status = digitalRead(ledPin) ? "ON" : "OFF";
    Serial.println("LED toggled to " + status);
    server.send(200, "text/plain", status);
  });
  server.on("/status", []() {
    String status = digitalRead(ledPin) ? "ON" : "OFF";
    server.send(200, "text/plain", status);
  });
  server.begin();
  Serial.println("Web server started at http://192.168.4.1");
}

void handleWebServer() {
  server.handleClient();
}