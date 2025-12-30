/**
 * @file hash_table.cpp
 * @brief Hash Table implementation (C++ version).
 * @details Provides O(1) average-time access to recipes by their ID.
 *          Uses separate chaining with linked lists for collisions.
 */

#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <iomanip>
#include "hash_table.hpp"
#include "recipe.hpp"

// === HashTable Constructor ===
HashTable::HashTable(int size) : table(size), count(0) {
}

// === HashTable::insert ===
bool HashTable::insert(std::shared_ptr<Recipe> recipe) {
    if (!recipe) {
        std::cerr << "ERROR: Invalid recipe pointer!\n";
        return false;
    }

    size_t index = hashFunction(recipe->getId());
    table[index].emplace_back(recipe);
    count++;
    return true;
}

// === HashTable::search ===
std::shared_ptr<Recipe> HashTable::search(int id) const {
    size_t index = hashFunction(id);
    for (const auto& node : table[index]) {
        if (node.recipe && node.recipe->getId() == id) {
            return node.recipe;
        }
    }
    return nullptr;
}

// === HashTable::remove ===
bool HashTable::remove(int id) {
    size_t index = hashFunction(id);
    auto& bucket = table[index];
    for (auto it = bucket.begin(); it != bucket.end(); ++it) {
        if (it->recipe && it->recipe->getId() == id) {
            bucket.erase(it);
            count--;
            return true;
        }
    }
    std::cerr << "WARNING: Recipe to delete not found (ID: " << id << ")\n";
    return false;
}

// === HashTable::display ===
void HashTable::display() const {
    std::cout << "\n=== HASH TABLE CONTENT ===\n";
    std::cout << "Total Recipes: " << count << "\n\n";

    for (size_t i = 0; i < table.size(); i++) {
        if (!table[i].empty()) {
            std::cout << "Slot " << i << ":\n";
            for (const auto& node : table[i]) {
                std::cout << "  -> Recipe #" << node.recipe->getId()
                    << ": " << node.recipe->getName() << "\n";
            }
            std::cout << "  (Total " << table[i].size() << " recipes)\n\n";
        }
    }
}

// === HashTable::clear ===
void HashTable::clear() {
    for (auto& bucket : table) {
        bucket.clear();
    }
    count = 0;
}
