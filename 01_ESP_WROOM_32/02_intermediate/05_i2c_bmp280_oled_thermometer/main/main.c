#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/i2c_master.h"
#include "driver/gpio.h"
#include "esp_err.h"
#include "esp_log.h"
#include "ssd1306.h"
#include "bmp280.h"

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

    bmp280_config_t bmp_cfg = I2C_BMP280_CONFIG_DEFAULT;
    bmp_cfg.i2c_address = I2C_BMP280_DEV_ADDR_LO;
    bmp280_handle_t bmp_hdl;
    ESP_ERROR_CHECK(bmp280_init(bus_hdl, &bmp_cfg, &bmp_hdl));

    ssd1306_clear_display(dev_hdl, false);
    ssd1306_set_contrast(dev_hdl, 0xff);

    while (1) {
        
        float temp, pres;
        char buf[17];

        bmp280_get_measurements(bmp_hdl, &temp, &pres);

        snprintf(buf, sizeof(buf), "Temp: %.1f C", temp);
        ssd1306_display_text(dev_hdl, 0, buf, false);
        snprintf(buf, sizeof(buf), "Pres: %.1f hPa", pres / 100.0f);
        ssd1306_display_text(dev_hdl, 1, buf, false);

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

