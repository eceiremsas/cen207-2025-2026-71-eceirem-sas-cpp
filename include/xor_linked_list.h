#ifndef XOR_LINKED_LIST_H
#define XOR_LINKED_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "recipe.h"

/**
 * @file xor_linked_list.h
 * @brief XOR Linked List implementation for memory-efficient bidirectional traversal
 * @details Uses XOR pointer technique to store both next and previous pointers in a single field
 *          This reduces memory usage by half compared to a doubly linked list
 */

// === Structure Definitions ===

/**
 * @struct XORListNode
 * @brief Node in XOR linked list
 * @details The npx field stores the XOR of next and previous node addresses
 */
typedef struct XORListNode {
    Recipe* recipe;              // Pointer to the recipe stored in this node
    struct XORListNode* npx;     // XOR of next and previous node pointers
} XORListNode;

/**
 * @struct XORList
 * @brief XOR Linked List structure
 */
typedef struct {
    XORListNode* head;           // Pointer to the first node
    XORListNode* tail;           // Pointer to the last node
    int count;                   // Number of recipes currently stored
} XORList;

// === Function Declarations ===

/**
 * @brief Creates and initializes an empty XOR linked list
 * @return Pointer to the created list, or NULL on failure
 */
XORList* xor_list_create(void);

/**
 * @brief Inserts a recipe at the beginning of the list
 * @param list Pointer to the XOR list
 * @param recipe Pointer to the recipe to insert
 * @return 1 on success, 0 on failure
 */
int xor_list_insert_head(XORList* list, Recipe* recipe);

/**
 * @brief Inserts a recipe at the end of the list
 * @param list Pointer to the XOR list
 * @param recipe Pointer to the recipe to insert
 * @return 1 on success, 0 on failure
 */
int xor_list_insert_tail(XORList* list, Recipe* recipe);

/**
 * @brief Removes a recipe from the list by its ID
 * @param list Pointer to the XOR list
 * @param id Recipe ID to remove
 * @return Pointer to the removed recipe, or NULL if not found
 */
Recipe* xor_list_remove(XORList* list, int id);

/**
 * @brief Searches for and returns a recipe by its ID
 * @param list Pointer to the XOR list
 * @param id Recipe ID to search for
 * @return Pointer to the found recipe, or NULL if not found
 */
Recipe* xor_list_find(XORList* list, int id);

/**
 * @brief Traverses the list forward (head to tail)
 * @param list Pointer to the XOR list
 * @param visit Function pointer to call for each recipe
 */
void xor_list_traverse_forward(XORList* list, void (*visit)(Recipe* recipe));

/**
 * @brief Traverses the list backward (tail to head)
 * @param list Pointer to the XOR list
 * @param visit Function pointer to call for each recipe
 */
void xor_list_traverse_backward(XORList* list, void (*visit)(Recipe* recipe));

/**
 * @brief Returns the number of recipes in the list
 * @param list Pointer to the XOR list
 * @return Number of recipes
 */
int xor_list_size(const XORList* list);

/**
 * @brief Checks if the list is empty
 * @param list Pointer to the XOR list
 * @return 1 if empty, 0 otherwise
 */
int xor_list_is_empty(const XORList* list);

/**
 * @brief Frees all memory associated with the list
 * @param list Pointer to the XOR list
 */
void xor_list_destroy(XORList* list);

// === Binary File Operations ===

/**
 * @brief Saves the XOR linked list to a binary file
 * @param list Pointer to the XOR list
 * @param filename Name of the binary file
 * @return 1 on success, 0 on failure
 */
int xor_list_save_binary(const XORList* list, const char* filename);

/**
 * @brief Loads an XOR linked list from a binary file
 * @param filename Name of the binary file
 * @return Pointer to the loaded list, or NULL on failure
 */
XORList* xor_list_load_binary(const char* filename);

// === Helper Functions ===

/**
 * @brief Computes XOR of two pointers
 * @param a First pointer
 * @param b Second pointer
 * @return XOR of the two pointers
 */
XORListNode* xor_list_xor(XORListNode* a, XORListNode* b);

#endif // XOR_LINKED_LIST_H


