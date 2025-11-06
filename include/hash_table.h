#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdio.h>
#include <stdlib.h>
#include "recipe.h"

// === Structure Definitions ===

// Represents a single node in the hash table's linked list (chaining method)
typedef struct HashNode {
    Recipe* recipe;             // Pointer to the recipe stored in this node
    struct HashNode* next;      // Pointer to the next node in the same bucket
} HashNode;

// Represents the hash table structure
typedef struct {
    int size;                   // Total number of buckets in the hash table
    int count;                  // Number of recipes currently stored
    HashNode** table;           // Array of pointers to hash buckets
} HashTable;

// === Function Declarations ===

// Creates and initializes a new hash table with the given size
HashTable* hash_table_create(int size);

// Inserts a recipe into the hash table
int hash_table_insert(HashTable* ht, Recipe* recipe);

// Searches for a recipe by its ID
Recipe* hash_table_search(HashTable* ht, int id);

// Deletes a recipe entry by its ID
int hash_table_delete(HashTable* ht, int id);

// Displays all recipes currently stored in the hash table
void hash_table_display(HashTable* ht);

// Frees all memory used by the hash table
void hash_table_destroy(HashTable* ht);

// === Binary File Operations ===

// Saves the hash table to a binary file
int hash_table_save_binary(const HashTable* ht, const char* filename);

// Loads a hash table from a binary file
HashTable* hash_table_load_binary(const char* filename);

#endif // HASH_TABLE_H
