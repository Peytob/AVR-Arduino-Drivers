#include <Tm1637DriverBase.hpp>

namespace Tm1637
{

DriverBase::DriverBase(uint8_t clkPin_, uint8_t dioPin_) :
	m_clkPin(clkPin_),
	m_dioPin(dioPin_),
	m_configuration(0x88)
{
	pinMode(m_clkPin, OUTPUT);
	pinMode(m_dioPin, OUTPUT);

	updateConfiguration();
}

void DriverBase::updateConfiguration()
{
	m_startSignal();
	m_sendByte(m_configuration);
	m_stopSignal();
}

void DriverBase::setBrightness(uint8_t value_)
{
	uint8_t brightness = value_ & ~(0x07);
	m_configuration &= ~(0x07) | brightness;
}

uint8_t DriverBase::getBrightness() const
{
	return m_configuration & ~(0x07);
}

void DriverBase::m_startSignal()
{
	digitalWrite(m_clkPin, true);
	digitalWrite(m_dioPin, true);
	digitalWrite(m_dioPin, false);
	digitalWrite(m_clkPin, false);
}

void DriverBase::m_stopSignal()
{
	digitalWrite(m_clkPin, false);
	digitalWrite(m_dioPin, false);
	digitalWrite(m_clkPin, true);
	digitalWrite(m_dioPin, true);
}

void DriverBase::m_sendByte(uint8_t data_)
{
	// Sending byte
	for (uint8_t i = 0; i < 8; ++i)
	{
		digitalWrite(m_clkPin, false);
		_delay_ms(2);
		digitalWrite(m_dioPin, data_ & 1 << i);
		digitalWrite(m_clkPin, true);
		_delay_ms(2);
	}

	// Getting ACK responce
	digitalWrite(m_clkPin, false);
	digitalWrite(m_dioPin, true);
	digitalWrite(m_clkPin, true);
	pinMode(m_dioPin, OUTPUT);
}

void DriverBase::setOn()
{
	m_configuration |= 1 << 3;
}

void DriverBase::setOff()
{
	m_configuration &= ~(1 << 3);
}

uint8_t DriverBase::isOn() const
{
	return m_configuration & (1 << 3);
}

} // namespace Tm1637
