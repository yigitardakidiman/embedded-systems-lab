# Gömülü Sistemler Laboratuvarı: Klasör Şeması ve 132 Proje Rehberi (11 Kart × 12 Proje)

Bu doküman, laboratuvar envanterindeki **11 geliştirme kartı**, **16 modül/sensör**, **40 renkli LED** ve **70 direnç** kullanılarak sıfırdan ileri seviyeye kadar uygulanacak **132 projenin** (her kart için 4 Başlangıç + 4 Orta + 4 İleri seviye, **1. proje her zaman LED Blink**) GitHub portföy şemasını ve teknik yol haritasını içerir.

---

## 📂 1. GitHub Portföy Klasör Şeması

Projeler tamamlandıkça ana dizine (`embedded-systems-lab/`) aşağıdaki isimlendirme standardıyla adım adım eklenecektir. Derleyicilerin (*STM32CubeIDE, TI CCS, Gowin EDA, CMake*) dosya yolu hatası vermemesi için klasör adlarında Türkçe karakter ve boşluk kullanılmaz:

```text
embedded-systems-lab/
│
├── README.md                          # Ana Portföy Vitrini ve İlerleme Matrisi
├── .gitignore                         # Derleme çıktıları (build/, Debug/, .pio/)
│
├── 00_docs/                           # Dokümantasyon ve Envanter Klasörü
│   ├── geliştirme kartı malzeme listesi.xlsx
│   └── proje_semasi_ve_132_proje_rehberi.md
│
├── 01_ESP_WROOM_32/                   # Çift Çekirdek Xtensa LX6, FreeRTOS & Wi-Fi/BLE
│   ├── 01_beginner/
│   │   ├── 01_led_blink_and_boot_button/
│   │   ├── 02_capacitive_touch_led_bar/
│   │   ├── 03_ledc_pwm_breathe_led/
│   │   └── 04_i2c_oled_display/
│   ├── 02_intermediate/               # 05..08 arası projeler
│   └── 03_advanced/                   # 09..12 arası projeler
│
├── 02_RPi_Pico_2_W/                   # RP2350: Çift Cortex-M33 / RISC-V & PIO
├── 03_CRIUS_ATmega2560/               # 8-Bit AVR & Uçuş Kontrol Mimarisi
├── 04_TI_MSP430G2553/                 # 16-Bit RISC, 512 Byte RAM Bare-Metal
├── 05_TI_MSP430F5529_LP/              # 16-Bit Gelişmiş UCS, DMA, 12-Bit ADC & USB
├── 06_TI_TM4C123GXL_TivaC/            # 32-Bit ARM Cortex-M4F (FPU & NVIC)
├── 07_ST_NUCLEO_U575ZI_Q/             # 32-Bit ARM Cortex-M33 (Ultra-Low-Power & TrustZone)
├── 08_ST_P_NUCLEO_WB55/               # 32-Bit Çift Çekirdek (M4 + M0+) & BLE 5.0
├── 09_ST_NUCLEO_H723ZG/               # 32-Bit ARM Cortex-M7 (550 MHz DSP & FFT)
├── 10_RPi_Zero_W_Linux/               # Embedded Linux (Kernel, Sysfs, Daemons, Camera Mux)
└── 11_Tang_Nano_9K_FPGA/              # Sayısal Donanım Tasarımı (Verilog / VHDL)
```

### Tekil Proje Klasörü İç Şablonu
Açılan her proje klasörünün kendi içinde şu standart yapıyı koruması hedeflenir:

```text
01_led_blink_and_boot_button/
├── README.md          # Projenin amacı, Pin bağlantı tablosu ve öğrenilen kavramlar
├── src/               # Kaynak kodlar (.ino, .c, .cpp, .v)
└── media/             # Devrenin çalışma anı fotoğrafı veya kısa GIF kaydı
```

---

## 📊 2. Proje İlerleme Matrisi (11 Kart × 12 Proje)

Laboratuvarda **Dikey (Kart Bazlı) İlerleme Modeli** izlenmektedir. İlk olarak **ESP-WROOM-32** platformunda yerel ESP-IDF ile `P1..P12` projeleri sırasıyla tamamlanacak, ardından sıradaki karta geçilecektir.

| # | Geliştirme Kartı | P1 (Blink) | P2 | P3 | P4 | P5 | P6 | P7 | P8 | P9 | P10 | P11 | P12 |
| :-: | :--- | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: |
| **01** | **ESP-WROOM-32** | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ |
| **02** | **Raspberry Pi Pico 2 W** | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ |
| **03** | **CRIUS ALL IN ONE PRO** | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ |
| **04** | **TI MSP-EXP430G2** | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ |
| **05** | **TI MSP430F5529 LP** | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ |
| **06** | **TI EK-TM4C123GXL** | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ |
| **07** | **ST NUCLEO-U575ZI-Q** | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ |
| **08** | **ST P-NUCLEO-WB55** | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ |
| **09** | **ST NUCLEO-H723ZG** | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ |
| **10** | **Raspberry Pi Zero W** | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ |
| **11** | **Tang Nano 9K FPGA** | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ |

---

## ⚠️ 3. Envanter Özeti ve Hayati Donanım Güvenliği Notları

> [!CAUTION]
> **3.3V / 5V Gerilim Uyumsuzluğu Uyarısı:**
> **CRIUS (ATmega2560)** dışındaki tüm kartlar (**STM32, MSP430, TM4C, ESP32, Pico 2 W, RPi Zero W, Tang Nano 9K**) **3.3V** lojik seviyesinde çalışır.
> - **HC-SR04:** 5V besleme ister; `Echo` pininden dönen 5V sinyali 3.3V kartlara doğrudan bağlama! Elindeki `1kΩ` ve `2kΩ` (iki adet seri `1kΩ`) dirençlerle **gerilim bölücü (Voltage Divider)** kurarak 3.3V'a düşür.
> - **HW-070 (Mini PWM DC Motor Hız Kontrolcüsü):** `Output-` ucunu dahili MOSFET ile GND'ye anahtarlar (Low-Side Switch). Bu çıkışı mikrodenetleyici ile **PWM analizörü / görev döngüsü (Duty Cycle) okuyucu** olarak ölçerken `Output-` ile 3.3V arasına `10kΩ` pull-up direnci bağla.
> - **Motor Sürücüsü ve HW-070:** Yüksek akım çeken modülleri kartların 3.3V pininden değil, **HW-131 Breadboard Güç Modülü** veya **LiPo + Şarj Entegresi** üzerinden besle (`GND` hatlarını mutlaka ortakla).

| Kategori | Elimizdeki Malzemeler |
| :--- | :--- |
| **Geliştirme Kartları (11 Adet)** | `ESP-WROOM-32`, `Raspberry Pi Pico 2 W`, `CRIUS ALL IN ONE PRO`, `TI MSP-EXP430G2`, `TI MSP430F5529 LP`, `TI EK-TM4C123GXL`, `ST NUCLEO-U575ZI-Q`, `ST P-NUCLEO-WB55`, `ST NUCLEO-H723ZG`, `Raspberry Pi Zero W V1.1`, `Tang Nano 9K FPGA` |
| **Ekranlar (2 Adet)** | `0.96" 80x160 RGB IPS Ekran` (SPI - ST7735), `0.91" OLED Ekran` (I2C - SSD1306) |
| **IMU & Hareket (3 Adet)** | `Pololu AltIMU-10 v5` (10-DOF I2C), `MPU6050` (6-DOF I2C), `HC-SR04` (Ultrasonik Mesafe) |
| **Çevresel & İklim (4 Adet)** | `MLX90614 V1.0` (IR Termometre), `GY-BMP280` (Basınç/Sıcaklık), `BMP180` (Basınç/Sıcaklık), `DHT11` (Sıcaklık/Nem) |
| **Ses & Optik (3 Adet)** | `MAX4466` (Kazançlı Mikrofon Amfisi), `Mikrofon Modülü` (Analog/Dijital Eşikli), `RPi Camera Multiplexer` |
| **Güç & Sürücü (4 Adet)** | `Motor Sürücüsü`, `HW-070` (PWM Kontrolcü), `HW-131` (3.3V/5V Breadboard Güç), `LiPo Şarj Entegresi` |
| **Pasif & LED (111 Parça)** | `1x Breadboard`, `40x LED` (10 Kırmızı, 10 Mavi, 10 Sarı, 10 Yeşil), `70x Direnç` (10'ar adet `220Ω`, `330Ω`, `1kΩ`, `10kΩ`, `100kΩ`, `1MΩ`) |

---

## 🛠️ 4. Kart Bazlı 132 Proje Rehberi

> [!TIP]
> ### 💡 Pedagojik İlerleme İlkesi (Adım Adım Öğrenme Modeli)
> Gömülü sistemler öğreniminde kavram karmaşasını ve donanım kargaşasını önlemek için her geliştirme kartının **Başlangıç Seviyesi (01_beginner)** 4 temel ve tekil basamağa ayrılmıştır:
> 1. **P1 — Dijital Giriş/Çıkış (GPIO & Buton):** LED yakıp söndürme, pull-up direnci ve buton okuma.
> 2. **P2 — Analog Çıkış / PWM (LED Karartma - Fade/Breathe):** Donanımsal PWM modülü ile tek bir LED'in parlaklığını yumuşakça kısıp açma (motor veya harici sürücü olmadan).
> 3. **P3 — Analog Giriş / ADC (Potansiyometre veya Tek Sensör):** Dahili ADC ile analog voltaj okuma ve Serial Monitor'de görme.
> 4. **P4 — Temel İletişim & Ekran (I2C & 0.91" OLED):** 2 telli donanımsal I2C protokolü ile 0.91" SSD1306 OLED ekrana dinamik metin, sayaç ve durum bilgisi yazdırma.
>
> ⚠️ **Karmaşık Bileşenler Nerede?**
> Motor sürücüleri, HW-070 harici güç kontrolü, HC-SR04 zamanlama analizi, çift sensör füzyonu ve kesmeler **Orta Seviye (02_intermediate)** ve **İleri Seviye (03_advanced)** aşamalarında, temeller sağlam oturduktan sonra devreye girecektir.

---

### 01. ESP-WROOM-32 (`01_ESP_WROOM_32/`)
**Odak Noktası:** IoT protokolleri, Çift Çekirdekli FreeRTOS görev yönetimi, Wi-Fi/BLE ve dahili analog/kapasitif çevrebirimler.

#### 🟢 Başlangıç Seviyesi (`01_beginner/`) — Temel Yapı Taşları
1. **`01_led_blink_and_boot_button`** — **Blink & Toolchain Doğrulaması (Harici LED & BOOT Butonu)** **[TAMAMLANDI ✅]**
   - *Kavram:* Doğal ESP-IDF v6.1 (C / FreeRTOS) mimarisi, `driver/gpio.h` ile dijital çıkış (`GPIO_MODE_OUTPUT`), dahili pull-up (`GPIO_PULLUP_ONLY`) ile Active-Low `BOOT` butonunu okuma, `vTaskDelay` ile TWDT yönetimi ve `idf.py` inşa/yükleme hattını doğrulama.
2. **`02_capacitive_touch_led_bar`** — **Dahili Kapasitif Dokunmatik Sensör ve Gösterge LED'i (`T9 / GPIO 32`, Harici LED)** **[TAMAMLANDI ✅]**
   - *Kavram:* ESP32'nin dahili kapasitif algılayıcısını (`touchRead()`) tanıma, parmak temasıyla kapasitans değişimini algılayıp dinamik eşik kalibrasyonuyla LED kontrolü sağlama.
3. **`03_ledc_pwm_breathe_led`** — **LEDC Donanım PWM ile LED Parlaklık ve Nefes Alma Efekti (`GPIO 25`, Harici LED)** **[TAMAMLANDI ✅]**
   - *Kavram:* `delay()` ile işlemciyi kitlemeden donanımsal `ledc` modülü ile PWM sinyali üretme; LED parlaklığını kademeli artırıp azaltarak (Fade/Breathe) analog çıkış mantığını kavrama.
4. **`04_i2c_oled_display`** — **I2C 0.91" OLED Ekran ile Metin ve Sayaç Göstergesi (`0.91" OLED - SSD1306`)** **[TAMAMLANDI ✅]**
   - *Kavram:* 2 telli I2C haberleşme protokolü (`SDA`, `SCL`) ile tanışma; ESP-IDF modern I2C Master sürücüsü (`driver/i2c_master.h`) üzerinden SSD1306 OLED denetleyicisini başlatma, sayfa adresleme moduyla ekrana başlık, çalışma sayacı (Uptime) ve dinamik metinler yazdırma.

#### 🟡 Orta Seviye (`02_intermediate/`) — Tekil Sensör, ADC ve SPI Temelleri
5. **`05_i2c_bmp280_oled_thermometer`** — **I2C Sensör Okuma ve OLED Dijital Termometre/Barometre (`GY-BMP280` veya `BMP180`, `0.91" OLED`)** **[TAMAMLANDI ✅]**
   - *Kavram:* P4'te kurulan I2C hattına (`SDA/SCL`) ikinci bir cihaz olarak basınç/sıcaklık sensörünü paralel bağlama; aynı I2C veri yolu üzerinden gerçek sıcaklık (`°C`) ve basınç (`hPa`) verisini okuyup `snprintf` ile `0.91" OLED` ekrana canlı yazdırma.
6. **`06_touch_led_oled_monitor`** — **Kapasitif Dokunmatik Sensör, LED ve Canlı OLED Gösterge Paneli (`T9 / GPIO 32`, `GPIO 25` LED, `0.91" OLED`)** **[TAMAMLANDI ✅]**
   - *Kavram:* ESP32'nin dahili kapasitif dokunmatik sensöründen (`TOUCH_PAD_NUM9`) okunan anlık kapasitans değerini ve temas durumunu (`DOKUNULDU` / `BOSTA`) eşzamanlı olarak hem harici LED üzerinde hem de `0.91" I2C OLED` ekranda canlı gösterme.
7. **`07_adc_microphone_vu_meter`** — **ESP32 ADC ile Analog Ses Seviyesi (VU Meter) Ölçümü (`MAX4466` Mikrofon Amfisi, `0.91" OLED` / LED)**
   - *Kavram:* ESP32'nin 12-bit **ADC (`esp_adc/adc_oneshot.h`)** birimini yapılandırarak `MAX4466` mikrofon amfisinden analog voltaj/ses genliğini okuma ve ses şiddetini ekranda veya LED'de dinamik seviye çubuğu (VU Meter) olarak gösterme.
8. **`08_spi_ips_color_display`** — **Yüksek Hızlı SPI Protokolü ve 0.96" Renkli IPS Ekran Sürüşü (`0.96" 80x160 RGB IPS Ekran - ST7735`)**
   - *Kavram:* Yanına ek sensör karıştırmadan, 4 telli yüksek hızlı **SPI (`MOSI`, `SCLK`, `CS`, `DC`, `RST`)** protokolü ile tanışma; `80x160` RGB565 renkli IPS ekranda temel geometrik şekiller, renk kutuları ve metinler çizdirme.

#### 🔴 İleri Seviye (`03_advanced/`) — IMU, Motor Kontrol, Wi-Fi ve BLE
9. **`09_mpu6050_imu_spirit_level`** — **MPU6050 İvmeölçer/Jiroskop ile Dijital Su Terazisi ve Eğim Ölçer (`MPU6050`, `0.96" IPS Ekran` veya `0.91" OLED`)**
   - *Kavram:* 6 eksenli `MPU6050` IMU sensöründen I2C ile ham ivme/jiroskop verilerini okuma, `atan2` ile Pitch (Yunuslama) ve Roll (Yatış) açılarını hesaplama ve ekranda canlı su terazisi / eğim göstergesi çizdirme.
10. **`10_motor_driver_pwm_speed_control`** — **Harici Güç İzolasyonlu DC Motor Hız ve Yön Kontrolü (`Motor Sürücüsü`, `HW-070`, `HW-131 Breadboard Güç`, `0.91" OLED`)**
    - *Kavram:* `HW-131` ile güç hattını izole etme, `HW-070` kontrolcüsünden hız referansı alıp `Motor Sürücüsü` ve donanımsal PWM üzerinden DC motorun hızını ve yönünü güvenli şekilde sürme.
11. **`11_wifi_webserver_sensor_dashboard`** — **Wi-Fi İstasyon Modu ve Canlı Web Sensör Paneli (`GY-BMP280` / `DHT11`, `0.91" OLED`)**
    - *Kavram:* ESP32'yi yerel Wi-Fi ağına bağlama (`esp_wifi` & `esp_http_server`), dahili HTTP web sunucusu üzerinden sensör verilerini tarayıcıda canlı görüntüleme ve web arayüzünden kart üzerindeki çıkışı kontrol etme.
12. **`12_ble_thermal_telemetry_monitor`** — **Bluetooth Low Energy (BLE) GATT Telemetri ve Kızılötesi Sıcaklık Monitörü (`MLX90614`, `0.96" IPS Ekran`)**
    - *Kavram:* `MLX90614` temassız kızılötesi termometre sensörüyle yüzey sıcaklığını ölçüp ESP32'nin **BLE GATT** servisi üzerinden cep telefonuna kablosuz bildirim (`Notification`) gönderme.

---

### 02. Raspberry Pi Pico 2 W (`02_RPi_Pico_2_W/`)
**Odak Noktası:** RP2350'nin benzersiz **PIO (Programmable I/O)** durum makineleri, hem ARM Cortex-M33 hem Hazard3 RISC-V çekirdeklerini deneyimleme ve DMA zincirleme.

#### 🟢 Başlangıç Seviyesi (`01_beginner/`) — Temel Yapı Taşları
1. **`01_led_blink_cyw43_and_gpio`** — **Blink & CYW43 Yardımcı Çip Mimarisi (`CYW43_WL_GPIO_LED_PIN` & Harici LED)**
   - *Kavram:* Resmi Pico C/C++ SDK v2.3.1 mimarisi, Pico 2 W üzerindeki dahili LED'in Wi-Fi çipine (`CYW43439`) bağlı olduğunu kavrayıp `cyw43_arch_init()` ile sürme, RP2350 SIO üzerinden harici GPIO LED (`hardware/gpio.h`) yönetimi ve UF2 bootloader hattını doğrulama.
2. **`02_pwm_slice_breathe_led`** — **Donanım PWM Dilimleri (PWM Slices) ile LED Nefes Alma Efekti (Harici Renkli LED)**
   - *Kavram:* Motor veya harici sürücülere girmeden; RP2350'nin donanımsal PWM dilimlerini (PWM slices) kullanarak tek bir LED'in parlaklığını yumuşakça kısıp açma (Fade In / Fade Out).
3. **`03_adc_sound_level_monitor`** — **ADC ile Analog Giriş Okuma ve Ses/Voltaj Seviyesi Göstergesi (`MAX4466` veya Dahili Sıcaklık Sensörü, LED)**
   - *Kavram:* RP2350'nin 12-bit ADC kanalı ile analog voltaj okuma, Serial Monitor'de ham veriyi izleme ve belirlenen eşik değere göre durum LED'ini yakma.
4. **`04_i2c_bmp180_oled_weather`** — **I2C 0.91" OLED Ekran ve BMP180 Basınç/Sıcaklık İstasyonu (`0.91" OLED`, `BMP180`)**
   - *Kavram:* Donanımsal I2C hattı üzerinden BMP180 sensöründen sıcaklık ve barometrik basınç verisini okuyup 0.91" OLED ekranda temiz bir arayüzle gösterme.

#### 🟡 Orta Seviye (`02_intermediate/`)
5. **`05_motor_driver_and_hw070_pwm`** — **Motor Sürücüsü, HW-070 ve Harici Güç Yönetimi (`Motor Sürücüsü`, `HW-070`, `HW-131 Breadboard Güç`)**
   - *Kavram:* Harici breadboard güç modülü (HW-131) ile 5V/3.3V güç izolasyonu kurma; HW-070 potansiyometresi PWM çıkışını okuyup motor sürücüsü üzerinden DC motor hız ve yön kontrolü yapma.
6. **`06_pio_ultrasonic_hcsr04_driver`** — **PIO (Programmable I/O) ile Sıfır CPU Yüklü HC-SR04 Sürücüsü (`HC-SR04`, `1kΩ/2kΩ Direnç`, `0.91" OLED`)**
   - *Kavram:* **PIO** assembly diliyle sadece birkaç satırlık bir durum makinesi yazarak, CPU hiç müdahale etmeden `HC-SR04`'e 10µs tetik verip Echo süresini sayarak RX FIFO'ya atan özel donanım modülü tasarlama.
7. **`07_spi_dma_double_buffer_gui`** — **SPI DMA ile Yüksek Hızlı Grafik Arayüzü (`0.96" 80x160 RGB IPS Ekran`, `MPU6050`)**
   - *Kavram:* RAM'de tutulan 80x160x16-bit (25.6 KB) ekran tamponunu (Framebuffer) DMA kanalı üzerinden SPI'a aktarırken, işlemcinin aynı anda `MPU6050`'den veri okuyup bir sonraki kareyi (Double Buffering) hazırlaması.
8. **`08_multicore_fifo_weather_station`** — **Çift Çekirdek (Multicore) FIFO Haberleşmeli Hava İstasyonu (`Pololu AltIMU-10 v5`, `0.96" IPS Ekran`)**
   - *Kavram:* **Core 0**'da kullanıcı arayüzü ve ekran çizimini yürütürken, **Core 1**'de `AltIMU-10 v5` sensörlerini okuyup donanımsal `multicore_fifo` üzerinden çekirdekler arası güvenli veri aktarımı yapma.

#### 🔴 İleri Seviye (`03_advanced/`)
9. **`09_arm_m33_vs_riscv_benchmark`** — **ARM Cortex-M33 vs Hazard3 RISC-V Mimari Kıyaslama Laboratuvarı (`Pololu AltIMU-10 v5`, `0.91" OLED`)**
   - *Kavram:* RP2350'nin mimari değiştirme özelliğini kullanarak aynı Kalman/Madgwick sensör füzyonu kodunu önce **ARM Cortex-M33 (FPU açık)**, sonra **Hazard3 RISC-V** modunda derleyip çalışma sürelerini mikrosaniye bazında kıyaslama.
10. **`10_dma_pingpong_audio_oscilloscope`** — **DMA Zincirleme (Ping-Pong Buffer) ile Gerçek Zamanlı Ses Osiloskobu (`MAX4466`, `0.96" IPS Ekran`)**
    - *Kavram:* İki adet DMA kanalını birbirini tetikleyecek şekilde (`chain_to`) bağlayarak, bir tampon ADC'den `MAX4466` ses verisiyle dolarken diğer tamponun dalga formunu `0.96" IPS` ekrana kesintisiz çizdirme.
11. **`11_wifi_udp_pid_tilt_controller`** — **Wi-Fi UDP Telemetri ve Kapalı Çevrim Eğim Kontrolcüsü (`MPU6050`, `Motor Sürücüsü`, `HW-131`)**
    - *Kavram:* `CYW43439` Wi-Fi çipi üzerinden bilgisayardaki arayüzden PID katsayılarını ($K_p, K_i, K_d$) canlı olarak değiştirip, `MPU6050` geri beslemesiyle motor tepkisini gerçek zamanlı grafikleme.
12. **`12_pio_150mhz_logic_analyzer`** — **PIO Tabanlı 150 MHz Dijital Lojik Analizör ve R-2R DAC (`HW-070`, `10kΩ Dirençler`, `0.96" IPS Ekran`)**
    - *Kavram:* PIO durum makinesini 150 MHz'de (6.6 ns çözünürlük!) çalıştırarak `HW-070` ve R-2R direnç merdiveni sinyallerini yakalayıp `0.96" IPS` ekranda çift kanal lojik analizör/osiloskop gibi çizdirme.

---

### 03. CRIUS ALL IN ONE PRO (`03_CRIUS_ATmega2560/`)
**Odak Noktası:** 8-bit AVR mimarisi (`DDRx`, `PORTx`, `TCNTx`, `TWI`), kart üzerinde **yerleşik `MPU6050`, `HMC5883L` (Pusula) ve `MS5611` (Hassas Barometre)** sensörleri ve uçuş kontrol algoritmaları.

#### 🟢 Başlangıç Seviyesi (`01_beginner/`) — Temel Yapı Taşları
1. **`01_avr_register_blink_timer1`** — **8-Bit AVR Register Blink & Timer1 CTC Kesmesi**
   - *Kavram:* `DDRB` ve `PINB` yazmaçlarıyla bare-metal pin kontrolü, 16-bit Timer1 CTC kesmesiyle arka plan durum flaşörü ve GPIO toggling mantığını anlama.
2. **`02_timer_fast_pwm_led_dimmer`** — **Timer Fast-PWM ile LED Karartma / Dimmer (Harici LED)**
   - *Kavram:* ATmega2560 donanımsal Timer Fast-PWM modunu (`OCRnA/B` yazmaçları) kullanarak işlemci döngüsünü meşgul etmeden harici LED'in parlaklığını kademeli kontrol etme.
3. **`03_adc_analog_reading_and_threshold`** — **Dahili ADC ile Analog Voltaj Okuma ve Eşik Algılama (`ADMUX`, `ADCSRA`, LED)**
   - *Kavram:* 10-bit dahili ADC çeviricisini yapılandırıp analog voltaj/potansiyometre okuma ve belirlenen eşik aşıldığında durum LED'ini tetikleme.
4. **`04_i2c_oled_internal_sensor`** — **I2C 0.91" OLED Ekran ve Kart Üzerindeki Dahili MPU6050 Eğim Açısı (`0.91" OLED`, Dahili Sensör)**
   - *Kavram:* CRIUS kartı üzerinde yerleşik bulunan MPU6050 sensöründen I2C ile açı verisi çekip 0.91" OLED ekrana su terazisi gibi temiz bir gösterge çizdirme.

#### 🟡 Orta Seviye (`02_intermediate/`)
5. **`05_nonblocking_twi_isr_driver`** — **8-Bit İşlemcide Kesme Güdümlü (Non-Blocking) TWI (I2C) Durum Makinesi (`Pololu AltIMU-10 v5`, `0.91" OLED`)**
   - *Kavram:* Uçuş kontrol döngüsünü I2C bekleyerek bloklamamak için ATmega2560'ın `TWCR`, `TWSR`, `TWDR` yazmaçlarını ve `TWI_vect` kesmesini kullanarak arka planda çalışan I2C sürücüsü yazma.
6. **`06_tilt_compensated_compass_hud`** — **Eğim Kompanzasyonlu (Tilt-Compensated) Dijital Pusula ve HUD (`Dahili MPU6050 + HMC5883L` veya `AltIMU-10 v5`, `0.96" IPS Ekran`)**
   - *Kavram:* İvmeölçerden alınan Roll ve Pitch açılarıyla manyetik vektörü yatay düzleme izdüşürerek (Tilt Compensation) her eğimde doğru kuzeyi gösteren uçak yapay ufuk (HUD) ekranı yapma.
7. **`07_active_gimbal_stabilizer`** — **Aktif Kamera/Platform Stabilizasyon (Gimbal) Kontrolcüsü (`Dahili MPU6050`, `Motor Sürücüsü`, `HW-070`)**
   - *Kavram:* CRIUS kartını elinde sağa sola eğdiğinde açıyı anında ters yönde telafi edecek şekilde `Motor Sürücüsü`nü sürme ve `HW-070` ile hedef eğim açısını (Pitch Trim) manuel ayarlama.
8. **`08_mavlink_style_binary_telemetry`** — **Çoklu Donanım UART (`USART0..3`) ve MAVLink Benzeri Telemetri Paketi (`MLX90614`, `DHT11`, `0.91" OLED`)**
   - *Kavram:* Başlık baytı (`0xFE`), paket uzunluğu, mesaj ID'si, faydalı yük ve 16-bit **CRC-CCITT** içeren ikili (Binary) telemetri protokolü tasarlayıp `USART` TX boş kesmesi (`UDRE_vect`) ile gönderme.

#### 🔴 İleri Seviye (`03_advanced/`)
9. **`09_variometer_sensor_fusion`** — **Barometrik + İvmeölçer + Ultrasonik Dikey Hız (Variometer) Füzyonu (`Dahili MS5611`, `Dahili MPU6050`, `HC-SR04`, `0.96" IPS Ekran`)**
   - *Kavram:* Kısa vadede hızlı olan Z-ekseni ivmesini, yere yakınken (<2m) mutlak doğru olan `HC-SR04`'ü ve yüksek irtifada çalışan `MS5611` barometreyi birleştirerek dikey tırmanma/alçalma hızını ($m/s$) hesaplama.
10. **`10_cascaded_pid_flight_stabilizer`** — **Çift Kademeli (Cascaded) Açı ve Açısal Hız PID Kontrolcüsü (`Dahili MPU6050`, `Motor Sürücüsü`, `0.91" OLED`)**
    - *Kavram:* Gerçek uçuş kontrolcülerinin kalbi olan **Cascaded PID** mimarisi: Dış döngüde (Outer Loop) hedef açı hatasından hedef açısal hız (deg/s) üretip, iç döngüde (Inner Loop - 400 Hz) Gyro verisiyle motor çıkışını sürme.
11. **`11_progmem_eeprom_blackbox_logger`** — **PROGMEM Optimizasyonu ve Uçuş Veri Kaydedici (Blackbox Logger) (`Pololu AltIMU-10 v5`, `MLX90614`, `0.96" IPS Ekran`)**
    - *Kavram:* 8 KB SRAM'i korumak için sabit tabloları Flash bellekte (`PROGMEM`) tutma ve dahili 4 KB EEPROM'a sıkıştırılmış (Delta Encoding) sensör logları kaydetme.
12. **`12_motor_propeller_balance_stand`** — **Akustik ve İvme Tabanlı Pervane/Motor Balans Analizörü (`MAX4466`, `Dahili MPU6050`, `HW-070`, `Motor Sürücüsü`, `0.96" IPS Ekran`)**
    - *Kavram:* Motoru farklı gaz seviyelerinde döndürürken hem `MPU6050` ivme gürültüsünü hem de `MAX4466` akustik gürültüsünü analiz ederek rezonans frekanslarını tespit eden test standı yapma.

---

### 04. TI MSP-EXP430G2 LaunchPad (`04_TI_MSP430G2553/`)
**Odak Noktası:** Sadece **16 KB Flash ve 512 Byte RAM**! Doğrudan **Register seviyesinde (`P1DIR`, `TACTL`, `UCB0CTL1`)** kod yazma, bellek optimizasyonu ve Low-Power Mode (`LPM0` - `LPM4`).

#### 🟢 Başlangıç Seviyesi (`01_beginner/`) — Temel Yapı Taşları
1. **`01_baremetal_wdt_and_gpio_blink`** — **Bare-Metal Blink & Buton Okuma (`WDTCTL`, Dahili `P1.0/P1.6` LED, `P1.3` Buton)**
   - *Kavram:* `WDTCTL = WDTPW | WDTHOLD;` ile Watchdog'u durdurma; bit maskeleme (`P1DIR`, `P1OUT`), `P1IN` ile buton okuma ve kesmeler.
2. **`02_timera_pwm_led_fade`** — **Timer_A Donanımsal PWM ile LED Nefes Alma Efekti (Harici Renkli LED)**
   - *Kavram:* Motor veya harici devrelere girmeden, sadece `Timer_A` `OUTMOD_7` modu ile işlemci uykudayken LED parlaklığını kademeli kısıp açma.
3. **`03_adc10_single_channel_reading`** — **10-Bit ADC10 ile Analog Voltaj Okuma ve Eşik Algılama (Potansiyometre/Sensör)**
   - *Kavram:* `ADC10CTL0` ve `ADC10CTL1` yazmaçlarıyla analog voltaj okuma; belirlenen eşik aşıldığında durum LED'ini yakma.
4. **`04_uart_serial_telemetry_print`** — **Donanımsal UART ile Seri Veri İletişimi (`USCI_A0`, 9600 Baud)**
   - *Kavram:* 512 Byte RAM'i yormadan, donanımsal UART modülü üzerinden okunan analog verileri ve metinleri bilgisayar ekranına (Serial Monitor) yazdırma.

#### 🟡 Orta Seviye (`02_intermediate/`)
5. **`05_zero_buffer_oled_driver`** — **512 Byte RAM ile OLED Ekran Sürme (Framebuffersız Doğrudan Çizim) (`0.91" OLED`)**
   - *Kavram:* `USCI_B0` I2C donanımını kullanarak RAM'de 512 Byte tampon tutmadan, Flash bellekte (`const`) saklanan 5x7 font tablosundan doğrudan ekrana karakter basan hafif (Zero-Copy) sürücü yazma.
6. **`06_dco_16mhz_fsm_dht11_reader`** — **Durum Makinesi (FSM) ve Timer ile DHT11 Okuyucu (`DHT11`, `0.91" OLED`)**
   - *Kavram:* `DCO` saatini 16 MHz'e kalibre edip (`CALBC1_16MHZ`), `DHT11`'in 40 bitlik veri akışını port kesmeleri (`PORT1_VECTOR`) ve zamanlayıcı farklarıyla yakalayarak OLED ekrana yazdırma.
7. **`07_fixed_point_bmp180_barometer`** — **Sabit Nokta Aritmetiği (Fixed-Point Math) ile BMP180 Hesaplaması (`BMP180`, `0.91" OLED`)**
   - *Kavram:* FPU olmayan MSP430G2'de `float` kullanmadan (16 KB Flash'ı koruyarak) tam sayı ve bit kaydırma (Integer / Bit-shift) algoritmasıyla 0.1°C ve 1 Pa hassasiyetle ölçüm yapma.
8. **`08_lpm4_submicroamp_motion_wakeup`** — **LPM3 / LPM4 Ultra Düşük Güçlü Hareket Uyandırıcı (`MPU6050`, `HW-070`, `LiPo Şarj Entegresi`)**
   - *Kavram:* I2C üzerinden `MPU6050`'nin hareket algılama kesmesini kurduktan sonra MSP430'u **LPM4 (0.1 µA!)** uykusuna yatırma; sarsıntı olduğunda `P1` port kesmesiyle sistemi uyandırma.

#### 🔴 İleri Seviye (`03_advanced/`)
9. **`09_bitbanged_spi_vs_usci_ips`** — **Bit-Banging (Yazılımsal) SPI ile Donanım USCI Kıyaslaması (`0.96" IPS Ekran`, `MLX90614`)**
   - *Kavram:* USCI modülü I2C için meşgulken (`MLX90614`), herhangi iki GPIO pini üzerinden kendi **Bit-Banged SPI** fonksiyonunu yazarak `0.96" RGB IPS` ekranı sürme ve hız farkını analiz etme.
10. **`10_adc10_dtc_dma_audio_sampler`** — **DTC (Data Transfer Controller) ile Çok Kanallı ADC Örnekleme (`MAX4466`, `LiPo Şarj Entegresi`, `0.91" OLED`)**
    - *Kavram:* MSP430G2553'ün mini-DMA'sı sayılan **ADC10 DTC** birimini kullanarak, CPU uykudayken ardışık 32 ses örneğini doğrudan RAM'e aktarma.
11. **`11_q16_fixed_point_imu_filter`** — **16-Bit Sabit Nokta Tamamlayıcı Filtre (Complementary Filter) (`MPU6050`, `0.91" OLED`)**
    - *Kavram:* Q8.8 sabit nokta formatında yaklaşıklık algoritması yazarak, 512 Byte RAM sınırları içinde ivmeölçer ve jiroskop verilerini birleştirip eğim açısı hesaplama.
12. **`12_cooperative_task_scheduler`** — **Kooperatif Görev Zamanlayıcı (Cooperative Task Scheduler) Tasarımı (`BMP180`, `HC-SR04`, `0.91" OLED`, `HW-070`)**
    - *Kavram:* RTOS sığmayan bu işlemcide, `Timer_A` 1 ms sistem tikine dayalı fonksiyon işaretçisi (Function Pointer) tablosuyla çalışan kendi hafif **Non-Preemptive Görev Zamanlayıcını** sıfırdan yazma.

---

### 05. TI MSP430F5529 LaunchPad (`05_TI_MSP430F5529_LP/`)
**Odak Noktası:** Gelişmiş UCS (Unified Clock System), 3 kanallı DMA, 12-bit `ADC12_A`, donanım çarpanı `MPY32` ve çip içi **Full-Speed USB 2.0** donanımı.

#### 🟢 Başlangıç Seviyesi (`01_beginner/`) — Temel Yapı Taşları
1. **`01_ucs_25mhz_dual_port_blink`** — **Blink & UCS 25 MHz Doğrulaması (Dahili `P1.0` Kırmızı, `P4.7` Yeşil LED)**
   - *Kavram:* `PMM` çekirdek voltajı ve UCS ile MCLK saatini 25 MHz'e çıkarma; Timer kesmeleriyle poliritmik LED Blink yapma.
2. **`02_timerb_pwm_led_fade`** — **Timer_B Donanımsal PWM ile LED Nefes Alma Efekti (Harici Renkli LED)**
   - *Kavram:* Motor veya karmaşık sürücüler olmadan, `Timer_B` modülünü kullanarak pürüzsüz donanımsal PWM üretme ve LED parlaklığını nefes alma efektiyle kontrol etme.
3. **`03_adc12_single_channel_pot`** — **12-Bit ADC12_A ile Analog Voltaj Okuma ve Eşik Algılama (Potansiyometre/Sensör)**
   - *Kavram:* 12-bit yüksek çözünürlüklü ADC12 kanalından veri okuyup belirlenen voltaj eşiğine göre durum LED'ini tetikleme.
4. **`04_i2c_oled_basic_display`** — **USCI_B I2C Modülü ve 0.91" OLED Ekran (`0.91" OLED`, `BMP180`)**
   - *Kavram:* USCI_B donanımsal I2C hattı üzerinden OLED ekrana yazı yazdırma ve sensör sıcaklık değerini ekranda gösterme.

#### 🟡 Orta Seviye (`02_intermediate/`)
5. **`05_dma0_spi_thermal_display`** — **DMA Kontrolcüsü ile SPI Ekran Yenileme (`0.96" IPS Ekran`, `MLX90614`)**
   - *Kavram:* F5529'un dahili DMA'sını (`DMA0`) `UCA0TXIFG` tetiklemesiyle kurarak, `MLX90614` sıcaklık verilerinin grafiksel gösterimini CPU döngüsü harcamadan SPI ekrana aktarma.
6. **`06_usb_cdc_altimu10_streamer`** — **USB CDC (Sanal Seri Port) Veri Kaydedici (`Pololu AltIMU-10 v5`)**
   - *Kavram:* Doğrudan F5529'un kendi **USB 2.0** donanımı üzerinde USB CDC yığınını çalıştırarak 10 eksenli `AltIMU-10 v5` verilerini yüksek hızda bilgisayara aktarma.
7. **`07_ultrasonic_polar_radar_map`** — **Ultrasonik Radar ve Grafik Haritalama (`HC-SR04`, `MPU6050`, `0.96" IPS Ekran`)**
   - *Kavram:* `HC-SR04` sensörünü `MPU6050` ile birlikte döndürerek, hangi açıda (`Gyro Z` entegrasyonu) hangi mesafede engel olduğunu polar koordinatlarda (`r, θ`) `0.96" IPS` ekrana radar gibi çizdirme.
8. **`08_rtca_calendar_climate_logger`** — **Gerçek Zamanlı Saat (`RTC_A`) ve Info-Flash İklim Kaydedici (`DHT11`, `BMP180`, `0.91" OLED`)**
   - *Kavram:* Donanımsal takvim modlu **RTC_A** birimini ve dahili *Information Flash* segmentlerini kullanarak, enerji kesilse bile silinmeyen saatlik iklim kayıtları tutma.

#### 🔴 İleri Seviye (`03_advanced/`)
9. **`09_usb_hid_6dof_gamepad_throttle`** — **Özel USB HID 6-Eksen Oyun Kolu / Hava Faresi + Gaz Kolu (`MPU6050`, `HW-070`)**
   - *Kavram:* Bilgisayara takıldığında sürücü gerektirmeden **USB Oyun Kolu / Fare** olarak tanınan bir USB HID cihazı yapma; eksenleri `MPU6050`'den, gaz kolunu ise `HW-070` görev döngüsünden okuma.
10. **`10_pmap_dynamic_pin_remapper`** — **Port Mapping Controller (PMAP) ile Dinamik Pin Yönlendirme (`Motor Sürücüsü`, `HW-070`, `0.91" OLED`)**
    - *Kavram:* F5529'un **Port 4 PMAP** özelliğini kullanarak, çalışma esnasında (Run-time) Timer Capture/PWM veya SPI sinyallerini yazılımsal olarak farklı fiziksel pinlere yönlendirme.
11. **`11_mpy32_mac_pitch_detector`** — **DMA + ADC12 + Donanım Çarpanı (`MPY32`) ile Gerçek Zamanlı Ses Korelasyonu (`MAX4466`, `0.96" IPS Ekran`)**
    - *Kavram:* `MPY32`'nin **MAC (Multiply-and-Accumulate)** modunu kullanarak ses sinyalinin otokorelasyonunu hesaplama ve ıslık/enstrüman sesinin temel frekansını (Pitch Detection) bulma.
12. **`12_usb_msc_virtual_flash_drive`** — **USB MSC (Mass Storage Class) Sanal Flash Bellek Kaydedici (`GY-BMP280`, `MLX90614`)**
    - *Kavram:* F5529'un 128 KB Flash belleğinin bir kısmını FAT12 dosya sistemiyle formatlayıp, kartı bilgisayara taktığında içinde `SENSOR.CSV` dosyası bulunan bir **USB Flash Bellek** gibi görünmesini sağlama.

---

### 06. TI EK-TM4C123GXL (`06_TI_TM4C123GXL_TivaC/`)
**Odak Noktası:** ARM Cortex-M4F mimarisi (NVIC kesme öncelikleri, SysTick, Bit-Banding), Motion Control PWM modülleri ve çift 12-bit ADC (Sample Sequencer yapısı).

#### 🟢 Başlangıç Seviyesi (`01_beginner/`) — Temel Yapı Taşları
1. **`01_rgb_blink_bitbanding_pf0_unlock`** — **7-Renkli RGB Blink, Bit-Banding ve PF0 Kilidi Açma**
   - *Kavram:* `PF0 (SW2)` pininin NMI kilidini açma; Cortex-M4 Bit-Banding adreslemesi ve SysTick kesmesiyle dahili RGB LED'de temel Blink yapma.
2. **`02_pwm_rgb_breathe_color_mixing`** — **Donanım PWM ile RGB LED Nefes Alma ve Renk Karışımı (Dahili RGB LED)**
   - *Kavram:* Donanımsal PWM modülünü kullanarak Kırmızı, Yeşil ve Mavi kanalların doluluk oranını (Duty Cycle) bağımsız değiştirip renk geçişleri (Color Fading) yapma.
3. **`03_adc_sequencer_pot_reading`** — **ADC Sample Sequencer ile Analog Voltaj Okuma ve Eşik Algılama (Potansiyometre/Sensör)**
   - *Kavram:* TM4C123'ün benzersiz **Sample Sequencer** mimarisini tanıma; tek kanaldan analog voltaj okuma ve belirlenen eşik aşıldığında RGB LED ile renkli uyarı verme.
4. **`04_i2c_oled_climate_display`** — **I2C Master Modülü ve 0.91" OLED Ekran (`0.91" OLED`, `BMP180`)**
   - *Kavram:* TM4C123'ün donanımsal I2C modülünü kullanarak 0.91" OLED ekranda yazı ve BMP180 sensöründen sıcaklık verisini gösterme.

#### 🟡 Orta Seviye (`02_intermediate/`)
5. **`05_motion_pwm_deadband_generator`** — **Özel Motion Control PWM Üreteci ve Ölü Zaman (Dead-Band) Kontrolü (`Motor Sürücüsü`, `HW-070`, `HW-131`, `0.91" OLED`)**
   - *Kavram:* TM4C123'ün çift yönlü **M0PWM / M1PWM** motor kontrol bloklarını ve H-köprüsü kısa devrelerini önleyen donanımsal **Dead-Band Generator** özelliğini uygulama.
6. **`06_ssi_udma_ips_display_driver`** — **SSI (Synchronous Serial Interface) ve µDMA ile Hızlı IPS Ekran Sürücüsü (`0.96" IPS Ekran`, `GY-BMP280`)**
   - *Kavram:* TI'ın SPI karşılığı olan **SSI** modülünü ve **µDMA** kontrol tablosunu 1024-byte hizalayarak (`__attribute__((aligned(1024)))`) `0.96" RGB IPS` ekranı yüksek hızda sürme.
7. **`07_nvic_priority_preemption_lab`** — **NVIC Kesme Öncelikleri ve Tail-Chaining Deneyi (`MPU6050`, `HC-SR04`, `DHT11`, `4 Renk LED`)**
   - *Kavram:* ARM Cortex-M **NVIC**'de farklı kesme öncelikleri (Priority Levels 0-7) atayarak; kritik zamanlamalı kesmelerin düşük öncelikli kesmeleri nasıl böldüğünü (Nesting/Preemption) LED'lerle gözlemleme.
8. **`08_ultrasonic_cruise_control_pi`** — **Kapalı Çevrim Ultrasonik Mesafe Sabitleyici (Cruise Control) (`HC-SR04`, `Motor Sürücüsü`, `0.91" OLED`)**
   - *Kavram:* `HC-SR04` önünde hareket eden bir nesneye olan mesafeyi ölçüp, PI (Oransal-İntegral) kontrolcü ile `Motor Sürücüsü` hızını ayarlayarak hedef mesafeyi (ör. 20 cm) koruma.

#### 🔴 İleri Seviye (`03_advanced/`)
9. **`09_interleaved_dual_adc_2msps`** — **Çift ADC Modülü (`ADC0` + `ADC1`) Faz Kaydırmalı 2 MSPS Örnekleme (`MAX4466`, `0.96" IPS Ekran`)**
   - *Kavram:* İki ayrı 1 MSPS ADC'yi 180 derece faz farkıyla (Interleaved) çalıştırarak toplamda **2 MSPS** örnekleme hızına ulaşma ve yüksek frekanslı akustik sinyalleri yakalama.
10. **`10_fpu_quaternion_artificial_horizon`** — **9-DOF Quaternion Yönelim Hesaplayıcı ve 3B Küp/Ufuk Çizimi (`Pololu AltIMU-10 v5`, `0.96" IPS Ekran`)**
    - *Kavram:* Cortex-M4F'in tek çevrimlik float MAC (`VMLA.F32`) ve karekök (`VSQRT.F32`) komutlarından yararlanarak Quaternion tabanlı 3B tel-kafes küp ve yapay ufuk çizdirme.
11. **`11_custom_pendsv_rtos_kernel`** — **Sıfırdan Preemptive RTOS Çekirdeği (Context Switcher) Yazımı (`MPU6050`, `BMP180`, `0.91" OLED`)**
    - *Kavram:* `PendSV_Handler` içinde ARM Assembly (`MRS`, `STMDB`, `LDMIA`, `MSR`) ile `R4-R11` yazmaçlarını ve `PSP` yığın işaretçisini değiştirerek 3 ayrı görevi zaman dilimli çalıştıran **kendi mini-RTOS çekirdeğini** yazma.
12. **`12_acoustic_rpm_closed_loop_pid`** — **Akustik/İvme Geri Beslemeli Motor Devir (RPM) ve Yük Regülatörü (`HW-070`, `Motor Sürücüsü`, `MAX4466`, `0.96" IPS Ekran`)**
    - *Kavram:* `HW-070` ile hedef RPM değerini belirleyip, motorun akustik/titreşim frekansından gerçek devrini ölçerek yük değişse bile devri sabit tutan kapalı çevrim PID hız regülatörü yapma.

---

### 07. ST NUCLEO-U575ZI-Q (`07_ST_NUCLEO_U575ZI_Q/`)
**Odak Noktası:** Ultra-Low-Power (`STOP 0/1/2/3`, `STANDBY`), dahili SMPS (`-Q` serisi), **LPBAM** (CPU uyurken DMA ve çevrebirimlerin otonom çalışması), CORDIC/FMAC ve ARM **TrustZone**.

#### 🟢 Başlangıç Seviyesi (`01_beginner/`) — Temel Yapı Taşları
1. **`01_smps_power_and_bsrr_blink`** — **Blink & SMPS Güç Modu Doğrulaması (Dahili `LD1/LD2/LD3`, `B1` Butonu)**
   - *Kavram:* Dahili SMPS regülatörünü aktif ederek `GPIOx_BSRR` atomik yazmacıyla Blink yapma, butonu okuma ve `LPUART1` konsol çıkışını doğrulama.
2. **`02_timer_pwm_breathe_led`** — **Donanım Timer PWM ile LED Nefes Alma Efekti (Harici Renkli LED)**
   - *Kavram:* STM32 Timer donanımını kullanarak işlemciyi yormadan PWM sinyali üretme ve LED parlaklığını yumuşakça değiştirme.
3. **`03_adc14_single_channel_reading`** — **14-Bit ADC ile Analog Voltaj Okuma ve Eşik Algılama (Potansiyometre/Sensör)**
   - *Kavram:* STM32U5'in 14-bit ADC'sini kullanarak analog voltaj okuma ve belirlenen eşik aşıldığında durum LED'ini yakma.
4. **`04_i2c_oled_climate_display`** — **I2C 0.91" OLED Ekran ve BMP180 Sıcaklık/Basınç İstasyonu (`0.91" OLED`, `BMP180`)**
   - *Kavram:* Donanımsal I2C hattı üzerinden BMP180 sensörünü okuyup 0.91" OLED ekranda temiz bir kullanıcı arayüzü ile gösterme.

#### 🟡 Orta Seviye (`02_intermediate/`)
5. **`05_stop2_rtc_forced_bmp280`** — **STOP2 Uyku Modu ve RTC Wakeup ile Yıllarca Yaşayan Hava İstasyonu (`GY-BMP280`, `0.91" OLED`, `LiPo Şarj Entegresi`)**
   - *Kavram:* İşlemciyi mikroamper seviyesinde akım çeken **STOP2** moduna sokma, RTC Wakeup Timer ile uyanıp `GY-BMP280`'i **Forced Mode**'da okuma ve tekrar uykuya dalma.
6. **`06_analog_watchdog_rc_filter_wake`** — **Analog Watchdog (AWD) ve RC Filtreli PWM Voltaj İzleyici (`MAX4466`, `HW-070`, `10kΩ Direnç`, `0.91" OLED`)**
   - *Kavram:* İşlemci uyku modundayken `ADC4`'ün **Analog Watchdog** özelliğini kullanarak ses veya hız referansı eşiği aştığı anda donanımsal kesme üretip CPU'yu uyandırma.
7. **`07_gpdma_linked_list_imu_reader`** — **GPDMA Bağlantılı Liste (Linked-List) ile Çoklu Sensör Okuma (`Pololu AltIMU-10 v5`, `0.96" IPS Ekran`)**
   - *Kavram:* STM32U5'in **GPDMA** kontrolcüsünü Linked-List modunda kurarakve **CORDIC** trigonometri hızlandırıcısını kullanarak 10-DOF IMU verilerini otonom işleme.
8. **`08_rng_aes_encrypted_flash_log`** — **Donanımsal RNG ve Kriptografi ile Şifreli Sensör Günlüğü (`MLX90614`, `MPU6050`, `0.91" OLED`)**
   - *Kavram:* Donanımsal Rastgele Sayı Üreteci (**RNG**) kullanarak `MLX90614` ve `MPU6050` verilerini bütünlük kodlu şekilde Flash belleğin ayrılmış sayfasına kaydetme.

#### 🔴 İleri Seviye (`03_advanced/`)
9. **`09_lpbam_autonomous_sensor_batch`** — **LPBAM (Low-Power Background Autonomous Mode) ile CPU Uyurken Veri Toplama (`MAX4466`, `GY-BMP280`, `0.96" IPS Ekran`)**
   - *Kavram:* CPU tamamen **STOP2** uykusundayken `LPTIM` + `LPDMA` + `ADC4/I2C3` çevrebirimlerinin kendi başlarına 100 örnek toplayıp SRAM'e yazmasını ve sadece tampon dolunca CPU'yu uyandırmasını sağlama.
10. **`10_trustzone_secure_motor_guard`** — **ARM TrustZone ile Güvenli (Secure) ve Güvensiz (Non-Secure) Bölge Ayrımı (`MLX90614`, `0.96" IPS Ekran`, `Motor Sürücüsü`, `HW-070`)**
    - *Kavram:* Belleği ve çevrebirimleri **TrustZone** ile ikiye bölme: Kritik sıcaklık ve motor sınır kontrolünü **Secure World** içine alıp ekran çizimini **Non-Secure World**'de çalıştırma.
11. **`11_freefall_interrupt_blackbox`** — **Serbest Düşüş ve Darbe Algılayan Kara Kutu (`MPU6050`, `BMP180`, `0.91" OLED`)**
    - *Kavram:* `MPU6050`'nin donanımsal **Free-Fall / Motion Interrupt** özelliğini Wakeup pinine bağlayarak, darbe anında uyanıp darbe öncesi/sonrası verileri dairesel tampondan Flash'a kaydetme.
12. **`12_dynamic_voltage_scaling_profiler`** — **Dinamik Voltaj Ölçekleme (VOS) ve FMAC Filtreli Enerji Profilleyici (`Pololu AltIMU-10 v5`, `MAX4466`, `0.96" IPS Ekran`)**
    - *Kavram:* İşlemci yüküne göre çalışma anında frekansı (4 MHz MSI ↔ 160 MHz PLL), **FMAC** filtre hızlandırıcısını ve güç regülatörü kademesini (**Range 4 ↔ Range 1**) dinamik değiştiren güç yöneticisi tasarlama.

---

### 08. ST P-NUCLEO-WB55 (`08_ST_P_NUCLEO_WB55/`)
**Odak Noktası:** Cortex-M0+ radyo çekirdeği (BLE 5.0, Zigbee, 802.15.4), Cortex-M4 uygulama çekirdeği, çekirdekler arası **IPCC / HSEM** haberleşmesi ve paket içindeki **USB Dongle** ile çift taraflı kablosuz ağ kurma.

#### 🟢 Başlangıç Seviyesi (`01_beginner/`) — Temel Yapı Taşları
1. **`01_dual_core_hsem_and_dongle_blink`** — **Dual-Core Blink & HSEM Doğrulaması (Nucleo & USB Dongle LED)**
   - *Kavram:* Donanım semaforlarını (`HSEM`) ve çift çekirdekli mimaride GPIO erişimini doğrulama; harici LED üzerinde temel Blink yapma.
2. **`02_timer_pwm_breathe_led`** — **Timer PWM ile LED Parlaklık ve Nefes Alma Efekti (Harici Renkli LED)**
   - *Kavram:* Donanımsal Timer PWM kanalı kullanarak harici LED'in parlaklığını nefes alma (Fade) efektiyle pürüzsüz kontrol etme.
3. **`03_adc_audio_envelope_alert`** — **ADC ile Analog Giriş Okuma ve Eşik Algılama (`MAX4466` / Potansiyometre, LED)**
   - *Kavram:* 12-bit ADC ile mikrofon veya analog potansiyometre voltajını okuma; ses/voltaj seviyesine göre durum LED'lerini yakma.
4. **`04_i2c_oled_climate_display`** — **I2C 0.91" OLED Ekran ve BMP180 İstasyonu (`0.91" OLED`, `BMP180`)**
   - *Kavram:* I2C1 hattı üzerinden BMP180 sensörünü okuyup 0.91" OLED ekranda oda sıcaklık ve basıncını temiz bir arayüzle gösterme.

#### 🟡 Orta Seviye (`02_intermediate/`)
5. **`05_custom_ble_gatt_weather_server`** — **Özel BLE GATT Sunucusu (Custom Service & Characteristic) (`GY-BMP280`, `DHT11`, `0.91" OLED`)**
   - *Kavram:* STM32_WPAN ara katmanını kullanarak 128-bit UUID'li özel bir BLE servisi oluşturma; telefondaki ST BLE Toolbox uygulamasından `Read` ve `Notify` ile sıcaklık/nem/basınç verilerini izleme.
6. **`06_ble_hybrid_remote_motor_control`** — **BLE Üzerinden Uzaktan ve Manuel (Hibrit) Motor Kontrolü (`Motor Sürücüsü`, `HW-070`, `HC-SR04`, `HW-131`)**
   - *Kavram:* Telefondan gönderilen BLE paketleriyle veya masa üzerindeki `HW-070` ile `Motor Sürücüsü` hızını kontrol etme; `HC-SR04` yakın engel gördüğünde otonom koruma sağlama.
7. **`07_p2p_nucleo_to_usb_dongle_bridge`** — **Nucleo-68 + USB Dongle ile Noktadan Noktaya (P2P) Kablosuz Köprü (`MPU6050`, `0.96" IPS Ekran`)**
   - *Kavram:* Kutudan çıkan **USB Dongle**'ı **BLE Central (İstemci)**, **Nucleo-68** kartını ise `MPU6050` bağlı **BLE Peripheral (Sunucu)** olarak programlayarak iki kart arasında doğrudan kablosuz veri hattı kurma.
8. **`08_ble_connection_interval_power_opt`** — **BLE Bağlantı Aralığı (Connection Interval) ve Güç Optimizasyonu (`MLX90614`, `LiPo Şarj Entegresi`)**
   - *Kavram:* BLE bağlantısı kopmadan sistemin uyku moduna girebilmesi için **Connection Interval**, **Slave Latency** ve **Supervision Timeout** parametrelerini optimize etme.

#### 🔴 İleri Seviye (`03_advanced/`)
9. **`09_ieee_802154_mac_sensor_network`** — **IEEE 802.15.4 MAC Katmanında Özel Kablosuz Sensör Ağı (`Pololu AltIMU-10 v5`, `0.96" IPS Ekran`)**
   - *Kavram:* Cortex-M0+ çekirdeğine BLE yerine **802.15.4 MAC** yığınını yükleyerek, Nucleo kartı ile USB Dongle arasında endüstriyel sensör telemetrisi taşıyan düşük gecikmeli çerçeveler gönderme.
10. **`10_zigbee_ble_mesh_smart_room_node`** — **BLE Mesh veya Zigbee Akıllı Oda Düğümü (`DHT11`, `GY-BMP280`, `Motor Sürücüsü`, `0.91" OLED`)**
    - *Kavram:* Sıcaklık ve nem sınır değerin üzerine çıktığında `Motor Sürücüsü`ne bağlı fanı otomatik çalıştıran ve durumunu Zigbee Cluster / BLE Mesh modeli üzerinden ağa bildiren otonom düğüm tasarlama.
11. **`11_ble_ota_wireless_firmware_update`** — **BLE OTA (Over-The-Air) Kablosuz Firmware Güncelleme (`0.96" IPS Ekran`, `BMP180`)**
    - *Kavram:* STM32WB'nin `BLE_Ota` önyükleyicisini ve Flash bellek sektör yapısını yapılandırarak, yeni bir sensör ekran tasarımını kablo takmadan telefon üzerinden karta yükleme.
12. **`12_ipcc_2m_phy_highspeed_imu_stream`** — **IPCC Derinlemesine Analizi ve Yüksek Hızlı IMU Akışı (`MPU6050`, `MAX4466`)**
    - *Kavram:* BLE MTU boyutunu 247 bayta çıkarıp **2M PHY** modunu aktif ederek, `MPU6050` ve `MAX4466` verilerini paket kaybı olmadan maksimum bant genişliğinde kablosuz aktarma.

---

### 09. ST NUCLEO-H723ZG (`09_ST_NUCLEO_H723ZG/`)
**Odak Noktası:** 550 MHz hız, Çift Hassasiyetli FPU, ARM CMSIS-DSP kütüphanesi, Önbellek (I-Cache / D-Cache) tutarlılığı, gelişmiş DMA (MDMA/BDMA) ve yüksek hızlı sinyal işleme.

#### 🟢 Başlangıç Seviyesi (`01_beginner/`) — Temel Yapı Taşları
1. **`01_550mhz_pll_and_dwt_cycle_blink`** — **Blink & 550 MHz Mimari Doğrulaması (Dahili LD1/LD2/LD3)**
   - *Kavram:* 550 MHz Cortex-M7 mimarisinde D-Cache ve saat ağacını yapılandırarak atomik GPIO çıkışı ve temel Blink kontrolü.
2. **`02_timer_pwm_breathe_led`** — **550 MHz Timer PWM ile LED Nefes Alma Efekti (Harici Renkli LED)**
   - *Kavram:* Yüksek hızlı timer çevrebirimini kullanarak donanımsal PWM üretme ve LED parlaklığını nefes alma efektiyle yumuşakça kontrol etme.
3. **`03_adc16_single_channel_pot`** — **16-Bit Yüksek Çözünürlüklü ADC ile Analog Voltaj Okuma (Potansiyometre/Sensör)**
   - *Kavram:* H7'nin 16-bit ADC çeviricisini kullanarak gürültüsüz analog voltaj okuma ve eşik değere göre durum LED'ini tetikleme.
4. **`04_i2c_oled_climate_display`** — **I2C 0.91" OLED Ekran ve BMP180 Basınç/Sıcaklık İstasyonu (`0.91" OLED`, `BMP180`)**
   - *Kavram:* I2C donanım modülü üzerinden BMP180 sensörünü okuyup 0.91" OLED ekranda temiz bir kullanıcı arayüzü ile gösterme.

#### 🟡 Orta Seviye (`02_intermediate/`)
5. **`05_dma_dcache_coherency_ips_gui`** — **DMA + D-Cache Tutarlılığı (Cache Coherency) ile Yüksek Hızlı Ekran Sürüşü (`0.96" IPS Ekran`, `MLX90614`)**
   - *Kavram:* Cortex-M7'de D-Cache açıkken DMA kullanıldığında oluşan veri bozulmasını `SCB_CleanDCache_by_Addr()` veya MPU ayarlarıyla çözerek `0.96" IPS` ekranda 60+ FPS termal gösterge paneli yapma.
6. **`06_hardware_smbus_pec_mlx90614`** — **Donanımsal SMBus ve PEC (CRC-8) Doğrulamalı Kızılötesi Termometre (`MLX90614`, `0.91" OLED`)**
   - *Kavram:* `MLX90614`'ü standart I2C yerine STM32'nin donanımsal **SMBus** modunda çalıştırma ve veri bütünlüğü için **PEC (Packet Error Code - CRC8)** baytını donanımsal doğrulama.
7. **`07_async_i2c_dma_altimu10_fsm`** — **Çoklu I2C Cihazı ve Kesme Güdümlü Durum Makinesi (`Pololu AltIMU-10 v5`, `0.96" IPS Ekran`)**
   - *Kavram:* Bloklayıcı fonksiyonlar yerine `HAL_I2C_Mem_Read_DMA` ve Callback fonksiyonlarıyla 3 ayrı sensör çipini (`LSM6DS33`, `LIS3MDL`, `LPS25H`) asenkron durum makinesi içinde okuma.
8. **`08_timer_trgo_adc_fir_voice_filter`** — **Timer Tetiklemeli (`TRGO`) ADC ve Dijital Ses Filtresi (`MAX4466`, `0.96" IPS Ekran`)**
   - *Kavram:* Bir Timer'ın `TRGO` çıkışıyla ADC'yi tam 44.1 kHz'de tetikleme; gelen ses verisine gerçek zamanlı **FIR / IIR Dijital Bant Geçiren Filtre** uygulayarak sadece insan sesi frekanslarını geçirme.

#### 🔴 İleri Seviye (`03_advanced/`)
9. **`09_cmsis_dsp_1024fft_spectrogram`** — **CMSIS-DSP ile 1024-Nokta Gerçek Zamanlı Ses Spektrogramı (`MAX4466`, `0.96" IPS Ekran`)**
   - *Kavram:* ARM **CMSIS-DSP** kütüphanesindeki `arm_rfft_fast_f32` ve Hanning pencereleme fonksiyonlarını kullanarak 550 MHz'de gerçek zamanlı **Şelale Spektrogram (Waterfall Spectrogram)** hesaplayıp renkli IPS ekrana basma.
10. **`10_10dof_extended_kalman_filter`** — **10-DOF Genişletilmiş Kalman Filtresi (EKF) ile 3B Yönelim (`Pololu AltIMU-10 v5`, `MPU6050`)**
    - *Kavram:* Matris çarpımı ve tersi (`arm_mat_mult_f32`, `arm_mat_inverse_f32`) işlemlerini CMSIS-DSP ile hızlandırarak 10 eksenli tam bir **Extended Kalman Filter** gerçekleme.
11. **`11_1khz_discrete_pid_cubemonitor`** — **Yüksek Frekanslı (1 kHz) Kapalı Çevrim PID Kontrol ve Sistem Tanılama (`Motor Sürücüsü`, `MPU6050`, `HC-SR04`)**
    - *Kavram:* Anti-windup ve türev filtresi içeren ayrık zamanlı PID kontrolcüyü 1 kHz donanım kesmesinde koşturma; STM32CubeMonitor ile değişkenleri çalışma anında bellekten izleyip grafikleme.
12. **`12_rtos_priority_inversion_controller`** — **FreeRTOS / ThreadX ile Çok Görevli Endüstriyel Denetleyici (`MLX90614`, `GY-BMP280`, `MAX4466`, `0.96" IPS Ekran`)**
    - *Kavram:* Öncelik tersinmesini (Priority Inversion) önleyen `Mutex`, `Event Flags` ve `Message Queue` yapılarını kullanarak; veri toplama, DSP analizi, ekran çizimi ve CLI görevlerini eşzamanlı koşturma.

---

### 10. Raspberry Pi Zero W V1.1 (`10_RPi_Zero_W_Linux/`)
**Odak Noktası:** **Gömülü Linux (Embedded Linux)** mimarisi, kullanıcı uzayı C/Python donanım erişimi (`/dev/i2c-*`, `/dev/spidev*`, `libgpiod`), Linux daemon servisleri, merkezi IoT sunucusu ve **Raspberry Pi Camera Multiplexer**.

#### 🟢 Başlangıç Seviyesi (`01_beginner/`)
1. **`01_linux_sysfs_and_libgpiod_blink`** — **Gömülü Linux Blink: `/sys/class/leds/ACT` Tetikleyicileri ve `libgpiod` (Dahili `ACT` LED & Breadboard 8 LED)**
   - *Kavram:* Önce `/sys/class/leds/ACT/trigger` dosyasına `none`, `heartbeat` veya `timer` yazarak kart üzerindeki yeşil LED'i kontrol etme, ardından C/Python ve `libgpiod` (`/dev/gpiochip0`) ile harici LED'lerde Blink yapma ve Linux zamanlama sapmasını (Jitter) gözlemleme.
2. **`02_userspace_i2c_dev_sensor_driver`** — **Linux `/dev/i2c-1` Karakter Cihazı ile Ham Sensör Sürücüsü (`BMP180`, `MLX90614`)**
   - *Kavram:* Hazır kütüphane kullanmadan Linux sistem çağrıları (`open("/dev/i2c-1")`, `ioctl(fd, I2C_SLAVE, addr)`, `read()`, `write()`) ile C dilinde kendi `BMP180` ve `MLX90614` kullanıcı uzayı sürücünü yazma.
3. **`03_spidev_proc_system_monitor_ips`** — **Linux `/dev/spidev0.0` ile Sistem Kaynak Monitörü Ekranı (`0.96" 80x160 RGB IPS Ekran`, `Durum LED'leri`)**
   - *Kavram:* Linux `/proc/stat`, `/proc/meminfo` ve `/sys/class/thermal/thermal_zone0/temp` dosyalarından CPU yükünü, RAM kullanımını ve işlemci sıcaklığını okuyup SPI `0.96" IPS` ekranda canlı sistem monitörü olarak gösterme.
4. **`04_camera_multiplexer_channel_switcher`** — **Raspberry Pi Camera Multiplexer Kurulumu ve Kanal Anahtarlama (`RPi Camera Multiplexer`, `0.91" OLED`, `4x LED`)**
   - *Kavram:* `Raspberry Pi Camera Multiplexer` kartının GPIO seçim pinlerini ve I2C çoklayıcı hattını kontrol ederek kamera kanalları arasında sırayla geçiş yapma ve aktif kanalı `0.91" OLED` ekranda ve LED'lerde gösterme.

#### 🟡 Orta Seviye (`02_intermediate/`)
5. **`05_sonar_acoustic_security_camera`** — **Ultrasonik ve Ses Tetiklemeli Çok Açılı Güvenlik Kamerası (`RPi Camera Multiplexer`, `HC-SR04`, `Mikrofon Modülü`)**
   - *Kavram:* `HC-SR04` yaklaşma veya `Mikrofon Modülü` ses algıladığında `RPi Camera Multiplexer` üzerinden ilgili kameraya geçerek zaman damgalı görüntü/log kaydeden servis.
6. **`06_thermal_osd_overlay_inspection_cam`** — **Termal + Görsel (Overlay) Muayene Kamerası (`RPi Camera Multiplexer`, `MLX90614`, `HW-070`, `0.96" IPS Ekran`)**
   - *Kavram:* Güç devrelerinin üzerine tutulan kameranın görüntüsünün merkezine `MLX90614`'ten okunan kızılötesi sıcaklığı ve nişangah grafiğini bindirip (OSD Overlay) `0.96" IPS` ekranda ve web arayüzünde gösterme.
7. **`07_linux_iio_device_tree_overlay`** — **Linux IIO (Industrial I/O) Alt Sistemi ve Device Tree Overlay (`GY-BMP280`, `MPU6050`)**
   - *Kavram:* Sensörleri kullanıcı uzayında yoklamak yerine, Linux çekirdeğinin yerleşik sürücülerini **Device Tree Overlay (`config.txt` / `.dts`)** ile yükleyerek sensör verilerini doğrudan `/sys/bus/iio/devices/iio:device0/` altından okuma.
8. **`08_systemd_daemon_sqlite_logger`** — **Systemd Arka Plan Servisi (Daemon) ve SQLite Zaman Serisi Veritabanı (`DHT11`, `GY-BMP280`, `0.91" OLED`)**
   - *Kavram:* Cihaz açıldığında otomatik başlayan, çökerse kendini yeniden başlatan bir Linux **systemd daemon** yazarak, sensör verilerini yerel bir **SQLite** veritabanına kaydetme.

#### 🔴 İleri Seviye (`03_advanced/`)
9. **`09_mosquitto_mqtt_edge_gateway`** — **Merkezi IoT Ağ Geçidi (Edge Gateway): Mosquitto MQTT Broker + Web Dashboard (`ESP32` / `WB55` / `Pico 2 W` ile birlikte, `0.96" IPS Ekran`)**
   - *Kavram:* RPi Zero W'yu yerel ağın merkezi sunucusu yapma: Diğer kartlardan gelen MQTT/UDP sensör paketlerini toplayan, veritabanına yazan ve REST API / Web arayüzü sunan tam teşekküllü Edge Gateway.
10. **`10_pthread_sched_fifo_visual_inertial`** — **POSIX Threads (`pthread`), Mutex ve Gerçek Zamanlı (`SCHED_FIFO`) IMU + Kamera Senkronizasyonu (`Pololu AltIMU-10 v5`, `RPi Camera Multiplexer`)**
    - *Kavram:* C dilinde çok iş parçacıklı (`pthread`) mimari kurup, IMU okuma thread'ine gerçek zamanlı zamanlama politikası (`SCHED_FIFO`) vererek kamera kareleriyle 3B yönelim verisini mikrosaniye bazında eşleştirme.
11. **`11_hybrid_linux_mcu_robotics_brain`** — **Hibrit Mimari: RPi Zero W (Linux Üst Beyin) + Mikrodenetleyici (Gerçek Zamanlı Alt Kontrolcü) (`Motor Sürücüsü`, `MPU6050`, `MAX4466`)**
    - *Kavram:* Linux'un zayıf olduğu gerçek zamanlı PWM/ADC işlerini UART/SPI üzerinden bağlı bir mikrodenetleyiciye devredip, RPi Zero W üzerinde yüksek seviyeli karar ve kamera işleme yürütme.
12. **`12_custom_linux_kernel_module_driver`** — **Özel Linux Karakter Sürücüsü (Kernel Module - LKM) Yazımı (`HW-070`, `HC-SR04`, `LED'ler`)**
    - *Kavram:* C dilinde kendi **Linux Kernel Module (`.ko`)** sürücünü yazarak (`module_init`, `file_operations`, `gpio_to_irq`, `ktime_get_ns`), `/dev/pwm_sonar` adında bir cihaz düğümü oluşturma ve çekirdek uzayında (Kernel-space) kesme ile darbe süresi ölçme.

---

### 11. Tang Nano 9K FPGA (`11_Tang_Nano_9K_FPGA/`)
**Odak Noktası:** Yazılan **Verilog / VHDL** kodunun doğrudan kapı devrelerine, flip-floplara ve **tamamen paralel** çalışan gerçek donanıma dönüşmesi! Kendi PWM, UART, I2C, SPI donanımlarını ve Soft-Core RISC-V işlemcini tasarlama.

#### 🟢 Başlangıç Seviyesi (`01_beginner/`)
1. **`01_verilog_clock_divider_led_blink`** — **Donanım Seviyesinde Blink: 27 MHz Saat Bölücü ve Yürüyen Işık (Dahili 6 Turuncu LED, `S1/S2` Butonları & Harici 8 LED)**
   - *Kavram:* FPGA'da zamanın **27 MHz kristali sayan 25-bitlik bir flip-flop sayacı (`reg [24:0] cnt`)** ile ölçüldüğünü öğrenme; Pin kısıtlama dosyasını (`.cst`) yazıp Gowin IDE ile sentezleyerek dahili ve harici LED'lerde yürüyen ışık ve 4-bit ALU devresi kurma.
2. **`02_hardware_pwm_and_sonar_counter`** — **Donanımsal PWM Görev Döngüsü Çözücü ve Ultrasonik Mesafe Sayacı (`HW-070`, `HC-SR04`, `10x Renkli LED`)**
   - *Kavram:* İşlemci olmadan, sadece sayaçlar (Counters) ve karşılaştırıcı kapılar kullanarak `HW-070` görev döngüsünü ve `HC-SR04` mesafesini ölçüp 10 LED üzerinde bar-grafik olarak gösterme.
3. **`03_custom_uart_tx_rx_hardware`** — **Sıfırdan UART TX/RX Donanımı Tasarımı ve Mesafe/PWM Raporlama (`HC-SR04`, `HW-070`)**
   - *Kavram:* Baud Rate üreteci (27 MHz $\rightarrow$ 115200 baud), başlangıç biti, 8 veri biti ve durdurma bitini kaydıran (Shift Register) kendi **UART Transmitter/Receiver** donanımını Verilog ile yazıp ölçümleri PC terminaline basma.
4. **`04_hbridge_interlock_logic_circuit`** — **Çift Kanallı H-Köprüsü Motor Kontrol ve Yön Mantık Devresi (`Motor Sürücüsü`, `HW-070`, `HW-131`, `HC-SR04`)**
   - *Kavram:* `HW-070`'ten gelen hız darbesini okuyup, buton kombinasyonlarına ve engel mesafesine (`HC-SR04`) göre `Motor Sürücüsü` sinyallerini **1 saat vuruşunda (37 ns gecikmeyle!)** üreten donanımsal güvenlik kilidi (Interlock) bloğu.

#### 🟡 Orta Seviye (`02_intermediate/`)
5. **`05_tristate_fsm_dht11_decoder`** — **Verilog ile Özel DHT11 Tek Hat (One-Wire) Protokol Çözücü (`DHT11`)**
   - *Kavram:* Çift yönlü (`inout` / Tri-state buffer `assign dq = oe ? out_bit : 1'bz;`) pin yapısını FPGA'da kurarak, `DHT11`'in 18ms başlatma ve 40-bit okuma evrelerini yöneten 6 durumlu bir **Sonlu Durum Makinesi (FSM)** yazma.
6. **`06_i2c_master_fsm_oled_initializer`** — **Sıfırdan I2C Master Donanımı ve SSD1306 OLED Başlatıcı (`0.91" OLED`)**
   - *Kavram:* Başlatma (START), adresleme, ACK kontrolü ve durdurma (STOP) bitlerini üreten bir **I2C Master FSM** ve FPGA içindeki **BSRAM (Block RAM / ROM)**'da tutulan başlatma komutlarını `0.91" OLED`'e gönderen donanım.
7. **`07_spi_master_st7735_gpu_accelerator`** — **Sıfırdan SPI Master ve ST7735 Donanımsal Desen Üreteci (`0.96" 80x160 RGB IPS Ekran`)**
   - *Kavram:* 27 MHz hızında çalışan **SPI Master** donanımıyla `0.96" IPS` ekrana renk barları, hareketli plazma efekti ve metin basan **Donanımsal Grafik Hızlandırıcı**.
8. **`08_pure_hardware_i2c_imu_oled`** — **I2C Sensör Okuma Donanımı ve OLED Gösterge (`MPU6050` veya `MLX90614`, `0.91" OLED`)**
   - *Kavram:* Hiçbir mikrodenetleyici veya C kodu kullanmadan, tamamen Verilog durum makineleriyle `MPU6050` veya `MLX90614` yazmaçlarını periyodik okuyup değeri `0.91" OLED` ekrana çizen saf donanım sistemi.

#### 🔴 İleri Seviye (`03_advanced/`)
9. **`09_true_parallel_multi_sensor_engine`** — **Tamamen Donanımsal (Parallel Hardware) Çoklu Sensör Toplayıcı (`HC-SR04`, `DHT11`, `MPU6050`, `0.96" IPS Ekran`)**
   - *Kavram:* FPGA'nın gerçek **paralel** gücünü görme: `HC-SR04`, `DHT11`, `MPU6050` ve `0.96" IPS` ekran sürücü bloklarının birbirini hiç bekletmeden, tamamen bağımsız paralel donanımlar olarak aynı anda çalışması.
10. **`10_pipelined_cordic_angle_processor`** — **CORDIC Algoritması ile Donanımsal Açı Hesaplayıcı (`MPU6050`, `0.96" IPS Ekran`)**
    - *Kavram:* Çarpma veya bölme kullanmak yerine, sadece toplama ve bit kaydırma (Shift-and-Add) ile çalışan boru hatlı (**Pipelined CORDIC**) donanımı tasarlayarak `MPU6050` ivme verisinden gerçek zamanlı eğim açısı hesaplama.
11. **`11_hdmi_720p_digital_oscilloscope`** — **Tang Nano 9K HDMI Çıkışı ile Canlı Dijital Osiloskop ve Sensör Paneli (`HW-070`, `MPU6050`, `HC-SR04`)**
    - *Kavram:* Tang Nano 9K üzerindeki **HDMI (TMDS)** çıkışını sürerek 720p çözünürlükte monitöre görüntü verme; `HW-070` PWM kare dalgasını ve `MPU6050` verilerini monitörde gecikmesiz dijital osiloskop olarak çizdirme.
12. **`12_picorv32_softcore_riscv_soc`** — **FPGA İçine Kendi İşlemcini Gömme: PicoRV32 (Soft-Core RISC-V SoC) (`Pololu AltIMU-10 v5`, `0.91" OLED`, `HW-070`)**
    - *Kavram:* FPGA içine açık kaynaklı **PicoRV32 (32-bit RISC-V)** işlemci çekirdeğini sentezleyip, yanına kendi yazdığın bellek eşlemeli (Memory-Mapped) `HW-070` PWM okuyucu ve I2C donanımlarını bağlayarak, kendi tasarladığın işlemcinin üzerinde C kodu çalıştırma.
