#include "Tm1637.h"

/* CONFIGURATION */
// Pins
#define CLK 3
#define DIO 2

Tm1637 display(CLK, DIO);

void setup()
{
	// Brightness of all digits.
	display.setBrightness(4);

	/*
	Shows the "HELLO" message for 5 seconds.
	Hexadecimal values are character codes for seven segment display.
	*/
	display.setByte(0x77, 0x4e, 0x4f, 0x47);
	display.display();
	delay(5000);
}

void loop()
{
	// Shows all numbers from -999 to 9999
	for (int16_t i = -999; i <= 9999; ++i)
	{
		display.setNumber(i);
		display.display();
	}
	display.clear(); // Clear display
	delay(1000);

	// Some clock moment
	display.setNumber(1536);
	for (int8_t i = 0; i < 10; ++i)
	{
		display.toggleColon();
		display.display();
		delay(1000);
	}
	display.clear();

	// Sets some numbers in different digits
	for (int8_t i = 0; i < 4; ++i)
	{
		for (int8_t j = 0; j < 10; ++j)
		{
			display.setByte(i, Tm1637::encodeNumeral(j));
			display.display();
			delay(500);
		}
		display.clear();
	}

	// Brigntness levels
	for (int8_t i = 0; i <= 7; ++i)
	{
		uint8_t dspi = Tm1637::encodeNumeral(i);
		display.setBrightness(i);
		display.setByte(dspi, dspi, dspi, dspi);
		display.display();
		delay(1000);
	}
	display.clear();
}
