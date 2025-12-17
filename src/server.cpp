#include <Arduino.h>
#include "server.h"
#include <WiFi.h>

const char* ssid = "ESP32 Server";

// cache
LocalServer::LocalServer(IPAddress ip, IPAddress gateway, IPAddress subnet)
{
    this->ip = ip;
    this->subnet = subnet;
    this->gateway = gateway;

    if(Serial.available())
        Serial.println("Server initialized.");
}

void LocalServer::softAPInit()
{
  WiFi.softAPConfig(this->ip,this->gateway,this->subnet);
  WiFi.softAP(ssid);
  Serial.printf("IP address: %s", this->ip.toString());
}