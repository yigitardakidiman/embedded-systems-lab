#include <stdio.h>               // Standart C giriş/çıkış kütüphanesi
#include "freertos/FreeRTOS.h"   // FreeRTOS temel veri tipleri ve sistem yapılandırması
#include "freertos/task.h"       // FreeRTOS görev (task) ve zamanlama (delay) fonksiyonları
#include "driver/gpio.h"         // ESP-IDF donanımsal GPIO sürücüsü

#define LED_PIN GPIO_NUM_25      // LED'in bağlı olduğu GPIO pini (Çıkış)
#define BUTTON_PIN GPIO_NUM_0    // ESP32 üzerindeki dahili BOOT buton pini (Giriş)

void app_main(void) {
    // LED pinini varsayılan GPIO durumuna sıfırla ve çıkış olarak ayarla
    gpio_reset_pin(LED_PIN);
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);

    // Buton pinini varsayılan GPIO durumuna sıfırla ve giriş olarak ayarla
    gpio_reset_pin(BUTTON_PIN);
    gpio_set_direction(BUTTON_PIN, GPIO_MODE_INPUT);
    // Buton pini boştayken elektriksel gürültüden etkilenmesin diye dahili Pull-Up direncini aktif et
    gpio_set_pull_mode(BUTTON_PIN, GPIO_PULLUP_ONLY);

    // Ana çalışma döngüsü (Sonsuz döngü)
    while (1) {
        // BOOT butonu Active-Low çalıştığı için basıldığında GND'ye (0 seviyesine) çekilir
        if (gpio_get_level(BUTTON_PIN) == 0) {
            gpio_set_level(LED_PIN, 1);  // Butona basıldıysa LED'i yak (3.3V ver)
        } else {
            gpio_set_level(LED_PIN, 0);  // Buton basılı değilse LED'i söndür (0V ver)
        }

        // Görevi 10 ms uyut; CPU'yu serbest bırakır (Watchdog resetini önler ve kontak sıçramasını filtreler)
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}
