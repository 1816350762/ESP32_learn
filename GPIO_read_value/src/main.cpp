#include <Arduino.h>

#define POT 5

void setup() {
  Serial.begin(112500);
  pinMode(POT, INPUT);
}

void loop() {
  int val = analogRead(POT);
  Serial.println(val);
  delay(100);
}