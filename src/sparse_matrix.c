/**
 * @file sparse_matrix.c
 * @brief Sparse Matrix implementation for ingredient-recipe relationships
 * @details Linked list-based sparse matrix for efficient ingredient search
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sparse_matrix.h"

/**
 * @brief Creates and initializes an empty sparse matrix
 * @return Pointer to the created sparse matrix, or NULL on failure
 */
SparseMatrix* sparse_matrix_create(void) {
    SparseMatrix* matrix = (SparseMatrix*)malloc(sizeof(SparseMatrix));
    if (!matrix) {
        return NULL;
    }

    matrix->head = NULL;
    matrix->row_count = 0;
    matrix->col_count = 0;
    matrix->entry_count = 0;

    return matrix;
}

/**
 * @brief Adds a new non-zero entry to the sparse matrix
 * @param matrix Pointer to the sparse matrix
 * @param row Row index (typically recipe ID)
 * @param col Column index (typically ingredient ID)
 * @param value Non-zero value
 * @param ingredient Ingredient name
 */
void sparse_matrix_add_entry(SparseMatrix* matrix, int row, int col, int value, const char* ingredient) {
    if (!matrix || !ingredient) {
        return;
    }

    MatrixEntry* new_entry = (MatrixEntry*)malloc(sizeof(MatrixEntry));
    if (!new_entry) {
        return;
    }

    new_entry->row = row;
    new_entry->col = col;
    new_entry->value = value;
    strncpy(new_entry->ingredient, ingredient, MAX_INGREDIENT_NAME - 1);
    new_entry->ingredient[MAX_INGREDIENT_NAME - 1] = '\0';
    new_entry->next = matrix->head;
    matrix->head = new_entry;
    matrix->entry_count++;

    if (row >= matrix->row_count) {
        matrix->row_count = row + 1;
    }
    if (col >= matrix->col_count) {
        matrix->col_count = col + 1;
    }
}

/**
 * @brief Retrieves the value of a specific matrix cell (row, col)
 * @param matrix Pointer to the sparse matrix
 * @param row Row index
 * @param col Column index
 * @return Value at (row, col), or 0 if not found
 */
int sparse_matrix_get_value(SparseMatrix* matrix, int row, int col) {
    if (!matrix) {
        return 0;
    }

    MatrixEntry* current = matrix->head;
    while (current) {
        if (current->row == row && current->col == col) {
            return current->value;
        }
        current = current->next;
    }

    return 0;
}

/**
 * @brief Finds all recipe IDs that include a specific ingredient
 * @param matrix Pointer to the sparse matrix
 * @param ingredient Ingredient name to search for
 * @param recipe_ids Array to store found recipe IDs
 * @param max_results Maximum number of results
 * @return Number of recipes found
 */
int sparse_matrix_find_recipes_by_ingredient(SparseMatrix* matrix, const char* ingredient, int* recipe_ids, int max_results) {
    if (!matrix || !ingredient || !recipe_ids || max_results <= 0) {
        return 0;
    }

    int count = 0;
    MatrixEntry* current = matrix->head;

    while (current && count < max_results) {
        if (strcmp(current->ingredient, ingredient) == 0) {
            recipe_ids[count] = current->row;  // row represents recipe ID
            count++;
        }
        current = current->next;
    }

    return count;
}

/**
 * @brief Finds all ingredients associated with a given recipe ID
 * @param matrix Pointer to the sparse matrix
 * @param recipe_id Recipe ID to search for
 * @return Number of ingredients found
 */
int sparse_matrix_find_ingredients_by_recipe(SparseMatrix* matrix, int recipe_id) {
    if (!matrix) {
        return 0;
    }

    int count = 0;
    MatrixEntry* current = matrix->head;

    while (current) {
        if (current->col == recipe_id) {
            count++;
        }
        current = current->next;
    }

    return count;
}

/**
 * @brief Displays all non-zero entries in the sparse matrix
 * @param matrix Pointer to the sparse matrix
 */
void sparse_matrix_display(SparseMatrix* matrix) {
    if (!matrix) {
        printf("Sparse matrix pointer is NULL.\n");
        return;
    }

    printf("\n--- Sparse Matrix Contents ---\n");
    MatrixEntry* current = matrix->head;
    while (current) {
        printf("[row=%d, col=%d, val=%d, ingredient=%s]\n",
               current->row, current->col, current->value, current->ingredient);
        current = current->next;
    }
}

/**
 * @brief Frees all memory allocated for the sparse matrix
 * @param matrix Pointer to the sparse matrix
 */
void sparse_matrix_destroy(SparseMatrix* matrix) {
    if (!matrix) {
        return;
    }

    MatrixEntry* current = matrix->head;
    while (current) {
        MatrixEntry* next = current->next;
        free(current);
        current = next;
    }

    free(matrix);
}

/**
 * @brief Saves the sparse matrix to a binary file
 * @param matrix Pointer to the sparse matrix
 * @param filename Name of the binary file
 * @return 1 on success, 0 on failure
 */
int sparse_matrix_save_binary(const SparseMatrix* matrix, const char* filename) {
    if (!matrix || !filename) {
        return 0;
    }

    FILE* file = fopen(filename, "wb");
    if (!file) {
        return 0;
    }

    if (fwrite(&matrix->row_count, sizeof(int), 1, file) != 1) {
        fclose(file);
        return 0;
    }
    if (fwrite(&matrix->col_count, sizeof(int), 1, file) != 1) {
        fclose(file);
        return 0;
    }
    if (fwrite(&matrix->entry_count, sizeof(int), 1, file) != 1) {
        fclose(file);
        return 0;
    }

    MatrixEntry* current = matrix->head;
    while (current) {
        if (fwrite(&current->row, sizeof(int), 1, file) != 1) {
            fclose(file);
            return 0;
        }
        if (fwrite(&current->col, sizeof(int), 1, file) != 1) {
            fclose(file);
            return 0;
        }
        if (fwrite(&current->value, sizeof(int), 1, file) != 1) {
            fclose(file);
            return 0;
        }
        if (fwrite(current->ingredient, sizeof(char), MAX_INGREDIENT_NAME, file) != MAX_INGREDIENT_NAME) {
            fclose(file);
            return 0;
        }
        current = current->next;
    }

    fclose(file);
    return 1;
}

/**
 * @brief Loads a sparse matrix from a binary file
 * @param filename Name of the binary file
 * @return Pointer to the loaded sparse matrix, or NULL on failure
 */
SparseMatrix* sparse_matrix_load_binary(const char* filename) {
    if (!filename) {
        return NULL;
    }

    FILE* file = fopen(filename, "rb");
    if (!file) {
        return NULL;
    }

    SparseMatrix* matrix = sparse_matrix_create();
    if (!matrix) {
        fclose(file);
        return NULL;
    }

    int row_count, col_count, entry_count;
    if (fread(&row_count, sizeof(int), 1, file) != 1) {
        fclose(file);
        sparse_matrix_destroy(matrix);
        return NULL;
    }
    if (fread(&col_count, sizeof(int), 1, file) != 1) {
        fclose(file);
        sparse_matrix_destroy(matrix);
        return NULL;
    }
    if (fread(&entry_count, sizeof(int), 1, file) != 1) {
        fclose(file);
        sparse_matrix_destroy(matrix);
        return NULL;
    }

    matrix->row_count = row_count;
    matrix->col_count = col_count;

    for (int i = 0; i < entry_count; i++) {
        int row, col, value;
        char ingredient[MAX_INGREDIENT_NAME];

        if (fread(&row, sizeof(int), 1, file) != 1) {
            break;
        }
        if (fread(&col, sizeof(int), 1, file) != 1) {
            break;
        }
        if (fread(&value, sizeof(int), 1, file) != 1) {
            break;
        }
        if (fread(ingredient, sizeof(char), MAX_INGREDIENT_NAME, file) != MAX_INGREDIENT_NAME) {
            break;
        }

        sparse_matrix_add_entry(matrix, row, col, value, ingredient);
    }

    fclose(file);
    return matrix;
}

