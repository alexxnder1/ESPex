
#pragma once
#include <vector>
#include <string>
#include "libraries/gui/text.h"

class List {
    public:
        List(const std::string& titleStr, const std::vector<std::string>& menu, int textSize, std::vector<void (*)()> f, void (*oe)()=nullptr);

        Text* title=nullptr;
        
        std::vector<Text*> options;
        
        void (*onExit)() = nullptr;
        std::vector<void (*)()> functions;
        int textSize;
        
        int selectedMenu = 0;
        void selectUp();
        void selectDown();
        void clearOptions();
        void AddOption(std::string opt);
        ~List();
};