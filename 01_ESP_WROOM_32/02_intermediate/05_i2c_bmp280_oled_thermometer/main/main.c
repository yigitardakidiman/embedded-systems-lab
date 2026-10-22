#include <stdio.h>               // Standart C giriş/çıkış kütüphanesi (snprintf vb. için)
#include <string.h>              // Bellek ve metin/karakter dizisi işlemleri kütüphanesi
#include "freertos/FreeRTOS.h"   // FreeRTOS çekirdek veri tipleri ve sistem yapılandırması
#include "freertos/task.h"       // FreeRTOS görev (task) ve zamanlama (delay) fonksiyonları
#include "driver/i2c_master.h"   // ESP-IDF v5.x modern donanımsal I2C Master sürücüsü
#include "driver/gpio.h"         // ESP-IDF donanımsal GPIO pin tanımları ve numaralandırmaları
#include "esp_err.h"             // ESP-IDF hata denetim makroları (ESP_ERROR_CHECK vb.)
#include "esp_log.h"             // ESP-IDF konsol loglama kütüphanesi (ESP_LOGI vb.)
#include "ssd1306.h"             // SSD1306 OLED ekran sürücüsü kütüphanesi
#include "bmp280.h"              // Bosch BMP280 sıcaklık ve barometrik basınç sensörü sürücüsü

#define I2C_SDA_PIN GPIO_NUM_16  // Ortak I2C Seri Veri (SDA - Serial Data) hattının bağlı olduğu pin
#define I2C_SCK_PIN GPIO_NUM_17  // Ortak I2C Seri Saat (SCL/SCK - Serial Clock) hattının bağlı olduğu pin

void app_main(void)
{
    // 1. ADIM: Donanımsal I2C Veri Yolu (I2C Bus) Yapılandırması
    // Hem OLED ekran hem BMP280 sensörü bu tek veri yolunu (bus) ortaklaşa paylaşacaktır.
    i2c_master_bus_config_t i2c_bus_cfg = {
        .clk_source                   = I2C_CLK_SRC_DEFAULT, // Varsayılan saat kaynağı (XTAL/APB saati)
        .i2c_port                     = I2C_NUM_0,           // ESP32'nin 0 numaralı I2C donanım kontrolcüsü
        .scl_io_num                   = I2C_SCK_PIN,         // Saat (SCL) hattı pini (GPIO 17)
        .sda_io_num                   = I2C_SDA_PIN,         // Veri (SDA) hattı pini (GPIO 16)
        .glitch_ignore_cnt            = 7,                   // Hatta oluşabilecek elektriksel gürültüleri filtreleme katsayısı
        .flags.enable_internal_pullup = true,                // I2C hatlarını 3.3V seviyesine çeken dahili pull-up dirençlerini aç
    };
    
    // Ortak I2C master veri yolunun tanıtıcı (handle) işaretçisi
    i2c_master_bus_handle_t bus_hdl;
    
    // I2C veri yolunu donanımsal olarak başlat ve hata varsa programı durdurup bildir
    ESP_ERROR_CHECK(i2c_new_master_bus(&i2c_bus_cfg, &bus_hdl));

    // 2. ADIM: SSD1306 OLED Ekranını Yapılandırma ve Başlatma
    // 128x32 piksel OLED için varsayılan ayarları yükle (Varsayılan I2C adresi: 0x3C)
    ssd1306_config_t dev_cfg = I2C_SSD1306_128x32_CONFIG_DEFAULT;
    ssd1306_handle_t dev_hdl;
    // OLED ekranı I2C veri yoluna bağlayıp açılış komutlarını göndererek hazırla
    ESP_ERROR_CHECK(ssd1306_init(bus_hdl, &dev_cfg, &dev_hdl));

    // 3. ADIM: BMP280 Sıcaklık ve Basınç Sensörünü Yapılandırma ve Başlatma
    bmp280_config_t bmp_cfg = I2C_BMP280_CONFIG_DEFAULT;
    // SDO pini GND'ye bağlıysa sensörün I2C adresi 0x76 (LO), 3.3V'a bağlıysa 0x77 (HI) olur
    bmp_cfg.i2c_address = I2C_BMP280_DEV_ADDR_LO;
    bmp280_handle_t bmp_hdl;
    // BMP280 sensörünü aynı I2C yoluna bağla, fabrika kalibrasyon katsayılarını oku ve başlat
    ESP_ERROR_CHECK(bmp280_init(bus_hdl, &bmp_cfg, &bmp_hdl));

    // 4. ADIM: Ekranı Başlangıç İçin Temizleme ve Parlaklık Ayarı
    ssd1306_clear_display(dev_hdl, false); // Ekran hafızasını (GRAM) temizle
    ssd1306_set_contrast(dev_hdl, 0xff);  // Ekran kontrastını/parlaklığını maksimuma ayarla (255)

    // 5. ADIM: Ana Ölçüm ve Güncelleme Döngüsü
    while (1) {
        float temp, pres; // Ölçülen sıcaklık (°C) ve basınç (Pa) değerlerini tutacak değişkenler
        char buf[17];     // 128 piksel ekranda 16 karakter + 1 null sonlandırıcı (\0) için metin tamponu

        // BMP280'den sıcaklık ve basınç değerlerini oku (Adres/pointer yöntemiyle değişkenlere yazar)
        bmp280_get_measurements(bmp_hdl, &temp, &pres);

        // Sıcaklık metnini formatla ve OLED ekranın 0. satırına (en üst satır) yazdır
        snprintf(buf, sizeof(buf), "Temp: %.1f C", temp);
        ssd1306_display_text(dev_hdl, 0, buf, false);

        // Basıncı Pascal'dan (Pa) Hektopaskal'a (hPa / milibar) çevirip 1. satıra yazdır (1 hPa = 100 Pa)
        snprintf(buf, sizeof(buf), "Pres: %.1f hPa", pres / 100.0f);
        ssd1306_display_text(dev_hdl, 1, buf, false);

        // Sensörü ve ekranı saniyede bir güncellemek için görevi 1 saniye uyut (CPU'yu serbest bırakır)
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
