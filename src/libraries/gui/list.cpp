#include "gui.h"
#include "list.h"
#include "defines.h"
#include "text.h"
#include "gui.h"

extern GUI gui;

List::List(const std::string& titleStr, const std::vector<std::string>& menu, int m, int size)
{
  this->title = new Text(titleStr, WHITE,  Text::Vector2 { SCREEN_WIDTH/2-(6*2*titleStr.size())/2, 0}, 2);
  this->selectedMenu = m;
  this->textSize = size;

  for(const std::string &item : menu)
    this->AddOption(item);
}
// asds

void List::clearOptions()
{
  for(Text* opt : this->options)
  {
    if(opt != nullptr)
    {
      delete opt;
      opt = nullptr;
    }
  }

  this->options.clear();
}

void List::AddOption(std::string item)
{
  int index = this->options.size();
  std::string lbl = (std::string("* ") + item);
  std::string label = this->selectedMenu == index ? lbl : item;
  
  /*
  Text::Vector2 Text::GetCenterCoordinates()
{
    int16_t x1, y1;
    uint16_t w, h;
    
    gui.display->setTextSize(this->textSize);
    gui.display->getTextBounds(this->text.c_str(), 0, 0, &x1, &y1, &w, &h);
    
    return Text::Vector2 {(SCREEN_WIDTH  - w) / 2,(SCREEN_HEIGHT - h) / 2};
}
// asddas
  
  */
  // if(index >0)
  Text* tm = new Text(label, SSD1306_WHITE, Text::Vector2 { static_cast<int16_t>(0), static_cast<int16_t>(8*2 + this->textSize*4 + this->textSize*8*index)}, this->textSize);
  this->options.push_back(tm);
}

List::~List()
{
  delete this->title;
  this->clearOptions();
}
void removeAllOccurrences(std::string& str, const std::string& seq) {
    size_t pos = 0;
    while ((pos = str.find(seq, pos)) != std::string::npos) {
        str.erase(pos, seq.length());
    }
}
void List::selectDown()
{
  removeAllOccurrences(this->options[this->selectedMenu]->text, "* ");

  this->selectedMenu++;
  if(this->selectedMenu >= this->options.size())
    this->selectedMenu = 0;

  this->options[this->selectedMenu]->text.insert(0, "* ");
  // if(this->options[this->selectedMenu]->position.y+8*this->options[this->selectedMenu]->textSize > SCREEN_HEIGHT)
  // {
  //   gui.scroll(false);
  // }
}
void List::selectUp()
{
  removeAllOccurrences(this->options[this->selectedMenu]->text, "* ");

  this->selectedMenu--;
  if(this->selectedMenu < 0)
    this->selectedMenu = this->options.size()-1;

  this->options[this->selectedMenu]->text.insert(0, "* ");
}