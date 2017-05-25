#include "chords.h"

const int numButtons = 7;

void setup(){
	Serial.begin(9200);

	pinMode(13, OUTPUT);
	digitalWrite(13, HIGH);

	for(int i = 0; i < numButtons; i++){
		pinMode(i, INPUT_PULLUP);
	}
}

byte lastKeyState, previousStableReading, currentStableReading;
int lastDebounceTime;

void loop(){
	byte keyState = 0, mask = 1;
	bool isDown = false;
	for (int i = 0; i < 7; i++) {
		isDown = digitalRead(i) == LOW;
		if(i > 0) keyState <<= 1;
		if (isDown) keyState |= mask;
	}

	if (lastKeyState != keyState) {
		lastDebounceTime = millis();
	}

	if ((millis() - lastDebounceTime) > 50) {
		currentStableReading = keyState;
	}

	if (previousStableReading != currentStableReading) {
		Keyboard.set_key1(keymap_default[keyState]);
		Keyboard.send_now();
		previousStableReading = currentStableReading;
	}

	lastKeyState = keyState;
}