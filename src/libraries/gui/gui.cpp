#include <Arduino.h>
#include <string>
#include <vector>
#include "gui.h"
#include "libraries/gui/text.h"
#include "libraries/menus/index.h"
#include "defines.h"
#include "option.h"
#include "icons.h"

GUI::GUI(Adafruit_SSD1306* disp)
{
    display = disp;
}

// creating text
void GUI::drawText(Text* text)
{
  display->setTextSize(text->textSize);
  display->setTextColor(text->c);
  display->setCursor(text->position.x, text->position.y);
  display->println(text->text.c_str());
  display->display();
}

void GUI::clear()
{
  if(this->GlobalList != nullptr)
  {
    this->GlobalList->clearOptions();
    this->GlobalList = nullptr;
  }

  if(display != nullptr)
    display->clearDisplay();

  for(GUIElement* elem : this->elements)
  {
      // if(elem != nullptr)
      //   delete elem;
      
      elem = nullptr;
  }

  this->elements.clear();
}

void GUI::prepareList(List* list)
{
  if(this->GlobalList != nullptr)
  {
    delete this->GlobalList;
    this->GlobalList = nullptr;
  }

  this->clear();
  this->GlobalList = list;
  this->drawList();
}


void GUI::drawList()
{
  display->clearDisplay();

  if(this->GlobalList!=nullptr)
  {
    this->drawText(this->GlobalList->title);

    if(this->GlobalList->selectedMenu >= this->GlobalList->options.size())
      this->GlobalList->selectedMenu = 0;

    if(this->GlobalList->theme == List::Theme::One)
    {
        Option* item = this->GlobalList->options[this->GlobalList->selectedMenu];
        
        this->drawText(item->text);
      
        if(item->bitmap != nullptr)
        {
          display->drawBitmap(
              64-48/2,
              32-48/2-5,
              item->bitmap,
              48,
              48,
              SSD1306_WHITE
          );  
        } 
        if(this->GlobalList->selectedMenu < this->GlobalList->options.size()-1)
        {    
          display->drawBitmap(
            SCREEN_WIDTH-8,
            SCREEN_HEIGHT/2-16/2,
            ra_bitmapra,
            8,
            16,
            SSD1306_WHITE
          );  
        }

        if(this->GlobalList->selectedMenu > 0)
        {    
          display->drawBitmap(
            0,
            SCREEN_HEIGHT/2-16/2,
            la_bitmapla,
            8,
            16,
            SSD1306_WHITE
          );  
        }

    }
    else if(this->GlobalList->theme == List::Theme::Multiple)
    {
      for(Option* opt : this->GlobalList->options)
      {
        this->drawText(opt->text);
      }
    }

    display->display();
  } 
}
GUI::~GUI()
{
  // for(GUIElement* elem : this->elements)
  //     delete elem;

  // this->elements.clear();
}

void GUI::assignLastMenu(void (*m)())
{
  this->previousFunction = m;
}

namespace {
  unsigned long previousMillis = 0;
  const unsigned long scanInterval = 250;
  bool reset = false; 
}

void GUI::loop()
{ 
    // ! processing controls
    uint16_t y = analogRead(JOYSTICK_VRx);
    uint16_t x = analogRead(JOYSTICK_VRy);
    bool pressed = digitalRead(JOYSTICK_SW) == 0;
    unsigned long currentMillis = millis();

    // ------------------------
    // Double-tap detection X=4095
    // ------------------------
    static bool lastXPressed = false;            
    static unsigned long firstTapTime = 0;       
    static bool waitingForSecondTap = false;     

    bool xPressed = (x == 4095);
    bool justPressed = xPressed && !lastXPressed; // rising edge
    lastXPressed = xPressed;

    if(justPressed)
    {
        if(!waitingForSecondTap)
        {
            firstTapTime = currentMillis;
            waitingForSecondTap = true;
        }
        else
        {
            if(currentMillis - firstTapTime <= 400) // double-tap detected
            {
                Serial.println("Double-tap detected!");
                if(this->previousFunction != nullptr)
                    this->previousFunction();

                IndexMenu::scan = false;
                waitingForSecondTap = false; // reset
            }
            else
                firstTapTime = currentMillis;
        }
    }

    // Timeout pentru al doilea tap
    if(waitingForSecondTap && (currentMillis - firstTapTime > 260))
    {
        waitingForSecondTap = false;
    }

    // ------------------------
    // periodic scan interval
    // ------------------------
    if(currentMillis - previousMillis < scanInterval)
        return;

    previousMillis = currentMillis;

    // ------------------------
    // list navigation
    // ------------------------
    if(xPressed)
    {  
        if(this->GlobalList != nullptr && this->GlobalList->options.size() > 1) {
            if(this->GlobalList->theme == List::Theme::One)
            {
              this->GlobalList->ScrollUp();
              reset=true;
            }
        }
    }

    if(x == 0)
    {
        if(this->GlobalList != nullptr && this->GlobalList->options.size() > 1) {
            if(this->GlobalList->theme == List::Theme::One)
            {
              this->GlobalList->ScrollDown();
              reset=true;
            }
        }
    }

    else if(y == 0)
    {
        if(this->GlobalList == nullptr)
        {
            this->scroll(true);
            reset = true;
        }
        else if(this->GlobalList->theme == List::Theme::Multiple && this->GlobalList->options.size() > 1)
        {
            this->GlobalList->ScrollUp();
            reset=true;
        }
    }
    
    else if(y == 4095)
    {
        if(this->GlobalList == nullptr)
        {
            this->scroll(false);
            reset = true;
        }
        else if(this->GlobalList->theme == List::Theme::Multiple && this->GlobalList->options.size() > 1)
        {
          this->GlobalList->ScrollDown();
          reset=true;
        }
    }

    else if(!reset && (pressed && this->GlobalList != nullptr))
    {
      this->GetCurrentOption()->onClickFunction();   
      reset = true; 
    }
    
    else reset = false; 
}

Option* GUI::GetCurrentOption()
{
  return this->GlobalList != nullptr ? this->GlobalList->options[this->GlobalList->selectedMenu] : nullptr;
}

#define SCROLL_SIZE 16

void GUI::scroll(bool b)
{
  display->clearDisplay();
  
  for(int i = 0; i < this->elements.size(); i++)
  {
    if(this->elements[i] == nullptr)
      continue;

      GUIElement* elem = this->elements[i];
      if(elem != nullptr)
      {
        Serial.println(elem->position.y);
        // int16_t newY =  elem->position.y+SCROLL_SIZE;
        elem->position.y += (b ? 1 : -1) *SCROLL_SIZE;
        if(elem->type == GUIElement::Type::Text)
          this->drawText(static_cast<Text*>(elem)); // safe, i checked type.

        // this->updateElementPosition(elem, GUIElement::Vector2 { elem->position.x, newY});
      }
  }

  display->display();
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

  Serial.println("[GUI] Init.");
}