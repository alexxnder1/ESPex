
#pragma once
#include <vector>
#include <string>
#include "libraries/gui/text.h"
#include "option.h"

class List {
    public:
        List(const std::string& titleStr, std::vector<Option*> options, void (*oe)()=nullptr);

        Text* title=nullptr;
        
        std::vector<Option*> options;
        
        void (*onExit)() = nullptr;
        int textSize;
        
        int selectedMenu = 0;
        void selectUp();
        void selectDown();
        void clearOptions();
        void AddOption(Option* opt);
        ~List();
};