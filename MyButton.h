#ifndef MYBUTTON_H
#define MYBUTTON_H

#include "Arduino.h"

struct button{
  uint8_t input;
  long time_idle;
  long time_active;
  int time_count;
  int repeat_count;
  void (*proc_1)(uint8_t, uint8_t, int);
  void (*proc_2)(uint8_t, uint8_t, int);
};

class MyButton
{
  public:
    MyButton(uint8_t c);
    void add_button(uint8_t input, void (*p_1)(uint8_t, uint8_t, int), void (*p_2)(uint8_t, uint8_t, int));
    void loop();
  private:
    uint8_t _button_count;
    uint8_t _max_count;
    struct button *_buttons;
};

#endif
