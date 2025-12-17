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

// creating text
void GUI::createText(Text* text)
{
  display->setTextSize(text->textSize);
  display->setTextColor(text->c);
  display->setCursor(text->position.x, text->position.y);
  display->println(text->text.c_str());
  display->display();

  Serial.println(text->text.c_str());
}

void GUI::clear()
{
  display->clearDisplay();
  display->display();
  for(GUIElement* elem : this->elements)
      delete elem;

  this->elements.clear();
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
  Text* title = new Text(this->GlobalList->title, SSD1306_WHITE, Text::Vector2 { SCREEN_WIDTH/2-(12*this->GlobalList->title.size())/2, 0}, 2);
  this->createText(title);

  Serial.println(this->GlobalList->title.c_str());
  int index=0;
  for(const auto& item : this->GlobalList->options)
  {
    Text* option = new Text(this->GlobalList->selectedMenu == index ? (std::string("* ") + item).c_str() : item.c_str(), SSD1306_WHITE, Text::Vector2 { static_cast<int16_t>(0), static_cast<int16_t>(16+6+this->GlobalList->textSize*8*index)}, this->GlobalList->textSize);
    this->createText(option);
    index++;
  }
  
}

GUI::~GUI()
{
  for(GUIElement* elem : this->elements)
      delete elem;

  this->elements.clear();
}

void GUI::assignLastMenu(void (*m)())
{
  this->previousFunction = m;
}

void GUI::processControls(uint16_t x, uint16_t y, bool pressed)
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
#define SCROLL_SIZE 16

void GUI::scrollUp()
{
  for(int i = 0; i <= this->elements.size()-1; i++)
  {
    if(this->elements[i] == nullptr)
      continue;

      GUIElement* elem = this->elements[i];
      if(elem != nullptr)
      {
        int16_t newY =  elem->position.y+SCROLL_SIZE;
        this->updateElementPosition(elem, GUIElement::Vector2 { elem->position.x, newY});
      }
  }
}

void GUI::scrollDown()
{
  for(int i = this->elements.size()-1; i >= 0; i--)
  {
      if(this->elements[i] == nullptr)
        continue;

      GUIElement* elem = this->elements[i];
      if(elem != nullptr)
      {
        int16_t newY =  elem->position.y-SCROLL_SIZE;
        this->updateElementPosition(elem, GUIElement::Vector2 { elem->position.x, newY});
      }
  }
}

void GUI::updateElementPosition(GUIElement* g, GUIElement::Vector2 newPos)
{
  if(g == nullptr)
    return;

  display->fillRect(g->position.x, g->position.y, g->size.x, g->size.y, BLACK);
  display->display();

  g->position = newPos;

  if(g->type == GUIElement::Type::Text)
    this->createText(static_cast<Text*>(g)); // safe, i checked type.
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

  Text* t = new Text(std::string("GUI Initialized."), SSD1306_WHITE, Text::Vector2 {0, 0}, 2);
  this->createText(t);
}