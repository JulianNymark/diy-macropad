#include "config.h"
#include <Keyboard.h>

const int sensorPin = A0;

int sensorValue = 0;
int keyState[13] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

void setup() {
  pinMode(sensorPin, INPUT_PULLUP);
  pinMode(D1, INPUT);
  pinMode(D2, INPUT);
  pinMode(D3, INPUT);
  pinMode(D4, INPUT);
  pinMode(D5, INPUT);
  pinMode(D6, INPUT);
  pinMode(D7, INPUT);
  pinMode(D8, INPUT);
  pinMode(D9, INPUT);
  pinMode(D10, INPUT);
  Serial.begin(9600);
}

void loop() {
  Keyboard.begin();
  digitalPins();
  analogSignal();
  triggerConfigKeys();
  delay(20);
}

int lastKeyState[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

void triggerConfigKeys() {
  for (int i = 0; i < 13; i++) {
    if (keyState[i] && !lastKeyState[i]) {
      lastKeyState[i] = keyState[i];
      Keyboard.press(keyMap[i]);
    }
    if (!keyState[i] && lastKeyState[i]) {
      lastKeyState[i] = keyState[i];
      Keyboard.release(keyMap[i]);
    }    
  }
}

void digitalPins() {
  keyState[0] = digitalRead(D4);
  keyState[1] = digitalRead(D3);
  keyState[2] = digitalRead(D2);
  keyState[3] = digitalRead(D1);
  keyState[4] = digitalRead(D8);
  keyState[5] = digitalRead(D7);
  keyState[6] = digitalRead(D6);
  keyState[7] = digitalRead(D5);
  keyState[11] = digitalRead(D9);
  keyState[12] = digitalRead(D10);
}

// magic numbers for analog value thresholds found through trial and error
void analogSignal() {
  sensorValue = analogRead(sensorPin);
  //  Serial.println(sensorValue);/

  if (sensorValue < 1750) {
    keyState[10] = 0;
    keyState[9] = 0;
    keyState[8] = 0;
  } else if (sensorValue < 2055) {
    keyState[10] = 1;
    keyState[9] = 0;
    keyState[8] = 0;
  } else if (sensorValue < 2600) {
    keyState[10] = 0;
    keyState[9] = 1;
    keyState[8] = 0;
  } else if (sensorValue < 2920) {
    keyState[10] = 1;
    keyState[9] = 1;
    keyState[8] = 0;
  } else if (sensorValue < 3125) {
    keyState[10] = 0;
    keyState[9] = 0;
    keyState[8] = 1;
  } else if (sensorValue < 3180) {
    keyState[10] = 1;
    keyState[9] = 0;
    keyState[8] = 1;
  } else if (sensorValue < 3310) {
    keyState[10] = 0;
    keyState[9] = 1;
    keyState[8] = 1;
  } else {
    keyState[10] = 1;
    keyState[9] = 1;
    keyState[8] = 1;
  }
}
