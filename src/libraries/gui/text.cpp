#include <string>
#include "text.h"
#include "defines.h"
#include <cmath>
#include "gui.h"

extern GUI gui;

Text::Text(const std::string& t, uint16_t color, Text::Vector2 pos, int ts)
{
    this->c = color;
    this->text = t;
    this->position = pos;
    this->textSize = ts;
    this->type = Type::Text;
    
    this->size = this->CalculateSize();
    gui.elements.push_back(static_cast<Text*>(this));
}

GUIElement::Vector2 Text::CalculateSize()
{
    int16_t x = this->text.size()*(6*this->textSize);
    
    int16_t lineHeight = 8*this->textSize;
    int16_t y = lineHeight;
    int16_t wrapLines = static_cast<int>(ceil(static_cast<double>(x) / SCREEN_WIDTH)-1);
    
    if(wrapLines > 0)
        y+=lineHeight*wrapLines;
        
    return { x, y };
}

Text::Vector2 Text::GetCenterCoordinates()
{
    int16_t x1, y1;
    uint16_t w, h;
    
    gui.display->setTextSize(this->textSize);
    gui.display->getTextBounds(this->text.c_str(), 0, 0, &x1, &y1, &w, &h);
    
    return Text::Vector2 {(SCREEN_WIDTH  - w) / 2,(SCREEN_HEIGHT - h) / 2};
}
