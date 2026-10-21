#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/touch_pad.h"
#include "driver/i2c_master.h"
#include "esp_err.h"
#include "esp_log.h"
#include "ssd1306.h"

#define TOUCH_PAD_CHANNEL TOUCH_PAD_NUM9
#define LED_GPIO_PIN GPIO_NUM_25

#define I2C_SDA_PIN GPIO_NUM_27
#define I2C_SCK_PIN GPIO_NUM_14

static const char *TAG = "TOUCH_LED";

void app_main(void)
{
    ESP_LOGI(TAG, "ESP32 Kapasitif Dokunmatik Sensör & LED Bar Projesi Başlatılıyor...");

    touch_pad_init();
    touch_pad_config(TOUCH_PAD_CHANNEL, 0);
    gpio_set_direction(LED_GPIO_PIN, GPIO_MODE_OUTPUT);

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

    while (1) {
        uint16_t touch_val = 0;
        char buf[17];

        touch_pad_read(TOUCH_PAD_CHANNEL, &touch_val);
        ESP_LOGI(TAG, "Dokunma Degeri: %u", touch_val);

        snprintf(buf, sizeof(buf), "Deger: %-4u", touch_val);
        ssd1306_display_text(dev_hdl, 0, buf, false);

        if (touch_val < 500) {
            gpio_set_level(LED_GPIO_PIN, 1);
            ssd1306_display_text(dev_hdl, 2, "DOKUNULDU", false);
        } else {
            gpio_set_level(LED_GPIO_PIN, 0);
            ssd1306_display_text(dev_hdl, 2, "BOSTA    ", false);
        }

        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

