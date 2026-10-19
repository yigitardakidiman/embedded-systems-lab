# 02 - ESP-WROOM-32: Dahili Kapasitif Dokunmatik Sensör (Touch Sensor) ve Gösterge LED'i

Bu proje, **ESP-WROOM-32 (ESP32-D0WD-V3)** mikrodenetleyicisinin dâhili **Kapasitif Dokunmatik (Capacitive Touch)** çevre birimini (`T0` / `GPIO 4`) tanımak, harici bir buton veya mekanik anahtara ihtiyaç duymadan doğrudan insan vücudunun kapasitansını algılamak ve bu veriyi harici bir durum LED'i ile görselleştirmek amacıyla geliştirilmiştir.

---

## 🎯 Projenin Amacı ve Öğrenilen Kavramlar

1. **Dahili Kapasitif Algılama Mekanizması:** ESP32 üzerinde bulunan 10 adet dahili kapasitif dokunmatik girişten biri olan `T0` (`GPIO 4`) pininin `touchRead()` fonksiyonu ile okunması.
2. **Kapasitans Değişimi ve Ters Orantı Prensibi:** 
   - İnsan vücudu bir dielektrik ve toprak referanslı kapasitördür.
   - Pinin ucundaki iletkene parmak temas ettiğinde hattın toplam kapasitansı artar; bu da donanımsal RC osilatörün şarj/deşarj frekansını düşürür.
   - Dolayısıyla `touchRead()` okuma değeri **boştayken yüksek (örn. ~70–90)**, **dokunulduğunda ise aniden düşer (örn. ~10–25)**.
3. **Otomatik Ortam Kalibrasyonu:** `setup()` aşamasında 10 örnek alınarak ortamın baz gürültüsü (`bosDeger`) hesaplanır ve dinamik bir eşik değeri (`esikDegeri = bosDeger * 0.70`) oluşturulur. Böylece ortam nemi veya kablo uzunluğundan bağımsız kararlı çalışma sağlanır.
4. **Harici Durum Göstergesi:** Dokunma algılandığı anda `GPIO 16` pinine bağlı LED sürülerek anlık geri bildirim sağlanır.

---

## 🛠️ Kullanılan Malzemeler

| Malzeme | Adet | Açıklama |
| :--- | :---: | :--- |
| **ESP-WROOM-32** | 1 | 240 MHz Çift Çekirdek Xtensa LX6 (`ESP32-D0WD-V3`) |
| **Breadboard** | 1 | Devre kurulum tablası |
| **Mavi LED** | 1 | Dokunmatik durum göstergesi (`GPIO 16`) |
| **Direnç** | 1 × `330Ω` | LED akım sınırlama direnci |
| **Jumper Kablo** | 3 | Dokunmatik algılama probu ve bağlantılar |

---

## 🔌 Pin Bağlantı Tablosu

| ESP32 Pini | Bağlantı Noktası | Yön / Mod | Açıklama |
| :--- | :--- | :--- | :--- |
| **`GPIO 4` (`T0`)** | Açıkta Duran Jumper Kablo Ucu | `TOUCH` (Giriş) | Dokunmatik elektrot (Parmağın temas ettiği iletken) |
| **`GPIO 16` (`D16`)**| `330Ω` Direnç $\rightarrow$ LED Anot (`+`) | `OUTPUT` | Dokunulduğunda `HIGH (3.3V)`, bırakıldığında `LOW (0V)` |
| **`GND`** | LED Katot (`-`) | `GND (0V)` | Ortak toprak hattı |

---

## 💻 Kaynak Kod ([`src/main.cpp`](src/main.cpp))

```cpp
#include <Arduino.h>

// Pin Tanımlamaları
#define DOKUNMATIK_PIN 4       // T0 (GPIO 4) - Dokunmatik Elektrot / Jumper Kablo
#define HARICI_LED_PIN 16      // GPIO 16     - Durum Gösterge LED'i

int bosDeger = 0;
int esikDegeri = 0;

void setup() {
    Serial.begin(115200);
    delay(200);

    pinMode(HARICI_LED_PIN, OUTPUT);
    digitalWrite(HARICI_LED_PIN, LOW);

    // Açılış LED doğrulaması
    digitalWrite(HARICI_LED_PIN, HIGH);
    delay(300);
    digitalWrite(HARICI_LED_PIN, LOW);

    // Kapasitif Dokunmatik Kalibrasyonu (10 Örnek Ortalaması)
    Serial.println("ESP32 Dokunmatik Kalibrasyonu Baslatiliyor...");
    long toplam = 0;
    for (int i = 0; i < 10; i++) {
        toplam += touchRead(DOKUNMATIK_PIN);
        delay(50);
    }
    bosDeger = toplam / 10;
    esikDegeri = (int)(bosDeger * 0.70); // %70 eşik değeri

    Serial.print("Kalibrasyon Tamam. Bos Deger: ");
    Serial.print(bosDeger);
    Serial.print(" | Esik Degeri: ");
    Serial.println(esikDegeri);
}

void loop() {
    int anlikDeger = touchRead(DOKUNMATIK_PIN);

    // Dokunma Durumu Kontrolü
    if (anlikDeger < esikDegeri) {
        // DOKUNULDU!
        digitalWrite(HARICI_LED_PIN, HIGH);
        Serial.print("[DOKUNULDU] Ham Deger: ");
        Serial.println(anlikDeger);
    } else {
        // BOŞTA
        digitalWrite(HARICI_LED_PIN, LOW);
        Serial.print("[BOSTA]     Ham Deger: ");
        Serial.println(anlikDeger);
    }

    delay(50);
}
```

---

## 🚀 Derleme ve Karta Yükleme Komutları (`arduino-cli`)

Proje ana dizinindeyken (`embedded-systems-lab/`):

```powershell
# Sadece derlemek (Compile) için:
arduino-cli compile --fqbn esp32:esp32:esp32 01_ESP_WROOM_32/01_beginner/02_capacitive_touch_led_bar/src

# Derleyip COM4 portundaki ESP32'ye yüklemek için:
arduino-cli compile -u -p COM4 --fqbn esp32:esp32:esp32 01_ESP_WROOM_32/01_beginner/02_capacitive_touch_led_bar/src
```

---

## 📸 Uygulama Görselleri

| Boşta / Dokunulmuyor (`touch_release.JPEG`) | Dokunuldu / Algılandı (`touch_press.JPEG`) |
| :---: | :---: |
| ![Kapasitif Dokunmatik Boşta](media/touch_release.JPEG) | ![Kapasitif Dokunmatik Dokunuldu](media/touch_press.JPEG) |
| *Kablo boşta dururken kapasitans eşik üstündedir; LED sönüktür.* | *Metal uca dokunulduğunda kapasitans düşer, eşik aşılır ve LED anında yanar.* |

