/**
 * @file sparse_matrix.cpp
 * @brief Sparse Matrix implementation (C++ version)
 * @details Represents a linked-list-based sparse matrix where each entry maps
 *          a recipe (column) and an ingredient (row) for efficient ingredient search.
 */

#include "sparse_matrix.hpp"

// === SparseMatrix Constructor ===
SparseMatrix::SparseMatrix() : head(nullptr), rowCount(0), colCount(0), entryCount(0) {
}

// === SparseMatrix::addEntry ===
void SparseMatrix::addEntry(int row, int col, int value, const std::string& ingredient) {
    auto newEntry = std::make_shared<MatrixEntry>(row, col, value, ingredient);
    newEntry->next = head;
    head = newEntry;
    entryCount++;
}

// === SparseMatrix::getValue ===
int SparseMatrix::getValue(int row, int col) const {
    auto current = head;
    while (current) {
        if (current->row == row && current->col == col)
            return current->value;
        current = current->next;
    }
    return 0;
}

// === SparseMatrix::findRecipesByIngredient ===
std::vector<int> SparseMatrix::findRecipesByIngredient(const std::string& ingredient) const {
    std::vector<int> recipeIds;
    auto current = head;
    while (current) {
        if (current->ingredient == ingredient)
            recipeIds.push_back(current->row);  // row is recipe ID
        current = current->next;
    }
    return recipeIds;
}

// === SparseMatrix::findIngredientsByRecipe ===
std::vector<std::string> SparseMatrix::findIngredientsByRecipe(int recipeId) const {
    std::vector<std::string> ingredients;
    auto current = head;
    while (current) {
        if (current->row == recipeId)
            ingredients.push_back(current->ingredient);
        current = current->next;
    }
    return ingredients;
}

// === SparseMatrix::display ===
void SparseMatrix::display() const {
    std::cout << "\n--- Sparse Matrix Contents ---\n";
    auto current = head;
    while (current) {
        std::cout << "[row=" << current->row
                  << ", col=" << current->col
                  << ", val=" << current->value
                  << ", ingredient=" << current->ingredient << "]\n";
        current = current->next;
    }
}

// === SparseMatrix::clear ===
void SparseMatrix::clear() {
    head.reset();
    rowCount = colCount = entryCount = 0;
}
