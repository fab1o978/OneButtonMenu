#include <OneButtonMenu.h>
#include <Arduino.h>

#define NUMITEMS(arg) (sizeof(arg) / sizeof(arg[0]))

OneButtonMenu::OneButtonMenu(int _pin, String _items[])
{
    itemsCount = NUMITEMS(_items);

    items = _items;
    buttonPin = _pin;
}

void OneButtonMenu::init()
{
    Serial.print("Created menus with ");
    Serial.print(itemsCount);
    Serial.print(" items");

    // attachInterrupt(digitalPinToInterrupt(buttonPin), releaseButton, RISING);
}

void OneButtonMenu::next()
{
    index++;

    if (index > itemsCount)
        index = 0;
}

String OneButtonMenu::current()
{
    return items[index];
}

bool OneButtonMenu::readState(){
    bool state = digitalRead(buttonPin) == LOW ? true : false;

    if(!isPressed && state){
        timer.restart();
        isPressed = true;

        delay(100); // debounce
    }

    return state;
}

state OneButtonMenu::releaseButton(){

    isPressed = false;

    if(timer.hasPassed(pressTime)){
        return LONG_PRESS;
    }

    return PRESS;
}