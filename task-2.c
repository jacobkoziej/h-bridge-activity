/*
 * Jacob Koziej
 * H-Bridge Activity (Task 2)
 * 2020-10-08
 * 2020-10-10
 */
#include <avr/io.h>
#include <util/delay.h>


/*
 * PIN MAPPING
 *
 * Q1 == PORTB1/OC1A
 * Q2 == PORTB2/OC1B
 */


// Function prototypes
void setup(void);
void CW(uint8_t);
void CCW(uint8_t);
void brake(void);
void coast(void);


// BEGIN
int main(void)
{
	setup();

	while (1) {
		CW(128);
		_delay_ms(2000);
		CCW(128);
		_delay_ms(2000);
	}

	return 0;
}


// Function declarations
void setup(void)
{
	// Set outputs
	DDRB = _BV(1) | _BV(2);

	// 8-bit Fast PWM for OCA1A:B w/o prescaler
	TCCR1A = _BV(COM1A1) | _BV(COM1B1) | _BV(WGM10);
	TCCR1B = _BV(WGM12)  | _BV(CS10);

	// Set everything high
	PORTB = OCR1A = OCR1B = 0xFF;
}

void CW(uint8_t speed)
{
	// Disable PWM for OCA1A
	if (bit_is_set(TCCR1A, COM1A1))
		TCCR1A &= ~_BV(COM1A1);

	// Enable PWM for OCA1B
	if (bit_is_clear(TCCR1A, COM1B1))
		TCCR1A |= _BV(COM1B1);

	PORTB |= _BV(1);
	OCR1B  = speed;
}

void CCW(uint8_t speed)
{
	// Disable PWM for OCA1B
	if (bit_is_set(TCCR1A, COM1B1))
		TCCR1A &= ~_BV(COM1B1);

	// Enable PWM for OCA1A
	if (bit_is_clear(TCCR1A, COM1A1))
		TCCR1A |= _BV(COM1A1);

	PORTB |= _BV(2);
	OCR1A  = speed;
}

void brake(void)
{
	// Disable PWM for OCA1A:B
	TCCR1A &= ~(_BV(COM1A1) | _BV(COM1B1));

	// This will destroy circuit
	PORTB &= ~(_BV(1) | _BV(2));
}

void coast(void)
{
	// Disable PWM for OCA1A:B
	TCCR1A &= ~(_BV(COM1A1) | _BV(COM1B1));

	PORTB |= _BV(1) | _BV(2);
}
