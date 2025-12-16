#include <string>
#include "text.h"

Text::Text(std::string t, uint16_t color, Text::Vector2 pos, int size)
{
    this->c = color;
    this->text = t;
    this->position = pos;
    this->size = size;
}
