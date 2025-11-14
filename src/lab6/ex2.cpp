#include <RGBDiod.h>

#define LED_RED 6
#define LED_GREEN 5
#define LED_BLUE 3

RGBDiod diod;

void setup() {
    diod.init(LED_RED, LED_GREEN, LED_BLUE);
}


void loop() {
    diod.setColor(255, 255, 255);
    delay(1000);

    diod.setColor(0, 0, 0); 
    delay(1000);

    diod.setColor(255, 0, 0); 
    delay(1000);

    diod.setColor(Color::RED);
    delay(1000);

    diod.setColor(Color::GREEN);
    delay(1000);

    diod.setColor(Color::BLUE);
    delay(1000);

    diod.setColor(Color::YELLOW);
    delay(1000);

    diod.setColor(Color::CYAN);
    delay(1000);

    diod.setColor(Color::MAGENTA);
    delay(1000);

    diod.setColor(Color::BLACK);
    delay(1000);

    diod.setColor(Color::WHITE);
    delay(1000);
}
