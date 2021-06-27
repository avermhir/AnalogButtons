#ifndef ANALOG_KEYABORD_H

#define ANALOG_KEYABORD_H

#include <Arduino.h>

// timeout for long press
#define AK_KEY_PRESS_TIMEOUT 2000

// limits for button readings
// each button gives a value below its corresponding entry
#ifndef AK_KEY_KEY_VALUE_1
#define AK_KEY_KEY_VALUE_1 190  //Left
#endif // !AK_KEY_KEY_VALUE_1
#ifndef AK_KEY_KEY_VALUE_2
#define AK_KEY_KEY_VALUE_2 300 //Top
#endif // !AK_KEY_KEY_VALUE_2

#ifndef AK_KEY_KEY_VALUE_3
#define AK_KEY_KEY_VALUE_3 460 //Bottom
#endif // !AK_KEY_KEY_VALUE_3

#ifndef AK_KEY_KEY_VALUE_4
#define AK_KEY_KEY_VALUE_4 600 //Right
#endif // !AK_KEY_KEY_VALUE_4

#ifndef AK_KEY_KEY_VALUE_5
#define AK_KEY_KEY_VALUE_5 790 //Far Right Button
#endif // !AK_KEY_KEY_VALUE_5

#ifndef AK_KEY_KEY_VALUE_NONE
#define AK_KEY_KEY_VALUE_NONE 1000 //No button
#endif // !AK_KEY_KEY_VALUE_NONE

#ifndef AK_KEY_READINGCORRECTION
#define AK_KEY_READINGCORRECTION 25
#endif 

#ifndef AK_STABLESTATECORRECTION
#define AK_STABLESTATECORRECTION 5
#endif 

#ifndef AK_KEYBOARD_A_PIN 
#define AK_KEYBOARD_A_PIN 3
#endif 

#ifndef AK_DEBOUNCEDEPTH
#define AK_DEBOUNCEDEPTH 200
#endif

#define AK_UP 1
#define AK_DOWN 0

class AnalogKeyboard {
public:
    AnalogKeyboard(void (*buttonHandler)(int buttonNumber) );
    void update();
    int buttonState(int buttonNumber);

private:
    int debounceTracker[AK_DEBOUNCEDEPTH];
    unsigned int debounceLoc;
    void(*eventHandler)(int state);

    unsigned long lastState; // last value 
    unsigned long processedState;
    int AnalogKeyboard::ActivatedButton(unsigned long state);
    bool isStable(int state);   
};

#endif // !AK_KEYABORD_H



