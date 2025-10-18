/* 
    the RED led turns on and off every 0.9s, GREEN every 1s and BLUE every 1.1s
*/

#include <Arduino.h>

#define LED_GREEN 5
#define LED_RED 6
#define LED_BLUE 3

#define RED_PERIOD 900UL
#define GREEN_PERIOD 1000UL
#define BLUE_PERIOD 1100UL

void initRGB() {
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);

    pinMode(LED_GREEN, OUTPUT);
    digitalWrite(LED_GREEN, LOW);

    pinMode(LED_RED, OUTPUT);
    digitalWrite(LED_RED, HIGH);

    pinMode(LED_BLUE, OUTPUT);
    digitalWrite(LED_BLUE, LOW);
}

void setup() {
    initRGB();
}

void changeColorsState(int led, unsigned long period) {
    static bool colorsState[3] = {LOW, LOW, LOW}; //RGB
    static unsigned long colorLastChange[3] = {0UL, 0UL, 0UL};

    int index = -1;

    switch (led) {
        case LED_RED: index = 0; break;
        case LED_GREEN: index = 1; break;
        case LED_BLUE: index = 2; break;
        default: return; // Invalid LED value, exit the function
    }

    if(millis() - colorLastChange[index] >= period) {
        switch (colorsState[index]) {
            case LOW: colorsState[index] = HIGH; break;
            case HIGH: colorsState[index] = LOW; break;
        }
        digitalWrite(led, colorsState[index]);
        colorLastChange[index] = millis();
    }
}

void loop() {
    changeColorsState(LED_RED, RED_PERIOD);
    changeColorsState(LED_GREEN, GREEN_PERIOD);
    changeColorsState(LED_BLUE, BLUE_PERIOD);
}
