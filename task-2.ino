/*
 * Jacob Koziej
 * H-Bridge Activity (Task 2)
 * 2020-10-08
 * 2020-10-12
 */


// Constants
#define Q0 9
#define Q1 10

#define DELAY 2000


// Function prototypes
void cw(uint8_t);
void ccw(uint8_t);
void brake(void);
void coast(void);


// BEGIN
void setup()
{
	pinMode(Q0, OUTPUT);
	pinMode(Q1, OUTPUT);
}

void loop()
{
	cw(128);
	delay(DELAY);
	coast();
	delay(DELAY);
	ccw(128);
	delay(DELAY);
	brake();
	delay(DELAY);
}

// Function declarations
void cw(uint8_t speed)
{
	digitalWrite(Q0, HIGH);
	analogWrite(Q1, ~speed);
}

void ccw(uint8_t speed)
{
	digitalWrite(Q0, HIGH);
	analogWrite(Q1, ~speed);
}

void brake(void)
{
	digitalWrite(Q0, LOW);
	digitalWrite(Q1, LOW);
}

void coast(void)
{
	digitalWrite(Q0, HIGH);
	digitalWrite(Q1, HIGH);
}
