#include <Arduino.h>
#include <WiFi.h>
#include "wifi_server.h"

const char* ssid = "ESP32 Server";

WifiServer::WifiServer(IPAddress ip, IPAddress gateway, IPAddress subnet)
{
    this->ip = ip;
    this->subnet = subnet;
    this->gateway = gateway;

    if(Serial.available())
        Serial.println("Server initialized.");
}

void WifiServer::softAPInit()
{
  // WiFi.mode(WIFI_OFF);
  WiFi.softAPConfig(this->ip,this->gateway,this->subnet);
  WiFi.softAP(ssid);
  Serial.printf("IP address: %s", this->ip.toString());
}