#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

#define POTENTIOMETER A0
#define VOLT 5

LiquidCrystal_I2C lcd(0x27, 16, 2);

int prevVal = 0;

void setup() {
    lcd.init();
    lcd.backlight();
    lcd.setCursor(0,0);
    lcd.print("ADC: ");
    lcd.setCursor(0,1);
    lcd.print("VOLT: ");
}

void updateDisplay() { 
    int val = analogRead(POTENTIOMETER);
    
    if(val!=prevVal){
        float voltage = (val/1023.0) * VOLT;
        lcd.setCursor(5,0);
        lcd.print("    ");
        lcd.setCursor(5,0);
        lcd.print(val);
        lcd.setCursor(6,1);
        lcd.print("    ");
        lcd.setCursor(6,1);
        lcd.print(voltage, 2);
        prevVal = val;
    }
}

void loop() {
    updateDisplay();
}