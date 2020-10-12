/*
 * Jacob Koziej
 * H-Bridge Activity (Task 2)
 * 2020-10-08
 * 2020-10-08
 */
#define SIZEOF(X, Y) (sizeof(X) / sizeof(Y))


// Function prototypes
void cw(uint8_t);
void ccw(uint8_t);
void brake(void);
void coast(void);


// Global variables
const uint8_t h_bridge_q[] = {9, 10};


// BEGIN
void setup()
{
	for (int i = 0; i < SIZEOF(h_bridge_q, uint8_t); i++) {
		pinMode(h_bridge_q[i], OUTPUT);
	}
}

void loop()
{
	cw(128);
	delay(2000);
	ccw(128);
	delay(2000);
}

// Function declarations
void cw(uint8_t speed)
{
	digitalWrite(h_bridge_q[0], HIGH);
	analogWrite(h_bridge_q[1], ~speed);
}

void ccw(uint8_t speed)
{
	digitalWrite(h_bridge_q[1], HIGH);
	analogWrite(h_bridge_q[0], ~speed);
}

void brake(void)
{
	// This will destroy circuit
	digitalWrite(h_bridge_q[0], LOW);
	digitalWrite(h_bridge_q[1], LOW);
}

void coast(void)
{
	digitalWrite(h_bridge_q[0], HIGH);
	digitalWrite(h_bridge_q[1], HIGH);
}
