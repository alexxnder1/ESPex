#include "gui.h"
#include "list.h"
#include "defines.h"
#include "text.h"

List::List(const std::string& titleStr, const std::vector<std::string>& menu, int m, int size)
{
  Serial.begin(115200);

  this->title = new Text(titleStr, WHITE,  Text::Vector2 { SCREEN_WIDTH/2-(6*size*titleStr.size())/2, 0}, 2);

  int index=0;
    Serial.println(menu.size());
  Serial.println("LOOOL");

  for(const std::string &item : menu)
  {
    std::string lbl = (std::string("* ") + item);
    std::string label = m == index ? lbl : item;
  //   // Serial.println("[LIST**]")
    
    Serial.println(label.c_str());
    Text* tm = new Text(label, SSD1306_WHITE, Text::Vector2 { static_cast<int16_t>(0), static_cast<int16_t>(16+6+size*8*index)}, size);
    this->options.push_back(tm);
    index++;
  }  

  this->selectedMenu = m;
  this->textSize = size;
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
}
void List::selectUp()
{
  removeAllOccurrences(this->options[this->selectedMenu]->text, "* ");

  this->selectedMenu--;
  if(this->selectedMenu < 0)
    this->selectedMenu = this->options.size()-1;

  this->options[this->selectedMenu]->text.insert(0, "* ");
}