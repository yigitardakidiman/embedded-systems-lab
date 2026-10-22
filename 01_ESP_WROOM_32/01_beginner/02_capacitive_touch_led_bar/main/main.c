#include <stdio.h>               // Standart C giriş/çıkış kütüphanesi
#include "freertos/FreeRTOS.h"   // FreeRTOS temel veri tipleri ve çekirdek yapılandırması
#include "freertos/task.h"       // FreeRTOS görev (task) ve zamanlama (delay) fonksiyonları
#include "driver/gpio.h"         // ESP-IDF donanımsal GPIO sürücüsü (LED kontrolü için)
#include "driver/touch_pad.h"    // ESP-IDF dahili kapasitif dokunmatik (Touch Sensor) çevre birimi sürücüsü
#include "esp_log.h"             // ESP-IDF seri port loglama kütüphanesi (ESP_LOGI vb.)

#define TOUCH_PAD_CHANNEL TOUCH_PAD_NUM9  // ESP32 Donanımsal Touch Pad 9 (GPIO 32 pinine denk gelir)
#define LED_GPIO_PIN GPIO_NUM_25          // LED'in bağlı olduğu GPIO pini (Çıkış)

static const char *TAG = "TOUCH_LED";     // Log çıktılarında görünecek etiket (filtreleme için kullanılır)

void app_main(void)
{
    
    // Dokunmatik sensör çevre biriminin donanımını ve saat sinyalini başlat
    touch_pad_init();
    
    // İlgili dokunmatik kanalı yapılandır (0: Eşik değeri kullanılmadan doğrudan ham okuma modu)
    touch_pad_config(TOUCH_PAD_CHANNEL, 0);
    
    // LED pininin yönünü çıkış (OUTPUT) olarak ayarla
    gpio_set_direction(LED_GPIO_PIN, GPIO_MODE_OUTPUT);

    // Ana çalışma döngüsü (Sonsuz döngü)
    while (1) {
        uint16_t touch_val = 0; // Dokunmatik sensörden okunacak 16-bitlik ham değeri tutan değişken
        
        // Kapasitif pinden anlık şarj/deşarj sayım değerini oku
        // (Parmağınız dokunduğunda vücut kapasitansından dolayı bu değer belirgin şekilde DÜŞER)
        touch_pad_read(TOUCH_PAD_CHANNEL, &touch_val);
        
        // Okunan değeri seri monitöre yazdır
        ESP_LOGI(TAG, "Dokunma Degeri: %u", touch_val);

        // Dokunma eşik kontrolü: Değer 500'ün altına indiyse temas var kabul edilir
        if (touch_val < 500) {
            gpio_set_level(LED_GPIO_PIN, 1);  // Dokunma algılandı: LED'i yak (3.3V ver)
        } else {
            gpio_set_level(LED_GPIO_PIN, 0);  // Dokunma yok: LED'i söndür (0V ver)
        }

        // 100 ms kilitlenmeyen (non-blocking) gecikme; CPU'yu serbest bırakır ve okuma hızını 10 Hz yapar
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}
