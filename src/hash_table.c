/**
 * @file hash_table.c
 * @brief Hash Table implementasyonu
 * @details Tarif ID'sine göre O(1) zamanda erişim sağlar.
 *          Collision durumlarında separate chaining (ayrık zincirleme) kullanır.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_table.h"  // Hash table header dosyası
#include "recipe.h"

/**
 * @brief Hash table oluşturur ve başlatır
 */
HashTable* hash_table_create(int size) {
    // Hash table için bellek ayır
    HashTable* ht = (HashTable*)malloc(sizeof(HashTable));
    
    // Bellek ayırma kontrolü
    if (ht == NULL) {
        printf("HATA: Hash table olusturulamadi!\n");
        return NULL;
    }
    
    // Hash table boyutunu ayarla
    ht->size = size;
    
    // Başlangıçta hiç tarif yok
    ht->count = 0;
    
    // Hash node pointer dizisi için bellek ayır
    // Her slot bir linked list başı olacak
    ht->table = (HashNode**)malloc(sizeof(HashNode*) * size);
    
    // Tablo belleği ayırma kontrolü
    if (ht->table == NULL) {
        printf("HATA: Hash table dizisi olusturulamadi!\n");
        free(ht);  // Ana yapıyı serbest bırak
        return NULL;
    }
    
    // Tüm slotları NULL ile başlat (boş liste)
    for (int i = 0; i < size; i++) {
        ht->table[i] = NULL;  // i. slot'ta henüz düğüm yok
    }
    
    // Oluşturulan hash table'ı döndür
    return ht;
}

/**
 * @brief Hash fonksiyonu - ID'den hash değeri hesaplar
 * @details Basit modulo işlemi kullanır
 */
int hash_function(int id, int size) {
    // ID'yi table boyutuna böl ve kalanı al
    // Sonuç 0 ile size-1 arasında olacak
    return id % size;
}

/**
 * @brief Hash table'a yeni tarif ekler
 */
int hash_table_insert(HashTable* ht, Recipe* recipe) {
    // Parametre kontrolü
    if (ht == NULL || recipe == NULL) {
        printf("HATA: Gecersiz parametre!\n");
        return 0;
    }
    
    // Hash değerini hesapla (hangi slot'a gideceğini bul)
    int index = hash_function(recipe->id, ht->size);
    
    // Yeni hash node oluştur
    HashNode* new_node = (HashNode*)malloc(sizeof(HashNode));
    
    // Bellek kontrolü
    if (new_node == NULL) {
        printf("HATA: Hash node olusturulamadi!\n");
        return 0;
    }
    
    // Node'a tarifi ata
    new_node->recipe = recipe;
    
    // Yeni node'u listenin başına ekle (separate chaining)
    // Mevcut baş node'u yeni node'un next'i yap
    new_node->next = ht->table[index];
    
    // Yeni node'u liste başı yap
    ht->table[index] = new_node;
    
    // Toplam tarif sayısını artır
    ht->count++;
    
    return 1;  // Başarılı
}

/**
 * @brief Hash table'da ID'ye göre tarif arar
 */
Recipe* hash_table_search(HashTable* ht, int id) {
    // Parametre kontrolü
    if (ht == NULL) {
        return NULL;
    }
    
    // Hash değerini hesapla (hangi slot'a bakacağımızı bul)
    int index = hash_function(id, ht->size);
    
    // O slot'taki linked list'i dolaş
    HashNode* current = ht->table[index];
    
    // Liste boş değilken devam et
    while (current != NULL) {
        // Bu node'un tarifinin ID'si aradığımız ID'ye eşit mi?
        if (current->recipe->id == id) {
            return current->recipe;  // Bulundu! Tarifi döndür
        }
        
        // Bir sonraki node'a geç
        current = current->next;
    }
    
    // Bulunamadı
    return NULL;
}

/**
 * @brief Hash table'dan tarif siler
 */
int hash_table_delete(HashTable* ht, int id) {
    // Parametre kontrolü
    if (ht == NULL) {
        printf("HATA: Gecersiz hash table!\n");
        return 0;
    }
    
    // Hash değerini hesapla
    int index = hash_function(id, ht->size);
    
    // O slot'taki linked list'i dolaş
    HashNode* current = ht->table[index];
    HashNode* prev = NULL;  // Bir önceki node'u takip et
    
    // Liste boş değilken ara
    while (current != NULL) {
        // Aradığımız tarifi bulduk mu?
        if (current->recipe->id == id) {
            // Bulduk! Şimdi listeden çıkar
            
            // Eğer liste başındaysa
            if (prev == NULL) {
                ht->table[index] = current->next;  // Başı güncelle
            } else {
                // Ortada veya sondaysa
                prev->next = current->next;  // Öncekinin next'ini güncelle
            }
            
            // Node'u serbest bırak (ama tarifi değil - başka yerde kullanılabilir)
            free(current);
            
            // Toplam sayıyı azalt
            ht->count--;
            
            return 1;  // Başarılı
        }
        
        // Bir sonraki node'a geç
        prev = current;
        current = current->next;
    }
    
    // Bulunamadı
    printf("UYARI: Silinecek tarif bulunamadi (ID: %d)\n", id);
    return 0;
}

/**
 * @brief Hash table'daki tüm tarifleri gösterir
 */
void hash_table_display(HashTable* ht) {
    // Parametre kontrolü
    if (ht == NULL) {
        printf("HATA: Gecersiz hash table!\n");
        return;
    }
    
    printf("\n=== HASH TABLE ICERIGI ===\n");
    printf("Toplam Tarif Sayisi: %d\n\n", ht->count);
    
    // Tüm slotları dolaş
    for (int i = 0; i < ht->size; i++) {
        // Bu slot boş mu?
        if (ht->table[i] != NULL) {
            printf("Slot %d:\n", i);
            
            // Bu slot'taki linked list'i dolaş
            HashNode* current = ht->table[i];
            int node_count = 0;
            
            while (current != NULL) {
                node_count++;
                printf("  -> Tarif #%d: %s\n", 
                       current->recipe->id, 
                       current->recipe->name);
                
                current = current->next;
            }
            
            printf("  (Toplam %d tarif)\n\n", node_count);
        }
    }
}

/**
 * @brief Hash table'ı ve içindekileri temizler
 */
void hash_table_destroy(HashTable* ht) {
    // Parametre kontrolü
    if (ht == NULL) {
        return;
    }
    
    // Tüm slotları dolaş
    for (int i = 0; i < ht->size; i++) {
        HashNode* current = ht->table[i];
        
        // Bu slot'taki tüm node'ları sil
        while (current != NULL) {
            HashNode* temp = current;  // Şu anki node'u sakla
            current = current->next;   // Bir sonrakine geç
            
            // Tarifi sil (bellek sızıntısı önleme)
            recipe_destroy(temp->recipe);
            
            // Node'u sil
            free(temp);
        }
    }
    
    // Table dizisini sil
    free(ht->table);
    
    // Hash table yapısını sil
    free(ht);
}
