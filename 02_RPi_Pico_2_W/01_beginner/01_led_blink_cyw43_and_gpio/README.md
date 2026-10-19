# Raspberry Pi Pico 2 W — Proje 1: Doğal Pico C/C++ SDK ile Dahili CYW43 LED ve Harici GPIO LED Sürüşü

Bu proje, **Raspberry Pi Pico 2 W (RP2350)** geliştirme kartı üzerinde **Arduino soyutlaması olmadan**, tamamen Raspberry Pi'ın resmi **Pico C/C++ SDK v2.3.1** framework'ü kullanılarak geliştirilmiştir. 

Pico 2 W'nin kablosuz iletişim çipi üzerindeki dahili LED (CYW43) ile mikrodenetleyicinin doğrudan SIO veri yolu üzerindeki harici bir GPIO LED'i eşzamanlı olarak periyodik olarak yakılıp söndürülmüştür.

---

## 📸 Devre ve Çalışma Görseli

![Devre Kurulumu](media/circuit.jpg)

---

## 🛠️ Donanım Gereksinimleri

* 1 × **Raspberry Pi Pico 2 W** Geliştirme Kartı (RP2350 Dual-Core Cortex-M33 / RISC-V @ 150 MHz)
* 1 × **Kırmızı LED** (5mm)
* 1 × **220Ω - 330Ω Direnç** (Akım sınırlayıcı)
* 1 × **Breadboard** ve Jumper Kablolar
* 1 × **Dahili CYW43 LED** (Kart üzerindeki Infineon CYW43439 Wi-Fi modülüne bağlı)

---

## 🔌 Pin Bağlantı Şeması

| Bileşen | Pin / Bacak | Pico 2 W Pin (Fiziksel) | Açıklama |
| :--- | :--- | :--- | :--- |
| **Dahili LED** | CYW43439 WL_GPIO0 | **Dahili (Onboard)** | CYW43 Wi-Fi çipi üzerinden kontrol edilir (`CYW43_WL_GPIO_LED_PIN`) |
| **Harici LED** | Anot (+) Uzun Bacak | **GP15 (Fiziksel Pin 20)** | Doğrudan RP2350 Dijital Çıkış (`GPIO_OUT`) |
| **Harici LED** | Katot (-) Kısa Bacak | **GND (Fiziksel Pin 23)** | 220Ω Direnç üzerinden toprağa bağlı |

---

## 🧠 Öğrenilen Temel Kavramlar & Teori

1. **Pico 2 W Dahili LED Mimarisi (`pico/cyw43_arch.h`):**
   * Standart Pico'da dahili LED doğrudan GPIO 25'e bağlıyken, Pico 2 W'da Wi-Fi çipine (CYW43439) bağlıdır.
   * Bu LED'i sürmek için önce `cyw43_arch_init()` fonksiyonuyla çip başlatılmalı, ardından `cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, seviye)` ile kontrol edilmelidir.
2. **RP2350 SIO Donanım Veriyolu (`hardware/gpio.h`):**
   * Harici LED pinleri RP2350'nin tek çevrimde erişilen SIO (Single-Cycle IO) veriyolu üzerinden yönetilir.
   * `gpio_init(pin)`: Pini donanımsal GPIO moduna alır.
   * `gpio_set_dir(pin, GPIO_OUT)`: Pini dijital çıkış yapar.
   * `gpio_put(pin, level)`: Çıkışa lojik 0 (0V) veya lojik 1 (3.3V) yazar.
3. **Zamanlama (`pico/stdlib.h`):**
   * `sleep_ms(milisaniye)`: Düşük güç tüketimli donanım sayacı (Hardware Timer) tabanlı bekleme fonksiyonu.
4. **UF2 (USB Flashing Format) ve Bootloader:**
   * Kart `BOOTSEL` basılı takıldığında depolama birimi (`RPI-RP2`) olarak açılır. Derlenen `.uf2` dosyası bu birime kopyalandığında donanımsal bootloader flaş belleği otomatik programlar ve kartı yeniden başlatır.

---

## 💻 Kaynak Kod (`main.c`)

```c
#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "hardware/gpio.h"

// Harici LED pini (Pico 2 W Fiziksel Pin 20 -> GP15)
#define EXTERNAL_LED_PIN 15

int main(void) {
    // 1. USB Seri iletisimini baslat
    stdio_init_all();

    // 2. Pico 2 W dahili Wi-Fi/Bluetooth cipini (CYW43) baslat
    if (cyw43_arch_init()) {
        printf("Hata: CYW43 cipi baslatilamadi!\n");
        return -1;
    }

    // 3. Harici LED pinini baslat ve cikis (GPIO_OUT) olarak ayarla
    gpio_init(EXTERNAL_LED_PIN);
    gpio_set_dir(EXTERNAL_LED_PIN, GPIO_OUT);

    // 4. Sonsuz dongude iki LED'i periyodik olarak yakip sondur
    while (true) {
        // Dahili LED ve Harici LED'i AÇ
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
        gpio_put(EXTERNAL_LED_PIN, 1);
        sleep_ms(500);

        // Dahili LED ve Harici LED'i KAPAT
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
        gpio_put(EXTERNAL_LED_PIN, 0);
        sleep_ms(500);
    }

    return 0;
}
```

---

## 🔨 Derleme ve Karta Yükleme (Terminalden)

Proje dizininde terminalden şu komutlarla inşa edilir:

```powershell
# 1. CMake Yapılandırması (Ninja ile)
cmake -B build -G Ninja -DPICO_BOARD=pico2_w

# 2. Derleme
ninja -C build

# 3. Karta Yükleme
# Üretilen build/01_led_blink_cyw43_and_gpio.uf2 dosyasını
# BOOTSEL ile bağlanan RPI-RP2 sürücüsüne kopyalayın.
```
