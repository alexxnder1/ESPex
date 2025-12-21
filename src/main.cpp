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
#include "bluetooth.h"

WifiServer server(IPAddress(192,168,4,1), IPAddress(192,168,4,1), IPAddress(255,255,255,0));

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

GUI gui(&display);

void setup() {
  Serial.begin(115200);
  gui.init();

  pinMode(JOYSTICK_SW, INPUT_PULLUP);

  Serial.println("ESP32 Booted!");
  server.softAPInit();

  IndexMenu::show();
  gui.assignLastMenu(IndexMenu::show);
}

void loop() {
  uint16_t y = analogRead(JOYSTICK_VRx);
  uint16_t x = analogRead(JOYSTICK_VRy);
  bool pressed = digitalRead(JOYSTICK_SW) == 0;

  gui.processControls(x,y,pressed);
  IndexMenu::loop();
  Bluetooth::Loop();
}