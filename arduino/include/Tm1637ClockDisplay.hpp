#ifndef TM1637_CLOCK_DISPLAY_HPP
#define TM1637_CLOCK_DISPLAY_HPP

#include "Tm1637DriverBase.hpp"
#include "Tm1637EncodeSymbols.hpp"

namespace Tm1637
{

class ClockDisplay : public DriverBase
{
public:
	ClockDisplay(uint8_t clkPin_, uint8_t dioPin_);

	void clear();

	void display();
	void displayDigit(uint8_t digit_);

	void setByte(uint8_t digit_, uint8_t byte_);
	inline void setByte(uint8_t byteArray_[4])
		{ setByte(byteArray_[0], byteArray_[1], byteArray_[2], byteArray_[3]); };
	void setByte(uint8_t byte0_, uint8_t byte1_, uint8_t byte2_, uint8_t byte3_);

	void setNumber(int16_t number);
	void setDataHex(int16_t data_);

	void toggleColon();
	void setColon(uint8_t value_);
	uint8_t isColonOn() const;

private:
	const static uint8_t colonDigit = 1;

	uint8_t m_displayData[4];
};

} // namespace Tm1637
#endif
