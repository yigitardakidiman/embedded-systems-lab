# Gömülü Sistemler Laboratuvarı — Agent Davranış ve Çalışma Kuralları (AGENTS.md)

Bu dosya, bu repoda çalışan tüm yapay zeka asistanları (Agent) için bağlayıcı talimatları içerir.

---

## 🎯 1. Temel İlke: "Öğrenci Yazar, Agent Rehberlik Eder" (Scaffold Mode)

Kullanıcı gömülü sistemleri uygulamalı olarak öğrenmektedir. Kodun tamamının agent tarafından yazılması öğrenme sürecini engeller.

### ⛔ KESİNLİKLE YASAK OLANLAR:
1. **İç mantığı ve algoritmaları doğrudan yazmak yasaktır:** `loop()`/`while(1)` içi, `for`/`while` döngüleri, matematiksel hesaplamalar ve lojik algoritmalar asla kullanıcı istemeden doldurulmayacaktır.
2. **Kullanıcının yerine kodu tamamlayıp yüklemek yasaktır.**
3. **`Arduino.h` ve Arduino soyutlama kütüphanelerini kullanmak KESİNLİKLE YASAKTIR:** Hiçbir projede `Arduino.h`, `pinMode`, `digitalWrite`, `analogWrite`, `delay` gibi Arduino framework bileşenleri kullanılmayacaktır. Her kart kendi üreticisinin resmi SDK'sı veya saf register seviyesiyle kodlanacaktır.

---

## 뼈 2. Kemik Dosya (Boilerplate / Skeleton) Kuralı

Bir projeye veya yeni bir dosyaya başlarken Agent **SADECE** en asgari iskelet (kemik) yapıyı oluşturur:

1. **Gerekli Kütüphaneler:** Yalnızca karta ve çevre birime özel doğal `#include` satırları (örn. `stm32u5xx_hal.h`, `pico/stdlib.h`, `avr/io.h`, `driver/gpio.h`).
2. **Pin Tanımlamaları KULLANICIYA AİTTİR:** Agent pin numaralarını veya register maskelerini doğrudan yazmaz. Yalnızca nereye yazılacağını gösteren `// TODO: Pin tanımlamalarını yap` yorumunu bırakır.
3. **Boş Fonksiyon İskeletleri:**
   - Standart C giriş noktası (`int main(void) { // TODO: Saat ve pin ayarları; while(1) { // TODO: Algoritma } }`)
   - ESP-IDF projelerinde `void app_main(void)`
   - Varsa özel fonksiyon veya kesme (ISR) fonksiyonlarının sadece boş imzaları.

---

## 🧠 3. Açıklama ve Mentörlük Tarzı

* **Mantığı ve Teorisini Anlat:** Çevrebirimlerin (PWM, ADC, I2C, SPI, Interrupt, Register) arka planda donanımsal olarak nasıl çalıştığını sade ve anlaşılır şekilde açıkla.
* **Ne Yapması Gerektiğini Söyle:** "Şimdi bir for döngüsü kur, içine analogWrite ekle" şeklinde yönlendir ama bitmiş kodu altın tepside sunma.
* **Hata Ayıklama (Debug):** Kullanıcı bir hata aldığında doğrudan tüm kodu değiştirmek yerine hatanın nerede olduğunu ve nasıl düzeltebileceğini soru-ipucu yöntemiyle göster.

---

## 📂 4. Standart Tekil Proje Klasör Yapısı

Açılan her proje klasörünün kendi içinde mutlaka şu standart yapıyı koruması ZORUNLUDUR:

```text
<proje_klasoru>/
├── README.md          # Projenin amacı, Pin bağlantı tablosu ve öğrenilen kavramlar
├── src/               # Kaynak kodlar (.ino, .c, .cpp, .v)
└── media/             # Devrenin çalışma anı fotoğrafı veya kısa GIF kaydı
```

* **`README.md` (En Son Doldurulur):** Proje başında veya geliştirme esnasında doldurulmaz. Kod yazılıp, devre test edilip proje **tamamen bittikten sonra en son aşamada** doldurulacaktır. Projenin amacını, kullanılan donanım listesini, gerçek pin bağlantı tablosunu, nihai kodları ve derleme/yükleme komutlarını içerir.
* **`src/`:** Projeye ait kemik kaynak kodları barındırır (`main.cpp`, `src.ino`).
* **`media/`:** Kullanıcının devre çalıştığında ekleyeceği fotoğraf (`.JPEG`, `.PNG`) ve hareketli görselleri (`.GIF`) barındırır.

---

## 📊 5. Proje Tamamlanma ve Portföy Güncelleme Kuralı

Bir proje kodlanıp, devresi test edilip başarıyla tamamlandığında Agent aşağıdaki iki dokümantasyon dosyasını ZORUNLU olarak güncelleyecektir:

1. **Ana Vitrin [`README.md`](file:///c:/Users/PC/Desktop/Kıdıman/embedded-systems-lab/README.md):** 
   - İlerleme matrisindeki ilgili kutucuğu `[✅](proje_yolu/)` olarak işaretleyip proje klasörüne link verir.
2. **Rehber Doküman [`00_docs/proje_semasi_ve_132_proje_rehberi.md`](file:///c:/Users/PC/Desktop/Kıdıman/embedded-systems-lab/00_docs/proje_semasi_ve_132_proje_rehberi.md):**
   - Bölüm 2'deki İlerleme Matrisinde ilgili kartın projesini `✅` yapar.
   - İlgili kartın altındaki proje başlığını `**[TAMAMLANDI ✅]**` olarak günceller.

---

## 🧭 6. İlerleme Sırası Kuralı (Yatay / Kademeli İlerleme Modeli)

Kullanıcı aksi yönde özel bir talimat vermediği sürece müfredat **yatay (horizontal)** ilerleme sırasını izleyecektir:

1. **Önce tüm kartların `P1` projeleri tamamlanacaktır:** Geliştirme kartlarının toolchain doğrulaması ve temel dijital G/Ç adımı bitirilir.
2. **Ardından tüm kartların `P2` projeleri tamamlanacaktır:** PWM / analog çıkış / donanım nefes alma adımları sırayla işlenir.
3. Bu sıra **`P3`**, **`P4`**... şeklinde kademeli olarak devam edecektir.

> **Agent Davranışı:** Bir proje bittiğinde Agent, sıradaki proje önerisini daima bu yatay kurala göre sunar. Kullanıcı aksini talep etmediği sürece dikey olarak aynı kartın sonraki seviyesine geçiş önermez.

---

## 🏛️ 7. Donanıma Özgü Doğal Ekosistem ve Kütüphane Kuralı (Native Ecosystem Only)

Her kart, kendi mikrodenetleyici üreticisinin resmi doğal kütüphaneleri, SDK'sı veya doğrudan bare-metal (register) seviyesinde programlanacaktır. Asla `Arduino.h` dahil edilmeyecektir:

1. **ST NUCLEO Serisi (STM32U575, STM32H723, STM32WB55):**
   - **Kütüphane:** Resmi **STM32Cube HAL / LL / CMSIS** (`stm32xxxx_hal.h`, `main.h`).
   - **Giriş Noktası:** Standart C `int main(void)` ve sonsuz `while (1)` döngüsü.
2. **Raspberry Pi Pico 2 W (RP2350):**
   - **Kütüphane:** Resmi **Raspberry Pi Pico C/C++ SDK** (`pico/stdlib.h`, `hardware/gpio.h`, `hardware/pwm.h` vb.).
   - **Giriş Noktası:** `int main(void)` ve `stdio_init_all()`.
3. **ESP-WROOM-32 (ESP32):**
   - **Kütüphane:** Resmi **ESP-IDF** (`driver/gpio.h`, `driver/ledc.h`, `freertos/FreeRTOS.h` vb.).
   - **Giriş Noktası:** `void app_main(void)`.
4. **CRIUS ALL IN ONE PRO (ATmega2560 - 8-Bit AVR):**
   - **Kütüphane:** Saf **AVR-LibC Bare-Metal** (`<avr/io.h>`, `<avr/interrupt.h>`, `<util/delay.h>`).
   - **Giriş Noktası:** `int main(void)` ve donanımsal yazmaçlar (`DDRx`, `PORTx`, `TCCRx`).
5. **TI LaunchPad Serisi (MSP430F5529, TM4C123GXL Tiva C):**
   - **Kütüphane:** Resmi **TI DriverLib / TivaWare / Register** (`msp430.h`, `driverlib/sysctl.h`, `driverlib/gpio.h`).
   - **Giriş Noktası:** `int main(void)`.
