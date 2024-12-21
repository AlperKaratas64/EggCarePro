# EggCarePro
# SmartIncubator

SmartIncubator, yumurtaların optimum sıcaklık ve nem koşullarında tutulmasını, belirli aralıklarla döndürülmesini sağlayarak başarılı bir şekilde çıkım almanızı hedefleyen bir kuluçka makinesi projesidir. Bu proje, farklı yumurta türlerinin özel ihtiyaçlarını karşılayacak şekilde otomatik olarak ayarlanabilir bir sistem sunar.

## 🌐 Proje Özeti
Kuluçka makinesi, yumurtaların gelişim sürecini desteklemek için tasarlanmıştır. 
- Farklı yumurta türlerine uygun sıcaklık, nem ve dönüş ayarlarını otomatik olarak yapar.
- Gelişim sürecinde yumurta türüne göre belirlenen farklı günlerde ayar değişiklikleri gerçekleştirir.

## 🛠️ Kullanılan Donanım
1. **Arduino Nano**: İşlemci olarak kullanıldı.
2. **DHT11**: Sıcaklık ve nem değerlerini ölçmek için kullanıldı.
3. **16x2 LCD Ekran**: Değerlerin kullanıcıya gösterilmesini sağlar.
4. **RTC Modülü**: Güncel saat ve tarih bilgilerini almak için kullanıldı.
5. **Röleler**:
   - Isıtıcı Rölesi
   - Nem Rölesi
   - Viyor (Dönüş) Rölesi
6. **BC547 Transistör ve Ters Diyot**: Röle sürücüsü olarak kullanıldı.
7. **12V DC Güç Kaynağı ve DC-DC Dönüştürücü**: 12V giriş gerilimini 5V‚ı dönüştürmek için kullanıldı.

## 📈 Sistemin İşleyişi
1. **Yumurta Türü Seçimi:** Menüden yumurta türü seçildiğinde, sıcaklık ve nem ayarları otomatik olarak atanır.
2. **Gelişim ve Dinlenme Süreci:** Her yumurta için gelişim ve dinlenme süreçlerine uygun ısı ve nem değerleri atanır.
3. **Nem ve Sıcaklık Takibi:**
   - DHT11 ile sıcaklık ve nem değerleri okunur.
   - Okunan değerler 16x2 LCD ekranda gösterilir.
4. **Yumurta Çevirme:** Viyor rölesi, yumurtaları belirli aralıklarla 45 derecelik eğimle çevirir.
5. **Güç Yönetimi:** Sistem 12V DC gerilimle çalışır ve DC-DC dönüştürücü ile röleler ve devre için gerekli 5V sağlanır.
6. **Röle Geri Bildirimi:** Röle konumları LED’lerle belirtilir.

## 🔧 Teknik Detaylar
- **İşlemci:** Arduino Nano kartı kullanıldı.
- **Sensör:** DHT11 sıcaklık ve nem ölçer.
- **Ekran:** 16x2 LCD ekran.
- **Saat:** RTC modülüyle zaman yönetimi.
- **Röle Sürücü:** BC547 transistör ve ters diyot kombinasyonu.

## 🔄 Gelecekteki Geliştirme Fikirleri
1. **Uzaktan Kontrol:** Wi-Fi modülü eklenerek mobil uygulama üzerinden kontrol.
2. **Veri Kaydı:** Nem ve sıcaklık verilerinin geçmişini tutma.
3. **Akıllı Alarm Sistemi:** Ayarlardan sapma durumunda kullanıcıya bildirim.

## 🔗 Proje Yapısı
- **`/src`**: Kaynak kodlar.
- **`/docs`**: Belge dosyaları.
- **`/hardware`**: Donanım şemaları ve diyagramları.

## 📢 Kullanım
1. Arduino IDE kullanarak kodları yükleyin.
2. Donanımı belirtilen şemaya uygun bir şekilde bağlayın.
3. Sistemi çalıştırın ve LCD ekrandaki menü üzerinden yumurta türünü seçin.

## 🔧 Gereksinimler
- Arduino IDE
- Gerekli kütüphaneler: `DHT`, `Wire`, `RTClib`

---
**Hazırlayan:** [Ayşegül](#)  
Proje hakkında daha fazla bilgi için [GitHub Proje Sayfası](#).
