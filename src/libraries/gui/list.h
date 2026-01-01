
#pragma once
#include <vector>
#include <string>
#include "libraries/gui/text.h"
#include "option.h"

class List {
    public:
        enum Theme {
            One,
            Multiple
        };

        List(const std::string& titleStr, std::vector<Option*> options, Theme theme, void (*oe)()=nullptr);

        Text* title=nullptr;
        
        std::vector<Option*> options;
        
        void (*onExit)() = nullptr;
        int textSize;

        Theme theme;
        
        int selectedMenu = 0;
        void selectUp();
        void selectDown();
        void ScrollDown();
        void ScrollUp();
        void clearOptions();
        void AddOption(Option* opt);
        ~List();
};