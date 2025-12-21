#pragma once
#include "BluetoothSerial.h"
#include <Arduino.h>

namespace Bluetooth {
    extern BluetoothSerial ble;
    void Init();
    void Loop();
}