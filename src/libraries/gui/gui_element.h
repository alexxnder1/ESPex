#pragma once
#include <cstdint>

class GUIElement
{
public:
    enum class Type { Text };
    struct Vector2 {
        int16_t  x;
        int16_t  y;
    };
    Type type;
    Vector2 position;
    Vector2 size;    

protected:
    GUIElement();
    ~GUIElement();

};