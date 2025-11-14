#include "RGBDiod.h"

void RGBDiod::init(byte redLed, byte greenLed, byte blueLed) {
    redLed_ = redLed;
    greenLed_ = greenLed;
    blueLed_ = blueLed;
    
    pinMode(redLed, OUTPUT);
    digitalWrite(redLed, LOW);

    pinMode(greenLed, OUTPUT);
    digitalWrite(greenLed, LOW);

    pinMode(blueLed, OUTPUT);
    digitalWrite(blueLed, LOW);
}

void RGBDiod::setColor(byte r, byte g, byte b) {
    analogWrite(redLed_, r);
    analogWrite(greenLed_, g);
    analogWrite(blueLed_, b);
}

void RGBDiod::setColor(Color color) {
    switch (color)
    {
        case Color::RED:
            setColor(255,0,0);
            break;        
        case Color::GREEN:
            setColor(0,255,0);
            break;
        case Color::BLUE:
            setColor(0,0,255);
            break;
        case Color::YELLOW:
            setColor(255,255,0);
            break;
        case Color::CYAN:
            setColor(0,255,255);
            break;
        case Color::MAGENTA:
            setColor(255,0,255);
            break;
        case Color::BLACK:
            setColor(0,0,0);
            break;
        case Color::WHITE:
            setColor(255,255,255);
            break;
        default:
            break;
    }
}