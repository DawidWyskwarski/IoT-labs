#include <Arduino.h>

#define RED_LED 6
#define GREEN_LED 5
#define BLUE_LED 3

int convertToInt(String s){
    s.trim();
    
    if (s.length() == 0) return -1;

    for (size_t i=0;i<s.length();++i){
        if(!isDigit(s[i])){
            Serial.println(s);
            return -1;
        }
    }

    int output = s.toInt();

    if(output>255) return -1;

    return output;
}

void parseInput(){
    int r = convertToInt(Serial.readStringUntil(';'));
    int g = convertToInt(Serial.readStringUntil(';'));
    int b = convertToInt(Serial.readStringUntil('\n'));

    if(r==-1 || g==-1 ||b==-1) {
        Serial.println("Something wrong with the input. Aborting Change");
        return;
    }
    
    analogWrite(RED_LED, r);
    analogWrite(GREEN_LED, g);
    analogWrite(BLUE_LED, b);
    Serial.println("Changing to new color");
}

void setup() {
    pinMode(RED_LED, OUTPUT);
    digitalWrite(RED_LED, LOW);

    pinMode(GREEN_LED, OUTPUT);
    digitalWrite(GREEN_LED, LOW);

    pinMode(BLUE_LED, OUTPUT);
    digitalWrite(BLUE_LED, LOW);

    Serial.begin(9600);
    while(!Serial) {}
}

void loop() {
    if (Serial.available()) {
        parseInput();
    }
}