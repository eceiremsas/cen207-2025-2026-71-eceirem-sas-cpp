/**
 * @file heap.cpp
 * @brief Min-Heap implementation used for sorting recipes by calorie values (C++ version).
 */

#include "heap.hpp"
#include <iostream>
#include <algorithm>

// === Heap Constructor ===
Heap::Heap(int maxCapacity) : capacity(maxCapacity) {
    recipes.reserve(maxCapacity);
}

// === Heap::heapifyUp ===
void Heap::heapifyUp(int index) {
    while (index > 0) {
        int p = parent(index);
        if (*recipes[index] < *recipes[p]) {
            swapNodes(index, p);
            index = p;
        } else {
            break;
        }
    }
}

// === Heap::heapifyDown ===
void Heap::heapifyDown(int index) {
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

        swapNodes(index, smallest);
        index = smallest;
    }
}

// === Heap::insert ===
bool Heap::insert(const std::shared_ptr<Recipe>& recipe) {
    if (!recipe) return false;
    if (isFull()) {
        std::cerr << "WARNING: Heap is full – cannot insert more recipes!\n";
        return false;
    }
    recipes.push_back(recipe);
    heapifyUp(static_cast<int>(recipes.size()) - 1);
    return true;
}

// === Heap::extractMin ===
std::shared_ptr<Recipe> Heap::extractMin() {
    if (isEmpty()) return nullptr;

    std::shared_ptr<Recipe> min = recipes.front();
    recipes[0] = recipes.back();
    recipes.pop_back();
    if (!isEmpty()) heapifyDown(0);
    return min;
}

// === Heap::peek ===
std::shared_ptr<Recipe> Heap::peek() const {
    if (isEmpty()) return nullptr;
    return recipes.front();
}

// === Heap::sortRecipes ===
void Heap::sortRecipes(std::vector<std::shared_ptr<Recipe>>& recipeList) {
    Heap heap(static_cast<int>(recipeList.size()));
    for (auto& r : recipeList) {
        heap.insert(r);
    }

    for (size_t i = 0; i < recipeList.size(); ++i) {
        recipeList[i] = heap.extractMin();
    }
}

// === Heap::display ===
void Heap::display() const {
    std::cout << "\n=== HEAP CONTENTS ===\n";
    std::cout << "Size: " << recipes.size() << "\n";
    for (size_t i = 0; i < recipes.size(); ++i) {
        std::cout << "[" << i << "] Recipe #" << recipes[i]->getId()
                  << ": " << recipes[i]->getName()
                  << " (" << recipes[i]->getCalories() << " kcal)\n";
    }
}
