#include <Arduino.h>

#define MY_LED_PIN PB_5
#define MY_BTN_PIN PF_4

void setup(){
    pinMode(MY_LED_PIN, OUTPUT);
    pinMode(MY_BTN_PIN, INPUT_PULLUP);
}

void loop(){
    if (digitalRead(MY_BTN_PIN) == LOW){
        digitalWrite(MY_LED_PIN, HIGH);
    }else{
        digitalWrite(MY_LED_PIN, LOW);
    }
}

