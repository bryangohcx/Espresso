#include "deps/wifi_manager.h"
#include "deps/ota_manager.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void drawEyes(bool openEyes) {
  display.clearDisplay();

  if (openEyes) {
    // Left eye (circle)
    display.fillCircle(40, 32, 12, SSD1306_WHITE);
    display.fillCircle(40, 32, 6, SSD1306_BLACK); // pupil
    // Right eye (circle)
    display.fillCircle(88, 32, 12, SSD1306_WHITE);
    display.fillCircle(88, 32, 6, SSD1306_BLACK); // pupil
  } else {
    // Closed eyes (lines)
    display.drawLine(28, 32, 52, 32, SSD1306_WHITE); // left eyelid
    display.drawLine(76, 32, 100, 32, SSD1306_WHITE); // right eyelid
  }

  display.display();
}

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);  // SDA, SCL

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  display.clearDisplay();
  display.display();
  
  setupWiFiStation();
  setupOTA();
}

void loop() {
  // Eyes open
  drawEyes(true);
  delay(random(2000, 5000)); // wait 2–5 seconds

  // Blink (close for short time)
  drawEyes(false);
  delay(200);

  // Eyes open again
  drawEyes(true);
  delay(200);

  handleOTA();
}