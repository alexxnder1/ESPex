#pragma once

#define OLED_RESET -1
#include <Adafruit_SSD1306.h>
#include <string>
#include <vector>

#include "libraries/list.h"
#include "libraries/gui.h"
#include "libraries/text.h"

class GUI {
    
    private:
        Adafruit_SSD1306* display;

    public:
        void (*previousFunction)();
        void assignLastMenu(void (*m)());

        List* GlobalList;
        std::vector<Text> texts;
        GUI(Adafruit_SSD1306* disp);
        void init();
        void clear();
        void updateControls(uint16_t x, uint16_t y, bool pressed);
        void showText (std::string text, int16_t size, uint16_t c, int16_t x, int16_t y);
        void showList (List* list);
        void destroyList ();
        void scrollDown ();
        void scrollUp ();
        void updateList ();
};