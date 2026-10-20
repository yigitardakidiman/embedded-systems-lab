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
2. **Pin Tanımlamaları KULLANICIYA AİTTİR:** Agent pin numaralarını, register maskelerini veya `// TODO` gibi herhangi bir yorum satırını kesinlikle yazmaz.
3. **Sadece Ana Giriş Fonksiyonu:**
   - Yalnızca içi tamamen boş ana fonksiyon oluşturulur (Standart C için `int main(void) {}`, ESP-IDF projeleri için `void app_main(void) {}`).
   - Fonksiyon içerisine veya dışına `// TODO` yorumları, `while(1)` döngüsü ya da başka yardımcı/kesme (ISR) fonksiyon iskeletleri kesinlikle eklenmez.

---

## 🧠 3. Açıklama ve Mentörlük Tarzı

* **Mantığı ve Teorisini Anlat:** Çevrebirimlerin (PWM, ADC, I2C, SPI, Interrupt, Register) arka planda donanımsal olarak nasıl çalıştığını sade ve anlaşılır şekilde açıkla.
* **Ne Yapması Gerektiğini Söyle:** "Şimdi bir for döngüsü kur, içine analogWrite ekle" şeklinde yönlendir ama bitmiş kodu altın tepside sunma.
* **Hata Ayıklama (Debug):** Kullanıcı bir hata aldığında doğrudan tüm kodu değiştirmek yerine hatanın nerede olduğunu ve nasıl düzeltebileceğini soru-ipucu yöntemiyle göster.

---

## 📂 4. Standart Tekil Proje Klasör Yapısı

Açılan her proje klasörünün kendi içinde mikrodenetleyici üreticisinin resmi standartlarına uygun şu temiz yapıyı koruması ZORUNLUDUR:

```text
<proje_klasoru>/
├── CMakeLists.txt     # Projenin resmi CMake / Build reçetesi
├── main/              # Kaynak kodlar (main.c, main.h, bileşen CMake)
│   ├── CMakeLists.txt # Bileşen kütüphane bağlantıları
│   └── main.c         # Kullanıcının yazdığı saf C kaynak kodu
├── media/             # Devrenin çalışma anı fotoğrafı veya kısa video kaydı
├── sdkconfig          # Donanım ve çip yapılandırması (ESP-IDF için)
└── README.md          # Projenin amacı, Pin bağlantı tablosu ve öğrenilen kavramlar
```

* **`CMakeLists.txt`:** Projenin ve bileşenlerin derleme reçetesini içerir.
* **`main/` (veya derleyiciye göre `src/`):** Projeye ait kemik kaynak kodları barındırır (`main.c`). Asla `.ino` dosyası içermez.
* **`media/`:** Kullanıcının devre çalıştığında ekleyeceği fotoğraf (`.JPEG`, `.PNG`) ve hareketli görselleri (`.GIF`, `.MP4`) barındırır.
* **`README.md` (En Son Doldurulur):** Proje başında veya geliştirme esnasında doldurulmaz. Kod yazılıp, devre test edilip proje **tamamen bittikten sonra en son aşamada** doldurulacaktır. Projenin amacını, kullanılan donanım listesini, gerçek pin bağlantı tablosunu, nihai kodları ve derleme/yükleme adımlarını içerir.

---

## 📊 5. Proje Tamamlanma ve Portföy Güncelleme Kuralı

Bir proje kodlanıp, devresi test edilip başarıyla tamamlandığında Agent aşağıdaki iki dokümantasyon dosyasını ZORUNLU olarak güncelleyecektir:

1. **Ana Vitrin [`README.md`](file:///c:/Users/PC/Desktop/kidiman/embedded-systems-lab/README.md):** 
   - İlerleme matrisindeki ilgili kutucuğu `[✅](proje_yolu/)` olarak işaretleyip proje klasörüne link verir.
2. **Rehber Doküman [`00_docs/proje_semasi_ve_132_proje_rehberi.md`](file:///c:/Users/PC/Desktop/kidiman/embedded-systems-lab/00_docs/proje_semasi_ve_132_proje_rehberi.md):**
   - Bölüm 2'deki İlerleme Matrisinde ilgili kartın projesini `✅` yapar.
   - İlgili kartın altındaki proje başlığını `**[TAMAMLANDI ✅]**` olarak günceller.

---

## 🧭 6. İlerleme Modeli: Dikey İlerleme (Kart Bazlı Derinleşme Modeli)

Farklı mikrodenetleyici ekosistemleri arasında sürekli geçiş yapmanın getirdiği zihinsel yorgunluğu ve bağlam değiştirme (context-switching) maliyetini önlemek amacıyla müfredat **dikey (kart bazlı)** ilerleyecektir:

1. **İlk Hedef:** **`01_ESP_WROOM_32`** geliştirme kartının başlangıçtan ileri seviyeye (P1'den P12'ye kadar) tüm projeleri resmi **ESP-IDF** ekosistemiyle eksiksiz tamamlanacaktır.
2. ESP32'nin tüm müfredatı tamamlandıktan sonra sıradaki karta geçilecek, o kartın klasörü açılacak ve projeleri sırayla işlenecektir.
3. Repoda karmaşıklığı önlemek için aktif olarak çalışılmayan kart klasörleri ana dizinde açılmayacak; odaklanılan kart tekil ve temiz bir şekilde geliştirilecektir.

---

## 🏛️ 7. Donanıma Özgü Doğal Ekosistem ve Kütüphane Kuralı (Native Ecosystem Only)

Her kart, kendi mikrodenetleyici üreticisinin resmi doğal kütüphaneleri, SDK'sı veya doğrudan bare-metal (register) seviyesinde programlanacaktır. Asla `Arduino.h` dahil edilmeyecektir.

Tüm projeler üreticilerin resmi doğal araçları (ESP-IDF, Raspberry Pi Pico SDK, STM32Cube CMake, TI CCS / DriverLib, AVR-GCC) ve doğrudan terminal/CMake komutlarıyla yönetilecektir.

---

### 1. ST NUCLEO Serisi (STM32U575, STM32H723, STM32WB55)
* **Kütüphane:** Resmi **STM32Cube HAL / LL / CMSIS** (`stm32xxxx_hal.h`, `main.h`).
* **Ortam & Araçlar:** **STM32 VS Code Extension** + **STM32CubeMX** + CMake + `arm-none-eabi-gcc`.
* **Giriş Noktası & Mantık:** Standart C `int main(void)` ve sonsuz `while (1)` döngüsü.
* **Temel Kavramlar:** Sistem Saat Ağacı (RCC Clock Tree / PLL), GPIO Saat Kapıları (`__HAL_RCC_GPIOx_CLK_ENABLE()`), `GPIO_InitTypeDef` (Pin modu, hızı, pull-up/pull-down).
* **Örnek Doğal Kod Yapısı:**
  ```c
  #include "main.h"

  int main(void) {
      HAL_Init();
      SystemClock_Config();
      MX_GPIO_Init(); // Saat açma ve GPIO_InitStruct ayarları burada yapılır

      while (1) {
          HAL_GPIO_TogglePin(LED_PORT, LED_PIN);
          HAL_Delay(500);
      }
  }
  ```

---

### 2. Raspberry Pi Pico 2 W (RP2350)
* **Kütüphane:** Resmi **Raspberry Pi Pico C/C++ SDK** (`pico/stdlib.h`, `hardware/gpio.h`, `hardware/pwm.h`, `hardware/adc.h` vb.).
* **VS Code Ortamı:** **Raspberry Pi Pico VS Code Extension** + CMake + `arm-none-eabi-gcc` + `picotool`.
* **Giriş Noktası & Mantık:** Standart C `int main(void)`, `stdio_init_all()` ve `while (1)`.
* **Temel Kavramlar:** SIO (Single-Cycle I/O) donanım veriyolu, donanımsal Timer alarmları, PIO (Programmable I/O) durum makineleri.
* **Örnek Doğal Kod Yapısı:**
  ```c
  #include "pico/stdlib.h"
  #include "hardware/gpio.h"

  #define LED_PIN 15

  int main(void) {
      stdio_init_all();
      gpio_init(LED_PIN);
      gpio_set_dir(LED_PIN, GPIO_OUT);

      while (1) {
          gpio_put(LED_PIN, 1);
          sleep_ms(500);
          gpio_put(LED_PIN, 0);
          sleep_ms(500);
      }
      return 0;
  }
  ```

---

### 3. ESP-WROOM-32 (ESP32)
* **Kütüphane:** Resmi **ESP-IDF (Espressif IoT Development Framework)** (`driver/gpio.h`, `driver/ledc.h`, `freertos/FreeRTOS.h`, `freertos/task.h` vb.).
* **VS Code Ortamı:** Resmi **Espressif ESP-IDF VS Code Extension** + CMake + Ninja (`idf.py`).
* **Klasör Yapısı:** Standart ESP-IDF yapısı (`CMakeLists.txt`, `main/main.c`, `main/CMakeLists.txt`).
* **Giriş Noktası & Mantık:** FreeRTOS başlatıcı girişi `void app_main(void)` ve görev (Task) döngüsü.
* **Temel Kavramlar:** Çoklu çekirdek (Dual-Core Xtensa), `gpio_reset_pin` & `gpio_set_direction` ile sade pin yönetimi, `vTaskDelay` ile kilitlenmeyen (non-blocking) görev zamanlaması. *(Not: Çoklu pin ve kesme gereken adımlarda `gpio_config_t` struct yapısı kullanılır).*
* **Örnek Doğal Kod Yapısı (Sade & Temiz Model):**
  ```c
  #include <stdio.h>
  #include "driver/gpio.h"
  #include "freertos/FreeRTOS.h"
  #include "freertos/task.h"

  #define LED_PIN GPIO_NUM_2

  void app_main(void) {
      gpio_reset_pin(LED_PIN);
      gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);

      while (1) {
          gpio_set_level(LED_PIN, 1);
          vTaskDelay(1000 / portTICK_PERIOD_MS);
          gpio_set_level(LED_PIN, 0);
          vTaskDelay(1000 / portTICK_PERIOD_MS);
      }
  }
  ```

---

### 4. CRIUS ALL IN ONE PRO (ATmega2560 - 8-Bit AVR)
* **Kütüphane:** Saf **AVR-LibC Bare-Metal** (`<avr/io.h>`, `<avr/interrupt.h>`, `<util/delay.h>`).
* **Ortam & Araçlar:** **avr-gcc** + **avrdude** + Makefile / Terminal.
* **Giriş Noktası & Mantık:** Standart C `int main(void)` ve doğrudan donanımsal yazmaçlar.
* **Temel Kavramlar:** `DDRx` (Yön), `PORTx` (Çıkış/Pull-up), `PINx` (Okuma/Toggle), `TCCRx` (Timer/Sayacı), `OCRx` (Output Compare / PWM).
* **Örnek Doğal Kod Yapısı:**
  ```c
  #include <avr/io.h>
  #include <util/delay.h>

  int main(void) {
      DDRB |= (1 << PB7); // Pin 13 çıkış yap (DDRB bit 7 = 1)

      while (1) {
          PORTB ^= (1 << PB7); // Durumu tersle (XOR)
          _delay_ms(500);
      }
      return 0;
  }
  ```

---

### 5. TI LaunchPad Serisi (MSP430F5529, TM4C123GXL Tiva C)
* **Kütüphane:** Resmi **TI DriverLib / TivaWare / Register** (`msp430.h`, `driverlib/sysctl.h`, `driverlib/gpio.h`).
* **Ortam & Araçlar:** **TI Code Composer Studio (CCS)** veya Makefile + `msp430-gcc` / `arm-none-eabi-gcc`.
* **Giriş Noktası & Mantık:** Standart C `int main(void)`.
* **Temel Kavramlar:** Watchdog Timer durdurma (`WDTCTL = WDTPW | WDTHOLD`), TivaWare PLL saat yapılandırması, periferik saat etkinleştirme.
* **Örnek Doğal Kod Yapısı (MSP430 Register):**
  ```c
  #include <msp430.h>

  int main(void) {
      WDTCTL = WDTPW | WDTHOLD; // Watchdog Timer'ı durdur
      P1DIR |= BIT0;            // P1.0 çıkış

      while (1) {
          P1OUT ^= BIT0;
          __delay_cycles(500000);
      }
  }
  ```

