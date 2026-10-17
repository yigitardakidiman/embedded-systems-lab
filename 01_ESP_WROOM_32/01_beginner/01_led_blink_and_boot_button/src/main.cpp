#include <Arduino.h>

#define MY_LED_PIN 25
#define BOOT_BTN 0

void setup(){
    pinMode(BOOT_BTN, INPUT_PULLUP);
    pinMode(MY_LED_PIN, OUTPUT);
}

void loop(){
    int butondurumu = digitalRead(BOOT_BTN);

    if (butondurumu == LOW){
        digitalWrite(MY_LED_PIN, LOW);
    }else{
        digitalWrite(MY_LED_PIN, HIGH);
    }
}