#include "text.h"
#include <string>
#include <vector>
#include "defines.h"
#include <Adafruit_SSD1306.h>
// 
#include "gui.h"
#include "option.h"
#include "icons.h"

extern GUI gui;

Option::Option(const std::string& t, uint16_t color, const unsigned char* bmp, void (*ocf)())
{  
  std::string label = t;

  Text* tm = new Text(label, SSD1306_WHITE, Text::Vector2{0,0}, 1);
  Text::Vector2 newPos = tm->GetCenterCoordinates();
 
 //asdasd
  newPos.y += SCREEN_HEIGHT/2.5f;
  tm->position = newPos;
  
  this->bitmap = bmp;
  this->onClickFunction = ocf; 
  this->text = tm;
}