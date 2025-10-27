/**
 * @file queue.c
 * @brief Circular Queue implementasyonu - 7 günlük haftalık plan için FIFO
 */

#include "queue.h"  // Queue header

// Boş queue oluştur
Queue* queue_create(void) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));  // Bellek ayır
    if (queue == NULL) {
        printf("HATA: Queue olusturulamadi!\n");
        return NULL;
    }
    queue->front = 0;   // İlk eleman index 0'da
    queue->rear = -1;   // Henüz eleman yok (-1 = boş)
    queue->count = 0;   // Eleman sayısı 0
    return queue;
}

// Queue'ya tarif ekle (enqueue)
int queue_enqueue(Queue* queue, Recipe* recipe) {
    if (queue == NULL || recipe == NULL) {  // Parametre kontrolü
        return 0;
    }
    
    if (queue_is_full(queue)) {  // Dolu mu?
        printf("UYARI: Haftalik plan dolu (7 gun)!\n");
        return 0;
    }
    
    // Circular mantık - rear'ı artır (7'ye ulaşınca 0'a dön)
    queue->rear = (queue->rear + 1) % WEEKLY_PLAN_SIZE;
    queue->recipes[queue->rear] = recipe;  // Tarifi ekle
    queue->count++;  // Sayıyı artır
    
    return 1;
}

// Queue'dan tarif çıkar (dequeue)
Recipe* queue_dequeue(Queue* queue) {
    if (queue == NULL || queue_is_empty(queue)) {  // Boş kontrolü
        return NULL;
    }
    
    Recipe* recipe = queue->recipes[queue->front];  // Front'taki tarifi al
    queue->front = (queue->front + 1) % WEEKLY_PLAN_SIZE;  // Front'u ilerlet (circular)
    queue->count--;  // Sayıyı azalt
    
    return recipe;
}

// Queue'nun önüne bak (peek)
Recipe* queue_peek(Queue* queue) {
    if (queue == NULL || queue_is_empty(queue)) {
        return NULL;
    }
    return queue->recipes[queue->front];  // Front'taki tarifi döndür (ama çıkarma)
}

// Queue boş mu?
int queue_is_empty(Queue* queue) {
    return (queue == NULL || queue->count == 0);  // Count 0 ise boş
}

// Queue dolu mu?
int queue_is_full(Queue* queue) {
    return (queue != NULL && queue->count == WEEKLY_PLAN_SIZE);  // 7 tarif varsa dolu
}

// Haftalık planı göster
void queue_display(Queue* queue) {
    if (queue == NULL) {
        printf("HATA: Gecersiz queue!\n");
        return;
    }
    
    if (queue_is_empty(queue)) {  // Boş kontrolü
        printf("\nHaftalik plan bos.\n");
        return;
    }
    
    printf("\n=== 7 GUNLUK BESLENME PLANI ===\n");
    
    // Günler dizisi
    const char* days[] = {"Pazartesi", "Sali", "Carsamba", "Persembe", "Cuma", "Cumartesi", "Pazar"};
    
    // Queue'daki tarifleri sırayla göster
    int index = queue->front;
    for (int i = 0; i < queue->count; i++) {
        printf("\n%s:\n", days[i]);  // Gün ismi
        printf("  -> %s (%d kcal)\n", 
               queue->recipes[index]->name,
               queue->recipes[index]->calories);
        index = (index + 1) % WEEKLY_PLAN_SIZE;  // Circular ilerle
    }
    printf("\n");
}

// Queue boyutu
int queue_size(Queue* queue) {
    return (queue != NULL) ? queue->count : 0;
}

// Queue'yu temizle
void queue_destroy(Queue* queue) {
    if (queue != NULL) {
        free(queue);  // Queue yapısını sil (tarifler hash table'da silinecek)
    }
}
