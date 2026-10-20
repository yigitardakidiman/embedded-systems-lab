# 04 — I2C 0.91" OLED Ekran ile Metin Göstergesi (SSD1306)

Bu proje, **ESP-WROOM-32** mikrodenetleyicisinin donanımsal **I2C (Inter-Integrated Circuit)** haberleşme birimini (`driver/i2c_master.h`) ve **GPIO Matrix** yönlendirme mimarisini kullanarak **0.91" 128x32 SSD1306 OLED** ekran üzerinde sayfa adresleme (*Page Addressing*) mantığıyla metin görüntülemeyi hedefler.

---

## 🎯 Hedefler ve Öğrenilen Kavramlar

1. **I2C Haberleşme Protokolü (2 Telli Senkron Veri Yolu):**
   - **`SDA` (Serial Data):** Çift yönlü seri veri hattı.
   - **`SCL / SCK` (Serial Clock):** Master (ESP32) tarafından üretilen senkronizasyon saat sinyali.
   - **7-Bit Cihaz Adresleme:** SSD1306 kontrolcüsüyle `0x3C` donanım adresi üzerinden el sıkışma (`ACK`) ve veri paketleme.
2. **ESP32 GPIO Matrix ve Saf Dijital Pin Seçimi:**
   - ESP32'nin dahili **GPIO Matrix** birimi sayesinde donanımsal `I2C_NUM_0` çevrebirimini saf dijital IO_MUX pinleri olan **`GPIO 16` (SDA)** ve **`GPIO 17` (SCL)** uçlarına yönlendirme.
3. **SSD1306 Sayfa (Page) Mimarisi:**
   - `128x32` piksellik ekranın dikeyde 8 piksellik 4 yatay şeride (**Page 0, Page 1, Page 2, Page 3**) bölünmesi ve her satırda `8x8` font ile 16 karakterlik metin basılması.

---

## 🧰 Donanım Listesi

| Bileşen | Miktar | Açıklama |
| :--- | :---: | :--- |
| **ESP-WROOM-32** | 1 | Geliştirme Kartı |
| **0.91" OLED Ekran** | 1 | `128x32` Piksel, I2C Arayüzlü (`SSD1306`, Adres: `0x3C`) |
| **Breadboard & Jumper** | 1 Set | Devre bağlantıları için |

---

## 🔌 Pin Bağlantı Tablosu

| OLED Ekran Pini | ESP-WROOM-32 Pini | İşlev / Donanım Kanalı | Not |
| :--- | :--- | :--- | :--- |
| **GND** | **GND** | Toprak Hattı | Ortak GND |
| **VCC** | **3V3** | Güç Beslemesi (`3.3V`) | 3.3V Lojik/Besleme |
| **SDA** | **GPIO 16 (RX2 / D16)** | `I2C_NUM_0` Veri Hattı | GPIO Matrix ile yönlendirildi |
| **SCK / SCL** | **GPIO 17 (TX2 / D17)** | `I2C_NUM_0` Saat Hattı | GPIO Matrix ile yönlendirildi |

---

## 📐 Devre Şeması

```text
        ESP-WROOM-32                   0.91" I2C OLED (128x32)
      +---------------+               +-----------------------+
      |           3V3 |-------------->| VCC                   |
      |           GND |-------------->| GND                   |
      |               |               |  +-----------------+  |
      |  GPIO 16 (SDA)|<------------->|  |  Hello World!   |  |
      |  GPIO 17 (SCK)|-------------->|  |   I'm KIDIMAN   |  |
      |               |               |  +-----------------+  |
      +---------------+               +-----------------------+
```

---

## 💻 Kaynak Kod (`main/main.c`)

```c
#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/i2c_master.h"
#include "driver/gpio.h"
#include "esp_err.h"
#include "esp_log.h"
#include "ssd1306.h"

#define I2C_SDA_PIN GPIO_NUM_16
#define I2C_SCK_PIN GPIO_NUM_17

void app_main(void)
{
    i2c_master_bus_config_t i2c_bus_cfg = {
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .i2c_port = I2C_NUM_0,
        .scl_io_num = I2C_SCK_PIN,
        .sda_io_num = I2C_SDA_PIN,
        .glitch_ignore_cnt = 7,
        .flags.enable_internal_pullup = true,
    };
    i2c_master_bus_handle_t bus_hdl;
    ESP_ERROR_CHECK(i2c_new_master_bus(&i2c_bus_cfg, &bus_hdl));

    ssd1306_config_t dev_cfg = I2C_SSD1306_128x32_CONFIG_DEFAULT;
    ssd1306_handle_t dev_hdl;
    ESP_ERROR_CHECK(ssd1306_init(bus_hdl, &dev_cfg, &dev_hdl));

    ssd1306_clear_display(dev_hdl, false);
    ssd1306_set_contrast(dev_hdl, 0xff); // Maksimum parlaklık

    ssd1306_display_text(dev_hdl, 2, " Hello World! ", false);
    ssd1306_display_text(dev_hdl, 3, " I'm KIDIMAN ", false);

    while (1) {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
```

---

## 🔨 Derleme ve Karta Yükleme

```powershell
# 1. ESP-IDF ortamını aktifleştirin
$env:IDF_TOOLS_PATH = "C:\Espressif"
. C:\esp\v6.1\esp-idf\export.ps1

# 2. Proje dizinine geçin
cd 01_ESP_WROOM_32/01_beginner/04_i2c_oled_display

# 3. Bağımlılığı çekin, derleyin ve karta yükleyin
idf.py -p COM4 build flash monitor
```
