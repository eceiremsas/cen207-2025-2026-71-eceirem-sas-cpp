/**
 * @file heap.h
 * @brief Min-Heap veri yapısı header dosyası
 * @details Tarifleri kalorilerine göre sıralamak için kullanılır.
 *          En düşük kalorili tarif her zaman heap'in tepesinde (root) bulunur.
 */

#ifndef HEAP_H  // Include guard başlangıcı
#define HEAP_H  // HEAP_H makrosunu tanımla

#include "recipe.h"  // Recipe veri yapısı için

/* ============================================================================
 * VERİ YAPILARI (DATA STRUCTURES)
 * ============================================================================ */

/**
 * @struct Heap
 * @brief Min-Heap yapısı
 * @details Array tabanlı complete binary tree (tam ikili ağaç) implementasyonu.
 *          Parent node her zaman child node'lardan küçük kalori değerine sahiptir.
 */
typedef struct {
    Recipe** recipes;  // Tarif pointer'ları dizisi (dinamik dizi)
    int size;          // Heap'te şu anda bulunan eleman sayısı
    int capacity;      // Heap'in maksimum kapasitesi
} Heap;

/* ============================================================================
 * FONKSİYON BİLDİRİMLERİ (FUNCTION DECLARATIONS)
 * ============================================================================ */

/**
 * @brief Yeni bir boş heap oluşturur
 * @param capacity Heap'in maksimum kapasitesi
 * @return Oluşturulan heap'e işaretçi, hata durumunda NULL
 * @details Bellekte recipe pointer dizisi için yer ayırır
 */
Heap* heap_create(int capacity);

/**
 * @brief Heap'e yeni tarif ekler
 * @param heap Heap yapısı
 * @param recipe Eklenecek tarif
 * @return Başarılı ise 1, başarısız ise 0
 * @details Tarif heap'in sonuna eklenir ve heapify_up ile doğru konuma yerleştirilir
 */
int heap_insert(Heap* heap, Recipe* recipe);

/**
 * @brief Heap'ten en küçük kalorili tarifi çıkarır
 * @param heap Heap yapısı
 * @return En küçük kalorili tarif, heap boşsa NULL
 * @details Root element çıkarılır ve heapify_down ile heap property korunur
 */
Recipe* heap_extract_min(Heap* heap);

/**
 * @brief Heap'in root elementine bakar ama çıkarmaz
 * @param heap Heap yapısı
 * @return En küçük kalorili tarif, heap boşsa NULL
 * @details Extract_min'den farkı: tarifi heap'ten çıkarmaz
 */
Recipe* heap_peek(Heap* heap);

/**
 * @brief Verilen index'ten başlayarak heap property'yi yukarı doğru sağlar
 * @param heap Heap yapısı
 * @param index Başlangıç index'i
 * @details Insert işleminden sonra çağrılır. Child parent'tan küçükse swap yapılır.
 */
void heapify_up(Heap* heap, int index);

/**
 * @brief Verilen index'ten başlayarak heap property'yi aşağı doğru sağlar
 * @param heap Heap yapısı
 * @param index Başlangıç index'i
 * @details Extract işleminden sonra çağrılır. Parent child'lardan büyükse swap yapılır.
 */
void heapify_down(Heap* heap, int index);

/**
 * @brief İki tarifin yerini değiştirir (swap)
 * @param recipe1 İlk tarif pointer'ının adresi
 * @param recipe2 İkinci tarif pointer'ının adresi
 * @details Heapify işlemlerinde kullanılır
 */
void heap_swap(Recipe** recipe1, Recipe** recipe2);

/**
 * @brief Tarifleri kaloriye göre sıralar (heap sort)
 * @param recipes Tarif dizisi
 * @param count Tarif sayısı
 * @details Tüm tarifleri heap'e ekler ve extract_min ile sıralı şekilde çıkarır
 */
void heap_sort_recipes(Recipe** recipes, int count);

/**
 * @brief Heap'in boş olup olmadığını kontrol eder
 * @param heap Heap yapısı
 * @return Heap boşsa 1, değilse 0
 * @details Size 0 ise heap boştur
 */
int heap_is_empty(Heap* heap);

/**
 * @brief Heap'in dolu olup olmadığını kontrol eder
 * @param heap Heap yapısı
 * @return Heap doluysa 1, değilse 0
 * @details Size capacity'ye eşitse heap doludur
 */
int heap_is_full(Heap* heap);

/**
 * @brief Heap'i ve içindeki verileri bellekten temizler
 * @param heap Heap yapısı
 * @details Recipe dizisini ve heap'i serbest bırakır
 */
void heap_destroy(Heap* heap);

/**
 * @brief Parent node'un index'ini hesaplar
 * @param index Child node index'i
 * @return Parent node index'i
 * @details Formula: (index - 1) / 2
 */
int heap_parent(int index);

/**
 * @brief Sol child node'un index'ini hesaplar
 * @param index Parent node index'i
 * @return Sol child node index'i
 * @details Formula: (2 * index) + 1
 */
int heap_left_child(int index);

/**
 * @brief Sağ child node'un index'ini hesaplar
 * @param index Parent node index'i
 * @return Sağ child node index'i
 * @details Formula: (2 * index) + 2
 */
int heap_right_child(int index);

#endif // HEAP_H - Include guard sonu
