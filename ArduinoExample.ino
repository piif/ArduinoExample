#ifdef PIF_TOOL_CHAIN
	#include <Arduino.h>
	// other includes with full pathes
	// example : #include "led7/led7.h"
#else
	// other includes with short pathes
	// example : #include "led7.h"
#endif

#ifndef DEFAULT_BAUDRATE
	#define DEFAULT_BAUDRATE 115200
#endif


void setup(void) {
	pinMode(13, OUTPUT);
}

bool flag = LOW;
void loop() {
	delay(500);
	flag = flag ? LOW : HIGH;
	digitalWrite(13, flag);
}
