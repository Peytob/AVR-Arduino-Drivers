#include <Tm1637EncodeSymbols.hpp>

namespace Tm1637
{

uint8_t encodeSymbol(uint8_t symbol)
{
	switch (symbol)
	{
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

	case 10:
		return TM1637_A;

	case 11:
		return TM1637_B;

	case 12:
		return TM1637_C;

	case 13:
		return TM1637_D;

	case 14:
		return TM1637_E;

	case 15:
		return TM1637_F;

	default:
		return 255;
	}
}

}
