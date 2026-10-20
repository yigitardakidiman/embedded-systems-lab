#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/ledc.h"
#include "driver/gpio.h"
#include "esp_err.h"
#include "esp_log.h"

#define LEDC_OUTPUT_IO          GPIO_NUM_25
#define LEDC_MODE               LEDC_LOW_SPEED_MODE
#define LEDC_CHANNEL            LEDC_CHANNEL_0
#define LEDC_TIMER              LEDC_TIMER_0
#define LEDC_DUTY_RES           LEDC_TIMER_13_BIT   // 13-bit: Duty değeri 0 ile 8191 arası
#define LEDC_FREQUENCY          (5000)              // 5 kHz PWM frekansı

static const char *TAG = "LEDC_BREATHE";

void app_main(void)
{
    ESP_LOGI(TAG, "ESP32 LEDC Donanım PWM Nefes Alma Projesi Başlatılıyor...");

    // 1. ADIM: Donanım PWM Zamanlayıcısını Yapılandırma (Timer Configuration)
    ledc_timer_config_t timer_cfg = {
        .speed_mode = LEDC_MODE,
        .timer_num = LEDC_TIMER,
        .duty_resolution = LEDC_DUTY_RES,
        .freq_hz = LEDC_FREQUENCY,
        .clk_cfg = LEDC_AUTO_CLK,
    };
    ledc_timer_config(&timer_cfg);

    // 2. ADIM: Donanım PWM Kanalını Yapılandırma (Channel Configuration)
    ledc_channel_config_t channel_cfg = {
        .gpio_num = LEDC_OUTPUT_IO,
        .speed_mode = LEDC_MODE,
        .channel = LEDC_CHANNEL,
        .timer_sel = LEDC_TIMER,
        .duty = 0,
        .hpoint = 0,
    };
    ledc_channel_config(&channel_cfg);

    // 3. ADIM: Ana Çalışma Döngüsü (Nefes Alma / Breathe Efekti)
    while (1) {
        // Fade In: 0'dan 8191'e kadar parlaklığı artır
        for (int duty = 0; duty <= 8191; duty += 50) {
            ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, duty);
            ledc_update_duty(LEDC_MODE, LEDC_CHANNEL);
            vTaskDelay(pdMS_TO_TICKS(10));
        }

        // Fade Out: 8191'den 0'a kadar parlaklığı azalt
        for (int duty = 8191; duty >= 0; duty -= 50) {
            ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, duty);
            ledc_update_duty(LEDC_MODE, LEDC_CHANNEL);
            vTaskDelay(pdMS_TO_TICKS(10));
        }
    }
}
