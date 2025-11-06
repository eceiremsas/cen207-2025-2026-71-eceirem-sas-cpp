/**
 * @file sparse_matrix.cpp
 * @brief Sparse Matrix implementation (C++ version)
 * @details Represents a linked-list-based sparse matrix where each entry maps
 *          a recipe (column) and an ingredient (row) for efficient ingredient search.
 */

#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <algorithm>

constexpr int MAX_INGREDIENT_NAME = 50;
constexpr int MAX_RESULTS = 100;

// ===============================
//   Matrix Entry Definition
// ===============================
struct MatrixEntry {
    int row;
    int col;
    int value;
    std::string ingredient;
    std::shared_ptr<MatrixEntry> next;

    MatrixEntry(int r, int c, int v, const std::string& ing)
        : row(r), col(c), value(v), ingredient(ing), next(nullptr) {}
};

// ===============================
//   Sparse Matrix Class
// ===============================
class SparseMatrix {
private:
    std::shared_ptr<MatrixEntry> head;
    int row_count;
    int col_count;
    int entry_count;

public:
    // === Constructor ===
    SparseMatrix() : head(nullptr), row_count(0), col_count(0), entry_count(0) {}

    // === Add Entry ===
    void addEntry(int row, int col, int value, const std::string& ingredient) {
        auto newEntry = std::make_shared<MatrixEntry>(row, col, value, ingredient);
        newEntry->next = head;
        head = newEntry;
        entry_count++;
    }

    // === Get Value at (row, col) ===
    int getValue(int row, int col) const {
        auto current = head;
        while (current) {
            if (current->row == row && current->col == col)
                return current->value;
            current = current->next;
        }
        return 0;
    }

    // === Find Recipes by Ingredient ===
    std::vector<int> findRecipesByIngredient(const std::string& ingredient) const {
        std::vector<int> recipeIds;
        auto current = head;
        while (current) {
            if (current->ingredient == ingredient)
                recipeIds.push_back(current->col);
            current = current->next;
        }
        return recipeIds;
    }

    // === Count Ingredients by Recipe ID ===
    int countIngredientsByRecipe(int recipe_id) const {
        int count = 0;
        auto current = head;
        while (current) {
            if (current->col == recipe_id)
                count++;
            current = current->next;
        }
        return count;
    }

    // === Display All Entries ===
    void display() const {
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

    // === Clear (optional manual cleanup) ===
    void clear() {
        head.reset();
        row_count = col_count = entry_count = 0;
    }

    // === Accessors ===
    int getEntryCount() const { return entry_count; }
    bool isEmpty() const { return entry_count == 0; }
};
