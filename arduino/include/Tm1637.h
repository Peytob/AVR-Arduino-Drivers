#ifndef TM1637_H
#define TM1637_H

#include <inttypes.h>
#include <Arduino.h>

#include "Tm1637SymbolsDefines.h"

class Tm1637
{
public:
	Tm1637(uint8_t clkPin_, uint8_t dioPin_);
	~Tm1637();

	void clear();

	void setNumber(int16_t data_);
	void setByte(uint8_t digit_, uint8_t data_);
	void setByte(uint8_t byte_[4]);
	void setByte(uint8_t digit0_, uint8_t digit1_, uint8_t digit2_, uint8_t digit3_);
	void display() const;

	void setBrightness(uint8_t brightness_);
	void toggleColon();

	static uint8_t encodeNumeral(uint8_t numeral_);

private:
	const static uint8_t colonDigit = 1;
	uint8_t m_clkPin;
	uint8_t m_dioPin;
	uint8_t m_brightness;

	uint8_t m_displayData[4];

	inline void m_sendDelay() const;
	void m_startSignal() const;
	void m_stopSignal() const;
	void m_sendByte(uint8_t data_) const;
};
#endif // #ifndef TM1637_H
