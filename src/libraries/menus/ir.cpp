#include "ir.h"
#include "libraries/gui/list.h"
#include <IRremoteESP8266.h>
#include "libraries/gui/gui.h"
#include <IRrecv.h>
#include <IRutils.h>
#include <IRsend.h>
#include "defines.h"
#include "libraries/gui/option.h"

IRrecv irrecv(RECEIVER_PIN);
IRsend irsend(EMITTER_PIN);

decode_results results;

extern GUI gui;

namespace IR {
    List* irDevices;
    std::vector<Option*> irOptions;

    struct NECcode {
        uint64_t value;
        uint16_t bits;
    };
    std::vector<NECcode> codes;

    void onExit()
    {
        codes.clear();
        irrecv.disableIRIn();
        Serial.println("[IR] Stopped capturing IR codes.");
    }

    void Init()
    {
        //////
        irrecv.enableIRIn();
        irsend.begin();
        Serial.println("[IR] Ready to capture IR codes....");
        //////
    }

    void Show()
    {
        Init();

        irDevices = new List("IR Devices", irOptions, List::Theme::Multiple, onExit);
        gui.prepareList(irDevices);
    }
    
    void onClick()
    {
        NECcode nec = codes[irDevices->selectedMenu];
        irsend.sendNEC(nec.value, nec.bits);
        Serial.println("Code retransmitted!");
    }
    
    void Loop()
    {
        if(irrecv.decode(&results))
        {
            Serial.println("IR Code received:");
            Serial.println(resultToHexidecimal(&results));
            if(irDevices != nullptr)
            {
                irDevices->AddOption(new Option(std::string(resultToHexidecimal(&results).c_str()), 1, NULL, onClick));
                codes.push_back(NECcode {results.value, results.bits});
                // networksList->AddOption(new Option(std::string(WiFi.SSID(i).c_str()), WHITE, sigData.bmp, nullptr));
                gui.drawList();
            }


            if(results.decode_type != UNKNOWN)
            {
                // delay(200);
                // irsend.sendNEC(results.value, results.bits);
                // Serial.println("Code retransmitted!");
            }

            irrecv.resume();
        }
    }
}