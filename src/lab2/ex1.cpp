/* 
    red button turns the LED on and off
    green changes its color
 */

#include <OneWire.h>

#define LED_GREEN 5
#define LED_RED 6
#define LED_BLUE 3

#define RED_BUTTON 2
#define GREEN_BUTTON 4

void initRGB() {
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);

    pinMode(LED_GREEN, OUTPUT);
    digitalWrite(LED_GREEN, LOW);

    pinMode(LED_RED, OUTPUT);
    digitalWrite(LED_RED, LOW);

    pinMode(LED_BLUE, OUTPUT);
    digitalWrite(LED_BLUE, LOW);
}

void initButtons() {
    pinMode(RED_BUTTON, INPUT_PULLUP);
    pinMode(GREEN_BUTTON, INPUT_PULLUP);
}

void setup() {
    initRGB();
    initButtons();
}

int currentColorIndex = 0;
const int colors[3] = {LED_RED, LED_GREEN, LED_BLUE};
bool is_on = false;
int redButtonLastState = HIGH;
int greenButtonLastState = HIGH;

void loop() {

    int redButtonState = digitalRead(RED_BUTTON);
    int greenButtonState = digitalRead(GREEN_BUTTON);

    if(redButtonLastState == HIGH && redButtonState == LOW)
    {
        is_on = !is_on;
        delay(200);
    }

    if(is_on && greenButtonState == LOW && greenButtonLastState == HIGH)
    {
        digitalWrite(colors[currentColorIndex], LOW); // turn off the previous color
        currentColorIndex = (currentColorIndex+1)%3;
        delay(200);
    }

    redButtonLastState = redButtonState;
    greenButtonLastState = greenButtonState;

    digitalWrite(colors[currentColorIndex], is_on); // turn on the color if system is on
}
