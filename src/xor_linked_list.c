/**
 * @file xor_linked_list.c
 * @brief XOR Linked List implementation for memory-efficient bidirectional traversal
 * @details Uses XOR pointer technique to store both next and previous pointers in a single field
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "xor_linked_list.h"

/**
 * @brief Computes XOR of two pointers
 * @param a First pointer
 * @param b Second pointer
 * @return XOR of the two pointers
 */
XORListNode* xor_list_xor(XORListNode* a, XORListNode* b) {
    return (XORListNode*)((uintptr_t)a ^ (uintptr_t)b);
}

/**
 * @brief Creates and initializes an empty XOR linked list
 * @return Pointer to the created list, or NULL on failure
 */
XORList* xor_list_create(void) {
    XORList* list = (XORList*)malloc(sizeof(XORList));
    if (!list) {
        return NULL;
    }

    list->head = NULL;
    list->tail = NULL;
    list->count = 0;

    return list;
}

/**
 * @brief Inserts a recipe at the beginning of the list
 * @param list Pointer to the XOR list
 * @param recipe Pointer to the recipe to insert
 * @return 1 on success, 0 on failure
 */
int xor_list_insert_head(XORList* list, Recipe* recipe) {
    if (!list || !recipe) {
        return 0;
    }

    XORListNode* new_node = (XORListNode*)malloc(sizeof(XORListNode));
    if (!new_node) {
        return 0;
    }

    new_node->recipe = recipe;
    new_node->npx = list->head;

    if (list->head) {
        list->head->npx = xor_list_xor(new_node, list->head->npx);
    } else {
        list->tail = new_node;
    }

    list->head = new_node;
    list->count++;

    return 1;
}

/**
 * @brief Inserts a recipe at the end of the list
 * @param list Pointer to the XOR list
 * @param recipe Pointer to the recipe to insert
 * @return 1 on success, 0 on failure
 */
int xor_list_insert_tail(XORList* list, Recipe* recipe) {
    if (!list || !recipe) {
        return 0;
    }

    XORListNode* new_node = (XORListNode*)malloc(sizeof(XORListNode));
    if (!new_node) {
        return 0;
    }

    new_node->recipe = recipe;
    new_node->npx = list->tail;

    if (list->tail) {
        list->tail->npx = xor_list_xor(list->tail->npx, new_node);
    } else {
        list->head = new_node;
    }

    list->tail = new_node;
    list->count++;

    return 1;
}

/**
 * @brief Removes a recipe from the list by its ID
 * @param list Pointer to the XOR list
 * @param id Recipe ID to remove
 * @return Pointer to the removed recipe, or NULL if not found
 */
Recipe* xor_list_remove(XORList* list, int id) {
    if (!list || !list->head) {
        return NULL;
    }

    XORListNode* current = list->head;
    XORListNode* prev = NULL;
    XORListNode* next;

    while (current) {
        next = xor_list_xor(prev, current->npx);

        if (current->recipe && current->recipe->id == id) {
            Recipe* recipe = current->recipe;

            if (prev) {
                prev->npx = xor_list_xor(xor_list_xor(prev->npx, current), next);
            } else {
                list->head = next;
            }

            if (next) {
                next->npx = xor_list_xor(xor_list_xor(next->npx, current), prev);
            } else {
                list->tail = prev;
            }

            free(current);
            list->count--;
            return recipe;
        }

        prev = current;
        current = next;
    }

    return NULL;
}

/**
 * @brief Searches for and returns a recipe by its ID
 * @param list Pointer to the XOR list
 * @param id Recipe ID to search for
 * @return Pointer to the found recipe, or NULL if not found
 */
Recipe* xor_list_find(XORList* list, int id) {
    if (!list || !list->head) {
        return NULL;
    }

    XORListNode* current = list->head;
    XORListNode* prev = NULL;
    XORListNode* next;

    while (current) {
        if (current->recipe && current->recipe->id == id) {
            return current->recipe;
        }

        next = xor_list_xor(prev, current->npx);
        prev = current;
        current = next;
    }

    return NULL;
}

/**
 * @brief Traverses the list forward (head to tail)
 * @param list Pointer to the XOR list
 * @param visit Function pointer to call for each recipe
 */
void xor_list_traverse_forward(XORList* list, void (*visit)(Recipe* recipe)) {
    if (!list || !list->head || !visit) {
        return;
    }

    XORListNode* current = list->head;
    XORListNode* prev = NULL;
    XORListNode* next;

    while (current) {
        visit(current->recipe);
        next = xor_list_xor(prev, current->npx);
        prev = current;
        current = next;
    }
}

/**
 * @brief Traverses the list backward (tail to head)
 * @param list Pointer to the XOR list
 * @param visit Function pointer to call for each recipe
 */
void xor_list_traverse_backward(XORList* list, void (*visit)(Recipe* recipe)) {
    if (!list || !list->tail || !visit) {
        return;
    }

    XORListNode* current = list->tail;
    XORListNode* next = NULL;
    XORListNode* prev;

    while (current) {
        visit(current->recipe);
        prev = xor_list_xor(next, current->npx);
        next = current;
        current = prev;
    }
}

/**
 * @brief Returns the number of recipes in the list
 * @param list Pointer to the XOR list
 * @return Number of recipes
 */
int xor_list_size(const XORList* list) {
    return (list) ? list->count : 0;
}

/**
 * @brief Checks if the list is empty
 * @param list Pointer to the XOR list
 * @return 1 if empty, 0 otherwise
 */
int xor_list_is_empty(const XORList* list) {
    return (list && list->head) ? 0 : 1;
}

/**
 * @brief Frees all memory associated with the list
 * @param list Pointer to the XOR list
 */
void xor_list_destroy(XORList* list) {
    if (!list) {
        return;
    }

    XORListNode* current = list->head;
    XORListNode* prev = NULL;
    XORListNode* next;

    while (current) {
        next = xor_list_xor(prev, current->npx);
        free(current);
        prev = current;
        current = next;
    }

    free(list);
}

/**
 * @brief Saves the XOR linked list to a binary file
 * @param list Pointer to the XOR list
 * @param filename Name of the binary file
 * @return 1 on success, 0 on failure
 */
int xor_list_save_binary(const XORList* list, const char* filename) {
    if (!list || !filename) {
        return 0;
    }

    FILE* file = fopen(filename, "wb");
    if (!file) {
        return 0;
    }

    if (fwrite(&list->count, sizeof(int), 1, file) != 1) {
        fclose(file);
        return 0;
    }

    XORListNode* current = list->head;
    XORListNode* prev = NULL;
    XORListNode* next;

    while (current) {
        if (current->recipe) {
            if (fwrite(current->recipe, sizeof(Recipe), 1, file) != 1) {
                fclose(file);
                return 0;
            }
        }
        next = xor_list_xor(prev, current->npx);
        prev = current;
        current = next;
    }

    fclose(file);
    return 1;
}

/**
 * @brief Loads an XOR linked list from a binary file
 * @param filename Name of the binary file
 * @return Pointer to the loaded list, or NULL on failure
 */
XORList* xor_list_load_binary(const char* filename) {
    if (!filename) {
        return NULL;
    }

    FILE* file = fopen(filename, "rb");
    if (!file) {
        return NULL;
    }

    XORList* list = xor_list_create();
    if (!list) {
        fclose(file);
        return NULL;
    }

    int count;
    if (fread(&count, sizeof(int), 1, file) != 1) {
        fclose(file);
        xor_list_destroy(list);
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
        xor_list_insert_tail(list, recipe);
    }

    fclose(file);
    return list;
}

