#include <vector>
#include <string>
#include <WiFi.h>
#include "defines.h"
#include "index.h"
#include "libraries/gui/gui.h"
#include "libraries/gui/text.h"
#include "libraries/gui/option.h"
#include <stdint.h>
#include <stdlib.h>
#include "icons.h"

std::vector<Option*> network_options;
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
    networksList = new List(std::string("Wifis"), network_options, List::Theme::One, onWifiExit);
    
    std::string str = std::string("Scanning...");
    Text* scanning = new Text(str, SSD1306_WHITE, Text::Vector2 {SCREEN_WIDTH/2 - 6*str.size()/2, SCREEN_HEIGHT/2}, 1);

    gui.drawText(scanning);   
    WiFi.scanNetworks(true);

    scan = true;
}


struct Signal {
    std::string text;
    const unsigned char* bmp;
};

Signal GetSignalData(int32_t dBm)
{
    int v = abs(dBm);

    if      (v <= 30)  return Signal { "Excellent", excellent_bitmap };
    else if (v <= 50)  return Signal { "Very Good", epd_bitmap_very_good };
    else if (v <= 70)  return Signal { "Good", epd_bitmap_good};
    else if (v <= 100) return Signal { "Weak", epd_bitmap_weak };

    return {};
}
void ScanWifi()
{
    networksList->clearOptions();
    Serial.println("network-s>clearOptions");
    
    int n = WiFi.scanComplete();
    if(n<=0)
        return;

    for(int i = 0; i < n; i++) 
    {
        int rssi = abs(WiFi.RSSI(i));
        Signal sigData = GetSignalData(rssi);
        //     Option(const std::string& t, const unsigned char* bmp, void (*onClickFunction)());

        networksList->AddOption(new Option(std::string(WiFi.SSID(i).c_str()), 1, sigData.bmp, nullptr));
    }


    if(networksList->options.size() > 0)
    {
        if(gui.GlobalList != networksList)
            gui.prepareList(networksList);

        else gui.drawList();
    }
    WiFi.scanDelete();
}


unsigned long previousMillis = 0;
const unsigned long scanInterval = 5000;

void IndexMenu::loop()
{
    if(!scan)
        return;

    unsigned long currentMillis = millis();
    if(currentMillis-previousMillis >= scanInterval)
    {
        previousMillis = millis();
        WiFi.scanNetworks(true);
    }

    int n = WiFi.scanComplete();
    if(n > 0)
    {
        ScanWifi();
    }
}