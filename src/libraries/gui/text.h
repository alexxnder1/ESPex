#pragma once 
#include <string>
#include "gui_element.h"

class Text : public GUIElement {

public:
    std::string text;
    uint16_t c;
    int textSize;
    
    Text(const std::string &t, uint16_t color, Text::Vector2 pos, int size);
    GUIElement::Vector2 CalculateSize();
};