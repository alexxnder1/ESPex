#include <ArduinoJson.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <Arduino.h>

#include <Adafruit_SSD1306.h>
#include <string>
#include <vector>

#include "wifi_server.h"

#include "defines.h"
#include "libraries/gui/list.h"
#include "libraries/gui/gui.h"
#include "libraries/menus/index.h"

AsyncWebServer aws(80);

WifiServer server(IPAddress(192,168,4,1), IPAddress(192,168,4,1), IPAddress(255,255,255,0));

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

GUI gui(&display);

void setup() {
  Serial.begin(115200);
  gui.init();

  pinMode(JOYSTICK_SW, INPUT_PULLUP);

  Serial.println("ESP32 Booted!");
  if(!SPIFFS.begin(true)) {
    Serial.println("SPIFFS mount failed.");
    return;
  }
  server.softAPInit();

  aws.serveStatic("/", SPIFFS, "/").setDefaultFile("index.html");

  gui.clear();

  IndexMenu::show();
  gui.assignLastMenu(IndexMenu::show);
  aws.begin();
}

void loop() {
  uint16_t y = analogRead(JOYSTICK_VRx);
  uint16_t x = analogRead(JOYSTICK_VRy);
  bool pressed = digitalRead(JOYSTICK_SW) == 0;

  gui.processControls(x,y,pressed);
  IndexMenu::loop();
  delay(10);
}