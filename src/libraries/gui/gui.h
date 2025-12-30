#pragma once

#define OLED_RESET -1
#include <Adafruit_SSD1306.h>
#include <string>
#include <vector>

#include "libraries/gui/list.h"
#include "libraries/gui/gui.h"
#include "libraries/gui/text.h"
#include "libraries/gui/option.h"

class GUI {
    
    public:
        Adafruit_SSD1306* display;
        void (*previousFunction)();
        void assignLastMenu(void (*m)());

        List* GlobalList;
        std::vector<GUIElement*> elements;
        GUI(Adafruit_SSD1306* disp);
        void init();
        void clear();
        void loop();
        void drawText (Text* text);
        void showList (List* list);
        void scroll(bool b);
        void updateList ();
        void scrollOnceToShow(Text* elem, int screenHeight);
        Option* GetCurrentOption();
        ~GUI();

};