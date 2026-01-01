#pragma once
#include "libraries/gui/gui.h"

namespace IndexMenu
{
    inline bool scan = false;
    void show();
    void hide();
    void WIFI();
    void IR();
    void BT();
    void loop();
    void About();   
}