#include <Tm1637ClockDisplay.hpp>

namespace Tm1637
{

ClockDisplay::ClockDisplay(const Portio::Pin & clkPin_, const Portio::Pin & dioPin_) :
	DriverBase(clkPin_, dioPin_)
{
	clear();
	display();
}

void ClockDisplay::clear()
{
	for (const auto & i : m_displayData)
		m_displayData[i] = 0;
}

void ClockDisplay::setByte(uint8_t digit_, uint8_t byte_)
{
	m_displayData[digit_] = byte_;
}

void ClockDisplay::setByte(uint8_t byte0_, uint8_t byte1_, uint8_t byte2_, uint8_t byte3_)
{
		m_displayData[0] = byte0_;
		m_displayData[1] = byte1_;
		m_displayData[2] = byte2_;
		m_displayData[3] = byte3_;
}

void ClockDisplay::display()
{
	m_startSignal();
	m_sendByte(0x40);
	m_stopSignal();

	m_startSignal();
	m_sendByte(0xc0);
	for (const auto & i : m_displayData)
		m_sendByte(i);
	m_stopSignal();
}

void ClockDisplay::displayDigit(uint8_t digit_)
{
	m_startSignal();
	m_sendByte(0x44);
	m_stopSignal();

	uint8_t digit = digit_ & ~(0x06);

	m_startSignal();
	m_sendByte(0xc0 + digit);
	m_sendByte(m_displayData[digit_]);
	m_stopSignal();
}

void ClockDisplay::setNumber(int16_t number_, uint8_t digit_)
{
	m_displayData[digit_] = encodeSymbol(number_);
}

void ClockDisplay::setNumber(int16_t number_)
{
	clear();

	uint8_t currentPosition = 3;
	uint8_t lastPosition = 0;

	if (number_ == 0)
	{
		m_displayData[3] = TM1637_0;
		return;
	}

	if (number_ < 0)
	{
		number_ = -number_;
		m_displayData[0] = 0b01000000;
		lastPosition = 1;
	}

	while (number_ != 0 && currentPosition >= lastPosition)
	{
		uint8_t digit = number_ % 10;

		m_displayData[currentPosition] = encodeSymbol(digit);
		number_ /= 10;
		currentPosition--;
	}
}

void ClockDisplay::setDataHex(int16_t data_)
{
	clear();

	uint8_t currentPosition = 3;
	while (data_ != 0)
	{
		uint8_t digit = data_ & 15;

		m_displayData[currentPosition] = encodeSymbol(digit);
		data_ >>= 4;
		currentPosition--;
	}
}

void ClockDisplay::toggleColon()
{
	m_displayData[TM1637_COLON_DIGIT] ^= 1 << 7;
}

void ClockDisplay::setColon(uint8_t value_)
{
	if (value_)
		m_displayData[TM1637_COLON_DIGIT] |= 1 << 7;
	else
		m_displayData[TM1637_COLON_DIGIT] &= ~(1 << 7);
}

uint8_t ClockDisplay::isColonOn() const
{
	return m_displayData[TM1637_COLON_DIGIT] & (1 << 7);
}

}
