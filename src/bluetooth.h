#pragma once
#include <BleKeyboard.h>
#include <Arduino.h>

namespace Bluetooth {
    extern BleKeyboard ble;
    void Init();
    void Loop();
    void OnConnect();
}