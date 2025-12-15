
#pragma once
#include <vector>
#include <string>

class List {
    public:
        List(std::string title, std::vector<std::string> options, int selectedMenu, int size=2);
        std::vector<std::string> options;
        std::string title;
        std::vector<void (*)()> functions;
        int textSize;
        
        int selectedMenu;
        void selectUp();
        void selectDown();
        
};