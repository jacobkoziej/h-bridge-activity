/*
 * Jacob Koziej
 * H-Bridge Activity (Task 1)
 * 2020-10-11
 * 2020-10-11
 */


/*
 * PIN MAPPING
 *
 * Q0 = PB1/OC1A
 * Q1 = PB2/OC1B
 * Q2 = PD0
 * Q3 = PD1
 */


#include <avr/io.h>
#include <util/delay.h>


// Constants
#define DELAY 1000

#define CW    0b0101
#define CCW   0b1010
#define BRAKE 0b0011
#define COAST 0b1100


// Function prototypes
void setup(void);
void cw(uint8_t);
void ccw(uint8_t);
void brake(void);
void coast(void);


// BEGIN
int main(void)
{
	setup();

	while (1) {
		cw(128);
		_delay_ms(DELAY);
		coast();
		_delay_ms(DELAY);
		ccw(128);
		_delay_ms(DELAY);
		brake();
		_delay_ms(DELAY);
	}

	return 0;
}


// Function declarations
void setup(void)
{
	// Set outputs
	DDRB = _BV(1) | _BV(2);
	DDRD = _BV(0) | _BV(1);

	// 8-bit Fast PWM w/o prescaler
	TCCR1A = _BV(WGM10);
	TCCR1B = _BV(WGM12) | _BV(CS10);

	// Turn everything off as a precaution
	PORTB = _BV(1) | _BV(2);
	PORTD = 0x00;
	OCR1A = OCR1B = 0xFF;
}

void cw(uint8_t speed)
{
	// Disable PWM for OCA1B
	TCCR1A &= ~_BV(COM1B1);

	// Enable PWM for OCA1A
	TCCR1A |= _BV(COM1A1);

	OCR1A =  ~speed;
	PORTB |=  _BV(2);
	PORTD |=  _BV(0);
	PORTD &= ~_BV(1);
}

void ccw(uint8_t speed)
{
	// Disable PWM for OCA1A
	TCCR1A &= ~_BV(COM1A1);

	// Enable PWM for OCA1B
	TCCR1A |= _BV(COM1B1);

	PORTB |=  _BV(1);
	OCR1B =  ~speed;
	PORTD &= ~_BV(0);
	PORTD |=  _BV(1);
}

void brake(void)
{
	TCCR1A &= ~(_BV(COM1A1) | _BV(COM1B1));

	PORTB &= ~(_BV(1) | _BV(2));
	PORTD &= ~(_BV(0) | _BV(1));
}

void coast(void)
{
	TCCR1A &= ~(_BV(COM1A1) | _BV(COM1B1));

	PORTB |= _BV(1) | _BV(2);
	PORTD |= _BV(0) | _BV(1);
}
