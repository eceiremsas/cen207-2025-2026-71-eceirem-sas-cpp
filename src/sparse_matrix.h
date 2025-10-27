#ifndef SPARSE_MATRIX_H
#define SPARSE_MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "recipe.h"

#define MAX_INGREDIENT_NAME 50

typedef struct MatrixEntry {
    int row;
    int col;
    int value;
    char ingredient[MAX_INGREDIENT_NAME];
    struct MatrixEntry* next;
} MatrixEntry;

typedef struct {
    MatrixEntry* head;
    int row_count;
    int col_count;
    int entry_count;
} SparseMatrix;

// Fonksiyon Bildirimleri
SparseMatrix* sparse_matrix_create(void);
void sparse_matrix_add_entry(SparseMatrix* matrix, int row, int col, int value, const char* ingredient);
int sparse_matrix_get_value(SparseMatrix* matrix, int row, int col);
int sparse_matrix_find_recipes_by_ingredient(SparseMatrix* matrix, const char* ingredient, int* recipe_ids, int max_results);
int sparse_matrix_find_ingredients_by_recipe(SparseMatrix* matrix, int recipe_id);
void sparse_matrix_display(SparseMatrix* matrix);
void sparse_matrix_destroy(SparseMatrix* matrix);

#endif
