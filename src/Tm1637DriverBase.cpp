#include <Tm1637DriverBase.hpp>

namespace Tm1637
{

DriverBase::DriverBase(const Portio::Pin & clkPin_, const Portio::Pin & dioPin_) :
	m_clkPin(clkPin_),
	m_dioPin(dioPin_),
	m_configuration(0x88)
{
	m_clkPin.setOutput();
	m_dioPin.setOutput();

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
	m_clkPin.set(true);
	m_dioPin.set(true);
	m_dioPin.set(false);
	m_clkPin.set(false);
}

void DriverBase::m_stopSignal()
{
	m_clkPin.set(false);
	m_dioPin.set(false);
	m_clkPin.set(true);
	m_dioPin.set(true);
}

void DriverBase::m_sendByte(uint8_t data_)
{
	// Sending byte
	for (uint8_t i = 0; i < 8; ++i)
	{
		m_clkPin.set(false);
		_delay_ms(2);
		m_dioPin.set(data_ & 1 << i);
		m_clkPin.set(true);
		_delay_ms(2);
	}

	// Getting ACK responce
	m_clkPin.set(false);
	m_dioPin.set(true);
	m_clkPin.set(true);
	m_dioPin.setOutput();
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
