#include <Arduino.h>

#define MY_LED_PIN 15

void setup() {
    pinMode(MY_LED_PIN, OUTPUT);
}

void loop() {
    if(BOOTSEL){
        digitalWrite(MY_LED_PIN, HIGH);
    }else{
        digitalWrite(MY_LED_PIN, LOW);
    }
}

