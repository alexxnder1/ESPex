
#pragma once
#include <vector>
#include <string>
#include "libraries/gui/text.h"

class List {
    public:
        List(const std::string& title, const  std::vector<std::string>& options, int selectedMenu, int size=2);

        Text* title=nullptr;
        
        std::vector<Text*> options;
        
        std::vector<void (*)()> functions;
        int textSize = 1;
        
        int selectedMenu = 0;
        void selectUp();
        void selectDown();
        void clearOptions();
        void AddOption(std::string opt);
        ~List();
};