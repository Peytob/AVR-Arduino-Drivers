#ifndef TM1637_DRIVER_BASE_HPP
#define TM1637_DRIVER_BASE_HPP

#include <inttypes.h>
#include <stdlib.h>
#include <tria/avr/Portio.hpp>
#include <util/delay.h>

namespace Tm1637
{

class DriverBase
{
public:
	DriverBase(uint8_t clkPin_, uint8_t dioPin_);
	DriverBase() = delete;

	~DriverBase() = default;

	void setOn();
	void setOff();
	uint8_t isOn() const;

	void setBrightness(uint8_t value_);
	uint8_t getBrightness() const;

	void updateConfiguration();

protected:
	uint8_t m_clkPin;
	uint8_t m_dioPin;
	uint8_t m_configuration;

	void m_startSignal();
	void m_stopSignal();
	void m_sendByte(uint8_t data_);
};

} // namespace Tm1637

#endif
