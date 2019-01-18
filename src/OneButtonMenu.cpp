#include <OneButtonMenu.h>
#include <Arduino.h>

// Button Pin, Menu Items array, Items count
OneButtonMenu::OneButtonMenu(int _pin, String _items[], int _itemsCount)
{
    buttonPin = _pin;
    items = _items;
    itemsCount = _itemsCount;
}

void OneButtonMenu::init()
{
    Serial.print("Created menus with ");
    Serial.print(itemsCount);
    Serial.println(" items\n");

    // attachInterrupt(digitalPinToInterrupt(buttonPin), releaseButton, RISING);
}

void OneButtonMenu::next()
{
    index++;

    if (index >= itemsCount)
        index = 0;
}

String OneButtonMenu::current()
{
    return items[index];
}

bool OneButtonMenu::readState()
{

    bool state = digitalRead(buttonPin) != defaultButtonState ? true : false;

    // If button is pressed
    if (state)
    {
        // If it wasn't pressed before
        if (!isPressed)
        {
            timer.restart();
            isPressed = true;
            buttonState = PRESS;

            delay(100); // debounce
        }

        // If is pressed and time has passed
        if(isPressed && timer.hasPassed(pressTime)){
            Serial.println(timer.elapsed());
            buttonState = LONG_PRESS;
        }
    } else {
        buttonState = NONE;
    }

    return state;
}

state OneButtonMenu::releaseButton()
{
    // act as debounce. presses shorter than 50ms will be ignored
    /*if(!timer.hasPassed(50))
        return NONE;*/

    isPressed = false;

    if (buttonState == LONG_PRESS)
    {
        // Elapsed time, debug purpose
        Serial.println(timer.elapsed());
        return LONG_PRESS;
    }

    return PRESS;
}