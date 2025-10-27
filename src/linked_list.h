#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include "recipe.h"  // Recipe yapısını kullanıyoruz

// Her bir liste elemanı (node)
typedef struct ListNode {
    Recipe* recipe;
    struct ListNode* next;
} ListNode;

// Liste yapısı
typedef struct {
    ListNode* head;
    int count;
} List;

// Fonksiyon bildirimleri
List* list_create(void);
int list_insert_head(List* list, Recipe* recipe);
int list_insert_tail(List* list, Recipe* recipe);
Recipe* list_remove(List* list, int id);
Recipe* list_find(List* list, int id);
void list_display(List* list);
int list_size(List* list);
int list_is_empty(List* list);
void list_destroy(List* list);

#endif
