/**
 * @file heap.c
 * @brief Min-Heap implementation for sorting recipes by calorie values
 * @details Array-based implementation of a complete binary tree
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heap.h"

/**
 * @brief Computes the index of a parent node
 * @param index Index of the child node
 * @return Index of the parent node
 */
int heap_parent(int index) {
    return (index - 1) / 2;
}

/**
 * @brief Computes the index of the left child node
 * @param index Index of the parent node
 * @return Index of the left child node
 */
int heap_left_child(int index) {
    return (2 * index) + 1;
}

/**
 * @brief Computes the index of the right child node
 * @param index Index of the parent node
 * @return Index of the right child node
 */
int heap_right_child(int index) {
    return (2 * index) + 2;
}

/**
 * @brief Swaps two recipes in the heap
 * @param recipe1 Address of the first recipe pointer
 * @param recipe2 Address of the second recipe pointer
 */
void heap_swap(Recipe** recipe1, Recipe** recipe2) {
    Recipe* temp = *recipe1;
    *recipe1 = *recipe2;
    *recipe2 = temp;
}

/**
 * @brief Restores the heap property by moving upward from a given index
 * @param heap Pointer to the heap
 * @param index Starting index
 */
void heapify_up(Heap* heap, int index) {
    while (index > 0) {
        int parent_idx = heap_parent(index);
        if (recipe_compare_by_calories(heap->recipes[index], heap->recipes[parent_idx]) < 0) {
            heap_swap(&heap->recipes[index], &heap->recipes[parent_idx]);
            index = parent_idx;
        } else {
            break;
        }
    }
}

/**
 * @brief Restores the heap property by moving downward from a given index
 * @param heap Pointer to the heap
 * @param index Starting index
 */
void heapify_down(Heap* heap, int index) {
    while (1) {
        int left = heap_left_child(index);
        int right = heap_right_child(index);
        int smallest = index;

        if (left < heap->size && 
            recipe_compare_by_calories(heap->recipes[left], heap->recipes[smallest]) < 0) {
            smallest = left;
        }

        if (right < heap->size && 
            recipe_compare_by_calories(heap->recipes[right], heap->recipes[smallest]) < 0) {
            smallest = right;
        }

        if (smallest == index) {
            break;
        }

        heap_swap(&heap->recipes[index], &heap->recipes[smallest]);
        index = smallest;
    }
}

/**
 * @brief Creates a new empty heap
 * @param capacity Maximum capacity of the heap
 * @return Pointer to the created heap, or NULL on failure
 */
Heap* heap_create(int capacity) {
    if (capacity <= 0) {
        return NULL;
    }

    Heap* heap = (Heap*)malloc(sizeof(Heap));
    if (!heap) {
        return NULL;
    }

    heap->recipes = (Recipe**)malloc(sizeof(Recipe*) * capacity);
    if (!heap->recipes) {
        free(heap);
        return NULL;
    }

    heap->size = 0;
    heap->capacity = capacity;

    return heap;
}

/**
 * @brief Inserts a new recipe into the heap
 * @param heap Pointer to the heap
 * @param recipe Recipe to be inserted
 * @return 1 on success, 0 on failure
 */
int heap_insert(Heap* heap, Recipe* recipe) {
    if (!heap || !recipe) {
        return 0;
    }

    if (heap_is_full(heap)) {
        return 0;
    }

    heap->recipes[heap->size] = recipe;
    heapify_up(heap, heap->size);
    heap->size++;

    return 1;
}

/**
 * @brief Removes and returns the recipe with the smallest calorie value
 * @param heap Pointer to the heap
 * @return Pointer to the recipe with the smallest calorie value, or NULL if heap is empty
 */
Recipe* heap_extract_min(Heap* heap) {
    if (!heap || heap_is_empty(heap)) {
        return NULL;
    }

    Recipe* min = heap->recipes[0];
    heap->recipes[0] = heap->recipes[heap->size - 1];
    heap->size--;

    if (heap->size > 0) {
        heapify_down(heap, 0);
    }

    return min;
}

/**
 * @brief Returns the root recipe without removing it
 * @param heap Pointer to the heap
 * @return Pointer to the recipe with the smallest calorie value, or NULL if heap is empty
 */
Recipe* heap_peek(Heap* heap) {
    if (!heap || heap_is_empty(heap)) {
        return NULL;
    }

    return heap->recipes[0];
}

/**
 * @brief Sorts recipes based on their calorie values using heap sort
 * @param recipes Array of recipe pointers
 * @param count Number of recipes in the array
 */
void heap_sort_recipes(Recipe** recipes, int count) {
    if (!recipes || count <= 0) {
        return;
    }

    Heap* heap = heap_create(count);
    if (!heap) {
        return;
    }

    // Insert all recipes into heap
    for (int i = 0; i < count; i++) {
        heap_insert(heap, recipes[i]);
    }

    // Extract all recipes in sorted order
    for (int i = 0; i < count; i++) {
        recipes[i] = heap_extract_min(heap);
    }

    heap_destroy(heap);
}

/**
 * @brief Checks if the heap is empty
 * @param heap Pointer to the heap
 * @return 1 if empty, 0 otherwise
 */
int heap_is_empty(Heap* heap) {
    return (heap && heap->size == 0) ? 1 : 0;
}

/**
 * @brief Checks if the heap is full
 * @param heap Pointer to the heap
 * @return 1 if full, 0 otherwise
 */
int heap_is_full(Heap* heap) {
    return (heap && heap->size >= heap->capacity) ? 1 : 0;
}

/**
 * @brief Frees all memory used by the heap and its elements
 * @param heap Pointer to the heap
 */
void heap_destroy(Heap* heap) {
    if (!heap) {
        return;
    }

    if (heap->recipes) {
        free(heap->recipes);
    }

    free(heap);
}

/**
 * @brief Saves the heap to a binary file
 * @param heap Pointer to the heap
 * @param filename Name of the binary file
 * @return 1 on success, 0 on failure
 */
int heap_save_binary(const Heap* heap, const char* filename) {
    if (!heap || !filename) {
        return 0;
    }

    FILE* file = fopen(filename, "wb");
    if (!file) {
        return 0;
    }

    if (fwrite(&heap->size, sizeof(int), 1, file) != 1) {
        fclose(file);
        return 0;
    }
    if (fwrite(&heap->capacity, sizeof(int), 1, file) != 1) {
        fclose(file);
        return 0;
    }

    for (int i = 0; i < heap->size; i++) {
        if (heap->recipes[i]) {
            if (fwrite(heap->recipes[i], sizeof(Recipe), 1, file) != 1) {
                fclose(file);
                return 0;
            }
        }
    }

    fclose(file);
    return 1;
}

/**
 * @brief Loads a heap from a binary file
 * @param filename Name of the binary file
 * @return Pointer to the loaded heap, or NULL on failure
 */
Heap* heap_load_binary(const char* filename) {
    if (!filename) {
        return NULL;
    }

    FILE* file = fopen(filename, "rb");
    if (!file) {
        return NULL;
    }

    int size, capacity;
    if (fread(&size, sizeof(int), 1, file) != 1) {
        fclose(file);
        return NULL;
    }
    if (fread(&capacity, sizeof(int), 1, file) != 1) {
        fclose(file);
        return NULL;
    }

    Heap* heap = heap_create(capacity);
    if (!heap) {
        fclose(file);
        return NULL;
    }

    for (int i = 0; i < size; i++) {
        Recipe* recipe = (Recipe*)malloc(sizeof(Recipe));
        if (!recipe) {
            break;
        }
        if (fread(recipe, sizeof(Recipe), 1, file) != 1) {
            free(recipe);
            break;
        }
        heap_insert(heap, recipe);
    }

    fclose(file);
    return heap;
}

