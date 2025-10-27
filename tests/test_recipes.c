#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "../src/recipe.h"
#include "../src/hash_table.h"
#include "../src/linked_list.h"

int main() {
    printf("=== UNIT TEST BASLADI ===\n");

    int passed = 0;
    int total = 0;

    // Test 1: Recipe oluşturma
    total++;
    Recipe* r = recipe_create(1, "Pizza", "Lunch", 800, 45);
    if (r && strcmp(r->name, "Pizza") == 0) {
        passed++;
    }
    else {
        printf("Test 1 basarisiz!\n");
    }

    // Test 2: Liste ekleme
    total++;
    List* lst = list_create();
    list_insert_tail(lst, r);
    if (list_size(lst) == 1) {
        passed++;
    }
    else {
        printf("Test 2 basarisiz!\n");
    }

    // Test 3: Hash table ekleme
    total++;
    HashTable* ht = hash_table_create(10);
    hash_table_insert(ht, r);
    if (hash_table_search(ht, 1) != NULL) {
        passed++;
    }
    else {
        printf("Test 3 basarisiz!\n");
    }

    // Test 4: Arama doğru sonuç veriyor mu?
    total++;
    Recipe* found = hash_table_search(ht, 1);
    if (found && strcmp(found->name, "Pizza") == 0) {
        passed++;
    }
    else {
        printf("Test 4 basarisiz!\n");
    }

    // Test 5: Silme işlemi
    total++;
    hash_table_delete(ht, 1);
    if (hash_table_search(ht, 1) == NULL) {
        passed++;
    }
    else {
        printf("Test 5 basarisiz!\n");
    }

    // Yüzdelik başarı oranı
    double success_rate = ((double)passed / total) * 100.0;
    printf("\nToplam %d testin %d tanesi basarili.\n", total, passed);
    printf("Test Sonucu: %%%.2f dogruluk orani\n", success_rate);

    printf("\n=== UNIT TEST BITTI ===\n");
    return 0;
}
