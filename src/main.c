
#include "menu.h"  // Menü sistemi ve tüm diğer header'lar buradan gelir

int main(void) {
    // Konsolu temizle ve hoş geldin mesajı göster
    printf("\n");
    printf("=== TARIF VE BESLENME TAKIP SISTEMI ===\n");
    printf("Recipe and Nutrition Tracker\n");
    printf("Veri Yapilari ve Algoritmalar Projesi\n");
    printf("\n");
    printf("Sistem baslatiliyor...\n\n");
    
    // === VERİ YAPILARI İNİTALİZASYONU ===
    // AppContext tüm veri yapılarını bir arada tutar
    printf("[1/7] Uygulama context'i olusturuluyor...\n");
    AppContext* ctx = app_context_create();
    
    // Context oluşturma kontrolü - başarısız olursa programı sonlandır
    if (ctx == NULL) {
        printf("\nHATA: Uygulama baslatilamadi! Bellek yetersiz.\n");
        printf("Program sonlandiriliyor...\n");
        return 1;  // Hata kodu ile çık
    }
    
    // Başarı mesajları - her veri yapısı için
    printf("[2/7] Hash Table olusturuldu (O(1) arama icin)\n");
    printf("[3/7] Linked List olusturuldu (dinamik liste icin)\n");
    printf("[4/7] Stack olusturuldu (undo icin)\n");
    printf("[5/7] Queue olusturuldu (haftalik plan icin)\n");
    printf("[6/7] Graph olusturuldu (bagimlilikar icin)\n");
    printf("[7/7] Sparse Matrix olusturuldu (malzeme arama icin)\n");
    printf("\n");
    
    // === ÖRNEK VERİ YÜKLEME ===
    // Program ilk çalıştığında 3 örnek tarif yükle
    // Bu tarifler kullanıcının tüm özellikleri test etmesini sağlar
    printf("Ornek veriler yukleniyor...\n\n");
    menu_load_sample_data(ctx);
    
    printf("\n");
    printf("Sistem hazir!\n");
    printf("\n");
    
    // Kullanıcıdan Enter bekle (hoş geldin ekranını okusun)
    printf("Devam etmek icin Enter'a basin...");
    getchar();  // Enter'ı bekle
    
    // === ANA PROGRAM DÖNGÜSÜ ===
    // Kullanıcı çıkış yapana kadar (seçim 0) döngü devam eder
    int choice = -1;  // Kullanıcının menü seçimi (-1 = henüz seçim yapılmadı)
    
    // 0 seçilene kadar döngüyü çalıştır
    while (choice != 0) {
        clear_console();  // Her iterasyonda ekranı temizle
        menu_display();   // Menü seçeneklerini göster
        
        // Kullanıcıdan seçim al (güvenli input fonksiyonu kullan)
        choice = safe_int_input();
        
        // Seçimi işle (menü fonksiyonlarını çağır)
        menu_handle_choice(ctx, choice);
    }
    
    // === PROGRAM SONLANDIRMA ===
    // Kullanıcı çıkış yaptı - temizlik zamanı
    printf("\n");
    printf("Program kapatiliyor...\n");
    printf("Bellek temizleniyor...\n");
    
    // Tüm veri yapılarını ve ayrılan belleği temizle
    // Bu çok önemli - bellek sızıntısını (memory leak) önler
    app_context_destroy(ctx);
    
    printf("Bellek basariyla temizlendi.\n");
    printf("\n");
    printf("Programi kullandiginiz icin tesekkur ederiz!\n");
    printf("Gule gule...\n\n");
    
    // Başarılı çıkış - return 0
    return 0;
}
