/*
 * Jacob Koziej
 * H-Bridge Activity (Task 3)
 * 2020-10-10
 * 2020-10-12
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
void motor(uint8_t, uint8_t);


// BEGIN
int main(void)
{
	setup();

	while (1) {
		motor(128, CW);
		_delay_ms(DELAY);
		motor(128, COAST);
		_delay_ms(DELAY);
		motor(128, CCW);
		_delay_ms(DELAY);
		motor(128, BRAKE);
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

void motor(uint8_t speed, uint8_t state)
{
	/*
	 * To enable a transistor set the appropriate bit, where Q0 is bit 0
	 * and Q3 is bit 3.  Bits 4-7 are don't cares.
	 */

	// Circuit protection
	if (state & _BV(0) && state & _BV(3)) return;
	if (state & _BV(1) && state & _BV(2)) return;

	// Account for digital states
	uint8_t pwm_mask   = _BV(COM1A1) | _BV(COM1B1);
	uint8_t portb_mask = _BV(1) | _BV(2);

	TCCR1A = (speed != 0xFF && speed != 0x00) ?
		(TCCR1A | pwm_mask) : (TCCR1A & ~pwm_mask);

	PORTB = (speed == 0xFF) ? (PORTB & ~portb_mask) : (PORTB | portb_mask);

	// Set port states
	OCR1A = OCR1B = ~speed;

	if (!(state & _BV(0))) {
		TCCR1A &= ~_BV(COM1A1);
		PORTB  |=  _BV(1);
	}
	if (!(state & _BV(1))) {
		TCCR1A &= ~_BV(COM1B1);
		PORTB  |=  _BV(2);
	}

	PORTD = (state & _BV(2)) ? (PORTD | _BV(0)) : (PORTD & ~_BV(0));
	PORTD = (state & _BV(3)) ? (PORTD | _BV(1)) : (PORTD & ~_BV(1));
}
