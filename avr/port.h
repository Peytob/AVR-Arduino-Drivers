/*
		port.h
	Authors: Neiver @ easyelectronics.ru (source code)
			 Sky-WaLkeR (wrap into .h file - almost nothing)
	
	Version: 1.1
	   Date: 28.12.2014

	Description:
  This library allows you to work with I\O ports and it bits very easy.
  
  Thanks to Neiver from easyelectronics.ru - he wrote all the code, I just wrapped it to library 
   and added this documentation.

	Usage:
  Firstly, we need to call MAKE_PORT ( PORTx, DDRx, PINx, name, ID), where:
  	  PORTx, DDRx, PINx - any available names, like PORTB, DDRB, PINB
  	  name - name of the port class
  	  ID - unique identificator
  Now you can work with that port like this:
    name::Write ( data ) - write data to port ( like old PORTx=data )
    name::Read () - read from port ( like old data=PORTx )
    name::PinRead() - read from PINx
    name::ClearAndSet ( clearMask, value ) - set bits in clearMask to 0 and write value
    name::DirWrite ( data ) - write to direction register ( like old DDRx=data )
    name::DirRead () - I think you understand =)
    name::Set ( data  ) - like PORTx|=data; 
    name::Clear ( data ) - like PORTx&=~(data)
    name::Toggle ( data ) - switch ( PORTx^=value )
    Set, Clear and Toggle also available with Dir prefix, like name.DirSet() - you know what is it =)
    
  This lib also allows you to easily manipulate with 1 bit in port. Like that:
    typedef TPin<name, x> ledPin, where:
      name - name of the class you chosen in MAKE_PORT
      x - number of bit
      ledPin - name of the bit
  Now you can manipulate with this bit like that:
    ledPin::Set() - set to HIGH
    ledPin::Clear() - set to LOW
	ledPin::GetPort() - returns port of pin (PORTx)
	ledPin::GetDdr() - returns DDR of pin
	ledPin::GetMask() - returns bit mask (if pin is 3, will return 0b1000) 
    Also available commands: Toggle, IsSet, SetDir, SetDirWrite, SetDirRead, SetDir(mode)
    I think you can understand what these functions do... If mode!=0, dir is Write (output)
  
*/
#ifndef _LIB_PORT_H_
#define _LIB_PORT_H_
#define _S2W_PORT_INCL_

#define MAKE_PORT(portName, ddrName, pinName, className) \
	class className{\
	public:\
		typedef uint8_t DataT;\
	private:\
		static volatile DataT &data(){\
			return portName;\
		}\
		static volatile DataT &dir(){\
			return ddrName;\
		}\
		static volatile DataT &pin(){\
			return pinName;\
		}\
	public:\
		static void Write(DataT value){\
			data() = value;\
		}\
		static void ClearAndSet(DataT clearMask, DataT value){\
			data() = (data() & ~clearMask) | value;\
		}\
		static DataT Read(){\
			return data();\
		}\
		static void DirWrite(DataT value){\
			dir() = value;\
		}\
		static DataT DirRead(){\
			return dir();\
		}\
		static void Set(DataT value){\
			data() |= value;\
		}\
		static void Clear(DataT value){\
			data() &= ~value;\
		}\
		static void Toggle(DataT value){\
			data() ^= value;\
		}\
		static void DirSet(DataT value){\
			dir() |= value;\
		}\
		static void DirClear(DataT value){\
			dir() &= ~value;\
		}\
		static void DirToggle(DataT value){\
			dir() ^= value;\
		}\
		static DataT PinRead(){\
			return pin();\
		}\
		enum{Width=sizeof(DataT)*8};\
	};
// END define MAKE_PORT

template<class PORT, uint8_t PIN>
	class Pin {
	public:
		typedef PORT Port;
		enum{Number = PIN};
		static void Set(){
			PORT::Set(1 << PIN);
		}
		static void Set(uint8_t val){
			if(val)
				Set();
			else Clear();
		}
		static void SetDir(uint8_t val){
			if(val)
				SetDirWrite();
			else SetDirRead();
		}
		static void Clear(){
			PORT::Clear(1 << PIN);
		}
		static void Toggle(){
			PORT::Toggle(1 << PIN);
		}
		static void SetDirRead(){
			PORT::DirClear(1 << PIN);
		}
		static void SetDirWrite(){
			PORT::DirSet(1 << PIN);
		}
		static uint8_t IsSet(){
			return (PORT::PinRead() & (1 << PIN)) >> PIN;
		}
		static uint8_t GetMask(){
			return (1 << PIN);
		}
		static uint8_t GetPort(){
			return PORT::data();
		}
		static uint8_t GetDdr(){
			return PORT::ddr();
		}
	};

#define MAKE_PORT_B MAKE_PORT(PORTB, DDRB, PINB, Pinb)
#define MAKE_PORT_C MAKE_PORT(PORTC, DDRC, PINC, Pinc)
#define MAKE_PORT_D MAKE_PORT(PORTD, DDRD, PIND, Pind)

#endif
