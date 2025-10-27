
#include "linked_list.h"  // Linked list header

// Yeni boş liste oluştur
List* list_create(void) {
    List* list = (List*)malloc(sizeof(List));  // Bellek ayır
    if (list == NULL) {  // Bellek kontrolü
        printf("HATA: Liste olusturulamadi!\n");
        return NULL;
    }
    list->head = NULL;  // Başlangıçta liste boş
    list->count = 0;    // Eleman sayısı 0
    return list;
}

// Listenin başına tarif ekle - O(1)
int list_insert_head(List* list, Recipe* recipe) {
    if (list == NULL || recipe == NULL) {  // Parametre kontrolü
        return 0;
    }
    
    ListNode* new_node = (ListNode*)malloc(sizeof(ListNode));  // Yeni node oluştur
    if (new_node == NULL) {  // Bellek kontrolü
        printf("HATA: Node olusturulamadi!\n");
        return 0;
    }
    
    new_node->recipe = recipe;     // Tarifi node'a ata
    new_node->next = list->head;   // Yeni node'un next'i mevcut head
    list->head = new_node;         // Yeni node artık head (liste başı)
    list->count++;                 // Eleman sayısını artır
    return 1;
}

// Listenin sonuna tarif ekle - O(n)
int list_insert_tail(List* list, Recipe* recipe) {
    if (list == NULL || recipe == NULL) {  // Parametre kontrolü
        return 0;
    }
    
    ListNode* new_node = (ListNode*)malloc(sizeof(ListNode));  // Yeni node
    if (new_node == NULL) {
        return 0;
    }
    
    new_node->recipe = recipe;  // Tarifi ata
    new_node->next = NULL;      // Son node olacağı için next = NULL
    
    if (list->head == NULL) {  // Liste boşsa
        list->head = new_node;  // Yeni node hem baş hem son
    } else {  // Liste doluysa
        ListNode* current = list->head;
        while (current->next != NULL) {  // Sona kadar git
            current = current->next;
        }
        current->next = new_node;  // Son node'un next'ine yeni node'u ekle
    }
    
    list->count++;  // Sayıyı artır
    return 1;
}

// ID'ye göre tarif bul ve listeden çıkar
Recipe* list_remove(List* list, int id) {
    if (list == NULL || list->head == NULL) {  // Liste boş kontrolü
        return NULL;
    }
    
    ListNode* current = list->head;
    ListNode* prev = NULL;
    
    while (current != NULL) {  // Listeyi dolaş
        if (current->recipe->id == id) {  // Aradığımız ID bulundu
            if (prev == NULL) {  // Baştaysa
                list->head = current->next;  // Head'i güncelle
            } else {  // Ortada/sondaysa
                prev->next = current->next;  // Öncekinin next'ini güncelle
            }
            
            Recipe* recipe = current->recipe;  // Tarifi sakla
            free(current);  // Node'u sil (ama tarifi değil)
            list->count--;  // Sayıyı azalt
            return recipe;  // Tarifi döndür
        }
        prev = current;
        current = current->next;
    }
    
    return NULL;  // Bulunamadı
}

// ID'ye göre tarif ara
Recipe* list_find(List* list, int id) {
    if (list == NULL) {
        return NULL;
    }
    
    ListNode* current = list->head;
    while (current != NULL) {  // Listeyi dolaş
        if (current->recipe->id == id) {  // Bulundu
            return current->recipe;
        }
        current = current->next;
    }
    
    return NULL;  // Bulunamadı
}

// Tüm tarifleri göster
void list_display(List* list) {
    if (list == NULL) {
        printf("HATA: Gecersiz liste!\n");
        return;
    }
    
    if (list->head == NULL) {  // Liste boş
        printf("\nListe bos - hic tarif yok.\n");
        return;
    }
    
    printf("\n=== TARIF LISTESI (%d tarif) ===\n", list->count);
    
    ListNode* current = list->head;
    int index = 1;
    
    while (current != NULL) {  // Tüm node'ları dolaş
        printf("\n%d. ", index++);
        recipe_display(current->recipe);  // Her tarifi göster
        current = current->next;
    }
}

// Liste boyutu döndür
int list_size(List* list) {
    return (list != NULL) ? list->count : 0;  // NULL kontrolü ile count döndür
}

// Liste boş mu kontrol et
int list_is_empty(List* list) {
    return (list == NULL || list->head == NULL);  // Boşsa 1, değilse 0
}

// Listeyi temizle
void list_destroy(List* list) {
    if (list == NULL) {
        return;
    }
    
    ListNode* current = list->head;
    while (current != NULL) {  // Tüm node'ları dolaş
        ListNode* temp = current;
        current = current->next;
        free(temp);  // Node'u sil (tarif hash table'da silinecek)
    }
    
    free(list);  // Liste yapısını sil
}
