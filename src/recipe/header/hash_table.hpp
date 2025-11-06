/**
 * @file hash_table.hpp
 * @brief Hash Table implementation (C++ version)
 * @details Provides O(1) average-time access to recipes by their ID using
 *          separate chaining with linked lists for collision handling.
 */

#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP

#include <iostream>
#include <memory>
#include <vector>
#include <list>
#include <string>
#include <optional>
#include "recipe.hpp"

// ============================================================
//  Class: HashTable
// ============================================================
class HashTable {
private:
    struct Node {
        std::shared_ptr<Recipe> recipe;
        Node(std::shared_ptr<Recipe> r) : recipe(std::move(r)) {}
    };

    std::vector<std::list<Node>> table;  ///< Buckets for separate chaining
    int count;                           ///< Number of stored recipes

    // Simple hash function (ID mod table size)
    size_t hashFunction(int id) const {
        return static_cast<size_t>(id) % table.size();
    }

public:
    // === Constructor & Destructor ===
    explicit HashTable(int size = 101);
    ~HashTable() = default;

    // === Core Operations ===
    bool insert(std::shared_ptr<Recipe> recipe);
    std::shared_ptr<Recipe> search(int id) const;
    bool remove(int id);

    // === Display & Utility ===
    void display() const;
    int size() const { return count; }
    bool isEmpty() const { return count == 0; }

    // === Clear all entries ===
    void clear();
};

#endif // HASH_TABLE_HPP
