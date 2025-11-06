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
#include "recipe.h"  // Must define Recipe class or struct

 // --- HashNode: Linked list node for each hash slot ---
struct HashNode {
    std::shared_ptr<Recipe> recipe;
    std::shared_ptr<HashNode> next;

    explicit HashNode(std::shared_ptr<Recipe> r)
        : recipe(std::move(r)), next(nullptr) {
    }
};

// --- HashTable class ---
class HashTable {
private:
    std::vector<std::shared_ptr<HashNode>> table;
    int size;
    int count;

    // Hash function using modulo operation
    int hashFunction(int id) const {
        return id % size;
    }

public:
    explicit HashTable(int s)
        : table(s, nullptr), size(s), count(0) {
    }

    // Inserts a recipe into the hash table
    bool insert(std::shared_ptr<Recipe> recipe) {
        if (!recipe) {
            std::cerr << "ERROR: Invalid recipe pointer!\n";
            return false;
        }

        int index = hashFunction(recipe->id);
        auto newNode = std::make_shared<HashNode>(recipe);
        newNode->next = table[index];
        table[index] = newNode;
        count++;
        return true;
    }

    // Searches for a recipe by ID
    std::shared_ptr<Recipe> search(int id) const {
        int index = hashFunction(id);
        auto current = table[index];

        while (current) {
            if (current->recipe && current->recipe->id == id) {
                return current->recipe;
            }
            current = current->next;
        }
        return nullptr;
    }

    // Deletes a recipe by ID
    bool remove(int id) {
        int index = hashFunction(id);
        auto current = table[index];
        std::shared_ptr<HashNode> prev = nullptr;

        while (current) {
            if (current->recipe && current->recipe->id == id) {
                if (prev) {
                    prev->next = current->next;
                }
                else {
                    table[index] = current->next;
                }
                count--;
                return true;
            }
            prev = current;
            current = current->next;
        }

        std::cerr << "WARNING: Recipe to delete not found (ID: " << id << ")\n";
        return false;
    }

    // Displays the contents of the hash table
    void display() const {
        std::cout << "\n=== HASH TABLE CONTENT ===\n";
        std::cout << "Total Recipes: " << count << "\n\n";

        for (int i = 0; i < size; i++) {
            if (table[i]) {
                std::cout << "Slot " << i << ":\n";
                int nodeCount = 0;

                auto current = table[i];
                while (current) {
                    nodeCount++;
                    std::cout << "  -> Recipe #" << current->recipe->id
                        << ": " << current->recipe->name << "\n";
                    current = current->next;
                }
                std::cout << "  (Total " << nodeCount << " recipes)\n\n";
            }
        }
    }

    // Destroys all recipes and nodes (handled automatically by smart pointers)
    void destroy() {
        for (auto& slot : table) {
            while (slot) {
                slot = slot->next;  // Shared pointers free automatically
            }
        }
        table.clear();
        count = 0;
        std::cout << "HashTable destroyed successfully.\n";
    }

    // Returns total count
    int getCount() const { return count; }
};
