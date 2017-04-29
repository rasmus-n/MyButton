#include "MyButton.h"

MyButton::MyButton(uint8_t c)
{
  _buttons = (button *)calloc(c, sizeof(button));
  _button_count = 0;
  _max_count = c;
}

void MyButton::add_button(uint8_t input, void (*p_1)(uint8_t, uint8_t, int), void (*p_2)(uint8_t, uint8_t, int))
{
  if (_button_count < _max_count)
  {
    _buttons[_button_count].input = input;
    _buttons[_button_count].proc_1 = p_1;
    _buttons[_button_count].proc_2 = p_2;
    _button_count++;
    
    pinMode(input, INPUT_PULLUP);
  }
}

void MyButton::loop()
{
  for (int b = 0; b < _button_count; b++) 
  {
    if (digitalRead(_buttons[b].input))
    {
      
      _buttons[b].time_idle = millis();
      if ((_buttons[b].time_idle - _buttons[b].time_active) > 250)
      {
        if (_buttons[b].repeat_count)
        {
          _buttons[b].proc_2(b + 1, _buttons[b].input, _buttons[b].repeat_count + 1);
        }
        else if (_buttons[b].time_count)
        {
          _buttons[b].proc_1(b + 1, _buttons[b].input, _buttons[b].time_count);
        }
        _buttons[b].repeat_count = 0;
        _buttons[b].time_count = 0;
      }
      
    }
    else
    {
      if ((_buttons[b].time_idle - _buttons[b].time_active) > 10 && (_buttons[b].time_count > 0))
      {
        _buttons[b].repeat_count++;
      }
      
      _buttons[b].time_active = millis();
      
      if ((_buttons[b].time_active - _buttons[b].time_idle) > 10)
      {
        _buttons[b].time_count = (_buttons[b].time_active - _buttons[b].time_idle) / 10;
      }
    }
  }
}
