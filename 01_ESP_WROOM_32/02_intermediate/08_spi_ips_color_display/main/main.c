#include <stdio.h>               // Standart C giriş/çıkış kütüphanesi
#include <string.h>              // Bellek ve dizi işleme kütüphanesi
#include "freertos/FreeRTOS.h"   // FreeRTOS çekirdek başlık dosyası
#include "freertos/task.h"       // FreeRTOS görev (task) ve zamanlama (delay) fonksiyonları
#include "driver/spi_master.h"   // ESP-IDF donanımsal SPI Master sürücüsü
#include "driver/gpio.h"         // ESP-IDF donanımsal GPIO sürücüsü
#include "esp_heap_caps.h"       // ESP-IDF donanım yetenekli bellek tahsisi (DMA RAM erişimi için)
#include "esp_err.h"             // ESP-IDF hata denetim makroları (ESP_ERROR_CHECK vb.)
#include "esp_log.h"             // ESP-IDF konsol loglama kütüphanesi (ESP_LOGI vb.)

// ============================================================
//  Pin Bağlantıları (ESP32 sol sütun GPIO pinleri)
// ============================================================
#define PIN_NUM_SCLK    GPIO_NUM_14   // Ekran SCL  (SPI Seri Saat hattı)
#define PIN_NUM_MOSI    GPIO_NUM_13   // Ekran SDA  (SPI Seri Veri çıkışı / Master Out Slave In)
#define PIN_NUM_RES     GPIO_NUM_33   // Ekran RES  (Donanımsal Reset pini, Aktif LOW)
#define PIN_NUM_DC      GPIO_NUM_27   // Ekran DC   (Veri/Komut seçimi: 0 = Komut, 1 = Veri/Piksel)
#define PIN_NUM_CS      GPIO_NUM_26   // Ekran CS   (Çip Seçimi / Chip Select, Aktif LOW)

// ============================================================
//  SPI Veri Yolu Ayarları
// ============================================================
#define LCD_HOST        SPI2_HOST            // ESP32'nin donanımsal HSPI / SPI2 kontrolcüsü
#define LCD_CLOCK_HZ    (10 * 1000 * 1000)   // SPI saat frekansı: 10 MHz (Hızlı ve kararlı veri aktarımı)

// ============================================================
//  Ekran Geometrisi (0.96" 80x160 ST7735S IPS Renkli Panel)
// ============================================================
#define LCD_WIDTH       80                   // Ekranın yatay piksel genişliği
#define LCD_HEIGHT      160                  // Ekranın dikey piksel yüksekliği
#define LCD_OFFSET_X    26                   // ST7735S denetleyicisi 132x162 hafızaya sahiptir; 80x160 panel merkeze oturtulduğundan X ofseti 26'dır
#define LCD_OFFSET_Y    1                    // Panel dikey hizalama ofseti

// Tek bir SPI DMA işleminde gönderilecek satır sayısı (DMA bellek tamponu boyutu)
#define LINES_PER_CHUNK 20                                 // Her parçada (chunk) aktarılacak satır miktarı
#define CHUNK_PIXELS    (LCD_WIDTH * LINES_PER_CHUNK)      // Parça başına düşen toplam piksel sayısı (80 * 20 = 1600 piksel)
#define CHUNK_BYTES     (CHUNK_PIXELS * 2)                 // Piksel başına 2 bayt (RGB565) olduğu için gereken tampon boyutu (3200 bayt)

// ============================================================
//  ST7735 Denetleyici Komut Kodları (Datasheet Standartları)
// ============================================================
#define ST7735_SWRESET  0x01   // Yazılımsal Reset komutu
#define ST7735_SLPOUT   0x11   // Uyku modundan çıkış (Sleep Out) komutu
#define ST7735_NORON    0x13   // Normal görüntüleme modunu açma komutu
#define ST7735_INVON    0x21   // Renk tersleme (Display Inversion On) komutu (IPS panellerde renk doğruluğu için şarttır)
#define ST7735_DISPON   0x29   // Ekran panelini ve pikselleri aktif etme (Display On) komutu
#define ST7735_CASET    0x2A   // Sütun adresi belirleme (Column Address Set - X ekseni)
#define ST7735_RASET    0x2B   // Satır adresi belirleme (Row Address Set - Y ekseni)
#define ST7735_RAMWR    0x2C   // Belleğe piksel yazma (Memory Write) komutu
#define ST7735_MADCTL   0x36   // Bellek veri erişim kontrolü (Döndürme / RGB-BGR yönü)
#define ST7735_COLMOD   0x3A   // Renk formatı seçimi (16-bit RGB565 / 18-bit RGB666)
#define ST7735_FRMCTR1  0xB1   // Normal mod kare hızı kontrolü
#define ST7735_FRMCTR2  0xB2   // Boşta (Idle) mod kare hızı kontrolü
#define ST7735_FRMCTR3  0xB3   // Kısmi (Partial) mod kare hızı kontrolü
#define ST7735_INVCTR   0xB4   // Ekran tersleme kontrolü
#define ST7735_PWCTR1   0xC0   // Güç kontrolü 1 (GVDD voltajı)
#define ST7735_PWCTR2   0xC1   // Güç kontrolü 2 (VGH/VGL voltajları)
#define ST7735_PWCTR3   0xC2   // Güç kontrolü 3 (Normal mod çalışma akımı)
#define ST7735_PWCTR4   0xC3   // Güç kontrolü 4 (Boşta mod çalışma akımı)
#define ST7735_PWCTR5   0xC4   // Güç kontrolü 5 (Kısmi mod çalışma akımı)
#define ST7735_VMCTR1   0xC5   // VCOM voltaj kontrolü
#define ST7735_GMCTRP1  0xE0   // Pozitif Gama düzeltme ayarları
#define ST7735_GMCTRN1  0xE1   // Negatif Gama düzeltme ayarları

// ============================================================
//  16-Bit RGB565 Renk Tanımlamaları (5 bit Kırmızı, 6 bit Yeşil, 5 bit Mavi)
// ============================================================
#define COLOR_BLACK     0x0000 // Siyah
#define COLOR_WHITE     0xFFFF // Beyaz
#define COLOR_RED       0xF800 // Kırmızı
#define COLOR_GREEN     0x07E0 // Yeşil
#define COLOR_BLUE      0x001F // Mavi
#define COLOR_YELLOW    0xFFE0 // Sarı (Kırmızı + Yeşil)
#define COLOR_CYAN      0x07FF // Camgöbeği (Yeşil + Mavi)
#define COLOR_MAGENTA   0xF81F // Eflatun / Magenta (Kırmızı + Mavi)

static const char *TAG = "ST7735";    // Seri log çıktısı için modül etiketi

static spi_device_handle_t lcd_spi;   // Ekran için oluşturulan SPI cihaz tanıtıcısı (handle)
static uint8_t *dma_buf;              // Donanımsal DMA biriminin erişebileceği özel RAM bölgesindeki piksel tamponu

// ============================================================
//  Düşük Seviye: Donanım SPI Üzerinden Komut ve Veri Gönderme
// ============================================================

// DC = 0 -> Ekran denetleyicisi gelen baytı bir KOMUT (ayar) olarak yorumlar
static void lcd_send_cmd(uint8_t cmd)
{
    spi_transaction_t t = {
        .length = 8,                     // Gönderilecek veri uzunluğu: 8 bit (1 bayt)
        .flags = SPI_TRANS_USE_TXDATA,   // Küçük verilerde dahili tx_data dizisini kullanarak aktarım yap
        .tx_data = { cmd },              // Gönderilecek komut baytı
    };
    gpio_set_level(PIN_NUM_DC, 0);       // DC pinini LOW yaparak ekrana "Bu bir komuttur" bilgisini ver
    ESP_ERROR_CHECK(spi_device_polling_transmit(lcd_spi, &t)); // SPI üzerinden komutu hatta bas ve tamamlanmasını bekle
}

// DC = 1 -> Ekran denetleyicisi gelen baytları VERİ (parametre / renk pikselleri) olarak yorumlar
static void lcd_send_data(const uint8_t *data, size_t len)
{
    if (len == 0) {
        return;                          // Gönderilecek veri yoksa fonksiyondan çık
    }
    spi_transaction_t t = {
        .length = len * 8,               // Toplam bit sayısı (bayt sayısı * 8)
        .tx_buffer = data,               // Gönderilecek verilerin bulunduğu bellek adresi (tampon)
    };
    gpio_set_level(PIN_NUM_DC, 1);       // DC pinini HIGH yaparak ekrana "Bu bir veridir" bilgisini ver
    ESP_ERROR_CHECK(spi_device_polling_transmit(lcd_spi, &t)); // SPI üzerinden veriyi ekrana aktar
}

// Bir komutu ve o komuta ait parametre baytlarını sırayla gönderen yardımcı fonksiyon
static void lcd_write(uint8_t cmd, const uint8_t *params, size_t len)
{
    lcd_send_cmd(cmd);                   // Önce komutu gönder (DC = 0)
    lcd_send_data(params, len);          // Ardından parametreleri gönder (DC = 1)
}

// ============================================================
//  Donanımsal Reset (Hardware Reset)
// ============================================================
static void lcd_hw_reset(void)
{
    gpio_set_level(PIN_NUM_RES, 1);      // Reset pinini HIGH yap
    vTaskDelay(pdMS_TO_TICKS(10));
    gpio_set_level(PIN_NUM_RES, 0);      // Reset pinini LOW'a çekerek ekran çipini donanımsal reset moduna sok
    vTaskDelay(pdMS_TO_TICKS(20));
    gpio_set_level(PIN_NUM_RES, 1);      // Reset pinini tekrar HIGH yaparak çipi serbest bırak ve uyandır
    vTaskDelay(pdMS_TO_TICKS(150));      // Ekranın iç osilatörlerinin oturması için 150 ms bekle
}

// ============================================================
//  ST7735S Ekran Başlatma Dizisi (Init Sequences)
// ============================================================
static void lcd_init(void)
{
    lcd_hw_reset();                               // Donanımsal reset uygula

    lcd_send_cmd(ST7735_SWRESET);                 // Yazılımsal reset komutu ver
    vTaskDelay(pdMS_TO_TICKS(150));

    lcd_send_cmd(ST7735_SLPOUT);                  // Ekranı uyku modundan çıkar; iç voltaj üreteçleri çalışmaya başlar
    vTaskDelay(pdMS_TO_TICKS(255));

    // Ekran tazeleme kare hızı ayarları (Normal, Boşta ve Kısmi modlar için)
    lcd_write(ST7735_FRMCTR1, (uint8_t[]){0x01, 0x2C, 0x2D}, 3);
    lcd_write(ST7735_FRMCTR2, (uint8_t[]){0x01, 0x2C, 0x2D}, 3);
    lcd_write(ST7735_FRMCTR3, (uint8_t[]){0x01, 0x2C, 0x2D, 0x01, 0x2C, 0x2D}, 6);
    lcd_write(ST7735_INVCTR,  (uint8_t[]){0x07}, 1); // Ekran satır tersleme kontrolü

    // Dahili güç devresi ve şarj pompası (Charge Pump) voltaj konfigürasyonları
    lcd_write(ST7735_PWCTR1,  (uint8_t[]){0xA2, 0x02, 0x84}, 3);
    lcd_write(ST7735_PWCTR2,  (uint8_t[]){0xC5}, 1);
    lcd_write(ST7735_PWCTR3,  (uint8_t[]){0x0A, 0x00}, 2);
    lcd_write(ST7735_PWCTR4,  (uint8_t[]){0x8A, 0x2A}, 2);
    lcd_write(ST7735_PWCTR5,  (uint8_t[]){0x8A, 0xEE}, 2);
    lcd_write(ST7735_VMCTR1,  (uint8_t[]){0x0E}, 1);

    // IPS paneller normal TFT'ye göre renkleri ters algılar; gerçek renkler için inversion komutu verilir
    lcd_send_cmd(ST7735_INVON);

    // Bellek erişim yönü: MY | MX | BGR bayrakları (Ekranı dikey ve doğru renk sırasıyla kullanmak için)
    lcd_write(ST7735_MADCTL,  (uint8_t[]){0xC8}, 1);

    // Piksel renk formatı: 0x05 -> 16-bit / piksel (RGB565 formatı)
    lcd_write(ST7735_COLMOD,  (uint8_t[]){0x05}, 1);

    // Ekranın renk doygunluğunu ve kontrastını optimize eden Gama eğrisi katsayıları
    lcd_write(ST7735_GMCTRP1, (uint8_t[]){0x02, 0x1C, 0x07, 0x12, 0x37, 0x32, 0x29, 0x2D,
                                          0x29, 0x25, 0x2B, 0x39, 0x00, 0x01, 0x03, 0x10}, 16);
    lcd_write(ST7735_GMCTRN1, (uint8_t[]){0x03, 0x1D, 0x07, 0x06, 0x2E, 0x2C, 0x29, 0x2D,
                                          0x2E, 0x2E, 0x37, 0x3F, 0x00, 0x00, 0x02, 0x10}, 16);

    lcd_send_cmd(ST7735_NORON);                   // Normal görüntüleme modunu etkinleştir
    vTaskDelay(pdMS_TO_TICKS(10));

    lcd_send_cmd(ST7735_DISPON);                  // Ekran panelini ve pikselleri tamamen aç
    vTaskDelay(pdMS_TO_TICKS(100));

    ESP_LOGI(TAG, "Ekran baslatildi.");           // Ekranın hazır olduğunu logla
}

// ============================================================
//  Grafik Çizim Fonksiyonları
// ============================================================

// Çizim yapılacak dikdörtgen pencere koordinatlarını çipe bildir ve piksel yazma (RAMWR) moduna geç
static void lcd_set_window(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1)
{
    // Fiziksel panel çipin belleğinde ortalanmış olduğundan ofset değerlerini ekle
    x0 += LCD_OFFSET_X;  x1 += LCD_OFFSET_X;
    y0 += LCD_OFFSET_Y;  y1 += LCD_OFFSET_Y;

    // Sütun (X) sınırlarını belirle (Başlangıç ve Bitiş adresi: 16-bit)
    lcd_write(ST7735_CASET, (uint8_t[]){x0 >> 8, x0 & 0xFF, x1 >> 8, x1 & 0xFF}, 4);
    // Satır (Y) sınırlarını belirle (Başlangıç ve Bitiş adresi: 16-bit)
    lcd_write(ST7735_RASET, (uint8_t[]){y0 >> 8, y0 & 0xFF, y1 >> 8, y1 & 0xFF}, 4);
    // Ekran denetleyicisini belleğe piksel yazma moduna al (Bundan sonra gelen tüm baytlar piksel rengidir)
    lcd_send_cmd(ST7735_RAMWR);
}

// Belirtilen koordinatlardaki dikdörtgen alanı tek bir renkle doldur
static void lcd_fill_rect(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color)
{
    lcd_set_window(x0, y0, x1, y1); // Çizim yapılacak pencereyi ekran denetleyicisine ayarla

    size_t total_pixels = (size_t)(x1 - x0 + 1) * (size_t)(y1 - y0 + 1); // Çizilecek toplam piksel adedi
    size_t fill_pixels  = (total_pixels < CHUNK_PIXELS) ? total_pixels : CHUNK_PIXELS;

    // DMA tamponunu belirtilen RGB565 rengin baytlarıyla doldur (Önce yüksek bayt, sonra alçak bayt)
    for (size_t i = 0; i < fill_pixels; i++) {
        dma_buf[i * 2]     = color >> 8;
        dma_buf[i * 2 + 1] = color & 0xFF;
    }

    // Pikselleri DMA tamponu büyüklüğündeki parçalar halinde (chunk) SPI üzerinden donanıma akıt
    while (total_pixels > 0) {
        size_t n = (total_pixels < CHUNK_PIXELS) ? total_pixels : CHUNK_PIXELS;
        lcd_send_data(dma_buf, n * 2); // n adet piksel = n * 2 bayt
        total_pixels -= n;
    }
}

// Tüm ekranı tek bir renkle temizle / boya
static void lcd_fill_screen(uint16_t color)
{
    lcd_fill_rect(0, 0, LCD_WIDTH - 1, LCD_HEIGHT - 1, color);
}

// ============================================================
//  Ana Giriş Programı (app_main)
// ============================================================
void app_main(void)
{
    ESP_LOGI(TAG, "08 - SPI ST7735 0.96\" IPS Ekran Testi");

    // 1. ADIM: Ekranın DC ve RES Kontrol Pinlerini Çıkış Olarak Yapılandırma
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << PIN_NUM_DC) | (1ULL << PIN_NUM_RES), // DC ve RES pin maskeleri
        .mode         = GPIO_MODE_OUTPUT,                              // Çıkış modu
        .pull_up_en   = GPIO_PULLUP_DISABLE,                           // Dirençler kapalı
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type    = GPIO_INTR_DISABLE,                             // Kesme yok
    };
    ESP_ERROR_CHECK(gpio_config(&io_conf)); // Pin ayarlarını donanıma uygula

    // 2. ADIM: Donanımsal SPI Veri Yolunu (SPI Bus) Yapılandırma
    spi_bus_config_t buscfg = {
        .mosi_io_num     = PIN_NUM_MOSI,     // SPI Master Out (Veri Çıkışı) pini (GPIO 13)
        .miso_io_num     = -1,               // Ekrana sadece yazıyoruz, okuma yapmadığımız için MISO kapalı (-1)
        .sclk_io_num     = PIN_NUM_SCLK,     // SPI Saat pini (GPIO 14)
        .quadwp_io_num   = -1,               // Quad SPI kullanılmıyor
        .quadhd_io_num   = -1,
        .max_transfer_sz = CHUNK_BYTES,      // Tek bir SPI işleminde taşınabilecek maksimum bayt miktarı (DMA boyutu)
    };
    // SPI2 veri yolunu başlat; SPI_DMA_CH_AUTO ile ESP32 otomatik uygun bir DMA kanalı tahsis eder
    ESP_ERROR_CHECK(spi_bus_initialize(LCD_HOST, &buscfg, SPI_DMA_CH_AUTO));

    // 3. ADIM: ST7735 Ekranını SPI Veri Yoluna Bir Cihaz Olarak Kaydetme
    spi_device_interface_config_t devcfg = {
        .clock_speed_hz = LCD_CLOCK_HZ,      // Cihaz iletişim hızı: 10 MHz
        .mode           = 0,                 // SPI Mod 0 (CPOL = 0, CPHA = 0)
        .spics_io_num   = PIN_NUM_CS,        // Donanımsal Çip Seçim (CS) pini (GPIO 26)
        .queue_size     = 1,                 // İşlem kuyruğu derinliği
    };
    ESP_ERROR_CHECK(spi_bus_add_device(LCD_HOST, &devcfg, &lcd_spi));

    // 4. ADIM: DMA'nın Doğrudan Erişebileceği RAM Bölgesinde Tampon Bellek Ayırma
    // (DMA birimi sadece dahili dahili DMA-uyumlu RAM adreslerini doğrudan okuyabilir)
    dma_buf = heap_caps_malloc(CHUNK_BYTES, MALLOC_CAP_DMA);
    if (dma_buf == NULL) {
        ESP_LOGE(TAG, "DMA tamponu ayrilamadi!"); // Bellek yetersizse hata verip dur
        return;
    }

    // 5. ADIM: Ekranı Başlatma ve Ekranı Temizleme
    lcd_init();                    // Ekranın açılış ve yapılandırma dizisini çalıştır
    lcd_fill_screen(COLOR_BLACK);  // Ekranı başlangıçta tamamen siyah yap

    // 6. ADIM: Renk Dizileri ve Test Döngüsü
    const uint16_t colors[] = {
        COLOR_RED, COLOR_GREEN, COLOR_BLUE, COLOR_YELLOW,
        COLOR_CYAN, COLOR_MAGENTA, COLOR_WHITE
    };
    const char *names[] = {
        "KIRMIZI", "YESIL", "MAVI", "SARI",
        "CAMGOBEGI", "EFLATUN", "BEYAZ"
    };
    const int num_colors = sizeof(colors) / sizeof(colors[0]); // Toplam test rengi sayısı

    // Ana görselleştirme döngüsü
    while (1) {
        // Sırayla tüm ekranı tek bir renkle doldur ve 800 ms bekle
        for (int i = 0; i < num_colors; i++) {
            ESP_LOGI(TAG, "Tam ekran: %s", names[i]);
            lcd_fill_screen(colors[i]);
            vTaskDelay(pdMS_TO_TICKS(800));
        }

        // Ekranı yatay 4 renkli şeride bölerek çiz (Kırmızı, Yeşil, Mavi, Sarı)
        ESP_LOGI(TAG, "4 renk serit");
        lcd_fill_rect(0,   0, 79,  39, COLOR_RED);
        lcd_fill_rect(0,  40, 79,  79, COLOR_GREEN);
        lcd_fill_rect(0,  80, 79, 119, COLOR_BLUE);
        lcd_fill_rect(0, 120, 79, 159, COLOR_YELLOW);
        vTaskDelay(pdMS_TO_TICKS(2000)); // 2 saniye şeritleri ekranda tut
    }
}
