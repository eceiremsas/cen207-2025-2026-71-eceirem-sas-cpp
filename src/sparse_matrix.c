#include "sparse_matrix.h"

SparseMatrix* sparse_matrix_create(void) {
    SparseMatrix* matrix = (SparseMatrix*)malloc(sizeof(SparseMatrix));
    if (!matrix) return NULL;
    matrix->head = NULL;
    matrix->row_count = 0;
    matrix->col_count = 0;
    matrix->entry_count = 0;
    return matrix;
}

void sparse_matrix_add_entry(SparseMatrix* matrix, int row, int col, int value, const char* ingredient) {
    MatrixEntry* new_entry = (MatrixEntry*)malloc(sizeof(MatrixEntry));
    new_entry->row = row;
    new_entry->col = col;
    new_entry->value = value;
    strncpy(new_entry->ingredient, ingredient, MAX_INGREDIENT_NAME);
    new_entry->next = matrix->head;
    matrix->head = new_entry;
    matrix->entry_count++;
}

int sparse_matrix_get_value(SparseMatrix* matrix, int row, int col) {
    MatrixEntry* current = matrix->head;
    while (current) {
        if (current->row == row && current->col == col)
            return current->value;
        current = current->next;
    }
    return 0;
}

int sparse_matrix_find_recipes_by_ingredient(SparseMatrix* matrix, const char* ingredient, int* recipe_ids, int max_results) {
    int count = 0;
    MatrixEntry* current = matrix->head;
    while (current && count < max_results) {
        if (strcmp(current->ingredient, ingredient) == 0)
            recipe_ids[count++] = current->col;
        current = current->next;
    }
    return count;
}

int sparse_matrix_find_ingredients_by_recipe(SparseMatrix* matrix, int recipe_id) {
    int count = 0;
    MatrixEntry* current = matrix->head;
    while (current) {
        if (current->col == recipe_id)
            count++;
        current = current->next;
    }
    return count;
}

void sparse_matrix_display(SparseMatrix* matrix) {
    MatrixEntry* current = matrix->head;
    printf("\n--- Sparse Matrix İçeriği ---\n");
    while (current) {
        printf("[r=%d, c=%d, val=%d, %s]\n",
            current->row, current->col, current->value, current->ingredient);
        current = current->next;
    }
}

void sparse_matrix_destroy(SparseMatrix* matrix) {
    MatrixEntry* current = matrix->head;
    while (current) {
        MatrixEntry* temp = current;
        current = current->next;
        free(temp);
    }
    free(matrix);
}
