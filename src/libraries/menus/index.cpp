
#include <vector>
#include <string>
#include "libraries/list.h"
#include "libraries/gui.h"

#include "index.h"

#include <Arduino.h>
#include "esp_system.h"

std::vector<std::string> menu = {"WiFi", "BT", "About"};
List mainList(std::string("Menu"), menu, 0);

extern GUI gui;

void IndexMenu::show()
{
    gui->showList(&mainList);
    mainList.functions.push_back(WIFI);
    mainList.functions.push_back(BT);
    mainList.functions.push_back(About);   
}


/*
WiFi.scanDelete();
    WiFi.scanNetworks(false);
    

*/

void IndexMenu::BT()
{
Serial.println("bt");
}


std::string getDeviceName(int model)
{

    switch(model)
    {
        case 1:
            return std::string("ESP32");
        case 2:
            return std::string("ESP32-S2");
        case 9:
            return std::string("ESP32-S3");
        case 5:
            return std::string("ESP32-C3");
        case 6:
            return std::string("ESP32-H2");
    }

}

void IndexMenu::About()
{
    esp_chip_info_t chipInfo;
    esp_chip_info(&chipInfo);

    gui->destroyList();
    gui->showText("About",  2, SSD1306_WHITE, 0, 0);

    gui->showText(std::string("Device: ") + getDeviceName(chipInfo.model), 1, SSD1306_WHITE, 0, 8*4);
    gui->showText(std::string("CPU Cores: ") + std::to_string(chipInfo.cores), 1, SSD1306_WHITE, 0, 8*5);

    gui->showText(std::string("Features: "), 1, SSD1306_WHITE, 0, 8*7);
    gui->showText(std::string("* WiFi: ") + std::string((chipInfo.features & CHIP_FEATURE_WIFI_BGN) ? "True" : "False"), 1, SSD1306_WHITE, 0, 8*8);
    gui->showText(std::string("* BLE: ") + std::string((chipInfo.features & CHIP_FEATURE_BLE) ? "True" : "False"), 1, SSD1306_WHITE, 0, 8*9);
    gui->showText(std::string("* BT: ") + std::string((chipInfo.features & CHIP_FEATURE_BT) ? "True" : "False"), 1, SSD1306_WHITE, 0, 8*10);
    gui->showText(std::string("* Embbed Flash: ") + std::string((chipInfo.features & CHIP_FEATURE_EMB_FLASH) ? "True" : "False"), 1, SSD1306_WHITE, 0, 8*11);
    gui->showText(std::string("Silicon Revision: ") + std::to_string(chipInfo.revision), 1, SSD1306_WHITE, 0, 8*13);
    gui->showText(std::string("Flash Size Revision: ") + std::to_string(spi_flash_get_chip_size() / (1024 * 1024)) + std::string(" MB"), 1, SSD1306_WHITE, 0, 8*14);
    gui->showText(std::string("ESP-IDF Version: ") + std::string(esp_get_idf_version()), 1, SSD1306_WHITE, 0, 8*15);
}