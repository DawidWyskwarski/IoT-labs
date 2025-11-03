#include <Arduino.h>
#include <util/atomic.h>
#include <LiquidCrystal_I2C.h>

#define LED_RED 6
#define LED_GREEN 5
#define LED_BLUE 3

#define RED_BUTTON 2

#define ENCODER1 A2
#define ENCODER2 A3

#define ENCODER_DEBOUNCING_PERIOD 100UL
#define BUTTON_DEBOUNCE_PERIOD 50UL
#define ENCODER_STEP 15

LiquidCrystal_I2C lcd(0x27, 16, 2);

int currentIndex = 0;
int ledStates[3] = {0,0,0};

volatile bool menuMode = true;
volatile int encoder1 = HIGH;
volatile int encoder2 = HIGH;
volatile unsigned long encoderTimestamp = 0UL;

int getLed(int index){
    if (index == 0)
        return LED_RED;
    if (index == 1)
        return LED_GREEN;
    if (index == 2)
        return LED_BLUE;

    return -1;
}

void printState(int index){
    char buffer[3];
    sprintf(buffer, "%3d", ledStates[index]);
    lcd.print(buffer);    
}

void clearLeds(){
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_BLUE, LOW);

    ledStates[0] = 0;
    ledStates[1] = 0;
    ledStates[2] = 0;
}

void updateLed(){
    analogWrite(getLed(currentIndex), ledStates[currentIndex]);
}

void printMenu(){
    if(currentIndex < 2){
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(" RED: ");
        printState(0);

        lcd.setCursor(0, 1);
        lcd.print(" GREEN: ");
        printState(1);
    }else{
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(" BLUE: ");
        printState(2);
        
        lcd.setCursor(0, 1);
        lcd.print(" CLEAR");
    }
    
    lcd.setCursor(0,currentIndex%2);
    
    if (menuMode){
        lcd.print(">");
    }else{
        lcd.print("#");
    }
    
}

bool isRedButtonPressed() 
{
  static int debounced_button_state = HIGH;
  static int previous_reading = HIGH;
  static unsigned long last_change_time = 0UL;
  bool isPressed = false;

  int current_reading = digitalRead(RED_BUTTON);

  if (previous_reading != current_reading) 
  {
    last_change_time = millis();
  }

  if (millis() - last_change_time > BUTTON_DEBOUNCE_PERIOD) {
    if (current_reading != debounced_button_state) {
      if (debounced_button_state == HIGH && current_reading == LOW) {
        isPressed = true;
      }
      debounced_button_state = current_reading;
    }
  }

  previous_reading = current_reading;

  return isPressed;
}

ISR(PCINT1_vect) {
    encoder1 = digitalRead(ENCODER1);
    encoder2 = digitalRead(ENCODER2);
    encoderTimestamp = millis();
}

int lastEn1 = LOW;
unsigned long lastChangeTimestamp = 0UL;

void setup() {
    pinMode(LED_RED, OUTPUT);
    pinMode(LED_GREEN, OUTPUT);
    pinMode(LED_BLUE, OUTPUT);
    clearLeds();

    pinMode(ENCODER1, INPUT_PULLUP);
    pinMode(ENCODER2, INPUT_PULLUP);

    pinMode(RED_BUTTON, INPUT_PULLUP);

    lcd.init();
    lcd.backlight();
    printMenu();

    PCICR |= (1 << PCIE1);
    PCMSK1 |= (1 << PCINT10);
}

void loop(){
    int en1;
    int en2;
    unsigned long timestamp;

    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        en1 = encoder1;
        en2 = encoder2;
        timestamp = encoderTimestamp;
    }

    if (en1 == LOW && timestamp > lastChangeTimestamp + ENCODER_DEBOUNCING_PERIOD) {
        if (en2 == HIGH) {
            if(menuMode){
                if (currentIndex < 3)
                    currentIndex += 1;
            } else {
                if (ledStates[currentIndex] < 255)
                    ledStates[currentIndex] += ENCODER_STEP;
            }
        } else {
            if(menuMode){
                if (currentIndex > 0)
                    currentIndex -= 1;
            } else {
                if(ledStates[currentIndex] > 0)
                    ledStates[currentIndex] -= ENCODER_STEP;
            }
        }
        lastChangeTimestamp = timestamp;
        
        updateLed();
        printMenu();
    }
    lastEn1 = en1;

    if (isRedButtonPressed()) 
    {
        if(currentIndex < 3)
            menuMode = !menuMode;
        else
            clearLeds();

        printMenu();      
    }
}