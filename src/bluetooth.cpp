#include "bluetooth.h"
#include <BleKeyboard.h>

// private scope (only in this file)
namespace {
    unsigned long previousMillis = 0;
    unsigned long previousMillis_ = 0;

    const unsigned long scanInterval = 5000;
}

namespace Bluetooth {
    BleKeyboard bk("ESP32_BK", "Dev software solutions", 100);

    void Init()
    {
        Serial.println("[Bluetooth] Starting BLE Keyboard...");
        bk.begin();
    }
    
    void Loop()
    {
        unsigned long currentMillis = millis();
        if(currentMillis-previousMillis >= scanInterval)
        {
            previousMillis = millis();
   
            if (bk.isConnected()) {
                Serial.println("[Bluetooth] Client connected, sending keys...");

                bk.press(KEY_LEFT_GUI);
                bk.press('r');
                bk.releaseAll();

                delay(500);
                bk.print("Hello from ESP32 BLE Keyboard!");
            }
        }
    }
}