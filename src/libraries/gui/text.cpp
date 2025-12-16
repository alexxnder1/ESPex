#include <string>
#include "text.h"
#include "defines.h"
#include <cmath>

Text::Text(std::string t, uint16_t color, Text::Vector2 pos, int ts)
{
    this->c = color;
    this->text = t;
    this->position = pos;
    this->textSize = ts;
    this->type = Type::Text;
    
    this->size = this->CalculateSize();
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
