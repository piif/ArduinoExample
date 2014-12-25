#ifdef PIF_TOOL_CHAIN
	#include <Arduino.h>
	// other includes with full pathes
	// example : #include "led7/led7.h"
	#include "serialInput/serialInput.h"
#else
	// other includes with short pathes
	// example : #include "led7.h"
	#include "serialInput.h"
#endif

#ifndef DEFAULT_BAUDRATE
	#define DEFAULT_BAUDRATE 115200
#endif

#define MOTOR_R_DIR 6
#define MOTOR_R_POW 5
#define MOTOR_L_DIR 4
#define MOTOR_L_POW 3

#define CAPTOR_L A0
#define CAPTOR_R A1

int left = 0,  right = 0;

void reset() {
	left = right = 0;
}

void updateMotors() {
	if (left < 0) {
		digitalWrite(MOTOR_L_DIR, HIGH);
		if (left < -255) {
			digitalWrite(MOTOR_L_POW, LOW);
		} else {
			analogWrite(MOTOR_L_POW, 255 + left);
		}
	} else {
		digitalWrite(MOTOR_L_DIR, LOW);
		if (left > 255) {
			digitalWrite(MOTOR_L_POW, HIGH);
		} else {
			analogWrite(MOTOR_L_POW, left);
		}
	}

	if (right < 0) {
		digitalWrite(MOTOR_R_DIR, HIGH);
		if (right < -255) {
			digitalWrite(MOTOR_R_POW, LOW);
		} else {
			analogWrite(MOTOR_R_POW, 255 + right);
		}
	} else {
		digitalWrite(MOTOR_R_DIR, LOW);
		if (right > 255) {
			digitalWrite(MOTOR_R_POW, HIGH);
		} else {
			analogWrite(MOTOR_R_POW, right);
		}
	}

}
void status() {
	Serial.print("left : "); Serial.println(left);
	Serial.print("right: "); Serial.println(right);
}

void brake(int d) {
	if (left > 0) {
		left = -300;
	} else if (left < 0) {
		left = 300;
	}
	if (right > 0) {
		right = -300;
	} else if (right < 0) {
		right = 300;
	}
	updateMotors();
	delay(d == 0 ? 150 : d);
	reset();
	updateMotors();
}

void moveTest(int d) {
	left = 300;
	right = -300;
	updateMotors();
	delay(d);
	brake(d > 500 ? 150 : d / 3);
}

void fullTest() {
//	for(byte i =0; i< 4; i++) {
		left = right = 100;
		updateMotors();
		delay(500);
		brake(100);

		delay(500);

		left = right = -200;
		updateMotors();
		delay(300);
		brake(100);

		delay(500);

		left = 300;
		right = -300;
		updateMotors();
		delay(200);
		brake(20);

		delay(500);

		left = 300;
		right = -300;
		updateMotors();
		delay(300);
		brake(20);
//	}
}
InputItem inputs[] = {
	{ 'l', 'i', &left },
	{ 'r', 'i', &right },
	{ 'm', 'I', (void *)moveTest },
	{ 'b', 'f', (void *)brake },
	{ 'z', 'f', (void *)reset },
	{ 't', 'f', (void *)fullTest },
	{ '?', 'f', (void *)status }
};

void setup(void) {
	Serial.begin(DEFAULT_BAUDRATE);
	Serial.println("setup");
	pinMode(MOTOR_L_DIR, OUTPUT);
	pinMode(MOTOR_L_POW, OUTPUT);
	pinMode(MOTOR_R_DIR, OUTPUT);
	pinMode(MOTOR_R_POW, OUTPUT);

	digitalWrite(MOTOR_L_DIR, 0);
	digitalWrite(MOTOR_L_POW, 0);
	digitalWrite(MOTOR_R_DIR, 0);
	digitalWrite(MOTOR_R_POW, 0);

	registerInput(sizeof(inputs), inputs);
	Serial.println("setup ok");
	status();
}

void loop() {
	fullTest();
	delay(3000);
//	handleInput();
//
//	updateMotors();
}
