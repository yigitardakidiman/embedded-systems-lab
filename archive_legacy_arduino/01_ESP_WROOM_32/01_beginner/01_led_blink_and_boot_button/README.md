# 01 - ESP-WROOM-32: LED Blink ve BOOT Butonu Kontrolü

Bu proje, **ESP-WROOM-32 (ESP32-D0WD-V3)** geliştirme kartı için derleyici/yükleyici (`arduino-cli`) zincirini doğrulamak, temel dijital giriş/çıkış (**GPIO**) yapılandırmasını öğrenmek ve dahili **Pull-Up** direnci kullanarak buton okumak amacıyla geliştirilmiştir.

---

## 🎯 Projenin Amacı ve Öğrenilen Kavramlar

1. **Toolchain & CLI Doğrulaması:** VS Code üzerinden `arduino-cli` kullanarak saf C++ (`main.cpp`) kodunu derleme (`compile`) ve `esptool` aracılığıyla `COM4` portundan ESP32 Flash belleğine yazma (`upload`).
2. **GPIO Dijital Çıkış (`OUTPUT`):** `GPIO 25` pininden `3.3V` (`HIGH`) ve `0V` (`LOW`) lojik seviyeleri üreterek akım sınırlama direnci üzerinden harici LED sürme.
3. **Dahili Pull-Up Giriş (`INPUT_PULLUP`) ve Active-Low Mantığı:** Kart üzerindeki yerleşik `BOOT` butonunun bağlı olduğu `GPIO 0` pinini dahili pull-up direnciyle okuma (basılmadığında `HIGH`, basıldığında `LOW`).
4. **Breadboard Yerleşim Pratiği:** Geniş form faktörlü ESP32 kartını breadboard deliklerini kapatmadan dişi-erkek jumper kablolarla harici devreye bağlama.

---

## 🛠️ Kullanılan Malzemeler

| Malzeme | Adet / Değer | Açıklama |
| :--- | :---: | :--- |
| **ESP-WROOM-32** | 1 | 240 MHz Çift Çekirdek Xtensa LX6 (`ESP32-D0WD-V3`) |
| **Breadboard** | 1 | Devre kurulum tablası |
| **Kırmızı LED** | 1 | Harici durum göstergesi (`GPIO 25`) |
| **Direnç** | 1 × `220Ω` / `330Ω` | LED akım sınırlama direnci |
| **Jumper Kablo** | 2 × Dişi-Erkek | ESP32 pinlerini breadboard'a taşımak için |

---

## 🔌 Pin Bağlantı Tablosu ve Devre Şeması (Active-Low / Current Sinking)

Devrede **Current Sinking (Akım Çekme / Active-Low)** topolojisi kullanılmıştır: Besleme `3.3V` hattından direnç üzerinden LED'in uzun bacağına (`+` Anot) verilir; LED'in kısa bacağı (`-` Katot) ise `GPIO 25` pinine bağlanır. Böylece `GPIO 25` pini `LOW (0V)` olduğunda devre tamamlanarak LED yanar, `HIGH (3.3V)` olduğunda ise iki uç arasındaki gerilim farkı sıfırlandığı için LED söner.

| ESP32 Pini | Bağlantı Noktası | Yön / Mod | Açıklama |
| :--- | :--- | :--- | :--- |
| **`3V3` (`3.3V`)** | Direnç $\rightarrow$ LED Uzun Bacak (`+` Anot) | `VCC (+3.3V)` | Sabit `+3.3V` anot beslemesi |
| **`GPIO 25` (`D25`)** | LED Kısa Bacak (`-` Katot) | `OUTPUT` | `LOW (0V)` verildiğinde akımı çeker (LED Yanar), `HIGH (3.3V)` verildiğinde LED Söner |
| **`GPIO 0` (`BOOT`)** | Kart üzerindeki `BOOT` tuşu | `INPUT_PULLUP` | Basılmadığında `HIGH (1)`, basıldığında `LOW (0)` |

### ASCII Devre Şeması:
```text
      +3.3V / 0V
   (GPIO 25 / D25)
          │
          ├───[ 330Ω Direnç ]───( + Anot )
          │                         │
          │                       [LED]
          │                         │
          │                     ( - Katot )
          │                         │
         GND ───────────────────────┘
```

---

## 💻 Geliştirme Aşamaları ve Kodlar

Proje iki aşamada uygulanmıştır:

### Aşama 1: Periyodik LED Blink (İlk Kıvılcım)
LED'in `500 ms` aralıklarla (1 Hz frekansında) otomatik olarak yanıp sönmesini sağlayan temel kod:

```cpp
#include <Arduino.h>

#define MY_LED_PIN 25

void setup() {
    pinMode(MY_LED_PIN, OUTPUT);
}

void loop() {
    digitalWrite(MY_LED_PIN, HIGH);
    delay(500);
    digitalWrite(MY_LED_PIN, LOW);
    delay(500);
}
```

### Aşama 2: `BOOT` Butonu ile LED Kontrolü ([`src/main.cpp`](src/main.cpp))
Kart üzerindeki `BOOT` (`GPIO 0`) butonunun durumunu okuyarak LED'i kontrol eden güncel kod:

```cpp
#include <Arduino.h>

#define MY_LED_PIN 25
#define BOOT_BTN 0

void setup() {
    pinMode(BOOT_BTN, INPUT_PULLUP);
    pinMode(MY_LED_PIN, OUTPUT);
}

void loop() {
    int butondurumu = digitalRead(BOOT_BTN);

    if (butondurumu == LOW) {
        digitalWrite(MY_LED_PIN, LOW);
    } else {
        digitalWrite(MY_LED_PIN, HIGH);
    }
}
```

---

## 🚀 Derleme ve Karta Yükleme Komutları (`arduino-cli`)

Ana proje dizinindeyken (`embedded-systems-lab/`):

```powershell
# Sadece derlemek (Compile) için:
arduino-cli compile --fqbn esp32:esp32:esp32 01_ESP_WROOM_32/01_beginner/01_led_blink_and_boot_button/src

# Derleyip doğrudan COM4 portundaki ESP32'ye yüklemek için:
arduino-cli compile -u -p COM4 --fqbn esp32:esp32:esp32 01_ESP_WROOM_32/01_beginner/01_led_blink_and_boot_button/src
```

---

## 📸 Uygulama Görselleri

| Aşama 1: Periyodik LED Blink (`delay.JPEG`) |
| :---: |
| ![ESP32 LED Blink Devresi](media/delay.JPEG) |


