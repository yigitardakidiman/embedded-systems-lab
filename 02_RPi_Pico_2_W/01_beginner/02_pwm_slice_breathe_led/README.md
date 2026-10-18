# 02 - Raspberry Pi Pico 2 W: Donanım PWM ile LED Nefes Alma Efekti (Tek ve Çift LED)

Bu proje, **Raspberry Pi Pico 2 W (RP2350)** mikrodenetleyicisinin dâhili **Donanımsal PWM (Pulse Width Modulation)** çevrebirimini kullanarak önce tek bir LED'in, ardından iki bağımsız LED'in parlaklığını kademeli olarak artırıp azaltmak (*Fade In / Fade Out - Nefes Alma Efekti*) ve sırayla yönetmek amacıyla geliştirilmiştir.

---

## 🎯 Projenin Amacı ve Öğrenilen Kavramlar

1. **`digitalWrite()` vs `analogWrite()` Ayrımı:**
   - `digitalWrite`: Pini sadece tam açık (`HIGH - 3.3V`) veya tam kapalı (`LOW - 0V`) yapar.
   - `analogWrite`: İşlemcinin donanımsal PWM dilimini devreye sokarak pini saniyede binlerce kez açıp kapatır ve `0 - 255` arasında ara parlaklık seviyeleri oluşturur.
2. **PWM (Darbe Genişlik Modülasyonu) ve Duty Cycle:**
   - Sinyalin periyot boyunca ne kadar süre `HIGH` kaldığına **Görev Döngüsü (Duty Cycle)** denir.
   - İnsan gözü bu anahtarlama hızını fark edemediğinden sinyalin doluluk oranını ortalama bir ışık şiddeti olarak algılar.
3. **Fiziksel Pin Numarası vs. GPIO Numarası:**
   - Bordun üzerindeki 15. sıradaki delik fiziksel Pin 15 olup `GP11`'e bağlıdır.
   - Kodda tanımlanan **`GP15` pini bordun sol en alt köşesindeki 20. pindir.**
4. **Breadboard Ortak Toprak (GND) Paylaşımı:**
   - İki farklı devrenin ortak eksi kutbunu breadboard'un mavi eksi (`-`) şeridine bağlayarak tek bir `GND` pini üzerinden birden fazla çıkışı besleme mantığı kavranmıştır.
5. **Çoklu PWM Kanalı Yönetimi:**
   - Peş peşe kurulan `for` döngüleriyle birden fazla GPIO çıkışını (`GP15` ve `GP14`) sıralı ve senkronize biçimde sürme pratiği yapılmıştır.

---

## 🛠️ Kullanılan Malzemeler

| Malzeme | Adet / Değer | Açıklama |
| :--- | :---: | :--- |
| **Raspberry Pi Pico 2 W** | 1 | RP2350 Mikrodenetleyici (Çift Çekirdek) |
| **Breadboard** | 1 | Devre kurulum tablası |
| **Renkli LED'ler** | 2 | PWM durum göstergeleri (1. LED ve 2. LED) |
| **Direnç** | 2 × `220Ω` / `330Ω` | Akım sınırlama dirençleri |
| **Jumper Kablo** | 3 × Erkek-Erkek | Sinyal ve ortak GND bağlantıları |

---

## 🔌 Pin Bağlantı Tablosu ve Devre Şeması

| Pico 2 W Pini | Konum / Ped Tipi | Breadboard Bağlantısı | Açıklama |
| :--- | :--- | :--- | :--- |
| **`GP15` (Pin 20)** | Sol en alt köşe (Yuvarlak `o` ped) | 1. Direnç $\rightarrow$ 1. LED Uzun Bacak (`+` Anot) | 1. LED PWM sinyal hattı |
| **`GP14` (Pin 19)** | Sol alttan 2. delik (Yuvarlak `o` ped) | 2. Direnç $\rightarrow$ 2. LED Uzun Bacak (`+` Anot) | 2. LED PWM sinyal hattı |
| **`GND` (Pin 18)** | Sol alttan 3. delik (Kare `■` ped) | Breadboard Mavi Eksi (`-`) Şeridi $\rightarrow$ Katotlar | Ortak toprak (GND) hattı |

### ASCII Devre Şeması:
```text
Pico (GP15 - Sol En Alt)   ───[ 330Ω Direnç ]───( + 1. LED Uzun Bacak )
                                                       │
Pico (GP14 - Sol Alttan 2) ───[ 330Ω Direnç ]───( + 2. LED Uzun Bacak )
                                                       │
Pico (GND  - Sol Alttan 3) ───[ Mavi (-) Şerit ]───( - İki LED'in Kısa Bacakları )
```

---

## 💻 Geliştirme Aşamaları ve Kodlar

Proje iki aşamada geliştirilmiştir:

### Aşama 1: Tek LED ile Donanım PWM Nefes Alma
Sadece `GP15` pinine bağlı LED'in `0`'dan `255`'e parlayıp ardından `255`'ten `0`'a söndüğü temel kod:

```cpp
#include <Arduino.h>

#define MY_LED_PIN 15

void setup() {
    pinMode(MY_LED_PIN, OUTPUT);
}

void loop() {
    for (int i = 0; i <= 255; i++){
        analogWrite(MY_LED_PIN, i);
        delay(5);
    }

    for(int i = 255; i >= 0; i--){
        analogWrite(MY_LED_PIN, i);
        delay(5);
    }
}
```

---

### Aşama 2: Çift LED ile Sırayla PWM Nefes Alma ([`src/main.cpp`](src/main.cpp))
Önce 1. LED'in (`GP15`) parlayıp söndüğü, o tamamen bittiğinde 2. LED'in (`GP14`) parlayıp söndüğü nihai sıralı kod:

```cpp
#include <Arduino.h>

#define LED1_PIN 15
#define LED2_PIN 14

void setup() {
    pinMode(LED1_PIN, OUTPUT);
    pinMode(LED2_PIN, OUTPUT);
}

void loop() {
    // 1. LED Nefes Alma Döngüsü
    for (int i = 0; i <= 255; i++){
        analogWrite(LED1_PIN, i);
        delay(5);
    }
    for(int i = 255; i >= 0; i--){
        analogWrite(LED1_PIN, i);
        delay(5);
    }

    // 2. LED Nefes Alma Döngüsü
    for (int i = 0; i <= 255; i++){
        analogWrite(LED2_PIN, i);
        delay(5);
    }
    for(int i = 255; i >= 0; i--){
        analogWrite(LED2_PIN, i);
        delay(5);
    }
}
```

---

## 🚀 Derleme ve Karta Yükleme Komutları (`arduino-cli`)

Ana proje dizinindeyken (`embedded-systems-lab/`):

```powershell
# Sadece derlemek (Compile) için:
arduino-cli compile --fqbn rp2040:rp2040:rpipico2w 02_RPi_Pico_2_W/01_beginner/02_pwm_slice_breathe_led/src

# Derleyip COM6 portundaki Pico 2 W'ya yüklemek için:
arduino-cli compile -u -p COM6 --fqbn rp2040:rp2040:rpipico2w 02_RPi_Pico_2_W/01_beginner/02_pwm_slice_breathe_led/src
```

---

## 📸 Uygulama Görselleri ve Videoları

| Aşama 1: Tek LED Nefes Alma | Aşama 2: Çift LED Sırayla Nefes Alma |
| :---: | :---: |
| [🎬 **breath.mp4 Videosunu İzle (Tıklayınız)**](media/breath.mp4) | [🎬 **breath2.mp4 Videosunu İzle (Tıklayınız)**](media/breath2.mp4) |
| *1. LED'in donanımsal PWM ile tek başına nefes alma döngüsü* | *1. ve 2. LED'lerin sırayla ve pürüzsüzce nefes alıp vermesi* |
