#include <string>
#include <vector>
#include "gui.h"
#include "text.h"
#include "libraries/menus/index.h"
#include "defines.h"

GUI::GUI(Adafruit_SSD1306* disp)
{
    display = disp;
}

void GUI::showText(std::string text, int16_t size, uint16_t c, int16_t x, int16_t y)
{
  display->setTextSize(size);
  display->setTextColor(c);
  display->setCursor(x, y);
  display->println(text.c_str());
  display->display();

  Text t { text = text, size = size, c = c, x = x, y = y };
  this->texts.push_back(t);
  Serial.println(text.c_str());
}

void GUI::clear()
{
  display->clearDisplay();
  display->display();
  this->texts.clear();
}

void GUI::destroyList()
{
  if(this->GlobalList != nullptr)
  {
    this->GlobalList = nullptr;
    this->clear();
    // this->GlobalList->sele
  }
}


void GUI::showList(List* list)
{
  this->destroyList();
  this->GlobalList = list;
  updateList();
}


void GUI::updateList()
{
  this->clear();
  this->showText(this->GlobalList->title, 2, SSD1306_WHITE, SCREEN_WIDTH/2-(12*this->GlobalList->title.size())/2, 0);
  Serial.println(this->GlobalList->title.c_str());
  int index=0;
  for(const auto& item : this->GlobalList->options)
  {
    this->showText(this->GlobalList->selectedMenu == index ? (std::string("* ") + item).c_str() : item.c_str(), this->GlobalList->textSize, SSD1306_WHITE, 0, 16+6+this->GlobalList->textSize*8*index);
    index++;
  }
  // font size..
}

void GUI::assignLastMenu(void (*m)())
{
  this->previousFunction = m;
}

void GUI::updateControls(uint16_t x, uint16_t y, bool pressed)
{ 
  if(x == 4095)
  {  
    if(this->previousFunction != nullptr)
      this->previousFunction(this);
    
    IndexMenu::scan = false;
  }


  if(x == 0)
  {
  }

 
  else if(y == 0)
  {
    if(this->GlobalList == nullptr)
    {
      this->scrollUp();
    }
    else {
      this->GlobalList->selectUp();
      this->updateList();
    }
  }
  
  else if(y == 4095)
  {
    if(this->GlobalList == nullptr)
    {
      this->scrollDown();
    }
    else {
      this->GlobalList->selectDown();
      this->updateList();
    }
  }

  else if(pressed&& this->GlobalList != nullptr)
  {
    // this->PreviousGlobalList

    this->GlobalList->functions[this->GlobalList->selectedMenu]();
  }
}
void GUI::scrollUp()
{
  std::vector<Text> textsCopy = this->texts;
  this->clear();
  for(Text& text: textsCopy)
  {
    this->showText(text.text, text.size, text.c, text.x, text.y+16);
  }
}

void GUI::scrollDown()
{
  std::vector<Text> textsCopy = this->texts;
  this->clear();
  for(Text& text: textsCopy)
  {
    this->showText(text.text, text.size, text.c, text.x, text.y-16);
  }
}

void GUI::init()
{
  Wire.begin(21, 22);
    if (!display->begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println("SSD1306 not found! Check wiring and voltage.");
        while (true); // Stop here
    }

  display->clearDisplay();
  display->setTextColor(SSD1306_WHITE);
  display->setCursor(0,0);
  display->display();
  this->showText(std::string("GUI Initialized."), 2, SSD1306_WHITE, 0, 0);
}