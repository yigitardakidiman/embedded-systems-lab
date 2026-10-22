#include <stdio.h>               // Standart C giriş/çıkış kütüphanesi
#include <string.h>              // Bellek ve metin/dizi işleme kütüphanesi
#include "freertos/FreeRTOS.h"   // FreeRTOS çekirdek veri tipleri ve sistem yapılandırması
#include "freertos/task.h"       // FreeRTOS görev (task) ve zamanlama (delay) fonksiyonları
#include "driver/i2c_master.h"   // ESP-IDF v5.x modern donanımsal I2C Master sürücüsü
#include "driver/gpio.h"         // ESP-IDF donanımsal GPIO pin tanımları ve numaralandırmaları
#include "esp_err.h"             // ESP-IDF hata kontrol makroları (ESP_ERROR_CHECK vb.)
#include "esp_log.h"             // ESP-IDF konsol loglama kütüphanesi (ESP_LOGI vb.)
#include "ssd1306.h"             // SSD1306 OLED ekran sürücüsü kütüphanesi

#define I2C_SDA_PIN GPIO_NUM_16  // I2C Seri Veri (SDA - Serial Data) hattının bağlı olduğu pin
#define I2C_SCK_PIN GPIO_NUM_17  // I2C Seri Saat (SCL/SCK - Serial Clock) hattının bağlı olduğu pin

void app_main(void)
{
    // 1. ADIM: Donanımsal I2C Veri Yolu (I2C Bus) Yapılandırması
    i2c_master_bus_config_t i2c_bus_cfg = {
        .clk_source                   = I2C_CLK_SRC_DEFAULT, // Varsayılan saat kaynağı (XTAL/APB saati)
        .i2c_port                     = I2C_NUM_0,           // ESP32'nin 0 numaralı I2C donanım kontrolcüsü
        .scl_io_num                   = I2C_SCK_PIN,         // Saat (SCL) hattı pini (GPIO 17)
        .sda_io_num                   = I2C_SDA_PIN,         // Veri (SDA) hattı pini (GPIO 16)
        .glitch_ignore_cnt            = 7,                   // Hatta oluşabilecek elektriksel gürültüleri filtreleme katsayısı
        .flags.enable_internal_pullup = true,                // I2C açık-kolektör (open-drain) yapıda olduğu için dahili pull-up'ları aç
    };
    
    // I2C Master veri yolunu temsil eden tanıtıcı (handle) işaretçisi
    i2c_master_bus_handle_t bus_hdl;
    
    // Yapılandırmayı donanıma uygula ve I2C yolunu başlat (hata dönerse ESP_ERROR_CHECK konsola yazıp durdurur)
    ESP_ERROR_CHECK(i2c_new_master_bus(&i2c_bus_cfg, &bus_hdl));

    // 2. ADIM: SSD1306 OLED Cihazını Yapılandırma ve Başlatma
    // 128x32 piksel OLED için varsayılan ayarları (I2C adresi: 0x3C, saat frekansı vb.) yükle
    ssd1306_config_t dev_cfg = I2C_SSD1306_128x32_CONFIG_DEFAULT;
    
    // OLED ekran cihazını temsil eden tanıtıcı (handle)
    ssd1306_handle_t dev_hdl;
    
    // Ekranı başlat ve I2C veri yoluna bağlayıp açılış komutlarını gönder
    ESP_ERROR_CHECK(ssd1306_init(bus_hdl, &dev_cfg, &dev_hdl));

    // 3. ADIM: Ekranı Temizleme ve Başlangıç Ayarları
    ssd1306_clear_display(dev_hdl, false); // Ekran hafızasını (GRAM) temizle (false: pikseller sönük/siyah)
    ssd1306_set_contrast(dev_hdl, 0xff);  // Ekran kontrastını/parlaklığını maksimuma ayarla (0xFF = 255)

    // 4. ADIM: Ekrana Metin Yazdırma
    // 2. satıra (Page 2) metin yazdır (false: normal metin, ters renk/invert değil)
    ssd1306_display_text(dev_hdl, 2, " Hello World! ", false);
    // 3. satıra (Page 3) metin yazdır
    ssd1306_display_text(dev_hdl, 3, " I'm KIDIMAN ", false);

    // 5. ADIM: Ana Bekleme Döngüsü
    while (1) {
        // Ekrandaki statik görüntü korunurken işlemciyi meşgul etmemek için görevi 1 saniye uyut
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
