#include "AnalogKeyboard.h"


AnalogKeyboard::AnalogKeyboard(void (*buttonHandler)(int buttonNumber))
{
    this->debounceLoc = 0;
    this->lastState = 0;
    this->processedState = 0;
    for (int i = 0; i < AK_DEBOUNCEDEPTH; i++)
    {
        debounceTracker[i] = AK_KEY_KEY_VALUE_NONE+1000;
    }
    this->eventHandler = buttonHandler;
}

void AnalogKeyboard::update()
{
    int val = analogRead(AK_KEYBOARD_A_PIN);
   
    unsigned long currentState = 0;

    if (this->isStable(val))
    {
        // get which key is pressed TODO: figure out how to return when multiple keys are pressed.
        //Set Them All Down
        bitWrite(currentState, 1, AK_DOWN);
        bitWrite(currentState, 2, AK_DOWN);
        bitWrite(currentState, 3, AK_DOWN);
        bitWrite(currentState, 4, AK_DOWN);
        bitWrite(currentState, 5, AK_DOWN);
        
        
        if (AK_KEY_KEY_VALUE_1 - AK_KEY_READINGCORRECTION < val && AK_KEY_KEY_VALUE_1 + AK_KEY_READINGCORRECTION > val)
        {
            bitWrite(currentState, 1, AK_UP);
        }   
        else
        {
            if (AK_KEY_KEY_VALUE_2 - AK_KEY_READINGCORRECTION < val && AK_KEY_KEY_VALUE_2 + AK_KEY_READINGCORRECTION > val)
            {
                bitWrite(currentState, 2, AK_UP);
            }
            else
            {
                if (AK_KEY_KEY_VALUE_3 - AK_KEY_READINGCORRECTION < val && AK_KEY_KEY_VALUE_3 + AK_KEY_READINGCORRECTION > val)
                {
                    bitWrite(currentState, 3, AK_UP);
                }
                else
                {
                    if (AK_KEY_KEY_VALUE_4 - AK_KEY_READINGCORRECTION < val && AK_KEY_KEY_VALUE_4 + AK_KEY_READINGCORRECTION > val)
                    {
                        bitWrite(currentState, 4, AK_UP);
                    }
                    else
                    {
                        if (AK_KEY_KEY_VALUE_5 - AK_KEY_READINGCORRECTION < val && AK_KEY_KEY_VALUE_5 + AK_KEY_READINGCORRECTION > val)
                        {
                            bitWrite(currentState, 5, AK_UP);
                        }
                        else
                        {

                        }

                    }
                }
            }
        }
        
        //if the button state has changed call the callback with  the button number.
        if (currentState != this->lastState)
        {
            this->lastState = currentState;
            this->eventHandler(this->ActivatedButton(currentState));
            this->processedState = currentState;
        }
    }   
}

int AnalogKeyboard::ActivatedButton(unsigned long state)
{
    for (int i = 1;i <= 5 ;i++)
    {
        if (bitRead(state, i) == 1)
        {
            return i;
        }
    }
    return 0;
}
int AnalogKeyboard::buttonState(int buttonNumber)
{
    return bitRead(this->lastState, buttonNumber);
}

bool AnalogKeyboard::isStable(int state)
{
    bool isStable = true;
    this->debounceTracker[debounceLoc] = state;
    this->debounceLoc = (this->debounceLoc + 1) % AK_DEBOUNCEDEPTH;
    for (int i = 0; i < AK_DEBOUNCEDEPTH - 1; i++)
    {
        if ((state < this->debounceTracker[i] - AK_STABLESTATECORRECTION) || (state > this->debounceTracker[i] + AK_STABLESTATECORRECTION))
        {
            isStable = false;
        }
    }
    return isStable;
}
