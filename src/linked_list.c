/**
 * @file linked_list.c
 * @brief Singly linked list implementation for managing recipes
 * @details Provides insertion, deletion, traversal, and search operations
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked_list.h"

/**
 * @brief Creates and initializes an empty linked list
 * @return Pointer to the created list, or NULL on failure
 */
List* list_create(void) {
    List* list = (List*)malloc(sizeof(List));
    if (!list) {
        return NULL;
    }
    
    list->head = NULL;
    list->count = 0;
    return list;
}

/**
 * @brief Inserts a recipe at the beginning of the list
 * @param list Pointer to the list
 * @param recipe Pointer to the recipe to insert
 * @return 1 on success, 0 on failure
 */
int list_insert_head(List* list, Recipe* recipe) {
    if (!list || !recipe) {
        return 0;
    }

    ListNode* new_node = (ListNode*)malloc(sizeof(ListNode));
    if (!new_node) {
        return 0;
    }

    new_node->recipe = recipe;
    new_node->next = list->head;
    list->head = new_node;
    list->count++;

    return 1;
}

/**
 * @brief Inserts a recipe at the end of the list
 * @param list Pointer to the list
 * @param recipe Pointer to the recipe to insert
 * @return 1 on success, 0 on failure
 */
int list_insert_tail(List* list, Recipe* recipe) {
    if (!list || !recipe) {
        return 0;
    }

    ListNode* new_node = (ListNode*)malloc(sizeof(ListNode));
    if (!new_node) {
        return 0;
    }

    new_node->recipe = recipe;
    new_node->next = NULL;

    if (!list->head) {
        list->head = new_node;
    } else {
        ListNode* current = list->head;
        while (current->next) {
            current = current->next;
        }
        current->next = new_node;
    }

    list->count++;
    return 1;
}

/**
 * @brief Removes a recipe from the list by its ID
 * @param list Pointer to the list
 * @param id Recipe ID to remove
 * @return Pointer to the removed recipe, or NULL if not found
 */
Recipe* list_remove(List* list, int id) {
    if (!list || !list->head) {
        return NULL;
    }

    ListNode* current = list->head;
    ListNode* prev = NULL;

    while (current) {
        if (current->recipe && current->recipe->id == id) {
            if (prev) {
                prev->next = current->next;
            } else {
                list->head = current->next;
            }
            
            Recipe* recipe = current->recipe;
            free(current);
            list->count--;
            return recipe;
        }
        prev = current;
        current = current->next;
    }

    return NULL;
}

/**
 * @brief Searches for and returns a recipe by its ID
 * @param list Pointer to the list
 * @param id Recipe ID to search for
 * @return Pointer to the found recipe, or NULL if not found
 */
Recipe* list_find(List* list, int id) {
    if (!list || !list->head) {
        return NULL;
    }

    ListNode* current = list->head;
    while (current) {
        if (current->recipe && current->recipe->id == id) {
            return current->recipe;
        }
        current = current->next;
    }

    return NULL;
}

/**
 * @brief Displays all recipes in the list
 * @param list Pointer to the list
 */
void list_display(List* list) {
    if (!list) {
        printf("List pointer is NULL.\n");
        return;
    }

    if (!list->head) {
        printf("\nThe list is empty - no recipes available.\n");
        return;
    }

    printf("\n=== RECIPE LIST (%d recipes) ===\n", list->count);
    int index = 1;
    ListNode* current = list->head;

    while (current) {
        printf("\n%d. ", index++);
        recipe_display(current->recipe);
        current = current->next;
    }
}

/**
 * @brief Returns the number of recipes in the list
 * @param list Pointer to the list
 * @return Number of recipes
 */
int list_size(List* list) {
    return (list) ? list->count : 0;
}

/**
 * @brief Checks if the list is empty
 * @param list Pointer to the list
 * @return 1 if empty, 0 otherwise
 */
int list_is_empty(List* list) {
    return (list && list->head) ? 0 : 1;
}

/**
 * @brief Frees all memory associated with the list
 * @param list Pointer to the list
 */
void list_destroy(List* list) {
    if (!list) {
        return;
    }

    ListNode* current = list->head;
    while (current) {
        ListNode* next = current->next;
        free(current);
        current = next;
    }

    free(list);
}

/**
 * @brief Saves the linked list to a binary file
 * @param list Pointer to the list
 * @param filename Name of the binary file
 * @return 1 on success, 0 on failure
 */
int list_save_binary(const List* list, const char* filename) {
    if (!list || !filename) {
        return 0;
    }

    FILE* file = fopen(filename, "wb");
    if (!file) {
        return 0;
    }

    // Write count
    if (fwrite(&list->count, sizeof(int), 1, file) != 1) {
        fclose(file);
        return 0;
    }

    // Write all recipes
    ListNode* current = list->head;
    while (current) {
        if (current->recipe) {
            if (fwrite(current->recipe, sizeof(Recipe), 1, file) != 1) {
                fclose(file);
                return 0;
            }
        }
        current = current->next;
    }

    fclose(file);
    return 1;
}

/**
 * @brief Loads a linked list from a binary file
 * @param filename Name of the binary file
 * @return Pointer to the loaded list, or NULL on failure
 */
List* list_load_binary(const char* filename) {
    if (!filename) {
        return NULL;
    }

    FILE* file = fopen(filename, "rb");
    if (!file) {
        return NULL;
    }

    List* list = list_create();
    if (!list) {
        fclose(file);
        return NULL;
    }

    int count;
    if (fread(&count, sizeof(int), 1, file) != 1) {
        fclose(file);
        list_destroy(list);
        return NULL;
    }

    for (int i = 0; i < count; i++) {
        Recipe* recipe = (Recipe*)malloc(sizeof(Recipe));
        if (!recipe) {
            fclose(file);
            list_destroy(list);
            return NULL;
        }

        if (fread(recipe, sizeof(Recipe), 1, file) != 1) {
            free(recipe);
            fclose(file);
            list_destroy(list);
            return NULL;
        }

        list_insert_tail(list, recipe);
    }

    fclose(file);
    return list;
}

