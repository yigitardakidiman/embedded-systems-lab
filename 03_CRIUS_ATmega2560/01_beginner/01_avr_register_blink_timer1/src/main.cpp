#include <Arduino.h>

void setup() {
    pinMode(2, OUTPUT);
    pinMode(13, OUTPUT);
    pinMode(30, OUTPUT);
    pinMode(31, OUTPUT);
}

void loop() {
    // 4 LED'i de AÇ
    digitalWrite(2, HIGH);
    digitalWrite(13, HIGH);
    digitalWrite(30, HIGH);
    digitalWrite(31, HIGH);
    delay(200);

    // 4 LED'i de KAPAT
    digitalWrite(2, LOW);
    digitalWrite(13, LOW);
    digitalWrite(30, LOW);
    digitalWrite(31, LOW);
    delay(200);
}