/**
 * @file hash_table.c
 * @brief Hash Table implementation with separate chaining
 * @details Provides O(1) average-time access to recipes by their ID
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_table.h"

/**
 * @brief Hash function using modulo operation
 * @param id Recipe ID
 * @param size Hash table size
 * @return Hash index
 */
static int hash_function(int id, int size) {
    return id % size;
}

/**
 * @brief Creates and initializes a new hash table with the given size
 * @param size Number of buckets in the hash table
 * @return Pointer to the created hash table, or NULL on failure
 */
HashTable* hash_table_create(int size) {
    if (size <= 0) {
        return NULL;
    }

    HashTable* ht = (HashTable*)malloc(sizeof(HashTable));
    if (!ht) {
        return NULL;
    }

    ht->size = size;
    ht->count = 0;
    ht->table = (HashNode**)calloc(size, sizeof(HashNode*));
    if (!ht->table) {
        free(ht);
        return NULL;
    }

    return ht;
}

/**
 * @brief Inserts a recipe into the hash table
 * @param ht Pointer to the hash table
 * @param recipe Pointer to the recipe to insert
 * @return 1 on success, 0 on failure
 */
int hash_table_insert(HashTable* ht, Recipe* recipe) {
    if (!ht || !recipe) {
        return 0;
    }

    int index = hash_function(recipe->id, ht->size);
    HashNode* new_node = (HashNode*)malloc(sizeof(HashNode));
    if (!new_node) {
        return 0;
    }

    new_node->recipe = recipe;
    new_node->next = ht->table[index];
    ht->table[index] = new_node;
    ht->count++;

    return 1;
}

/**
 * @brief Searches for a recipe by its ID
 * @param ht Pointer to the hash table
 * @param id Recipe ID to search for
 * @return Pointer to the found recipe, or NULL if not found
 */
Recipe* hash_table_search(HashTable* ht, int id) {
    if (!ht) {
        return NULL;
    }

    int index = hash_function(id, ht->size);
    HashNode* current = ht->table[index];

    while (current) {
        if (current->recipe && current->recipe->id == id) {
            return current->recipe;
        }
        current = current->next;
    }

    return NULL;
}

/**
 * @brief Deletes a recipe entry by its ID
 * @param ht Pointer to the hash table
 * @param id Recipe ID to delete
 * @return 1 on success, 0 on failure
 */
int hash_table_delete(HashTable* ht, int id) {
    if (!ht) {
        return 0;
    }

    int index = hash_function(id, ht->size);
    HashNode* current = ht->table[index];
    HashNode* prev = NULL;

    while (current) {
        if (current->recipe && current->recipe->id == id) {
            if (prev) {
                prev->next = current->next;
            } else {
                ht->table[index] = current->next;
            }
            free(current);
            ht->count--;
            return 1;
        }
        prev = current;
        current = current->next;
    }

    return 0;
}

/**
 * @brief Displays all recipes currently stored in the hash table
 * @param ht Pointer to the hash table
 */
void hash_table_display(HashTable* ht) {
    if (!ht) {
        printf("Hash table pointer is NULL.\n");
        return;
    }

    printf("\n=== HASH TABLE CONTENT ===\n");
    printf("Total Recipes: %d\n\n", ht->count);

    for (int i = 0; i < ht->size; i++) {
        if (ht->table[i]) {
            printf("Slot %d:\n", i);
            int node_count = 0;
            HashNode* current = ht->table[i];

            while (current) {
                node_count++;
                if (current->recipe) {
                    printf("  -> Recipe #%d: %s\n",
                           current->recipe->id,
                           current->recipe->name);
                }
                current = current->next;
            }
            printf("  (Total %d recipes)\n\n", node_count);
        }
    }
}

/**
 * @brief Frees all memory used by the hash table
 * @param ht Pointer to the hash table
 */
void hash_table_destroy(HashTable* ht) {
    if (!ht) {
        return;
    }

    for (int i = 0; i < ht->size; i++) {
        HashNode* current = ht->table[i];
        while (current) {
            HashNode* next = current->next;
            free(current);
            current = next;
        }
    }

    free(ht->table);
    free(ht);
}

/**
 * @brief Saves the hash table to a binary file
 * @param ht Pointer to the hash table
 * @param filename Name of the binary file
 * @return 1 on success, 0 on failure
 */
int hash_table_save_binary(const HashTable* ht, const char* filename) {
    if (!ht || !filename) {
        return 0;
    }

    FILE* file = fopen(filename, "wb");
    if (!file) {
        return 0;
    }

    if (fwrite(&ht->size, sizeof(int), 1, file) != 1) {
        fclose(file);
        return 0;
    }
    if (fwrite(&ht->count, sizeof(int), 1, file) != 1) {
        fclose(file);
        return 0;
    }

    for (int i = 0; i < ht->size; i++) {
        HashNode* current = ht->table[i];
        while (current) {
            if (current->recipe) {
                if (fwrite(current->recipe, sizeof(Recipe), 1, file) != 1) {
                    fclose(file);
                    return 0;
                }
            }
            current = current->next;
        }
    }

    fclose(file);
    return 1;
}

/**
 * @brief Loads a hash table from a binary file
 * @param filename Name of the binary file
 * @return Pointer to the loaded hash table, or NULL on failure
 */
HashTable* hash_table_load_binary(const char* filename) {
    if (!filename) {
        return NULL;
    }

    FILE* file = fopen(filename, "rb");
    if (!file) {
        return NULL;
    }

    int size, count;
    if (fread(&size, sizeof(int), 1, file) != 1) {
        fclose(file);
        return NULL;
    }
    if (fread(&count, sizeof(int), 1, file) != 1) {
        fclose(file);
        return NULL;
    }

    HashTable* ht = hash_table_create(size);
    if (!ht) {
        fclose(file);
        return NULL;
    }

    for (int i = 0; i < count; i++) {
        Recipe* recipe = (Recipe*)malloc(sizeof(Recipe));
        if (!recipe) {
            break;
        }
        if (fread(recipe, sizeof(Recipe), 1, file) != 1) {
            free(recipe);
            break;
        }
        hash_table_insert(ht, recipe);
    }

    fclose(file);
    return ht;
}

