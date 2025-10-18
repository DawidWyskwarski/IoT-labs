/* 
    green and red buttons changes LED color in a sequence red -> green -> blue -> red ...
 */

#include <Arduino.h>

#define LED_GREEN 5
#define LED_RED 6
#define LED_BLUE 3

#define RED_BUTTON 2
#define GREEN_BUTTON 4

#define DEBOUNCE_PERIOD 10UL

int currentColorIndex = 0;
const int colors[3] = {LED_RED, LED_GREEN, LED_BLUE};

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

void initButtons() {
    pinMode(RED_BUTTON, INPUT_PULLUP);
    pinMode(GREEN_BUTTON, INPUT_PULLUP);
}

void setup() {
    initRGB();
    initButtons();
}

bool isButtonPressed(int button) {
    static int debouncedButtonState[2] = {HIGH, HIGH};
    static int previousReading[2] = {HIGH, HIGH};
    static unsigned long lastChangeTime[2] = {0UL, 0UL};
    bool isPressed = false;

    int buttonIndex = (button == RED_BUTTON) ? 0 : 1;

    int currentReading = digitalRead(button);

    if(currentReading != previousReading[buttonIndex])
        lastChangeTime[buttonIndex] = millis();

    if(millis() - lastChangeTime[buttonIndex] > DEBOUNCE_PERIOD) {

        if(currentReading != debouncedButtonState[buttonIndex]) {
        
            if (debouncedButtonState[buttonIndex] == HIGH && currentReading == LOW){
                isPressed = true;
            }
        
            debouncedButtonState[buttonIndex] = currentReading;
        }
    }

    previousReading[buttonIndex] = currentReading;

    return isPressed;
}

void loop() {

    if(isButtonPressed(RED_BUTTON) || isButtonPressed(GREEN_BUTTON)){
        digitalWrite(colors[currentColorIndex], LOW);
        currentColorIndex = (currentColorIndex+1)%3;
        digitalWrite(colors[currentColorIndex], HIGH);
    }
}
