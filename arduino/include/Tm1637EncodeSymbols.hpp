#ifndef TM1637_ENCODE_SYMBOLS
#define TM1637_ENCODE_SYMBOLS

#define TM1637_0 0x3f
#define TM1637_1 0x06
#define TM1637_2 0x5b
#define TM1637_3 0x4f
#define TM1637_4 0x66
#define TM1637_5 0x6d
#define TM1637_6 0x7d
#define TM1637_7 0x07
#define TM1637_8 0x7f
#define TM1637_9 0x6f

#define TM1637_A 0x77
#define TM1637_B 0x7f
#define TM1637_C 0x39
#define TM1637_D 0x3D
#define TM1637_E 0x79
#define TM1637_F 0x71

#include <inttypes.h>

namespace Tm1637
{

uint8_t encodeSymbol(uint8_t symbol);

}

#endif
