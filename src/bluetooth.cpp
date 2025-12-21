#include <string>
#include <vector>

#include "bluetooth.h"
#include <BleKeyboard.h>

#include "BluetoothSerial.h"
#include "libraries/gui/list.h"
#include "libraries/gui/gui.h"

std::vector<std::string> devices;
List btList("BT", devices, 0, 1);

extern GUI gui;


// private scope (only in this file)
namespace {
    unsigned long previousMillis = 0;
    unsigned long previousMillis_ = 0;

    const unsigned long scanInterval = 5000;
}

int scanTime = 2;

bool INIT = false;


namespace Bluetooth {
    BluetoothSerial serialBT;

    void Init() {
        if(!serialBT.begin("ESP32_Scanner"))
        {
            Serial.println("[SerialBT] Init failed.");
            return;
        }
        
        Serial.println("[SerialBT] Init was successfully.");
        gui.showList(&btList);

        serialBT.discoverAsync([](BTAdvertisedDevice *device) {
            Serial.print("Name: ");
            Serial.print(device->getName().c_str());
            Serial.print(" | Address: ");
            Serial.println(device->getAddress().toString().c_str());

            btList.AddOption(device->getName());
            gui.updateList();
        });
        
        INIT = true;
    }

    void Loop() {
        if (!INIT) return;

        unsigned long currentMillis = millis();
        if (currentMillis - previousMillis >= scanInterval) {
            previousMillis = millis();

            // serialBT.discoverAsyncStop();
            // Serial.println("Scan stopped.");
            // if (bk.isConnected()) {
            //     Serial.println("[Bluetooth] Client connected, sending keys...");
            //     bk.press(KEY_LEFT_GUI);
            //     bk.press('r');
            //     bk.releaseAll();
            //     delay(500);
            //     bk.print("Hello from ESP32 BLE Keyboard!");
            // }
        }
    }
}
