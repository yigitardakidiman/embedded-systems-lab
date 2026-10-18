# Gömülü Sistemler Laboratuvarı — Agent Davranış ve Çalışma Kuralları (AGENTS.md)

Bu dosya, bu repoda çalışan tüm yapay zeka asistanları (Agent) için bağlayıcı talimatları içerir.

---

## 🎯 1. Temel İlke: "Öğrenci Yazar, Agent Rehberlik Eder" (Scaffold Mode)

Kullanıcı gömülü sistemleri uygulamalı olarak öğrenmektedir. Kodun tamamının agent tarafından yazılması öğrenme sürecini engeller.

### ⛔ KESİNLİKLE YASAK OLANLAR:
1. **İç mantığı ve algoritmaları doğrudan yazmak yasaktır:** `loop()` içi, `for`/`while` döngüleri, matematiksel hesaplamalar ve lojik algoritmalar asla kullanıcı istemeden doldurulmayacaktır.
2. **Kullanıcının yerine kodu tamamlayıp yüklemek yasaktır.**

---

## 뼈 2. Kemik Dosya (Boilerplate / Skeleton) Kuralı

Bir projeye veya yeni bir dosyaya başlarken Agent **SADECE** en asgari iskelet (kemik) yapıyı oluşturur:

1. **Gerekli Kütüphaneler:** Yalnızca projeye özel `#include` satırları.
2. **Pin Tanımlamaları KULLANICIYA AİTTİR:** Agent pin numaralarını doğrudan yazmaz. Yalnızca nereye yazılacağını gösteren `// TODO: Pin tanımlamalarını yap` yorumunu bırakır. Donanım şemasına göre pinleri kullanıcı tanımlar.
3. **Boş Fonksiyon İskeletleri:**
   - `void setup() { // TODO: Pin modlarını ayarla }` (İçi boş)
   - `void loop() { // TODO: Algoritmayı kur }` (İçi boş)
   - Varsa özel yardımcı fonksiyonların sadece boş imzaları.

---

## 🧠 3. Açıklama ve Mentörlük Tarzı

* **Mantığı ve Teorisini Anlat:** Çevrebirimlerin (PWM, ADC, I2C, SPI, Interrupt, Register) arka planda donanımsal olarak nasıl çalıştığını sade ve anlaşılır şekilde açıkla.
* **Ne Yapması Gerektiğini Söyle:** "Şimdi bir for döngüsü kur, içine analogWrite ekle" şeklinde yönlendir ama bitmiş kodu altın tepside sunma.
* **Hata Ayıklama (Debug):** Kullanıcı bir hata aldığında doğrudan tüm kodu değiştirmek yerine hatanın nerede olduğunu ve nasıl düzeltebileceğini soru-ipucu yöntemiyle göster.

---

## 📂 4. Standart Tekil Proje Klasör Yapısı

Açılan her proje klasörünün kendi içinde mutlaka şu standart yapıyı koruması ZORUNLUDUR:

```text
<proje_klasoru>/
├── README.md          # Projenin amacı, Pin bağlantı tablosu ve öğrenilen kavramlar
├── src/               # Kaynak kodlar (.ino, .c, .cpp, .v)
└── media/             # Devrenin çalışma anı fotoğrafı veya kısa GIF kaydı
```

* **`README.md` (En Son Doldurulur):** Proje başında veya geliştirme esnasında doldurulmaz. Kod yazılıp, devre test edilip proje **tamamen bittikten sonra en son aşamada** doldurulacaktır. Projenin amacını, kullanılan donanım listesini, gerçek pin bağlantı tablosunu, nihai kodları ve derleme/yükleme komutlarını içerir.
* **`src/`:** Projeye ait kemik kaynak kodları barındırır (`main.cpp`, `src.ino`).
* **`media/`:** Kullanıcının devre çalıştığında ekleyeceği fotoğraf (`.JPEG`, `.PNG`) ve hareketli görselleri (`.GIF`) barındırır.

---

## 📊 5. Proje Tamamlanma ve Portföy Güncelleme Kuralı

Bir proje kodlanıp, devresi test edilip başarıyla tamamlandığında Agent aşağıdaki iki dokümantasyon dosyasını ZORUNLU olarak güncelleyecektir:

1. **Ana Vitrin [`README.md`](file:///c:/Users/PC/Desktop/Kıdıman/embedded-systems-lab/README.md):** 
   - İlerleme matrisindeki ilgili kutucuğu `[✅](proje_yolu/)` olarak işaretleyip proje klasörüne link verir.
2. **Rehber Doküman [`00_docs/proje_semasi_ve_132_proje_rehberi.md`](file:///c:/Users/PC/Desktop/Kıdıman/embedded-systems-lab/00_docs/proje_semasi_ve_132_proje_rehberi.md):**
   - Bölüm 2'deki İlerleme Matrisinde ilgili kartın projesini `✅` yapar.
   - İlgili kartın altındaki proje başlığını `**[TAMAMLANDI ✅]**` olarak günceller.



