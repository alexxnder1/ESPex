#include "gui.h"
#include "list.h"
#include "defines.h"
#include "text.h"
#include "gui.h"
#include "option.h"

extern GUI gui;

List::List(const std::string& titleStr, std::vector<Option*> options, Theme theme, void (*oe)())
{
  this->title = new Text(titleStr, WHITE,  Text::Vector2 { 0, 0}, 1);
  this->selectedMenu = 0;
  // this->textSize = textSize;
  this->onExit = onExit;
  this->theme = theme;
  // this->options = options;
  for(Option* opt : options)
  {
    this->AddOption(opt);
  }
// 
}

void List::clearOptions()
{
  for(Option* opt : this->options)
  {
    if(opt != nullptr)
    {
      delete opt;
      opt = nullptr;
    }
  }
  
  this->options.clear();
}

// void List::ShowOption()

void List::AddOption(Option* opt)
{
  Text* tm = opt->text;
  tm->textSize = 1;
  tm->c = WHITE;

  if(theme == List::Theme::Multiple)
  {
    tm->position.y = 8*2+this->options.size()*8;
  }

  else if(theme == List::Theme::One)
  {
    tm->position = tm->GetCenterCoordinates();
    tm->position.y += SCREEN_HEIGHT/2.5f;
    Serial.println("center coordinates");
    Serial.println(tm->GetCenterCoordinates().y);

  }

  this->options.push_back(opt);
}

List::~List()
{
  this->clearOptions();
  
  if(this->onExit != nullptr)
    this->onExit();
}

void removeAllOccurrences(std::string& str, const std::string& seq) {
    size_t pos = 0;
    while ((pos = str.find(seq, pos)) != std::string::npos) {
        str.erase(pos, seq.length());
    }
}

void List::selectDown()
{  
  if(this->theme == List::Theme::Multiple)
    removeAllOccurrences(this->options[this->selectedMenu]->text->text, "* ");

  this->selectedMenu++;
  if(this->selectedMenu >= this->options.size())
    this->selectedMenu = 0;
  
  if(this->theme == List::Theme::Multiple)
    this->options[this->selectedMenu]->text->text.insert(0, "* ");
  // if(this->options[this->selectedMenu]->position.y+8*this->options[this->selectedMenu]->textSize > SCREEN_HEIGHT)
  // {
  //   gui.scroll(false);
  // }
}
void List::selectUp()
{
  if(this->theme == List::Theme::Multiple)
    removeAllOccurrences(this->options[this->selectedMenu]->text->text, "* ");

  this->selectedMenu--;
  if(this->selectedMenu < 0)
    this->selectedMenu = this->options.size()-1;

  if(this->theme == List::Theme::Multiple)
    this->options[this->selectedMenu]->text->text.insert(0, "* ");
}
void List::ScrollDown()
{
  this->selectDown();
  gui.drawList();
}

void List::ScrollUp()
{
  this->selectUp();
  gui.drawList();
}
