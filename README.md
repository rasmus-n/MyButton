# MyButton
Button input library for arduino

## Features
- Debouncing
- Measure press time
- Count press repeat

## Details
When a button has been released for 250ms after being pressed, one of two callback functions are called:
- If the button was pressed continously, the first callback function is called with the button number, input number and hold time (in 1/100 sec.) as arguments.
- If the button was released for one or more periods of more than 1/100 sec., the second callback function is caled with the button number, input number and the number of times the button was pressed as arguments.

The library will configure the supplied pin number as input with pull-up.

## Example of use
```cpp
#include <MyButton.h>
MyButton my_button(2);  //Max number of buttons

#define BUTTON_1 D1     //Pin names for NodeMCU, but numbers work just fine
#define BUTTON_2 D2

void hold_cb(uint8_t b, uint8_t i, int c)
{
  Serial.printf("Someone held button %d (input %d) for %d 1/100 seconds", b, i, c);
}

void repeat_cb(uint8_t b, uint8_t i, int c)
{
  Serial.printf("Someone pushed button %d (input %d) %d times", b, i, c);
}

void setup() {
  Serial.begin(115200);
  
  // Initialize button handling
  my_button.add_button(BUTTON_1, &hold_cb, &repeat_cb);
  my_button.add_button(BUTTON_2, &hold_cb, &repeat_cb);
}

void loop() {

  // Execute button handling
  my_button.loop();
}
```
