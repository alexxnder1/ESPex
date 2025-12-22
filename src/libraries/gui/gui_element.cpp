#include "gui_element.h"
#include "libraries/gui/gui.h"

extern GUI gui;

GUIElement::GUIElement()
{
    gui.elements.push_back(this);
}

GUIElement::~GUIElement()
{
    // gui.elements.erase(gui.elements.find)
}
