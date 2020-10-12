/*
 * Jacob Koziej
 * H-Bridge Activity (Task 1)
 * 2020-10-08
 * 2020-10-10
 */
#define SIZEOF(x, y) (sizeof(x) / sizeof(y))


// Function prototypes
void cw(uint8_t);
void ccw(uint8_t);
void brake(void);
void coast(void);


// Global variables
const uint8_t h_bridge_q[] = {10, 9, 0, 1};


// BEGIN
void setup()
{
	Serial.begin(9600);
	for (int i = 0; i < SIZEOF(h_bridge_q, uint8_t); i++) {
		pinMode(h_bridge_q[i], OUTPUT);
		Serial.println(i);
	}
}

void loop()
{
	cw(128);
	delay(2000);
	coast();
	delay(2000);
	ccw(128);
	delay(2000);
	brake();
	delay(2000);
}

// Function declarations
void cw(uint8_t speed)
{
	analogWrite(h_bridge_q[0], ~speed);
	digitalWrite(h_bridge_q[1], HIGH);
	digitalWrite(h_bridge_q[2], HIGH);
	digitalWrite(h_bridge_q[3], LOW);
}

void ccw(uint8_t speed)
{
	digitalWrite(h_bridge_q[0], HIGH);
	analogWrite(h_bridge_q[1], ~speed);
	digitalWrite(h_bridge_q[2], LOW);
	digitalWrite(h_bridge_q[3], HIGH);
}

void brake(void)
{
	for (int i = 0; i < SIZEOF(h_bridge_q, uint8_t); i++) {
		digitalWrite(h_bridge_q[i], LOW);
	}
}

void coast(void)
{
	for (int i = 0; i < SIZEOF(h_bridge_q, uint8_t); i++) {
		digitalWrite(h_bridge_q[i], HIGH);
	}
}
