
#include <vector>
#include <string>
#include "libraries/gui/list.h"
#include "libraries/gui/gui.h"

#include "index.h"

#include <Arduino.h>
#include "esp_system.h"
#include "libraries/gui/option.h"

#include "icons.h"

List* mainList;

extern GUI gui;

// asds
void IndexMenu::show()
{
    std::vector<Option*> options = {
        new Option("IR",  1, ir_bitmapir, IR),
        new Option("WiFi", 1, wifi_bitmapwifi, WIFI),
        new Option("BT", 1, bt_bitmapbt, BT),
        new Option("About", 1, about_bitmapinfo, About),
    };

    mainList = new List(std::string("Menu"), options, List::Theme::One);
    gui.prepareList(mainList);
}

#include "bluetooth.h"
#include "ir.h"

void IndexMenu::IR()
{
    IR::Show();
}

void IndexMenu::BT()
{
    // gui.clear();
    Bluetooth::Init();
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

// asd
    gui.clear();

    Text* about = new Text (std::string("About"),  SSD1306_WHITE, Text::Vector2 { 0,0 }, 2);
    Text* device = new Text(std::string("Device: ") + getDeviceName(chipInfo.model), SSD1306_WHITE, Text::Vector2 { 0, 8*4}, 1);
    Text* cpu_cores = new Text(std::string("CPU Cores: ") + std::to_string(chipInfo.cores), SSD1306_WHITE, Text::Vector2 {0, 8*5}, 1);
    Text* features = new Text(std::string("Features: "), SSD1306_WHITE, Text::Vector2 {0, 8*7}, 1);
    Text* wifi = new Text(std::string("* WiFi: ") + std::string((chipInfo.features & CHIP_FEATURE_WIFI_BGN) ? "True" : "False"), SSD1306_WHITE, Text::Vector2 {0, 8*8}, 1);
    Text* ble = new Text(std::string("* BLE: ") + std::string((chipInfo.features & CHIP_FEATURE_BLE) ? "True" : "False"), SSD1306_WHITE, Text::Vector2 {0, 8*9}, 1);
    Text* bt = new Text(std::string("* BT: ") + std::string((chipInfo.features & CHIP_FEATURE_BT) ? "True" : "False"), SSD1306_WHITE, Text::Vector2 {0, 8*10}, 1);
    Text* flash = new Text(std::string("* Embbed Flash: ") + std::string((chipInfo.features & CHIP_FEATURE_EMB_FLASH) ? "True" : "False"), SSD1306_WHITE, Text::Vector2 {0, 8*11}, 1);
    Text* sil = new Text(std::string("Silicon Revision: ") + std::to_string(chipInfo.revision), SSD1306_WHITE, Text::Vector2 {0, 8*13}, 1);
    Text* fsr = new Text(std::string("Flash Size Revision: ") + std::to_string(spi_flash_get_chip_size() / (1024 * 1024)) + std::string(" MB"),  SSD1306_WHITE, Text::Vector2 {0, 8*14}, 1);
    Text* idf = new Text(std::string("ESP-IDF Version: ") + std::string(esp_get_idf_version()), SSD1306_WHITE, Text::Vector2 {0, 8*15}, 1);

    gui.drawText(about);
    gui.drawText(device);
    gui.drawText(cpu_cores);
    gui.drawText(features);
    gui.drawText(wifi);
    gui.drawText(ble);
    gui.drawText(bt);
    gui.drawText(flash);
    gui.drawText(sil);
    gui.drawText(fsr);
    gui.drawText(idf);
} 