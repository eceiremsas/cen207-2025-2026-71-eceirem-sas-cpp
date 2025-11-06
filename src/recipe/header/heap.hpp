/**
 * @file heap.hpp
 * @brief Min-Heap class for sorting recipes by calorie values (C++ version)
 * @details The recipe with the lowest calorie count is always at the top (root) of the heap.
 */

#ifndef HEAP_HPP
#define HEAP_HPP

#include <iostream>
#include <vector>
#include <memory>
#include <stdexcept>
#include <algorithm>
#include "recipe.hpp"

 /**
  * @class Heap
  * @brief Min-Heap implementation using a dynamic array (std::vector).
  * @details Maintains the heap property based on Recipe calorie values.
  */
class Heap {
private:
    std::vector<std::shared_ptr<Recipe>> recipes;  ///< Heap storage
    int capacity;                                 ///< Maximum allowed elements

    // === Index utility functions ===
    static int parent(int index) { return (index - 1) / 2; }
    static int leftChild(int index) { return (2 * index) + 1; }
    static int rightChild(int index) { return (2 * index) + 2; }

    // === Swap helper ===
    void swapNodes(int i, int j) {
        std::swap(recipes[i], recipes[j]);
    }

    // === Heapify helpers ===
    void heapifyUp(int index);
    void heapifyDown(int index);

public:
    // === Constructor ===
    explicit Heap(int maxCapacity = 100);

    // === Core Operations ===
    bool insert(const std::shared_ptr<Recipe>& recipe);
    std::shared_ptr<Recipe> extractMin();
    std::shared_ptr<Recipe> peek() const;

    // === Sorting Utility ===
    static void sortRecipes(std::vector<std::shared_ptr<Recipe>>& recipeList);

    // === State Checks ===
    bool isEmpty() const { return recipes.empty(); }
    bool isFull() const { return static_cast<int>(recipes.size()) >= capacity; }
    int size() const { return static_cast<int>(recipes.size()); }

    // === Display for debugging ===
    void display() const;

    // === Destructor ===
    ~Heap() = default;
};

#endif // HEAP_HPP
