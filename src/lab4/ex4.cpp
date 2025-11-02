#include <Arduino.h>

#define POTENTIOMETER A0

void setup() {
    Serial.begin(9600);

    while(!Serial) {}
}

void loop() {
    int val = analogRead(POTENTIOMETER);
    Serial.println(val);
}