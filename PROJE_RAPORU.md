# CEN207 Veri Yapıları Projesi - Tarif ve Beslenme Takip Uygulaması
## Proje Raporu

---

## 1. PROJE ÖZETİ

### 1.1 Genel Bakış
Bu proje, CEN207 Veri Yapıları dersinin ara sınav aşaması için geliştirilmiş kapsamlı bir **Tarif ve Beslenme Takip Uygulaması**dır. Proje, 7 farklı veri yapısı ve algoritmanın pratik uygulamasını içermektedir.

### 1.2 Proje Bilgileri
- **Proje Adı:** Recipe and Nutrition Tracker (Tarif ve Beslenme Takip Uygulaması)
- **Ders:** CEN207 Veri Yapıları
- **Dönem:** 2025-2026
- **Proje Tipi:** Ara Sınav Projesi
- **Programlama Dilleri:** C (C99) ve C++ (C++17)
- **Build Sistemi:** CMake (>= 3.12)

### 1.3 Proje Amacı
Proje, aşağıdaki veri yapılarının ve algoritmaların gerçek dünya senaryosunda (tarif yönetimi) kullanımını göstermektedir:
1. Bağlı Liste (Linked List)
2. XOR Bağlı Liste (XOR Linked List)
3. Yığın (Stack)
4. Kuyruk (Queue)
5. Hash Tablosu (Hash Table)
6. Graf (Graph) - BFS ve DFS algoritmaları
7. Yığın (Heap) - Min-Heap
8. Seyrek Matris (Sparse Matrix)

---

## 2. PROJE YAPISI

### 2.1 Dizin Yapısı
```
cen207-2025-2026-71-eceirem-sas-cpp-1/
├── include/              # C başlık dosyaları (.h)
│   ├── recipe.h
│   ├── linked_list.h
│   ├── xor_linked_list.h
│   ├── stack.h
│   ├── queue.h
│   ├── hash_table.h
│   ├── graph.h
│   ├── heap.h
│   ├── sparse_matrix.h
│   └── menu.h
├── src/                  # Kaynak kod dosyaları
│   ├── recipe.c          # Tarif yönetimi
│   ├── linked_list.c     # Bağlı liste implementasyonu
│   ├── xor_linked_list.c # XOR bağlı liste implementasyonu
│   ├── stack.c           # Yığın implementasyonu
│   ├── queue.c           # Kuyruk implementasyonu
│   ├── hash_table.c      # Hash tablosu implementasyonu
│   ├── graph.c           # Graf implementasyonu (BFS/DFS)
│   ├── heap.c            # Min-Heap implementasyonu
│   ├── sparse_matrix.c   # Seyrek matris implementasyonu
│   ├── menu.c            # Menü yönetimi
│   ├── main.c            # Ana C uygulaması
│   ├── recipe/           # C++ tarif modülü
│   │   ├── header/       # C++ başlık dosyaları
│   │   └── src/          # C++ kaynak dosyaları
│   ├── recipeapp/        # C++ uygulama modülü
│   └── utility/          # Yardımcı fonksiyonlar
├── tests/                # Test dosyaları
│   ├── test_recipes.cpp  # GoogleTest testleri
│   └── test_recipes_cpp.cpp
├── docs/                 # Dokümantasyon
│   ├── index.md
│   ├── architecture.md
│   ├── developers.md
│   └── security.md
├── build/                # Build çıktıları
├── assets/               # Görseller ve rozetler
└── CMakeLists.txt        # Ana CMake yapılandırması
```

### 2.2 Dosya İstatistikleri
- **C Kaynak Dosyaları:** 11 dosya (.c)
- **C++ Kaynak Dosyaları:** 10 dosya (.cpp)
- **Başlık Dosyaları:** 10 dosya (.h/.hpp)
- **Test Dosyaları:** 2 dosya
- **Toplam Kod Satırı:** Yaklaşık 3000+ satır

---

## 3. KULLANILAN VERİ YAPILARI VE ALGORİTMALAR

### 3.1 Recipe (Tarif) Yapısı
**Amaç:** Tarif bilgilerini saklamak için temel veri yapısı

**Özellikler:**
- Benzersiz ID
- Tarif adı
- Kategori (örn: "Dessert", "Main Course")
- Kalori sayısı
- Hazırlık süresi (dakika)
- Malzeme listesi (maksimum 50 malzeme)
- Hazırlık talimatları

**Kullanılan Fonksiyonlar:**
- `recipe_create()` - Yeni tarif oluşturma
- `recipe_add_ingredient()` - Malzeme ekleme
- `recipe_set_instructions()` - Talimatları ayarlama
- `recipe_display()` - Tarif bilgilerini gösterme
- `recipe_copy()` - Derin kopyalama
- `recipe_destroy()` - Bellek temizleme

### 3.2 Linked List (Bağlı Liste)
**Amaç:** Tarifleri sıralı bir şekilde saklamak

**Özellikler:**
- Tek yönlü bağlı liste
- Başa ve sona ekleme
- Arama ve silme işlemleri
- Traversal (gezinme) fonksiyonları

**Karmaşıklık:**
- Ekleme: O(1) (başa/sona)
- Arama: O(n)
- Silme: O(n)

### 3.3 XOR Linked List (XOR Bağlı Liste)
**Amaç:** Bellek verimliliği için çift yönlü liste (tek pointer ile)

**Özellikler:**
- XOR pointer kullanarak önceki ve sonraki node'ları tek pointer'da saklama
- İleri ve geri yönde gezinme
- %50 bellek tasarrufu (çift yönlü liste için)

**Karmaşıklık:**
- Ekleme: O(1)
- Gezinme: O(n)

### 3.4 Stack (Yığın)
**Amaç:** Tarif işlemlerini LIFO (Last In First Out) prensibiyle yönetmek

**Özellikler:**
- Push (ekleme) ve Pop (çıkarma) işlemleri
- İşlem geçmişi takibi
- Geri alma (undo) özelliği

**Kullanım Senaryosu:**
- Tarif ekleme/silme işlemlerinin geri alınması

**Karmaşıklık:**
- Push: O(1)
- Pop: O(1)
- Peek: O(1)

### 3.5 Queue (Kuyruk)
**Amaç:** Haftalık yemek planlaması için FIFO (First In First Out) yapısı

**Özellikler:**
- Dairesel kuyruk implementasyonu
- Enqueue (ekleme) ve Dequeue (çıkarma) işlemleri
- Haftalık tarif sıralaması

**Kullanım Senaryosu:**
- Haftalık yemek planı oluşturma

**Karmaşıklık:**
- Enqueue: O(1)
- Dequeue: O(1)

### 3.6 Hash Table (Hash Tablosu)
**Amaç:** Hızlı tarif arama ve kategorilere göre gruplama

**Özellikler:**
- Chaining (zincirleme) ile çakışma çözümü
- Hash fonksiyonu ile hızlı erişim
- Kategori bazlı gruplama

**Karmaşıklık:**
- Ortalama: O(1)
- En kötü durum: O(n)

### 3.7 Graph (Graf)
**Amaç:** Tarifler arası ilişkileri modellemek (benzer malzemeler, benzer kategoriler)

**Özellikler:**
- Yönlü graf (directed graph)
- BFS (Breadth-First Search) algoritması
- DFS (Depth-First Search) algoritması
- Komşu tarif bulma

**Kullanım Senaryoları:**
- Benzer tarif önerileri
- Malzeme bazlı ilişki ağı

**Karmaşıklık:**
- BFS: O(V + E)
- DFS: O(V + E)
- V: Vertex (köşe) sayısı, E: Edge (kenar) sayısı

### 3.8 Heap (Yığın - Min-Heap)
**Amaç:** Kalori veya hazırlık süresine göre sıralama

**Özellikler:**
- Min-Heap implementasyonu
- En düşük kalorili/hazırlık süreli tarifleri önceliklendirme
- Heapify işlemleri

**Kullanım Senaryosu:**
- Düşük kalorili tarif önerileri
- Hızlı hazırlanan tarifler

**Karmaşıklık:**
- Ekleme: O(log n)
- Minimum bulma: O(1)
- Silme: O(log n)

### 3.9 Sparse Matrix (Seyrek Matris)
**Amaç:** Tarif-malzeme ilişkilerini verimli şekilde saklamak

**Özellikler:**
- Sadece sıfır olmayan değerleri saklama
- Bellek verimliliği
- Bağlı liste tabanlı implementasyon

**Kullanım Senaryosu:**
- Hangi tariflerde hangi malzemelerin kullanıldığını gösterme

**Karmaşıklık:**
- Ekleme: O(1)
- Arama: O(n)

---

## 4. TEKNİK DETAYLAR

### 4.1 Programlama Dilleri ve Standartlar
- **C Standardı:** C99
- **C++ Standardı:** C++17
- **Derleyici Uyarıları:** -Wall -Wextra -Wunused-function

### 4.2 Build Sistemi
**CMake Yapılandırması:**
- Minimum CMake versiyonu: 3.12
- Platform desteği: Windows, Linux (WSL), macOS
- Build tipleri: Debug ve Release
- Otomatik GoogleTest entegrasyonu
- Doxygen dokümantasyon desteği

### 4.3 Test Altyapısı
**GoogleTest Framework:**
- Otomatik test keşfi
- Unit testler
- Test coverage raporları
- JUnit XML formatında çıktı

**Test Kapsamı:**
- Tüm veri yapıları için kapsamlı testler
- Edge case'ler (sınır durumları)
- Bellek yönetimi testleri
- Algoritma doğrulama testleri

### 4.4 Dokümantasyon
**Doxygen:**
- Otomatik API dokümantasyonu
- Kod içi yorumlar
- HTML ve LaTeX çıktıları
- Dokümantasyon coverage raporları

**MkDocs:**
- Web tabanlı dokümantasyon
- Markdown desteği
- Otomatik site oluşturma

### 4.5 Kod Kalitesi
**Araçlar:**
- **AStyle:** Kod formatlama
- **OpenCppCoverage (Windows):** Test coverage
- **gcov/lcov (Linux):** Test coverage
- **ReportGenerator:** Coverage raporları

**Coverage Metrikleri:**
- Line Coverage (Satır kapsamı)
- Branch Coverage (Dal kapsamı)
- Method Coverage (Metod kapsamı)

---

## 5. PLATFORM DESTEĞİ

### 5.1 Desteklenen Platformlar
- ✅ **Windows** (Visual Studio Community Edition)
- ✅ **Linux** (WSL - Ubuntu 20.04)
- ✅ **macOS** (Xcode/Clang)

### 5.2 Build Scripts
**Windows:**
- `7-build-app-windows.bat` - Tam build işlemi (11-15 dakika)
- `7-build-doc-windows.bat` - Sadece dokümantasyon
- `8-build-test-windows.bat` - Sadece testler
- `9-clean-project.bat` - Proje temizleme

**Linux/WSL:**
- `7-build-app-linux.sh` - Tam build işlemi
- `8-build-test-linux.sh` - Test işlemleri

### 5.3 GitHub Actions
- Otomatik CI/CD pipeline
- Çoklu platform testleri
- Windows, macOS, Linux desteği

---

## 6. UYGULAMA ÖZELLİKLERİ

### 6.1 Ana Menü Özellikleri
1. **Tarif Ekleme:** Yeni tarif oluşturma ve kaydetme
2. **Tarif Arama:** ID, isim veya kategoriye göre arama
3. **Tarif Listeleme:** Tüm tarifleri görüntüleme
4. **Tarif Silme:** Tarif silme işlemleri
5. **Kategori Filtreleme:** Kategoriye göre filtreleme
6. **Kalori Bazlı Sıralama:** Heap kullanarak sıralama
7. **Graf Gezinme:** BFS/DFS ile benzer tarif bulma
8. **Hash Tablosu İşlemleri:** Hızlı arama ve gruplama
9. **Haftalık Plan:** Queue kullanarak haftalık plan
10. **İşlem Geçmişi:** Stack ile undo özelliği

### 6.2 Kullanıcı Arayüzü
- Konsol tabanlı interaktif menü
- Renkli çıktılar (platform bağımlı)
- Hata mesajları ve validasyon
- Kullanıcı dostu prompt'lar

---

## 7. TEST SONUÇLARI

### 7.1 Test Kapsamı
Proje, tüm veri yapıları için kapsamlı unit testler içermektedir:

**Test Edilen Bileşenler:**
- ✅ Recipe yapısı ve fonksiyonları
- ✅ Linked List tüm işlemleri
- ✅ XOR Linked List traversal
- ✅ Stack push/pop işlemleri
- ✅ Queue enqueue/dequeue işlemleri
- ✅ Hash Table ekleme/arama
- ✅ Graph BFS/DFS algoritmaları
- ✅ Heap ekleme/silme/peek
- ✅ Sparse Matrix işlemleri

**Test Senaryoları:**
- Normal durumlar (happy path)
- Edge case'ler (boş liste, tek eleman, vb.)
- Bellek yönetimi (memory leaks)
- Hata durumları (null pointer, overflow, vb.)

### 7.2 Coverage Metrikleri
Coverage raporları Windows ve Linux platformları için ayrı ayrı oluşturulmaktadır. Detaylı coverage bilgileri `assets/` klasöründeki rozetlerde görülebilir.

---

## 8. PROJE GELİŞTİRME SÜRECİ

### 8.1 Geliştirme Ortamı Kurulumu
1. **Git Hooks Yapılandırması:** Pre-commit ve pre-push kontrolleri
2. **Paket Yöneticileri:** Chocolatey ve Scoop (Windows)
3. **Gerekli Araçlar:** CMake, Doxygen, GoogleTest, vb.
4. **WSL Kurulumu:** Linux geliştirme ortamı

### 8.2 Geliştirme Akışı
1. Kod yazma (C/C++)
2. Kod formatlama (AStyle)
3. Build ve test
4. Coverage analizi
5. Dokümantasyon güncelleme
6. Commit ve push

### 8.3 Kalite Kontrol
- Pre-commit hook'ları ile otomatik kontrol
- Kod formatlama zorunluluğu
- Test zorunluluğu
- Dokümantasyon kontrolü

---

## 9. SONUÇ VE DEĞERLENDİRME

### 9.1 Proje Başarıları
✅ **7 veri yapısı başarıyla implemente edildi**
✅ **Kapsamlı test coverage sağlandı**
✅ **Çoklu platform desteği eklendi**
✅ **Profesyonel dokümantasyon hazırlandı**
✅ **CI/CD pipeline kuruldu**
✅ **Bellek yönetimi doğru yapıldı**
✅ **Kod kalitesi yüksek seviyede**

### 9.2 Öğrenilen Kavramlar
- Veri yapılarının pratik uygulamaları
- Algoritma karmaşıklığı analizi
- Bellek yönetimi (malloc/free)
- Test-driven development
- Dokümantasyon standartları
- Cross-platform geliştirme
- Build sistemleri (CMake)
- Version control (Git)

### 9.3 Teknik Kazanımlar
- C ve C++ dillerinde ileri seviye programlama
- Veri yapıları ve algoritmaların gerçek dünya uygulamaları
- Profesyonel yazılım geliştirme süreçleri
- Test ve dokümantasyon kültürü
- Build otomasyonu ve CI/CD

### 9.4 Gelecek Geliştirmeler
- GUI (Graphical User Interface) eklenebilir
- Veritabanı entegrasyonu
- Web API desteği
- Mobil uygulama
- Kullanıcı kimlik doğrulama
- Çoklu dil desteği

---

## 10. KAYNAKLAR VE REFERANSLAR

### 10.1 Kullanılan Kütüphaneler
- **GoogleTest:** Unit testing framework
- **Doxygen:** API documentation generator
- **CMake:** Build system generator
- **MkDocs:** Documentation site generator

### 10.2 Referanslar
- CEN207 Veri Yapıları ders notları
- Cormen, Leiserson, Rivest, Stein - "Introduction to Algorithms"
- Doxygen dokümantasyonu
- CMake dokümantasyonu
- GoogleTest dokümantasyonu

---

## 11. EK BİLGİLER

### 11.1 Proje Dosyaları
- **README.md:** Proje genel bilgileri
- **CMakeLists.txt:** Build yapılandırması
- **Doxyfile:** Dokümantasyon ayarları
- **mkdocs.yml:** Web dokümantasyon ayarları

### 11.2 Build Çıktıları
- **release_win/:** Windows release dosyaları
- **release_linux/:** Linux release dosyaları
- **docs/:** HTML dokümantasyon
- **site/:** MkDocs web sitesi

### 11.3 Test Raporları
- **report_test_hist_win/:** Windows test geçmişi
- **report_test_hist_linux/:** Linux test geçmişi
- **recipe_tests_unit_win_cobertura.xml:** Coverage raporu

---

## 12. PROJE EKİBİ

**Danışman:**
- Dr. Uğur CORUH - R&D Engineer and System Architecture

**Geliştirici:**
- Ece İrem ŞAŞ - Proje Geliştiricisi

---

**Rapor Tarihi:** 2025
**Proje Versiyonu:** 1.0
**Durum:** Tamamlandı ✅

---

*Bu rapor, CEN207 Veri Yapıları dersi ara sınav projesi için hazırlanmıştır.*

