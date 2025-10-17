/*
  green button makes LED brighter
  red button makes LED dimmer
*/

#include <OneWire.h>

#define LED_GREEN 5

#define RED_BUTTON 2
#define GREEN_BUTTON 4

void initRGB() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  pinMode(LED_GREEN, OUTPUT);
  digitalWrite(LED_GREEN, LOW);
}

void initButtons() {
  pinMode(RED_BUTTON, INPUT_PULLUP);
  pinMode(GREEN_BUTTON, INPUT_PULLUP);
}

int current_light = 0;

void setup() {
  initRGB();
  initButtons();
  analogWrite(LED_GREEN, current_light);
}

void loop() {
  if(digitalRead(GREEN_BUTTON) == LOW){
    
    if(current_light < 255)
      ++current_light;

    analogWrite(LED_GREEN, current_light);
    delay(10);
  }

  if(digitalRead(RED_BUTTON) == LOW){
    
    if(current_light > 0)
      --current_light;

    analogWrite(LED_GREEN, current_light);
    delay(10);
  }  
}
