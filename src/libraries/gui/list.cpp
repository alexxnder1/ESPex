#include "gui.h"
#include "list.h"

List::List(std::string title, std::vector<std::string> menu, int m, int size)
{
  this->title = title;
  this->options = menu;
  this->selectedMenu = m;
  this->textSize = size;
}

void List::selectDown()
{
  this->selectedMenu++;
  if(this->selectedMenu >= this->options.size())
    this->selectedMenu = 0;
}
void List::selectUp()
{
  this->selectedMenu--;
  if(this->selectedMenu < 0)
    this->selectedMenu = this->options.size()-1;
}