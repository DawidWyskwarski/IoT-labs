#pragma once

#include <Arduino.h>

enum class Color : uint8_t {
    RED,
    GREEN,
    BLUE,
    YELLOW,
    CYAN,
    MAGENTA,
    BLACK,
    WHITE
};

class RGBDiod
{
public:
    void init(byte redLed, byte greenLed, byte blueLed);
    void setColor(byte r, byte g, byte b);
    void setColor(Color color); 

private:
    byte redLed_;
    byte greenLed_;
    byte blueLed_;
};