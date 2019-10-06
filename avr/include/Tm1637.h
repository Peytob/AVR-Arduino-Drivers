#ifndef TM1637_H
#define TM1637_H

#include <inttypes.h>
#include "../port.h"

#include "Tm1637SymbolsDefines.h"

class Tm1637
{
public:
	Tm1637();
	~Tm1637() = default;

	static uint8_t encodeNumeral(uint8_t numeral_);

private:

};
#endif // #ifndef TM1637_H
