#include <stdio.h>               // Standart C giriş/çıkış kütüphanesi
#include "freertos/FreeRTOS.h"   // FreeRTOS temel veri tipleri ve çekirdek yapılandırması
#include "freertos/task.h"       // FreeRTOS görev (task) ve zamanlama (delay) fonksiyonları
#include "driver/ledc.h"         // ESP32 donanımsal LEDC (LED Controller / Donanımsal PWM) sürücüsü
#include "driver/gpio.h"         // ESP-IDF GPIO donanım ve pin numaralandırma tanımları
#include "esp_err.h"             // ESP-IDF standart hata kodları (esp_err_t)
#include "esp_log.h"             // ESP-IDF konsol loglama kütüphanesi (ESP_LOGI vb.)

#define LEDC_OUTPUT_IO          GPIO_NUM_25          // PWM sinyalinin aktarılacağı GPIO pini (LED çıkışı)
#define LEDC_MODE               LEDC_LOW_SPEED_MODE  // LEDC çalışma modu (ESP32 için kararlı Low-Speed modu)
#define LEDC_CHANNEL            LEDC_CHANNEL_0       // Kullanılacak donanımsal PWM kanalı (0-7 arası)
#define LEDC_TIMER              LEDC_TIMER_0         // Kanalın bağlanacağı donanımsal zamanlayıcı (Timer 0-3 arası)
#define LEDC_DUTY_RES           LEDC_TIMER_13_BIT    // PWM çözünürlüğü: 13-bit (2^13 = 8192 seviye, duty: 0-8191 arası)
#define LEDC_FREQUENCY          (5000)               // PWM anahtarlama frekansı: 5 kHz (Gözün titreşimi algılayamayacağı frekans)

static const char *TAG = "LEDC_BREATHE";             // Seri monitör loglarında görünecek kaynak etiketi

void app_main(void)
{
    // Konsola bilgilendirme logu yazdır
    ESP_LOGI(TAG, "ESP32 LEDC Donanım PWM Nefes Alma Projesi Başlatılıyor...");

    // 1. ADIM: Donanım PWM Zamanlayıcısını Yapılandırma (Timer Configuration)
    ledc_timer_config_t timer_cfg = {
        .speed_mode       = LEDC_MODE,        // Hız modu (Low speed)
        .timer_num        = LEDC_TIMER,       // Yapılandırılacak zamanlayıcı numarası (Timer 0)
        .duty_resolution  = LEDC_DUTY_RES,    // PWM çözünürlüğü (13-bit hassasiyet)
        .freq_hz          = LEDC_FREQUENCY,   // PWM periyot frekansı (5000 Hz)
        .clk_cfg          = LEDC_AUTO_CLK,    // Zamanlayıcı kaynak saati (ESP32 otomatik en uygun saati seçer)
    };
    ledc_timer_config(&timer_cfg);            // Zamanlayıcı ayarlarını donanım yazmaçlarına yazıp başlat

    // 2. ADIM: Donanım PWM Kanalını Yapılandırma (Channel Configuration)
    ledc_channel_config_t channel_cfg = {
        .gpio_num   = LEDC_OUTPUT_IO,         // PWM sinyalinin basılacağı fiziksel pin (GPIO 25)
        .speed_mode = LEDC_MODE,              // Zamanlayıcı ile uyumlu hız modu
        .channel    = LEDC_CHANNEL,           // Donanımsal kanal seçimi (Kanal 0)
        .timer_sel  = LEDC_TIMER,             // Bu kanalın dinleyeceği zamanlayıcı (Timer 0)
        .duty       = 0,                      // Başlangıç doluluk oranı (0: LED tamamen sönük)
        .hpoint     = 0,                      // PWM dalga formunun faz başlangıç noktası
    };
    ledc_channel_config(&channel_cfg);        // PWM kanalını donanıma bağla ve sinyal çıkışını başlat

    // 3. ADIM: Ana Çalışma Döngüsü (Nefes Alma / Breathe Efekti)
    while (1) {
        // Fade In: Doluluk oranını (Duty) 0'dan 8191'e doğru artırarak LED'i yavaşça parlat
        for (int duty = 0; duty <= 8191; duty += 50) {
            ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, duty);    // Yeni duty değerini gölge yazmaca yaz
            ledc_update_duty(LEDC_MODE, LEDC_CHANNEL);        // Yeni değeri donanımsal olarak yürürlüğe koy
            vTaskDelay(pdMS_TO_TICKS(10));                    // Geçişin pürüzsüz görünmesi için 10 ms bekle
        }

        // Fade Out: Doluluk oranını (Duty) 8191'den 0'a doğru azaltarak LED'i yavaşça söndür
        for (int duty = 8191; duty >= 0; duty -= 50) {
            ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, duty);    // Yeni duty değerini gölge yazmaca yaz
            ledc_update_duty(LEDC_MODE, LEDC_CHANNEL);        // Yeni değeri donanımsal olarak yürürlüğe koy
            vTaskDelay(pdMS_TO_TICKS(10));                    // Geçişin pürüzsüz görünmesi için 10 ms bekle
        }
    }
}
