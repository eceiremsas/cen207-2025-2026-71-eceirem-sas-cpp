/**
 * @file heap.h
 * @brief Header file for the Min-Heap data structure
 * @details Used to sort recipes based on their calorie values.
 *          The recipe with the lowest calorie count is always at the top (root) of the heap.
 */

#ifndef HEAP_H  // Include guard start
#define HEAP_H  // Define HEAP_H macro

#include "recipe.h"  // For the Recipe data structure

 /* ============================================================================
  * DATA STRUCTURES
  * ============================================================================ */

  /**
   * @struct Heap
   * @brief Min-Heap structure
   * @details Array-based implementation of a complete binary tree.
   *          The parent node always has a smaller calorie value than its child nodes.
   */
typedef struct {
    Recipe** recipes;  // Dynamic array of recipe pointers
    int size;          // Current number of elements in the heap
    int capacity;      // Maximum capacity of the heap
} Heap;

/* ============================================================================
 * FUNCTION DECLARATIONS
 * ============================================================================ */

 /**
  * @brief Creates a new empty heap
  * @param capacity Maximum capacity of the heap
  * @return Pointer to the created heap, or NULL on failure
  * @details Allocates memory for the recipe pointer array
  */
Heap* heap_create(int capacity);

/**
 * @brief Inserts a new recipe into the heap
 * @param heap Pointer to the heap structure
 * @param recipe Recipe to be inserted
 * @return 1 on success, 0 on failure
 * @details The recipe is added at the end and repositioned using heapify_up
 */
int heap_insert(Heap* heap, Recipe* recipe);

/**
 * @brief Removes and returns the recipe with the smallest calorie value
 * @param heap Pointer to the heap structure
 * @return Pointer to the recipe with the smallest calorie value, or NULL if heap is empty
 * @details The root element is removed, and heapify_down is called to maintain heap property
 */
Recipe* heap_extract_min(Heap* heap);

/**
 * @brief Returns the root recipe without removing it
 * @param heap Pointer to the heap structure
 * @return Pointer to the recipe with the smallest calorie value, or NULL if heap is empty
 * @details Unlike extract_min, this function does not remove the recipe from the heap
 */
Recipe* heap_peek(Heap* heap);

/**
 * @brief Restores the heap property by moving upward from a given index
 * @param heap Pointer to the heap structure
 * @param index Starting index
 * @details Called after insertion. Swaps elements if the child is smaller than its parent.
 */
void heapify_up(Heap* heap, int index);

/**
 * @brief Restores the heap property by moving downward from a given index
 * @param heap Pointer to the heap structure
 * @param index Starting index
 * @details Called after extraction. Swaps elements if the parent is larger than its children.
 */
void heapify_down(Heap* heap, int index);

/**
 * @brief Swaps two recipes in the heap
 * @param recipe1 Address of the first recipe pointer
 * @param recipe2 Address of the second recipe pointer
 * @details Used during heapify operations
 */
void heap_swap(Recipe** recipe1, Recipe** recipe2);

/**
 * @brief Sorts recipes based on their calorie values using heap sort
 * @param recipes Array of recipe pointers
 * @param count Number of recipes in the array
 * @details Inserts all recipes into the heap and extracts them in sorted order
 */
void heap_sort_recipes(Recipe** recipes, int count);

/**
 * @brief Checks if the heap is empty
 * @param heap Pointer to the heap structure
 * @return 1 if the heap is empty, 0 otherwise
 * @details The heap is empty if its size equals 0
 */
int heap_is_empty(Heap* heap);

/**
 * @brief Checks if the heap is full
 * @param heap Pointer to the heap structure
 * @return 1 if the heap is full, 0 otherwise
 * @details The heap is full if its size equals its capacity
 */
int heap_is_full(Heap* heap);

/**
 * @brief Frees all memory used by the heap and its elements
 * @param heap Pointer to the heap structure
 * @details Releases both the recipe array and the heap itself
 */
void heap_destroy(Heap* heap);

/**
 * @brief Computes the index of a parent node
 * @param index Index of the child node
 * @return Index of the parent node
 * @details Formula: (index - 1) / 2
 */
int heap_parent(int index);

/**
 * @brief Computes the index of the left child node
 * @param index Index of the parent node
 * @return Index of the left child node
 * @details Formula: (2 * index) + 1
 */
int heap_left_child(int index);

/**
 * @brief Computes the index of the right child node
 * @param index Index of the parent node
 * @return Index of the right child node
 * @details Formula: (2 * index) + 2
 */
int heap_right_child(int index);

// === Binary File Operations ===

// Saves the heap to a binary file
int heap_save_binary(const Heap* heap, const char* filename);

// Loads a heap from a binary file
Heap* heap_load_binary(const char* filename);

#endif // HEAP_H - Include guard end
