#ifndef SPARSE_MATRIX_H
#define SPARSE_MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "recipe.h"

#define MAX_INGREDIENT_NAME 50

// === Structure Definitions ===

/**
 * @struct MatrixEntry
 * @brief Represents a single non-zero entry in a sparse matrix.
 * @details Each entry contains the position (row, column), a numeric value,
 *          the ingredient name, and a pointer to the next entry.
 */
typedef struct MatrixEntry {
    int row;                                // Row index (typically represents recipe ID)
    int col;                                // Column index (typically represents ingredient ID)
    int value;                              // Non-zero value (e.g., occurrence or relation weight)
    char ingredient[MAX_INGREDIENT_NAME];   // Ingredient name
    struct MatrixEntry* next;               // Pointer to the next matrix entry
} MatrixEntry;

/**
 * @struct SparseMatrix
 * @brief Represents a sparse matrix storing ingredient-recipe relationships.
 * @details Implemented as a linked list of MatrixEntry nodes.
 */
typedef struct {
    MatrixEntry* head;      // Pointer to the first matrix entry
    int row_count;          // Number of rows (recipes)
    int col_count;          // Number of columns (ingredients)
    int entry_count;        // Total number of non-zero entries
} SparseMatrix;

// === Function Declarations ===

// Creates and initializes an empty sparse matrix
SparseMatrix* sparse_matrix_create(void);

// Adds a new non-zero entry to the sparse matrix
void sparse_matrix_add_entry(SparseMatrix* matrix, int row, int col, int value, const char* ingredient);

// Retrieves the value of a specific matrix cell (row, col)
int sparse_matrix_get_value(SparseMatrix* matrix, int row, int col);

// Finds all recipe IDs that include a specific ingredient
int sparse_matrix_find_recipes_by_ingredient(SparseMatrix* matrix, const char* ingredient, int* recipe_ids, int max_results);

// Finds all ingredients associated with a given recipe ID
int sparse_matrix_find_ingredients_by_recipe(SparseMatrix* matrix, int recipe_id);

// Displays all non-zero entries in the sparse matrix
void sparse_matrix_display(SparseMatrix* matrix);

// Frees all memory allocated for the sparse matrix
void sparse_matrix_destroy(SparseMatrix* matrix);

// === Binary File Operations ===

// Saves the sparse matrix to a binary file
int sparse_matrix_save_binary(const SparseMatrix* matrix, const char* filename);

// Loads a sparse matrix from a binary file
SparseMatrix* sparse_matrix_load_binary(const char* filename);

#endif // SPARSE_MATRIX_H
