#include <Arduino.h>

#define LED1_PIN 15
#define LED2_PIN 14

void setup() {
    pinMode(LED1_PIN, OUTPUT);
    pinMode(LED2_PIN, OUTPUT);
}

void loop() {
    for (int i = 0; i <= 255; i++){
        analogWrite(LED1_PIN, i);
        delay(5);
    }

    for(int i = 255; i >= 0; i--){
        analogWrite(LED1_PIN, i);
        delay(5);
    }

    for (int i = 0; i <= 255; i++){
        analogWrite(LED2_PIN, i);
        delay(5);
    }

    for(int i = 255; i >= 0; i--){
        analogWrite(LED2_PIN, i);
        delay(5);
    }
}
