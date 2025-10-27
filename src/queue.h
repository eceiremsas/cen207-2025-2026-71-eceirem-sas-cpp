
#ifndef QUEUE_H  // Include guard başlangıcı
#define QUEUE_H  // QUEUE_H makrosunu tanımla

#include "recipe.h"  // Recipe veri yapısı için
#define WEEKLY_PLAN_SIZE 7 

typedef struct {
    Recipe* recipes[WEEKLY_PLAN_SIZE];  // Tarifleri tutan dizi (her eleman bir günü temsil eder)
    int front;                           // Kuyruğun ön index'i (ilk eleman buradadır)
    int rear;                            // Kuyruğun arka index'i (son eleman buradadır)
    int count;                           // Kuyrukta şu anda bulunan eleman sayısı
} Queue;

Queue* queue_create(void);

int queue_enqueue(Queue* queue, Recipe* recipe);

Recipe* queue_dequeue(Queue* queue);

Recipe* queue_peek(Queue* queue);

int queue_is_empty(Queue* queue);

int queue_is_full(Queue* queue);

void queue_display(Queue* queue);

int queue_size(Queue* queue);

void queue_destroy(Queue* queue);

#endif // QUEUE_H - Include guard sonu
