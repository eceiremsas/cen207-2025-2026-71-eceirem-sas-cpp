/**
 * @file heap.cpp
 * @brief Min-Heap implementation used for sorting recipes by calorie values (C++ version).
 */

#include <iostream>
#include <vector>
#include <memory>
#include <stdexcept>
#include "recipe.hpp"  // Recipe class definition

// === Heap Class Definition ===
class Heap {
private:
    std::vector<std::shared_ptr<Recipe>> recipes;  // Dynamic container for heap
    int capacity;

    // Utility index functions
    static int parent(int index) { return (index - 1) / 2; }
    static int leftChild(int index) { return (2 * index) + 1; }
    static int rightChild(int index) { return (2 * index) + 2; }

    // Swaps two elements
    static void swap(std::shared_ptr<Recipe>& a, std::shared_ptr<Recipe>& b) {
        std::shared_ptr<Recipe> temp = a;
        a = b;
        b = temp;
    }

    // Moves an element upward to maintain heap property
    void heapifyUp(int index) {
        while (index > 0) {
            int p = parent(index);
            if (*recipes[index] < *recipes[p]) {
                swap(recipes[index], recipes[p]);
                index = p;
            } else {
                break;
            }
        }
    }

    // Moves an element downward to maintain heap property
    void heapifyDown(int index) {
        int size = static_cast<int>(recipes.size());
        while (true) {
            int left = leftChild(index);
            int right = rightChild(index);
            int smallest = index;

            if (left < size && *recipes[left] < *recipes[smallest])
                smallest = left;
            if (right < size && *recipes[right] < *recipes[smallest])
                smallest = right;

            if (smallest == index) break;

            swap(recipes[index], recipes[smallest]);
            index = smallest;
        }
    }

public:
    // === Constructors ===
    explicit Heap(int cap) : capacity(cap) {
        recipes.reserve(cap);
    }

    // === Utility Functions ===
    bool isEmpty() const { return recipes.empty(); }
    bool isFull() const { return static_cast<int>(recipes.size()) >= capacity; }
    int size() const { return static_cast<int>(recipes.size()); }

    // === Core Heap Operations ===
    bool insert(std::shared_ptr<Recipe> recipe) {
        if (!recipe) return false;
        if (isFull()) {
            std::cerr << "WARNING: Heap is full – cannot insert more recipes!\n";
            return false;
        }
        recipes.push_back(recipe);
        heapifyUp(static_cast<int>(recipes.size()) - 1);
        return true;
    }

    std::shared_ptr<Recipe> peek() const {
        if (isEmpty()) return nullptr;
        return recipes.front();
    }

    std::shared_ptr<Recipe> extractMin() {
        if (isEmpty()) return nullptr;

        std::shared_ptr<Recipe> min = recipes.front();
        recipes[0] = recipes.back();
        recipes.pop_back();
        if (!isEmpty()) heapifyDown(0);
        return min;
    }

    // === Static Helper: Heap Sort ===
    static void heapSort(std::vector<std::shared_ptr<Recipe>>& recipeList) {
        Heap heap(static_cast<int>(recipeList.size()));
        for (auto& r : recipeList) {
            heap.insert(r);
        }

        for (size_t i = 0; i < recipeList.size(); ++i) {
            recipeList[i] = heap.extractMin();
        }
    }

    // Destructor (smart pointers handle memory automatically)
    ~Heap() = default;
};
