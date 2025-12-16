#include <string>
#include <vector>
#include "gui.h"
#include "libraries/gui/text.h"
#include "libraries/menus/index.h"
#include "defines.h"

GUI::GUI(Adafruit_SSD1306* disp)
{
    display = disp;
}


void GUI::createText(Text* text)
{
  display->setTextSize(text->size);
  display->setTextColor(text->c);
  display->setCursor(text->position.x, text->position.y);
  display->println(text->text.c_str());
  display->display();

  // Text t = new Text(text, size, c,x, y);
  // this->texts.push_back(t);
  Serial.println(text->text.c_str());
}

void GUI::clear()
{
  display->clearDisplay();
  display->display();
  // this->texts.clear();
}
// ters
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
  Text title(this->GlobalList->title, SSD1306_WHITE, Text::Vector2 { SCREEN_WIDTH/2-(12*this->GlobalList->title.size())/2, 0}, 2);
  this->createText(&title);

  Serial.println(this->GlobalList->title.c_str());
  int index=0;
  for(const auto& item : this->GlobalList->options)
  {
    Text option(this->GlobalList->selectedMenu == index ? (std::string("* ") + item).c_str() : item.c_str(), SSD1306_WHITE, Text::Vector2 { 0,16+6+this->GlobalList->textSize*8*index}, this->GlobalList->textSize);
    this->createText(&option);
    index++;
  }
  
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
      this->previousFunction();
    
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
  // std::vector<Text> textsCopy = this->texts;
  // this->clear();
  // for(Text& text: textsCopy)
  // {
  //   this->createText(text.text, text.size, text.c, text.x, text.y+16);
  // }
}

void GUI::scrollDown()
{
  // std::vector<Text> textsCopy = this->texts;
  // this->clear();
  // for(Text& text: textsCopy)
  // {
  //   this->createText(text.text, text.size, text.c, text.x, text.y-16);
  // }
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

  Text t(std::string("GUI Initialized."), SSD1306_WHITE, Text::Vector2 {0, 0}, 2);
  this->createText(&t);
}