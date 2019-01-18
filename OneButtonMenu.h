#ifndef OBM_H
#define OBM_H

#include <Arduino.h>
#include <Chrono.h>

typedef enum
{
  PRESS,
  LONG_PRESS
} state;

class OneButtonMenu
{
  public:
    OneButtonMenu();
    OneButtonMenu(int buttonPin, String _items[]);
    void init();
    void next();
    String current();
    bool readState();
    bool isPressed = false;
    state releaseButton();
    Chrono timer;

  private:
    int index;
    int buttonPin;
    String *items;
};

#endif