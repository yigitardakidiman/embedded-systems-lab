#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/touch_pad.h"
#include "esp_log.h"

#define TOUCH_PAD_CHANNEL TOUCH_PAD_NUM9
#define LED_GPIO_PIN GPIO_NUM_25

static const char *TAG = "TOUCH_LED";

void app_main(void)
{
    ESP_LOGI(TAG, "ESP32 Kapasitif Dokunmatik Sensör & LED Bar Projesi Başlatılıyor...");

    touch_pad_init();
    touch_pad_config(TOUCH_PAD_CHANNEL, 0);
    gpio_set_direction(LED_GPIO_PIN, GPIO_MODE_OUTPUT);

    while (1) {
        uint16_t touch_val = 0;
        touch_pad_read(TOUCH_PAD_CHANNEL, &touch_val);
        ESP_LOGI(TAG, "Dokunma Degeri: %u", touch_val);

        if (touch_val < 500) {
            gpio_set_level(LED_GPIO_PIN, 1);
        } else {
            gpio_set_level(LED_GPIO_PIN, 0);
        }

        vTaskDelay(pdMS_TO_TICKS(100));
    }
}
