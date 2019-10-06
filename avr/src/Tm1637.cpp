#include <Tm1637.h>

Tm1637::Tm1637()
{

}

uint8_t Tm1637::encodeNumeral(uint8_t numeral)
{
	switch (numeral)
	{
		default:
			return 0;

		case 0:
			return TM1637_0;

		case 1:
			return TM1637_1;

		case 2:
			return TM1637_2;

		case 3:
			return TM1637_3;

		case 4:
			return TM1637_4;

		case 5:
			return TM1637_5;

		case 6:
			return TM1637_6;

		case 7:
			return TM1637_7;

		case 8:
			return TM1637_8;

		case 9:
			return TM1637_9;
	}
}
