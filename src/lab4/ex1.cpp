#include <Arduino.h>

#define RED_BUTTON 2
#define GREEN_BUTTON 4

void setup () {
    pinMode(RED_BUTTON, INPUT_PULLUP);
    pinMode(GREEN_BUTTON, INPUT_PULLUP);
    
    Serial.begin(9600);
    while (!Serial) {}
}

void loop() {
    Serial.print(digitalRead(GREEN_BUTTON));
    Serial.print(" ");
    Serial.println(digitalRead(RED_BUTTON));
}