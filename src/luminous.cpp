
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/*
 *
 *	File		:	luminous.cpp
 *	Release		:	v1.0
 *
 *	Created on	:	 Wed 19 Nov 2025
 *		Author	:	hii-nice-2-meet-u
 *
 */
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "luminous.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

bool LUMINOUS::begin(
    uint8_t sclk,
    uint8_t miso,
    uint8_t mosi,
    uint8_t ss0,
    uint8_t ss1)
{

	//- mark pin
	_sclk = sclk;
	_miso = miso;
	_mosi = mosi;
	_ss0  = ss0;
	_ss1  = ss1;

	//- Set PIN Mode
	pinMode(_sclk, OUTPUT);
	pinMode(_mosi, OUTPUT);
	pinMode(_miso, INPUT);
	pinMode(_ss0, OUTPUT);
	pinMode(_ss1, OUTPUT);

	//>> Close Communication
	digitalWrite(_ss0, HIGH);
	digitalWrite(_ss1, HIGH);

	//- ret status
	return true;
}

uint16_t LUMINOUS::read(uint8_t Channel)
{
	//- Temporary Variables of Receive Byte
	bool     SlaveSelect = (bool)(Channel & 0b00001000);
	uint16_t ReadValue   = 0;
	Channel |= 0b00011000;

	digitalWrite(_ss0, SlaveSelect);
	digitalWrite(_ss1, !SlaveSelect);

	digitalWrite(_sclk, LOW);

	//- Repeat For Transmit bit
	for (uint8_t ii = 0; ii < 5; ii++)
	{
		//+ Transmit Bit
		digitalWrite(_mosi, (bool)(Channel & 0b00010000));
		Channel <<= 1;

		//+ Shift to next Communication Bit
		digitalWrite(_sclk, HIGH);
		digitalWrite(_sclk, LOW);
	}

	//- Repeat For Receive bit
	for (uint8_t ii = 0; ii < 11; ii++)
	{
		//+ Shift to next Communication Bit
		digitalWrite(_sclk, HIGH);
		digitalWrite(_sclk, LOW);

		//+ Get Receive Bit
		ReadValue <<= 1;
		if (digitalRead(_miso))
		{
			ReadValue |= 1;
		}
	}

	//>> Close Communication
	digitalWrite(_ss0, HIGH);
	digitalWrite(_ss1, HIGH);
	digitalWrite(_sclk, HIGH);

	//? RETURN Receive Value
	return ReadValue;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~