#include <vector>
#include <string>
#include <WiFi.h>
#include "defines.h"
#include "index.h"
#include "libraries/gui/gui.h"
#include "libraries/gui/text.h"

std::vector<std::string> networks_names;
List* networksList;

extern GUI gui;

void onWifiExit()
{
    gui.clear();
    WiFi.scanNetworks(false);
    IndexMenu::scan = false;
}

void IndexMenu::WIFI()
{
    gui.clear();
    networksList = new List(std::string("Wifis"), networks_names, 1, {}, onWifiExit);

    std::string str = std::string("Scanning...");
    Text* scanning = new Text(str, SSD1306_WHITE, Text::Vector2 {SCREEN_WIDTH/2 - 6*str.size()/2, SCREEN_HEIGHT/2}, 1);

    gui.createText(scanning);   
    WiFi.scanNetworks(true);

    scan = true;
}

// 6x8
void ScanWifi()
{
    networksList->clearOptions();
    Serial.println("network-s>clearOptions");

    for(int i =0; i < WiFi.scanComplete(); i++) 
    {
        networksList->AddOption(std::string(WiFi.SSID(i).c_str()));
    }

    if(networksList->options.size() > 0)
    {
        if(gui.GlobalList != networksList)
            gui.showList(networksList);

        else gui.updateList();
    }
}

unsigned long previousMillis = 0;
const unsigned long scanInterval = 8000;

void IndexMenu::loop()
{
    if(!scan)
        return;

    unsigned long currentMillis = millis();
    if(currentMillis-previousMillis >= scanInterval)
    {
        previousMillis = millis();
        ScanWifi();   
    }
}