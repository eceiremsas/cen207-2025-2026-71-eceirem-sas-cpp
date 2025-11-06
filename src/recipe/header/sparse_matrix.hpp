/**
 * @file sparse_matrix.hpp
 * @brief Sparse Matrix implementation for ingredient-recipe relationships (C++ version)
 * @details Stores only non-zero entries (ingredient associations) in a linked-list–style structure.
 */

#ifndef SPARSE_MATRIX_HPP
#define SPARSE_MATRIX_HPP

#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <algorithm>
#include <iomanip>
#include "recipe.hpp"

constexpr int MAX_INGREDIENT_NAME = 50;

/**
 * @class MatrixEntry
 * @brief Represents a single non-zero entry in the sparse matrix.
 * @details Each entry includes a row (recipe ID), column (ingredient ID or index),
 *          a numeric value (association strength), an ingredient name, and a pointer
 *          to the next entry.
 */
class MatrixEntry {
public:
    int row;                                   ///< Row index (recipe ID)
    int col;                                   ///< Column index (ingredient index)
    int value;                                 ///< Non-zero value (usually 1)
    std::string ingredient;                    ///< Ingredient name
    std::shared_ptr<MatrixEntry> next;         ///< Pointer to next entry (singly linked)

    MatrixEntry(int r, int c, int val, std::string ingr)
        : row(r), col(c), value(val), ingredient(std::move(ingr)), next(nullptr) {
    }
};

/**
 * @class SparseMatrix
 * @brief Represents a sparse matrix linking recipes and ingredients.
 * @details Each non-zero cell is represented as a MatrixEntry node.
 */
class SparseMatrix {
private:
    std::shared_ptr<MatrixEntry> head;   ///< Head of the linked list
    int rowCount;                        ///< Number of rows (recipes)
    int colCount;                        ///< Number of columns (ingredients)
    int entryCount;                      ///< Number of non-zero entries

public:
    // === Constructors & Destructor ===
    SparseMatrix();
    ~SparseMatrix() = default;

    // === Core Operations ===
    void addEntry(int row, int col, int value, const std::string& ingredient);
    int getValue(int row, int col) const;

    // === Search Operations ===
    std::vector<int> findRecipesByIngredient(const std::string& ingredient) const;
    std::vector<std::string> findIngredientsByRecipe(int recipeId) const;

    // === Display & Info ===
    void display() const;
    int getEntryCount() const { return entryCount; }
    int getRowCount() const { return rowCount; }
    int getColCount() const { return colCount; }

    // === Utility ===
    void clear();
};

#endif // SPARSE_MATRIX_HPP
