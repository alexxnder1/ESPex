#include "text.h"
#include <string>
#include <vector>
#include "defines.h"
#include <Adafruit_SSD1306.h>
// 
#include "gui.h"
#include "option.h"
#include "list.h"
#include "icons.h"
#include "text.h"

extern GUI gui;

Option::Option(const std::string& t, int size, const unsigned char* bmp, void (*ocf)())
{  
  this->text = new Text(t, WHITE, GUIElement::Vector2{0,0}, size);
  this->bitmap = bmp;
  this->onClickFunction = ocf; 
}
// asd