#include <string>
#include <vector>

#include "bluetooth.h"
#include <BleKeyboard.h>

#include "libraries/gui/list.h"
#include "libraries/gui/gui.h"

#include "libraries/gui/gui_element.h"
#include "libraries/gui/text.h"
#include "defines.h"
#include "libraries/gui/list.h"

std::vector<std::string> devices;

extern GUI gui;

List btList("BT Action", { "Shutdown", "Restart", "Chaos", "Etc1", "Etc2", "Etc3" }, 0, 2);

// private scope (only in this file)
namespace {
    unsigned long previousMillis = 0;
    unsigned long previousMillis_ = 0;

    const unsigned long scanInterval = 5000;

    bool onConnectFired = false;
}

namespace Bluetooth {
    BleKeyboard bk("ESP32_BK", "Dev software solutions", 100);

    void Init()
    {
        gui.clear();

        Text* t = new Text(std::string("Waiting for BLE Connection..."), WHITE, GUIElement::Vector2{0,0}, 1);
        t->position = t->GetCenterCoordinates();

        gui.createText(t);  
        
        Serial.println("[Bluetooth] Starting BLE Keyboard...");

        bk.begin();
    }

    void OnConnect()
    {
        onConnectFired=true;
        gui.clear();
        
        Text* ble_connected = new Text(std::string("BLE Connected."), WHITE, GUIElement::Vector2{0,0}, 1);
        ble_connected->position = ble_connected->GetCenterCoordinates();
        gui.createText(ble_connected);  

        delay(1500);
        gui.clear();

        gui.showList(&btList);
        // lista
    }
    
    void Loop()
    {
        unsigned long currentMillis = millis();
        if(currentMillis-previousMillis >= scanInterval)
        {
            previousMillis = millis();
   
            if (bk.isConnected()) {
                if(!onConnectFired)
                    Bluetooth::OnConnect();

                // Serial.println("[Bluetooth] Client connected, sending keys...");

                // bk.press(KEY_LEFT_GUI);
                // bk.press('r');
                // bk.releaseAll();

                // delay(500);
                // bk.print("Hello from ESP32 BLE Keyboard!");
            }
        }
    }
}