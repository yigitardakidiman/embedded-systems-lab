#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_adc/adc_oneshot.h"
#include "driver/gpio.h"
#include "driver/i2c_master.h"
#include "esp_err.h"
#include "esp_log.h"
#include "ssd1306.h"

#define MIC_ADC_CHANNEL ADC_CHANNEL_4
#define LED_GPIO_PIN GPIO_NUM_25
#define I2C_SDA_PIN GPIO_NUM_27
#define I2C_SCK_PIN GPIO_NUM_14

void app_main(void)
{

    gpio_set_direction(LED_GPIO_PIN, GPIO_MODE_OUTPUT);

    adc_oneshot_unit_handle_t adc_hdl;
    adc_oneshot_unit_init_cfg_t init_cfg = {
        .unit_id = ADC_UNIT_1,
    };
    ESP_ERROR_CHECK(adc_oneshot_new_unit(&init_cfg, &adc_hdl));

    adc_oneshot_chan_cfg_t chan_cfg = {
        .bitwidth = ADC_BITWIDTH_DEFAULT,
        .atten = ADC_ATTEN_DB_12,
    };
    ESP_ERROR_CHECK(adc_oneshot_config_channel(adc_hdl, MIC_ADC_CHANNEL, &chan_cfg));

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
    ssd1306_set_contrast(dev_hdl, 0xff);

    while (1) {
        int min_val = 4095;
        int max_val = 0;
        char buf[17];

        for (int i = 0; i < 500; i++) {
            int val = 0;
            adc_oneshot_read(adc_hdl, MIC_ADC_CHANNEL, &val);
            if (val > max_val) max_val = val;
            if (val < min_val) min_val = val;
        }

        int ses_siddeti = max_val - min_val;

        snprintf(buf, sizeof(buf), "Ses: %-4d", ses_siddeti);
        ssd1306_display_text(dev_hdl, 0, buf, false);

        if (ses_siddeti > 900) {
            gpio_set_level(LED_GPIO_PIN, 1);
            ssd1306_display_text(dev_hdl, 2, "SES ALGILANDI", false);
            vTaskDelay(pdMS_TO_TICKS(300));
        } else {
            gpio_set_level(LED_GPIO_PIN, 0);
            ssd1306_display_text(dev_hdl, 2, "SESSIZ       ", false);
            vTaskDelay(pdMS_TO_TICKS(20));
        }
    }
}

