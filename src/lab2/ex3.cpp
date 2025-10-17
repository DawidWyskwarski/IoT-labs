/*
    the LED changes through colors smoothly
    red -> green -> blue -> red -> ... 
*/

#include <OneWire.h>

#define LED_GREEN 5
#define LED_RED 6
#define LED_BLUE 3

void initRGB() {
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);

    pinMode(LED_RED, OUTPUT);
    digitalWrite(LED_RED, HIGH);    
    
    pinMode(LED_BLUE, OUTPUT);
    digitalWrite(LED_BLUE, LOW);    
    
    pinMode(LED_GREEN, OUTPUT);
    digitalWrite(LED_GREEN, LOW);
}

void change(int startingColor, int finalColor) {
    for(int i=0;i<=255;++i){
        analogWrite(startingColor, 255-i);
        analogWrite(finalColor, i);
        delay(4);
    } 
}

void setup() {
    initRGB();
}

void loop() {
    change(LED_RED, LED_GREEN);
    change(LED_GREEN, LED_BLUE);
    change(LED_BLUE, LED_RED);
}
