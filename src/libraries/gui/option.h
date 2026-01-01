#pragma once
#include "text.h"
#include <vector>

class Option { 
public:
    Text* text;
    const unsigned char* bitmap;
    void (*onClickFunction)();
    Option(const std::string& t, int size, const unsigned char* bmp, void (*onClickFunction)());
};