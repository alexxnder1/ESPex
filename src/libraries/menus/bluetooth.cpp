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

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include "BLE2902.h"
#include "BLEHIDDevice.h"


List* btList;
std::vector<std::string> devices;

extern GUI gui;


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

    void onExit()
    {
        Serial.println("[Bluetooth] Stopping BLE Keyboard...");
        gui.clear();

        Text* t = new Text(std::string("Quiting..."), WHITE, GUIElement::Vector2{0,0}, 1);
        t->position = t->GetCenterCoordinates();
        gui.createText(t);  

        gui.clear();

        // stopping BLE
        bk.end();
        BLEDevice::stopAdvertising();
        BLEDevice::deinit();
           
        onConnectFired=false;
    }
    
    void Shutdown()
    {
        Serial.println("[Bluetooth] Shutdown executed.");

        // bk.releaseAll();
        bk.press(KEY_LEFT_GUI);
        bk.press('r');
        bk.releaseAll();
        
        delay(500);

        bk.print("cmd");
        bk.write(KEY_RETURN);
        delay(500);

        bk.print("shutdown /s /t 0");
        bk.write(KEY_RETURN);
    }

    void Restart()
    {

    }

    void Chaos()
    {

    }
    

    void OnConnect()
    {
        gui.clear();
        onConnectFired=true;
        
        btList = new List("BT Action", { "Shutdown", "Restart", "Chaos", "Etc1", "Etc2", "Etc3" }, 1, {Shutdown}, onExit);

        Text* ble_connected = new Text(std::string("BLE Connected."), WHITE, GUIElement::Vector2{0,0}, 1);
        ble_connected->position = ble_connected->GetCenterCoordinates();
        gui.createText(ble_connected);  

        delay(1500);
        // safe check (if user exits while waiting)
        if (bk.isConnected() && BLEDevice::getInitialized()) 
            gui.showList(btList);
    }

    void Loop()
    {
        unsigned long currentMillis = millis();
        if(currentMillis-previousMillis >= scanInterval)
        {
            previousMillis = millis();
   
            if (bk.isConnected() && BLEDevice::getInitialized()) 
                if(!onConnectFired)
                    Bluetooth::OnConnect();
        }
    }
}