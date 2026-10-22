#include <stdio.h>                   // Standart C giriş/çıkış kütüphanesi (snprintf vb. için)
#include <string.h>                  // Bellek ve karakter dizisi işlemleri kütüphanesi
#include "freertos/FreeRTOS.h"       // FreeRTOS çekirdek başlık dosyası
#include "freertos/task.h"           // FreeRTOS görev (task) ve zamanlama (delay) fonksiyonları
#include "esp_adc/adc_oneshot.h"     // ESP-IDF v5.x modern Analog-Dijital Dönüştürücü (ADC Oneshot) sürücüsü
#include "driver/gpio.h"             // ESP-IDF donanımsal GPIO sürücüsü
#include "driver/i2c_master.h"       // ESP-IDF v5.x donanımsal I2C Master sürücüsü
#include "esp_err.h"                 // ESP-IDF hata kontrol makroları (ESP_ERROR_CHECK vb.)
#include "esp_log.h"                 // ESP-IDF konsol loglama kütüphanesi
#include "ssd1306.h"                 // SSD1306 OLED ekran kütüphanesi

#define MIC_ADC_CHANNEL ADC_CHANNEL_4 // Analog mikrofonun bağlı olduğu ADC kanalı (ADC1 Kanal 4 -> GPIO 32)
#define LED_GPIO_PIN    GPIO_NUM_25   // Ses eşiği aşıldığında yanacak LED'in bağlı olduğu GPIO pini (Çıkış)
#define I2C_SDA_PIN     GPIO_NUM_27   // OLED Ekran I2C Veri (SDA) hattı pini
#define I2C_SCK_PIN     GPIO_NUM_14   // OLED Ekran I2C Saat (SCL/SCK) hattı pini

void app_main(void)
{
    // 1. ADIM: LED Çıkış Pinini Yapılandırma
    gpio_set_direction(LED_GPIO_PIN, GPIO_MODE_OUTPUT);

    // 2. ADIM: Donanımsal ADC1 Birimini Yapılandırma (ESP-IDF v5 Oneshot API)
    adc_oneshot_unit_handle_t adc_hdl;          // ADC birimi tanıtıcı işaretçisi
    adc_oneshot_unit_init_cfg_t init_cfg = {
        .unit_id = ADC_UNIT_1,                  // ESP32'nin 1 numaralı ADC donanım birimi (Wi-Fi ile çakışmaz)
    };
    ESP_ERROR_CHECK(adc_oneshot_new_unit(&init_cfg, &adc_hdl)); // ADC1 birimini başlat

    // 3. ADIM: Mikrofonun Bağlı Olduğu ADC Kanalını Yapılandırma
    adc_oneshot_chan_cfg_t chan_cfg = {
        .bitwidth = ADC_BITWIDTH_DEFAULT,       // Varsayılan çözünürlük: 12-bit (0 ile 4095 arası değer)
        .atten    = ADC_ATTEN_DB_12,            // Zayıflatma (Attenuation): ~0V ile 3.1V arası tam giriş voltaj aralığı
    };
    ESP_ERROR_CHECK(adc_oneshot_config_channel(adc_hdl, MIC_ADC_CHANNEL, &chan_cfg));

    // 4. ADIM: Donanımsal I2C Master Veri Yolunu Yapılandırma
    i2c_master_bus_config_t i2c_bus_cfg = {
        .clk_source                   = I2C_CLK_SRC_DEFAULT, // Varsayılan saat kaynağı (XTAL/APB)
        .i2c_port                     = I2C_NUM_0,           // ESP32'nin 0 numaralı donanımsal I2C portu
        .scl_io_num                   = I2C_SCK_PIN,         // Saat (SCL) hattı pini (GPIO 14)
        .sda_io_num                   = I2C_SDA_PIN,         // Veri (SDA) hattı pini (GPIO 27)
        .glitch_ignore_cnt            = 7,                   // Elektriksel hat gürültülerini filtreleme katsayısı
        .flags.enable_internal_pullup = true,                // Dahili pull-up dirençlerini aktif et
    };
    i2c_master_bus_handle_t bus_hdl;
    ESP_ERROR_CHECK(i2c_new_master_bus(&i2c_bus_cfg, &bus_hdl)); // I2C veri yolunu başlat

    // 5. ADIM: SSD1306 OLED Ekranını Yapılandırma ve Başlatma
    ssd1306_config_t dev_cfg = I2C_SSD1306_128x32_CONFIG_DEFAULT; // 128x32 piksel OLED varsayılan ayarları
    ssd1306_handle_t dev_hdl;
    ESP_ERROR_CHECK(ssd1306_init(bus_hdl, &dev_cfg, &dev_hdl));   // Ekranı I2C yoluna bağlayıp açılışını yap

    // 6. ADIM: Ekranı Temizleme ve Parlaklık Ayarı
    ssd1306_clear_display(dev_hdl, false); // Ekran belleğini (GRAM) temizle
    ssd1306_set_contrast(dev_hdl, 0xff);  // Ekran parlaklığını maksimuma ayarla (0xFF = 255)

    // 7. ADIM: Ana Örnekleme ve VU-Metre Döngüsü
    while (1) {
        int min_val = 4095; // 12-bit ADC için maksimum olası başlangıç değeri
        int max_val = 0;    // Minimum başlangıç değeri
        char buf[17];       // OLED satırı için karakter tamponu (16 karakter + null)

        // Ses dalgası AC (dalgalı) sinyal olduğu için tepeden tepeye (Peak-to-Peak) genlik ölçülür:
        // Hızlıca 500 ardışık analog örnek alınarak dalganın en yüksek ve en alçak noktaları yakalanır
        for (int i = 0; i < 500; i++) {
            int val = 0;
            adc_oneshot_read(adc_hdl, MIC_ADC_CHANNEL, &val); // Anlık analog voltajı oku (0 - 4095)
            if (val > max_val) max_val = val;                 // En yüksek tepe noktasını kaydet
            if (val < min_val) min_val = val;                 // En alçak çukur noktasını kaydet
        }

        // Ses şiddeti (genlik) = Maksimum tepe noktası - Minimum tepe noktası
        int ses_siddeti = max_val - min_val;

        // Ölçülen ses şiddetini formatla ve OLED ekranın 0. satırına yazdır
        snprintf(buf, sizeof(buf), "Ses: %-4d", ses_siddeti);
        ssd1306_display_text(dev_hdl, 0, buf, false);

        // Eşik kontrolü: Eğer ses şiddeti 900'ü aşarsa (alkış, bağırma, yüksek ses algılandıysa)
        if (ses_siddeti > 900) {
            gpio_set_level(LED_GPIO_PIN, 1);                         // LED'i yak (3.3V ver)
            ssd1306_display_text(dev_hdl, 2, "SES ALGILANDI", false); // OLED 2. satıra durum bildir
            vTaskDelay(pdMS_TO_TICKS(300));                          // LED'in yandığı gözle görülebilsin diye 300 ms bekle
        } else {
            gpio_set_level(LED_GPIO_PIN, 0);                         // Ses yoksa LED'i söndür (0V ver)
            ssd1306_display_text(dev_hdl, 2, "SESSIZ       ", false); // OLED 2. satıra durum bildir
            vTaskDelay(pdMS_TO_TICKS(20));                           // Hızlı tepki verebilmek için 20 ms bekle
        }
    }
}
