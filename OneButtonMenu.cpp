#include <OneButtonMenu.h>
#include <Arduino.h>

#define NUMITEMS(arg) (sizeof(arg) / sizeof(arg[0]))

OneButtonMenu::OneButtonMenu()
{
}

OneButtonMenu::OneButtonMenu(int _pin, String _items[])
{
    int count = NUMITEMS(items);

    items = _items;
    buttonPin = _pin;
}

void OneButtonMenu::init()
{
    Serial.print("Created menus with ");
    Serial.print(sizeof(items));
    Serial.print(" items");

    Serial.println(items[1]);

    // attachInterrupt(digitalPinToInterrupt(buttonPin), releaseButton, RISING);
}

void OneButtonMenu::next()
{
    index++;

    if (index > 3)
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
    }

    return state;
}

state OneButtonMenu::releaseButton(){

    isPressed = false;

    if(timer.hasPassed(500)){
        Serial.println("LONG PRESS");
        return LONG_PRESS;
    }

    return PRESS;
}