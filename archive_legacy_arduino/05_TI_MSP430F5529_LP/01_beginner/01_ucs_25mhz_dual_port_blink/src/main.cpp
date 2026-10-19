#include <Arduino.h>

#define MY_LED_PIN P1_2
#define BTN_SOL    P2_1

void setup() {
    pinMode(MY_LED_PIN, OUTPUT);
    pinMode(BTN_SOL, INPUT_PULLUP);
}

void loop() {
    // Sol VEYA Sag butondan herhangi birine basilirsa yansin!
    if (digitalRead(BTN_SOL) == LOW){
        digitalWrite(MY_LED_PIN, HIGH);
    } else {
        digitalWrite(MY_LED_PIN, LOW);
    }
}