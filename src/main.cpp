#include <ArduinoJson.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <Arduino.h>

#include <string>
#include <vector>

#include "defines.h"
#include "libraries/list.h"
#include "libraries/gui.h"
#include "libraries/menus/index.h"

const char* ssid = "ESP32 Server";
AsyncWebServer server(80);


IPAddress localIP(192,168,4,1);
IPAddress gateway(192,168,4,1);
IPAddress subnet(255,255,255,0);


Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

GUI gui(&display);

void setup() {
  Serial.begin(115200);
  gui.init();

  // pinMode(JOYSTICK_VRx, INPUT);
  // pinMode(JOYSTICK_VRy, INPUT);
  pinMode(JOYSTICK_SW, INPUT_PULLUP);

  Serial.println("ESP32 Booted!");
  if(!SPIFFS.begin(true)) {
    Serial.println("SPIFFS mount failed.");
    return;
  }

  WiFi.softAPConfig(localIP, gateway, subnet);
  WiFi.softAP(ssid);
  Serial.printf("Fixed AP IP address: %s", localIP.toString());

  server.serveStatic("/", SPIFFS, "/").setDefaultFile("index.html");

  gui.clear();
  IndexMenu::show();
  gui.assignLastMenu(IndexMenu::show);

  // server.on("/api/humidity_temp", HTTP_GET, [](AsyncWebServerRequest* request) {
  //   float temp = dht.readTemperature();
  //   float hum = dht.readHumidity();
  //   String json = "{\"temperature\":" + String(temp) + ",\"humidity\":" + String(hum) + "}";
  //   Serial.println(json);
    
  //   AsyncWebServerResponse* response = request->beginResponse(200, "application/json", json);
  //   response->addHeader("Access-Control-Allow-Origin", "*");  // CORS header
  //   response->addHeader("Access-Control-Allow-Methods", "GET, PUT, POST, OPTIONS");
  //   response->addHeader("Access-Control-Allow-Headers", "Content-Type");
  //   request->send(response);
  // }); 

  // server.on("/api/buzz", HTTP_GET, [](AsyncWebServerRequest* request) {
  //     digitalWrite(BUZZ_PIN, HIGH);
  //     delay(1000);
  //     digitalWrite(BUZZ_PIN, LOW);    
  //     request->send(200, "text/plain", "Buzzed!");
  // });

  server.on("/api/input", HTTP_POST,     [](AsyncWebServerRequest *request){
        request->send(200, "application/json", "{\"status\":\"ok\"}");
    },
    NULL,
    [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total){

        DynamicJsonDocument doc(256);
        deserializeJson(doc, (const char*) data, len);
        const char* text = doc["text"] | "NULL";
        Serial.printf("POST body: %s", data);

        // display.clearDisplay();
        // display.setTextSize(2);
        // display.setTextColor(SSD1306_WHITE);
        // display.setCursor(0,0);
        // display.println(text);
        // display.display();
        // Serial.println(text);
  });

  server.begin();
}
void loop() {
  uint16_t y = analogRead(JOYSTICK_VRx);
  uint16_t x = analogRead(JOYSTICK_VRy);
  bool pressed = digitalRead(JOYSTICK_SW) == 0;

// Serial.println(x);
  gui.updateControls(x,y,pressed);
  IndexMenu::loop();
  delay(50);
}