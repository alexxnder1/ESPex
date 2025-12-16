#pragma once

class GUIElement
{
public:
    struct Vector2 {
        int x;
        int y;
    };

    Vector2 position;
    int size;
};