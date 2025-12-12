
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include <avr/interrupt.h>
#include <avr/io.h>

#define DELAY_BACKWARD_COMPATIBLE
#include <util/atomic.h>
#include <util/delay.h>

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include <luminous.h>
luminous hii;

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

uint32_t __TIMER1_COUNTER__ = 0;

//$ Timer 1 compare match interrupt handler
ISR(TIMER1_COMPA_vect)
{
	__TIMER1_COUNTER__++;
}

//\ " Get "
/// Function to get the current Time Counter
uint32_t Timer__Get(void)
{
	uint32_t TEMP;
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		TEMP = __TIMER1_COUNTER__;
	}
	return TEMP;
}

//\ " Reset "
/// Function to Reset Time Counter
void Timer__Reset(void)
{
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		__TIMER1_COUNTER__ = 0;
	}
}

//$ Function Initialize Timer
void _init_Timer(void)
{
	//- Reset Timer/Counter 1
	/// Reset Timer1 Counter to exactly zero
	TCNT1 = 0;

	//- Set Timer 1 to CTC (Clear Timer on Compare Match) mode
	/// set Timer1 to CTC Mode 					: clear (1 <<
	/// WGM11) & (1 << WGM10) in TCCR1A
	TCCR1A = 0;

	//- Set prescaler to 001 ( Clk/1 from Pre-scaler )
	/// Prescaler - clk/1 ( from Pre-scaler )	: (1 << CS10)
	TCCR1B = (1 << WGM12) | (1 << CS10);

	//- Set compare match value for 1ms interval
	/// Calculation: OCR1A = (F_CPU / prescaler / 1000) - 1
	OCR1A = 639;

	TIMSK1 |= (1 << OCIE1A);

	//. Reset Timer Counter
	Timer__Reset();

	//. Enable Timer1 compare match A interrupt
	TIMSK0 |= (1 << TOIE0);

	//. Enable global interrupts
	sei();
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void MultiplexerAnalogRead_init(void)
{
	pinMode(A1, OUTPUT);
	pinMode(A2, OUTPUT);
	pinMode(A3, OUTPUT);
	pinMode(A4, OUTPUT);
}

uint16_t MultiplexerAnalogRead(uint8_t Channel)
{
	digitalWrite(A1, bitRead(Channel, 0));
	digitalWrite(A2, bitRead(Channel, 1));
	digitalWrite(A3, bitRead(Channel, 2));
	digitalWrite(A4, bitRead(Channel, 3));
	return analogRead(0);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void setup()
{
	_init_Timer();
	MultiplexerAnalogRead_init();

	hii.begin(13, 12, 11, 10, 9);
	Serial.begin(115200);
	Serial.print("\n\n\n");
}

uint16_t ReadValue, i;
uint32_t Start_T, Stop_T;
uint16_t ReadRepeatedTime = 16;

void loop()
{
	/*----------------------------------------------------------------*/
	//>	> Arduino analogRead

	Timer__Reset();
	Start_T = Timer__Get();
	i       = 0;
	do
	{
		ReadValue = analogRead(0);
		i++;
	} while (i < ReadRepeatedTime);
	Stop_T = Timer__Get();

	uint32_t TimeDifferent = Stop_T - Start_T;
	Serial.print(">  Arduino analogRead\t|\t");
	Serial.print(TimeDifferent);
	Serial.println("\tμs");

	/*----------------------------------------------------------------*/
	//> Multiplexer Read

	Timer__Reset();
	Start_T = Timer__Get();
	i       = 0;
	do
	{
		ReadValue = MultiplexerAnalogRead(0);
		i++;
	} while (i < ReadRepeatedTime);
	Stop_T = Timer__Get();

	TimeDifferent = Stop_T - Start_T;
	Serial.print(">  Multiplexer Read\t|\t");
	Serial.print(TimeDifferent);
	Serial.println("\tμs");

	/*----------------------------------------------------------------*/
	//>	ADC-SPI interface

	Timer__Reset();
	Start_T = Timer__Get();
	i       = 0;
	do
	{
		ReadValue = hii.read(0);
		i++;
	} while (i < ReadRepeatedTime);
	Stop_T = Timer__Get();

	TimeDifferent = Stop_T - Start_T;
	Serial.print(">  ADC-SPI interface\t|\t");
	Serial.print(TimeDifferent);
	Serial.println("\tμs");

	/*----------------------------------------------------------------*/

	while (1)
		;
}
