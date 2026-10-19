#include <Arduino.h>

#define EXT_LED D2

void setup() {
    pinMode(EXT_LED, OUTPUT);
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(LED3, OUTPUT);

    pinMode(SW1_BTN,INPUT_PULLUP);
    pinMode(SW2_BTN,INPUT_PULLUP);
    pinMode(SW3_BTN,INPUT_PULLUP);
}

void loop() {

    if (digitalRead(SW1_BTN) == LOW) {
        digitalWrite(LED1, HIGH);
        digitalWrite(EXT_LED, HIGH);
    } else {
        digitalWrite(LED1, LOW);
        digitalWrite(EXT_LED, LOW);
    }
    // 2. Buton (SW2) -> Yeşil LED
    if (digitalRead(SW2_BTN) == LOW) {
        digitalWrite(LED2, HIGH);
    } else {
        digitalWrite(LED2, LOW);
    }
    // 3. Buton (SW3) -> Kırmızı LED
    if (digitalRead(SW3_BTN) == LOW) {
        digitalWrite(LED3, HIGH);
    } else {
        digitalWrite(LED3, LOW);
    }
}