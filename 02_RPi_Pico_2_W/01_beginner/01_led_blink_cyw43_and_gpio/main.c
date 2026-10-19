#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "hardware/gpio.h"


#define EXTERNAL_LED_PIN 15

int main(void) {

    stdio_init_all();

    if (cyw43_arch_init()) {
        printf("Hata: CYW43 cipi baslatilamadi!\n");
        return -1;
    }


    gpio_init(EXTERNAL_LED_PIN);
    gpio_set_dir(EXTERNAL_LED_PIN, GPIO_OUT);


    while (true) {

        gpio_put(EXTERNAL_LED_PIN, 1);
        sleep_ms(500); 

        gpio_put(EXTERNAL_LED_PIN, 0);
        sleep_ms(500);
    }

    return 0;
}
