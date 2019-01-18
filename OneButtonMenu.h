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
    // Constructors
    OneButtonMenu(int buttonPin, String _items[]);

    // Methods
    void init();
    void next();
    String current();
    bool readState();
    bool isPressed = false;

    // Variables
    state releaseButton();
    Chrono timer;

  private:
    int index;
    int buttonPin;
    String *items;
};

#endif