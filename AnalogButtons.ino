/*
 Name:		AnalogButtons.ino
 Created:	6/26/2021 6:42:11 PM
 Author:	djkes
*/

#include "AnalogKeyboard.h";

/*This is a function the AnalogyKeyboard Class will call when a button is pressed. 
It will also call this when all buttons are released. 
*/
void AnalogButtonHandler(int buttonNumber)
{
	if (0 == buttonNumber)
	{
		Serial.println("Button Released");
	}
	else
	{
		Serial.print("Button Pressed:");
		Serial.println(buttonNumber);
	}
}

AnalogKeyboard akey(&AnalogButtonHandler);

void setup()
{
	Serial.begin(9600);
	Serial.println("STARTINGUP");
}

// besure to call the Update routine for the AnalogKeyboard frequently to debounce the keyboard.
void loop()
{
	akey.update();
}
