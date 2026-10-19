#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define LED_PIN GPIO_NUM_25
#define BUTTON_PIN GPIO_NUM_0

void app_main(void) {
    gpio_reset_pin(LED_PIN);
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);

    gpio_reset_pin(BUTTON_PIN);
    gpio_set_direction(BUTTON_PIN, GPIO_MODE_INPUT);
    gpio_set_pull_mode(BUTTON_PIN, GPIO_PULLUP_ONLY);

    while (1) {
        if (gpio_get_level(BUTTON_PIN) == 0){
            gpio_set_level(LED_PIN, 1);
        }else{
            gpio_set_level(LED_PIN,0);
        }

        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}

