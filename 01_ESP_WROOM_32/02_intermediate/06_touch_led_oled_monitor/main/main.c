#include <stdio.h>               // Standart C giriş/çıkış kütüphanesi (snprintf vb. için)
#include <string.h>              // Bellek ve metin/dizi işleme kütüphanesi
#include "freertos/FreeRTOS.h"   // FreeRTOS çekirdek veri tipleri ve sistem yapılandırması
#include "freertos/task.h"       // FreeRTOS görev (task) ve zamanlama (delay) fonksiyonları
#include "driver/gpio.h"         // ESP-IDF donanımsal GPIO sürücüsü (LED kontrolü)
#include "driver/touch_pad.h"    // ESP-IDF donanımsal kapasitif dokunmatik (Touch Pad) sürücüsü
#include "driver/i2c_master.h"   // ESP-IDF v5.x modern donanımsal I2C Master sürücüsü
#include "esp_err.h"             // ESP-IDF hata kontrol makroları (ESP_ERROR_CHECK vb.)
#include "esp_log.h"             // ESP-IDF konsol loglama kütüphanesi (ESP_LOGI vb.)
#include "ssd1306.h"             // SSD1306 OLED ekran kütüphanesi

#define TOUCH_PAD_CHANNEL TOUCH_PAD_NUM9  // ESP32 Donanımsal Dokunmatik Kanalı 9 (GPIO 32 pinine bağlı)
#define LED_GPIO_PIN      GPIO_NUM_25     // Harici LED'in bağlı olduğu GPIO pini (Çıkış)

#define I2C_SDA_PIN       GPIO_NUM_27     // OLED Ekran I2C Seri Veri (SDA) hattı pini
#define I2C_SCK_PIN       GPIO_NUM_14     // OLED Ekran I2C Seri Saat (SCL/SCK) hattı pini

static const char *TAG = "TOUCH_LED";     // Seri log çıktılarında kullanılacak etiket

void app_main(void)
{
    // Konsola başlangıç bilgilendirme logu yazdır
    ESP_LOGI(TAG, "ESP32 Kapasitif Dokunmatik Sensör & LED Bar Projesi Başlatılıyor...");

    // 1. ADIM: Donanımsal Dokunmatik Sensörü Başlatma
    touch_pad_init();                       // Dokunmatik çevre birimi saatini ve donanımını aç
    touch_pad_config(TOUCH_PAD_CHANNEL, 0); // 9 numaralı dokunmatik kanalı ham okuma modunda (eşiksiz) yapılandır
    
    // 2. ADIM: LED Çıkış Pinini Ayarlama
    gpio_set_direction(LED_GPIO_PIN, GPIO_MODE_OUTPUT); // LED pinini çıkış (OUTPUT) yap

    // 3. ADIM: Donanımsal I2C Master Veri Yolunu Yapılandırma
    i2c_master_bus_config_t i2c_bus_cfg = {
        .clk_source                   = I2C_CLK_SRC_DEFAULT, // Varsayılan APB/XTAL saat kaynağı
        .i2c_port                     = I2C_NUM_0,           // ESP32'nin 0 numaralı donanımsal I2C portu
        .scl_io_num                   = I2C_SCK_PIN,         // Saat (SCL) hattı pini (GPIO 14)
        .sda_io_num                   = I2C_SDA_PIN,         // Veri (SDA) hattı pini (GPIO 27)
        .glitch_ignore_cnt            = 7,                   // Elektriksel hat gürültülerini filtreleme katsayısı
        .flags.enable_internal_pullup = true,                // I2C hatları için dahili pull-up dirençlerini aktif et
    };
    i2c_master_bus_handle_t bus_hdl; // I2C veri yolu tanıtıcı işaretçisi
    // Yapılandırmayı uygula ve I2C Master veri yolunu başlat
    ESP_ERROR_CHECK(i2c_new_master_bus(&i2c_bus_cfg, &bus_hdl));

    // 4. ADIM: SSD1306 OLED Ekranını Yapılandırma ve Başlatma
    ssd1306_config_t dev_cfg = I2C_SSD1306_128x32_CONFIG_DEFAULT; // 128x32 piksel OLED varsayılan ayarları
    ssd1306_handle_t dev_hdl;                                      // OLED ekran cihaz tanıtıcısı
    // Ekranı I2C veri yoluna bağlayıp başlat
    ESP_ERROR_CHECK(ssd1306_init(bus_hdl, &dev_cfg, &dev_hdl));

    // 5. ADIM: Ekranı Temizleme ve Parlaklık Ayarı
    ssd1306_clear_display(dev_hdl, false); // Ekran belleğini (GRAM) temizle
    ssd1306_set_contrast(dev_hdl, 0xff);  // Ekran kontrastını/parlaklığını maksimuma ayarla (0xFF = 255)

    // 6. ADIM: Ana Okuma ve Gösterge Döngüsü
    while (1) {
        uint16_t touch_val = 0; // Dokunmatik sensörden okunacak ham sayım değeri
        char buf[17];           // OLED satırına yazılacak metin tamponu (16 karakter + 1 null karakteri)

        // Kapasitif pinden anlık şarj/deşarj süresi değerini oku (Temas anında bu değer düşer)
        touch_pad_read(TOUCH_PAD_CHANNEL, &touch_val);
        ESP_LOGI(TAG, "Dokunma Degeri: %u", touch_val); // Seri monitöre değeri logla

        // Okunan ham değeri formatla ve OLED ekranın 0. satırına (en üste) yazdır
        snprintf(buf, sizeof(buf), "Deger: %-4u", touch_val);
        ssd1306_display_text(dev_hdl, 0, buf, false);

        // Dokunma eşik kontrolü: 500'ün altındaysa parmak teması var demektir
        if (touch_val < 500) {
            gpio_set_level(LED_GPIO_PIN, 1);                     // LED'i yak (3.3V ver)
            ssd1306_display_text(dev_hdl, 2, "DOKUNULDU", false); // OLED 2. satıra durum metnini yazdır
        } else {
            gpio_set_level(LED_GPIO_PIN, 0);                     // LED'i söndür (0V ver)
            ssd1306_display_text(dev_hdl, 2, "BOSTA    ", false); // OLED 2. satıra durum metnini yazdır (boşluklar önceki yazıyı siler)
        }

        // Görevi 100 ms uyut; CPU'yu serbest bırakır ve ölçüm hızını 10 Hz yapar
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}
