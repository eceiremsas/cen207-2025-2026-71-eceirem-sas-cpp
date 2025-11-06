#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include "recipe.h"  // Using the Recipe structure

// === Structure Definitions ===

// Represents a single node in the linked list
typedef struct ListNode {
    Recipe* recipe;           // Pointer to the recipe stored in this node
    struct ListNode* next;    // Pointer to the next node in the list
} ListNode;

// Represents the linked list structure
typedef struct {
    ListNode* head;           // Pointer to the first node in the list
    int count;                // Number of recipes currently stored
} List;

// === Function Declarations ===

// Creates and initializes an empty linked list
List* list_create(void);

// Inserts a recipe at the beginning of the list
int list_insert_head(List* list, Recipe* recipe);

// Inserts a recipe at the end of the list
int list_insert_tail(List* list, Recipe* recipe);

// Removes a recipe from the list by its ID
Recipe* list_remove(List* list, int id);

// Searches for and returns a recipe by its ID
Recipe* list_find(List* list, int id);

// Displays all recipes in the list
void list_display(List* list);

// Returns the number of recipes in the list
int list_size(List* list);

// Checks if the list is empty
int list_is_empty(List* list);

// Frees all memory associated with the list
void list_destroy(List* list);

// === Binary File Operations ===

// Saves the linked list to a binary file
int list_save_binary(const List* list, const char* filename);

// Loads a linked list from a binary file
List* list_load_binary(const char* filename);

#endif // LINKED_LIST_H
