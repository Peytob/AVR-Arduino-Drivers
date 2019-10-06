#include <Tm1637.h>

Tm1637::Tm1637(uint8_t clkPin_, uint8_t dataPin_)
{
	m_clkPin = clkPin_;
	m_dioPin = dataPin_;
	m_brightness = 0x88 + 5;

	pinMode(m_clkPin, OUTPUT);
	pinMode(m_dioPin, OUTPUT);

	clear();
}

Tm1637::~Tm1637() { }

void Tm1637::display() const
{
	m_startSignal();
	m_sendByte(0x40);
	m_stopSignal();

	m_startSignal();
	m_sendByte(0xc0);
	for (size_t i = 0; i < 4; ++i)
		m_sendByte(m_displayData[i]);
	m_stopSignal();

	m_startSignal();
	m_sendByte(m_brightness);
	m_stopSignal();
}

void Tm1637::m_startSignal() const
{
	digitalWrite(m_clkPin, true);
	digitalWrite(m_dioPin, true); 
	digitalWrite(m_dioPin, false); 
	digitalWrite(m_clkPin, false); 
}

void Tm1637::m_stopSignal() const
{
	digitalWrite(m_clkPin, false);
	digitalWrite(m_dioPin, false);
	digitalWrite(m_clkPin, true);
	digitalWrite(m_dioPin, true); 
}

void Tm1637::m_sendByte(uint8_t data) const
{
	// Sending byte
	for (size_t i = 0; i < 8; ++i)
	{
		digitalWrite(m_clkPin, false);
		m_sendDelay();
		digitalWrite(m_dioPin, data & 1 << i);
		digitalWrite(m_clkPin, true);
		m_sendDelay();
	}
	
	// Getting ACK responce
	digitalWrite(m_clkPin, false);
	digitalWrite(m_dioPin, true);
	digitalWrite(m_clkPin, true);
	pinMode(m_dioPin, OUTPUT);
}

inline void Tm1637::m_sendDelay() const
{
	delayMicroseconds(2);
}

void Tm1637::clear()
{
	for (size_t i = 0; i < 4; ++i)
		m_displayData[i] = 0;
}

void Tm1637::setBrightness(uint8_t brightness_)
{
	m_brightness &= ~0x07; // clear 3 right bits
	m_brightness |= (brightness_ & 0x07); // copy 3 right bits from brightness_
}

void Tm1637::toggleColon()
{
	// Set point bit to on
	m_displayData[colonDigit] ^= 0x80;
}

void Tm1637::setNumber(int16_t data)
{
	clear();
	if (data == 0)
	{
		m_displayData[3] = TM1637_0;
		return;
	}

	uint8_t currentPosition = 3;
	uint8_t lastPosition = 0;
	if (data < 0)
	{
		m_displayData[0] = 0b01000000;
		lastPosition = 1;
		data = -data;
	}

	while (data != 0 && currentPosition >= lastPosition)
	{
		uint8_t rightDigit = data % 10;

		m_displayData[currentPosition] = encodeNumeral(rightDigit);
		data /= 10;
		currentPosition--;
	}
}

void Tm1637::setByte(uint8_t byte_[4])
{
	for (size_t i = 0; i < 4; ++i)
		m_displayData[i] = byte_[i];
}

void Tm1637::setByte(uint8_t digit_, uint8_t data_)
{
	m_displayData[digit_] = data_;
}

void Tm1637::setByte(uint8_t digit0_, uint8_t digit1_, uint8_t digit2_, uint8_t digit3_)
{
	m_displayData[0] = digit0_;
	m_displayData[1] = digit1_;
	m_displayData[2] = digit2_;
	m_displayData[3] = digit3_;
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
