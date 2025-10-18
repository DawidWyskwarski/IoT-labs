/*
    timer
*/

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

#define RED_BUTTON 2
#define GREEN_BUTTON 4

#define DEBOUNCE_PERIOD 10UL

#define SECOND 1000UL

LiquidCrystal_I2C lcd(0x27, 16, 2);

unsigned int time = 0;
bool is_on = false;

void initButtons() {
    pinMode(RED_BUTTON, INPUT_PULLUP);
    pinMode(GREEN_BUTTON, INPUT_PULLUP);
}

void setup() {
    lcd.init();
    lcd.backlight();
    
    lcd.print(0);

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

void timePassing() {
    
    static unsigned long lastRead = 0; 
    
    if (is_on){
        if (millis() - lastRead >= SECOND){
            lcd.setCursor(0,0);
            lcd.print(++time);
            lastRead = millis();
        }
    }
}

void loop(){
    timePassing();
    if (isButtonPressed(GREEN_BUTTON)){
        is_on = !is_on;
    }
    if (isButtonPressed(RED_BUTTON)){
        is_on = false;
        time = 0; 
        lcd.setCursor(0,0);
        lcd.print(0);
    }
}