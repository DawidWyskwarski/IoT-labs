#include <Arduino.h>
#include <Wire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal_I2C.h>

#define RED_LED 6
#define GREEN_LED 5
#define BLUE_LED 3

LiquidCrystal_I2C lcd(0x27, 16, 2);

OneWire oneWire(A1);
DallasTemperature tempSensors(&oneWire);

void setup() {
    pinMode(RED_LED, OUTPUT);
    digitalWrite(RED_LED, LOW);

    pinMode(GREEN_LED, OUTPUT);
    digitalWrite(GREEN_LED, LOW);

    pinMode(BLUE_LED, OUTPUT);
    digitalWrite(BLUE_LED, LOW);
    
    tempSensors.begin();

    lcd.init();
    lcd.backlight();
    lcd.clear();

    lcd.setCursor(0,0);
    lcd.print("Temp: ");
    
    lcd.setCursor(0,1);
    lcd.print("Max ");

    lcd.setCursor(8,1);
    lcd.print("Min ");
}

void ledSignal(float temp) {

    if (temp < 0) {
        digitalWrite(RED_LED, LOW);
        digitalWrite(GREEN_LED, LOW);
        digitalWrite(BLUE_LED, HIGH);
    }else if (temp > 30) {
        digitalWrite(RED_LED, HIGH);
        digitalWrite(GREEN_LED, LOW);
        digitalWrite(BLUE_LED, LOW);
    }
    else{
        digitalWrite(RED_LED, LOW);
        digitalWrite(GREEN_LED, HIGH);
        digitalWrite(BLUE_LED, LOW);
    }
}

void updateMax(float temp) {
    static float max = __FLT_MIN__;

    if (temp <= max) 
        return;

    lcd.setCursor(4,1);
    char buffer[4];
    sprintf(buffer, "%4s", String(temp,1).c_str());

    lcd.print(buffer);

    max = temp;
}

void updateMin(float temp){
    static float min = __FLT_MAX__;

    if (temp >= min) 
        return;

    lcd.setCursor(11,1);

    char buffer[4];
    sprintf(buffer, "%4s", String(temp,1).c_str());

    lcd.print(buffer);

    min = temp;
}

void updateTemp(float temp){
    static float prev;

    if(not prev || prev != temp){
        lcd.setCursor(5,0);
        char buffer[6];
        sprintf(buffer, "%6s", String(temp,1).c_str());

        lcd.print(buffer);;
    }
}

void loop() {

    tempSensors.requestTemperatures();
    float temp = tempSensors.getTempCByIndex(0);  

    updateTemp(temp);
    ledSignal(temp);
    updateMax(temp);    
    updateMin(temp); 
}