# 🛠️ Embedded Systems Lab 

Sıfırdan ileri seviyeye kadar **8-bit AVR**, **16-bit RISC (MSP430)**, **32-bit ARM Cortex-M (M0+/M4F/M33/M7)**, **Xtensa LX6**, **RISC-V (Hazard3)**, **Gömülü Linux** ve **FPGA (Verilog)** mimarilerini kapsayan uygulamalı gömülü sistemler laboratuvarı ve proje portföyü.

Laboratuvar envanterindeki **11 geliştirme kartının** her biri için **4 Başlangıç**, **4 Orta** ve **4 İleri Seviye** olmak üzere toplam **132 özgün donanım/yazılım projesi** hedeflenmektedir.

> 📖 Tüm 132 projenin detaylı teknik açıklamaları ve donanım notları için: **[132 Proje Rehberi ve Klasör Şeması](00_docs/proje_semasi_ve_132_proje_rehberi.md)**

---

## 📊 Proje İlerleme Matrisi

> 💡 **Başlangıç Seviyesi (P1..P4) Pedagojik Yapısı:**
> - **P1:** Dijital Giriş/Çıkış (GPIO Blink & Buton Okuma)
> - **P2:** Analog Çıkış / PWM (LED Parlaklık & Nefes Alma Efekti)
> - **P3:** Analog Giriş / ADC (Potansiyometre veya Tek Sensör Okuma)
> - **P4:** Temel İletişim & Ekran (I2C ve 0.91" OLED Göstergesi)

Laboratuvarda **Dikey (Kart Bazlı) İlerleme Modeli** izlenmektedir. İlk olarak **ESP-WROOM-32** platformunda yerel ESP-IDF ile `P1..P12` projeleri sırasıyla tamamlanacak, ardından sıradaki karta geçilecektir. Tamamlanan projelerin üzerindeki ✅ işaretine tıklayarak ilgili proje klasörüne gidebilirsiniz:

| # | Geliştirme Kartı | Mimari / Çekirdek | P1 (Blink) | P2 | P3 | P4 | P5 | P6 | P7 | P8 | P9 | P10 | P11 | P12 |
| :-: | :--- | :--- | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: |
| **01** | **ESP-WROOM-32** | Dual Xtensa LX6 (240 MHz, Wi-Fi/BLE) | [✅](01_ESP_WROOM_32/01_beginner/01_led_blink_and_boot_button/) | [✅](01_ESP_WROOM_32/01_beginner/02_capacitive_touch_led_bar/) | [✅](01_ESP_WROOM_32/01_beginner/03_ledc_pwm_breathe_led/) | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ |
| **02** | **Raspberry Pi Pico 2 W** | RP2350 (Dual Cortex-M33 / RISC-V + PIO) | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ |
| **03** | **CRIUS ALL IN ONE PRO** | 8-Bit AVR ATmega2560 (Flight Controller) | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ |
| **04** | **TI MSP-EXP430G2** | 16-Bit Ultra-Low-Power RISC (512B RAM) | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ |
| **05** | **TI MSP430F5529 LP** | 16-Bit RISC (25 MHz, DMA, USB, 12-Bit ADC) | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ |
| **06** | **TI EK-TM4C123GXL** | 32-Bit ARM Cortex-M4F (80 MHz, FPU, NVIC) | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ |
| **07** | **ST NUCLEO-U575ZI-Q** | 32-Bit ARM Cortex-M33 (ULP, SMPS, TrustZone) | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ |
| **08** | **ST P-NUCLEO-WB55** | Dual ARM Cortex-M4 + Cortex-M0+ (BLE 5.0) | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ |
| **09** | **ST NUCLEO-H723ZG** | 32-Bit ARM Cortex-M7 (550 MHz, Double FPU, DSP) | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ |
| **10** | **Raspberry Pi Zero W** | ARM11 BCM2835 (1 GHz, Embedded Linux) | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ |
| **11** | **Tang Nano 9K FPGA** | Gowin GW1NR-9 FPGA (8640 LUT, Verilog) | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ |

---

## 🧰 Laboratuvar Envanteri

| Kategori | Donanım ve Modüller |
| :--- | :--- |
| **Ekranlar** | `0.96" 80x160 RGB IPS Ekran` (SPI), `0.91" 128x32 OLED Ekran` (I2C) |
| **Hareket & Mesafe** | `Pololu AltIMU-10 v5` (10-DOF IMU), `MPU6050` (6-DOF IMU), `HC-SR04` (Ultrasonik Mesafe) |
| **Çevresel Sensörler** | `MLX90614 V1.0` (IR Termometre), `GY-BMP280` (Basınç/Sıcaklık), `BMP180` (Basınç/Sıcaklık), `DHT11` (Sıcaklık/Nem) |
| **Ses & Görüntü** | `MAX4466` (Kazançlı Mikrofon Amfisi), `Mikrofon Modülü` (Analog/Dijital Eşikli), `RPi Camera Multiplexer` |
| **Güç & Sürücüler** | `Motor Sürücüsü`, `HW-070` (PWM Kontrolcü), `HW-131` (3.3V/5V Breadboard Güç), `LiPo Şarj Entegresi` |
| **Pasif Bileşenler** | `1x Breadboard`, `40x LED` (Kırmızı, Mavi, Sarı, Yeşil), `70x Direnç` (`220Ω`, `330Ω`, `1kΩ`, `10kΩ`, `100kΩ`, `1MΩ`) |

---

## 📂 Klasör Yapısı

```text
embedded-systems-lab/
├── 00_docs/                           # Envanter listesi ve 132 proje rehberi
├── 01_ESP_WROOM_32/                   # ESP32 projeleri (01_beginner, 02_intermediate, 03_advanced)
├── 02_RPi_Pico_2_W/                   # Raspberry Pi Pico 2 W (RP2350) projeleri
├── 03_CRIUS_ATmega2560/               # CRIUS All In One Pro (AVR) projeleri
├── 04_TI_MSP430G2553/                 # TI MSP-EXP430G2 projeleri
├── 05_TI_MSP430F5529_LP/              # TI MSP430F5529 LaunchPad projeleri
├── 06_TI_TM4C123GXL_TivaC/            # TI Tiva C LaunchPad projeleri
├── 07_ST_NUCLEO_U575ZI_Q/             # STM32U575ZI-Q projeleri
├── 08_ST_P_NUCLEO_WB55/               # STM32WB55 BLE projeleri
├── 09_ST_NUCLEO_H723ZG/               # STM32H723ZG (Cortex-M7) projeleri
├── 10_RPi_Zero_W_Linux/               # Raspberry Pi Zero W Gömülü Linux projeleri
└── 11_Tang_Nano_9K_FPGA/              # Tang Nano 9K FPGA (Verilog) projeleri
```

Her proje klasörü kendi içinde standart olarak `README.md` (devre şeması ve pin tablosu), `src/` (kaynak kodlar) ve `media/` (uygulama fotoğrafları/videoları) dizinlerini barındırır.

