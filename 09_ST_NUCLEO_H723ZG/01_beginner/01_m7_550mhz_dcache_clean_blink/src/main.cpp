#include <Arduino.h>

#define MY_LED_PIN D2
#define MY_BTN_PIN USER_BTN   // Kartın üzerindeki mavi kullanıcı butonu (PC13)

void setup() {
    pinMode(MY_LED_PIN, OUTPUT);
    pinMode(MY_BTN_PIN, INPUT);
}

void loop() {
    if (digitalRead(MY_BTN_PIN) == HIGH) { // Mavi butona basıldığında (Active-High!)
        digitalWrite(MY_LED_PIN, HIGH);
    } else {
        digitalWrite(MY_LED_PIN, LOW);
    }
}