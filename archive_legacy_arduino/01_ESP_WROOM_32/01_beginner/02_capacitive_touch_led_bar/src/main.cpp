#include <Arduino.h>

// Pin Tanımlamaları
#define DOKUNMATIK_PIN 4       // T0 (GPIO 4) - Dokunmatik Elektrot / Jumper Kablo
#define HARICI_LED_PIN 16      // GPIO 16     - Durum Gösterge LED'i

int bosDeger = 0;
int esikDegeri = 0;

void setup() {
    Serial.begin(115200);
    delay(200);

    pinMode(HARICI_LED_PIN, OUTPUT);
    digitalWrite(HARICI_LED_PIN, LOW);

    // Açılış LED doğrulaması
    digitalWrite(HARICI_LED_PIN, HIGH);
    delay(300);
    digitalWrite(HARICI_LED_PIN, LOW);

    // Kapasitif Dokunmatik Kalibrasyonu (10 Örnek Ortalaması)
    Serial.println("ESP32 Dokunmatik Kalibrasyonu Baslatiliyor...");
    long toplam = 0;
    for (int i = 0; i < 10; i++) {
        toplam += touchRead(DOKUNMATIK_PIN);
        delay(50);
    }
    bosDeger = toplam / 10;
    esikDegeri = (int)(bosDeger * 0.70); // %70 eşik değeri

    Serial.print("Kalibrasyon Tamam. Bos Deger: ");
    Serial.print(bosDeger);
    Serial.print(" | Esik Degeri: ");
    Serial.println(esikDegeri);
}

void loop() {
    int anlikDeger = touchRead(DOKUNMATIK_PIN);

    // Dokunma Durumu Kontrolü
    if (anlikDeger < esikDegeri) {
        // DOKUNULDU!
        digitalWrite(HARICI_LED_PIN, HIGH);
        Serial.print("[DOKUNULDU] Ham Deger: ");
        Serial.println(anlikDeger);
    } else {
        // BOŞTA
        digitalWrite(HARICI_LED_PIN, LOW);
        Serial.print("[BOSTA]     Ham Deger: ");
        Serial.println(anlikDeger);
    }

    delay(50);
}