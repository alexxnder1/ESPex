#include "gui_element.h"
#include "libraries/gui.h"

extern GUI gui;

GUIElement::GUIElement()
{
    gui.elements.push_back(this);
}
