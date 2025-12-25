#pragma once
#include "text.h"
#include <vector>

class Option { 
public:
    Text* text;
    const unsigned char* bitmap;
    void (*onClickFunction)();
    Option(const std::string& t, uint16_t color, const unsigned char* bmp, void (*onClickFunction)());
    // hfgdh
   
};