/*
 * Jacob Koziej
 * H-Bridge Activity (Task 3)
 * 2020-10-11
 * 2020-10-11
 */
#define SIZEOF(x, y) (sizeof(x) / sizeof(y))


// Constants
#define DELAY 1000

#define CW    0b0101
#define CCW   0b1010
#define BRAKE 0b0011
#define COAST 0b1100

const uint8_t h_bridge_q[] = {10, 9, 0, 1};


// Function prototypes
void motor(uint8_t, uint8_t);


// BEGIN
void setup()
{
	for (int i = 0; i < SIZEOF(h_bridge_q, uint8_t); i++) {
		pinMode(h_bridge_q[i], OUTPUT);
	}
}

void loop()
{
	motor(128, CW);
	delay(DELAY);
	motor(128, COAST);
	delay(DELAY);
	motor(128, CCW);
	delay(DELAY);
	motor(128, BRAKE);
	delay(DELAY);
}

// Function declarations
void motor(uint8_t speed, uint8_t state)
{
	/*
	 * To enable a transistor set the appropriate bit, where Q0 is bit 0
	 * and Q3 is bit 3. Bits 4-7 are don't cares.
	 */

	// Circuit protection
	if (state & _BV(0) && state & _BV(3)) return;
	if (state & _BV(1) && state & _BV(2)) return;

	// Q0
	analogWrite(h_bridge_q[0], (state & _BV(0) ? ~speed : HIGH));

	// Q1
	analogWrite(h_bridge_q[1], (state & _BV(1) ? ~speed : HIGH));

	// Q2
	digitalWrite(h_bridge_q[2], (state & _BV(2) ? HIGH : LOW));

	// Q3
	digitalWrite(h_bridge_q[3], (state & _BV(3) ? HIGH : LOW));
}

/*
 * I wanted to create an array of function pointers to the previously written
 * functions because I wanted to be lazy.  But I couldn't figure out how to
 * create a prototype which would allow for different function parameter types.
 */
