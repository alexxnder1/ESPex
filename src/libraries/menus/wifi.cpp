#include <vector>
#include <string>
#include <WiFi.h>
#include "defines.h"
#include "index.h"
#include "libraries/gui.h"
#include "libraries/gui/text.h"

std::vector<std::string> networks_names;
List* networks = new List(std::string("WiFis"), networks_names, 0, 1);

extern GUI gui;

void IndexMenu::WIFI()
{
    gui.destroyList();

    std::string str = std::string("Scanning...");
    Text scanning = Text(str, SSD1306_WHITE, Text::Vector2 {SCREEN_WIDTH/2 - 6*str.size()/2, SCREEN_HEIGHT/2}, 1);

    gui.createText(&scanning);   
    WiFi.scanNetworks(true);

    int n = WiFi.scanComplete();
    while(n == WIFI_SCAN_RUNNING)
    {
        n = WiFi.scanComplete();
        Serial.println("Rescanning...");
    }

    // _gui.showList(networks);
    scan = true;

}



void ScanWifi()
{
    networks_names.clear();
    for(int i =0; i < WiFi.scanComplete(); i++) {
        networks_names.push_back(std::string(WiFi.SSID(i).c_str()));
    }
    networks->options = networks_names;
    if(networks->options.size() > 0)
    {
        if(gui.GlobalList != networks)
            gui.showList(networks);
        gui.updateList();
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