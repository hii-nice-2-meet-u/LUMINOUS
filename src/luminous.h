
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/*
 *
 *	File		:	luminous.h
 *	Release		:	v2.0.0
 *
 *	Created on	:	Fri 12 Nov 2025
 *		Author	:	hii-nice-2-meet-u
 *
 */
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#ifndef INC_LUMINOUS_H
#define INC_LUMINOUS_H

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include <Arduino.h>

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#define luminous LUMINOUS

class LUMINOUS
{
public:
	bool     begin(uint8_t sclk, uint8_t miso, uint8_t mosi, uint8_t ss0, uint8_t ss1);
	uint16_t read(uint8_t Channel);

private:
	uint16_t          read_MANUAL(uint8_t Channel);
	uint16_t          read_SPI(uint8_t Channel);
	volatile bool     isMode_SPI = false;
	volatile uint8_t  _sclk, _miso, _mosi, _ss0, _ss1;
	volatile uint8_t  X_SCLK, X_MISO, X_MOSI, X_SS0, X_SS1;
	volatile uint8_t *PORTX_SCLK, *PINX_MISO, *PORTX_MOSI, *PORTX_SS0, *PORTX_SS1;
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#endif
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~