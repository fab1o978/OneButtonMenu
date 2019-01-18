#ifndef OBM_H
#define OBM_H

#include <Arduino.h>
#include <Chrono.h>

#define NUMITEMS(arg) (sizeof(arg) / sizeof(arg[0]))

typedef enum
{
  PRESS,
  LONG_PRESS
} state;

class OneButtonMenu
{
  public:
    // Constructors
    OneButtonMenu(int buttonPin, String items[], int itemsCount);

    // Methods
    void init();
    void next();
    String current();
    bool readState();
    bool isPressed = false;
    state releaseButton();
    int pressTime = 500;

    // Variables
    Chrono timer;

  private:
    // Variables
    int index;
    int buttonPin;
    String *items;
    int itemsCount;
};

#endif