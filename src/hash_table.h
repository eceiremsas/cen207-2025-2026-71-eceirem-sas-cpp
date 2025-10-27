#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdio.h>
#include <stdlib.h>
#include "recipe.h"

typedef struct HashNode {
    Recipe* recipe;
    struct HashNode* next;
} HashNode;

typedef struct {
    int size;
    int count;
    HashNode** table;
} HashTable;

// Fonksiyon bildirimleri
HashTable* hash_table_create(int size);
int hash_table_insert(HashTable* ht, Recipe* recipe);
Recipe* hash_table_search(HashTable* ht, int id);
int hash_table_delete(HashTable* ht, int id);
void hash_table_display(HashTable* ht);
void hash_table_destroy(HashTable* ht);

#endif
