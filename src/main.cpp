#include <Arduino.h>

#include <Adafruit_SSD1306.h>
#include <string>
#include <vector>

#include "wifi_server.h"

#include "defines.h"
#include <WiFi.h>
#include "libraries/gui/list.h"
#include "libraries/gui/gui.h"
#include "libraries/menus/index.h"
#include "libraries/menus/bluetooth.h"

WifiServer server(IPAddress(192,168,4,1), IPAddress(192,168,4,1), IPAddress(255,255,255,0));

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

GUI gui(&display);

#include "icons.h"

void setup() {
  Serial.begin(115200);
  gui.init();

  pinMode(JOYSTICK_SW, INPUT_PULLUP);

  Serial.println("ESP32 Booted!");
  server.softAPInit();

  // logo showing
  display.drawBitmap(
    0,
    0,
    epd_bitmap_Bitmap,
    SCREEN_WIDTH,
    SCREEN_HEIGHT,
    SSD1306_WHITE
  );

  display.display(); 
  delay(2000);
  // 

  IndexMenu::show();
  gui.assignLastMenu(IndexMenu::show);
}

void loop() {
  gui.loop();
  IndexMenu::loop();
  Bluetooth::Loop();
}