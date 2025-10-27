/**
 * @file heap.c
 * @brief Min-Heap implementasyonu - Kaloriye göre sıralama
 */

#include "heap.h"  // Heap header

// Parent index'ini hesapla
int heap_parent(int index) { return (index - 1) / 2; }

// Sol child index'ini hesapla
int heap_left_child(int index) { return (2 * index) + 1; }

// Sağ child index'ini hesapla
int heap_right_child(int index) { return (2 * index) + 2; }

// İki recipe pointer'ını takas et
void heap_swap(Recipe** a, Recipe** b) {
    Recipe* temp = *a;  // Geçici değişken
    *a = *b;            // a'yı b yap
    *b = temp;          // b'yi temp (eski a) yap
}

// Boş heap oluştur
Heap* heap_create(int capacity) {
    Heap* heap = (Heap*)malloc(sizeof(Heap));  // Bellek ayır
    if (heap == NULL) {  // Bellek kontrolü
        printf("HATA: Heap olusturulamadi!\n");
        return NULL;
    }
    heap->recipes = (Recipe**)malloc(sizeof(Recipe*) * capacity);  // Dizi için bellek
    if (heap->recipes == NULL) {  // Bellek kontrolü
        printf("HATA: Heap dizisi olusturulamadi!\n");
        free(heap);
        return NULL;
    }
    heap->size = 0;        // Başlangıçta eleman yok
    heap->capacity = capacity;  // Kapasiteyi ayarla
    return heap;  // Heap'i döndür
}

// Heap boş mu?
int heap_is_empty(Heap* heap) { return (heap == NULL || heap->size == 0); }

// Heap dolu mu?
int heap_is_full(Heap* heap) { return (heap != NULL && heap->size == heap->capacity); }

// Yukarı doğru heapify (insert sonrası)
void heapify_up(Heap* heap, int index) {
    while (index > 0) {  // Root'a gelene kadar devam et
        int parent = heap_parent(index);  // Parent index'i
        // Eğer current node'un kalorisi parent'tan küçükse yer değiştir
        if (recipe_compare_by_calories(heap->recipes[index], heap->recipes[parent]) < 0) {
            heap_swap(&heap->recipes[index], &heap->recipes[parent]);  // Swap
            index = parent;  // Yukarı çıkmaya devam et
        } else {
            break;  // Doğru yerdeyiz, dur
        }
    }
}

// Aşağı doğru heapify (extract sonrası)
void heapify_down(Heap* heap, int index) {
    while (1) {  // Uygun child bulunana kadar devam et
        int left = heap_left_child(index);    // Sol child
        int right = heap_right_child(index);  // Sağ child
        int smallest = index;                 // Şimdilik en küçük current
        
        // Sol child varsa ve daha küçükse güncelle
        if (left < heap->size && recipe_compare_by_calories(heap->recipes[left], heap->recipes[smallest]) < 0) {
            smallest = left;
        }
        // Sağ child varsa ve daha küçükse güncelle
        if (right < heap->size && recipe_compare_by_calories(heap->recipes[right], heap->recipes[smallest]) < 0) {
            smallest = right;
        }
        // Eğer en küçük zaten current ise dur
        if (smallest == index) {
            break;
        }
        // Değilse current ile en küçük child'ı takas et ve devam et
        heap_swap(&heap->recipes[index], &heap->recipes[smallest]);
        index = smallest;
    }
}

// Heap'e tarif ekle
int heap_insert(Heap* heap, Recipe* recipe) {
    if (heap == NULL || recipe == NULL) {  // Parametre kontrolü
        return 0;
    }
    if (heap_is_full(heap)) {  // Dolu mu?
        printf("UYARI: Heap dolu - daha fazla tarif eklenemez!\n");
        return 0;
    }
    heap->recipes[heap->size] = recipe;  // Yeni tarifi sona ekle
    heapify_up(heap, heap->size);        // Yukarı doğru düzelt
    heap->size++;                        // Boyutu artır
    return 1;  // Başarılı
}

// Heap'in tepesine bak (en küçük kalori)
Recipe* heap_peek(Heap* heap) {
    if (heap_is_empty(heap)) {  // Boşsa NULL döndür
        return NULL;
    }
    return heap->recipes[0];  // Root eleman
}

// Heap'ten en küçük kalorili tarifi çıkar
Recipe* heap_extract_min(Heap* heap) {
    if (heap_is_empty(heap)) {  // Boş kontrolü
        return NULL;
    }
    Recipe* min = heap->recipes[0];             // Root'u sakla
    heap->recipes[0] = heap->recipes[heap->size - 1];  // Son elemanı root'a koy
    heap->size--;                                // Boyutu azalt
    heapify_down(heap, 0);                       // Aşağı doğru düzelt
    return min;  // En küçük elemanı döndür
}

// Heap sort - tarifleri kaloriye göre sırala
void heap_sort_recipes(Recipe** recipes, int count) {
    Heap* heap = heap_create(count);  // Geçici heap oluştur
    if (heap == NULL) { return; }     // Bellek kontrolü
    
    // Tüm tarifleri heap'e ekle
    for (int i = 0; i < count; i++) {
        heap_insert(heap, recipes[i]);
    }
    
    // En küçükten büyüğe çıkar ve diziye yaz
    for (int i = 0; i < count; i++) {
        recipes[i] = heap_extract_min(heap);
    }
    
    heap_destroy(heap);  // Geçici heap'i temizle
}

// Heap'i temizle
void heap_destroy(Heap* heap) {
    if (heap == NULL) { return; }
    free(heap->recipes);  // Dizi belleğini serbest bırak
    free(heap);           // Heap yapısını serbest bırak
}
