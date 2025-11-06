/**
 * @file linked_list.hpp
 * @brief Singly Linked List for managing recipes (C++ version)
 * @details Provides insertion, deletion, traversal, and search operations
 *          using modern C++ memory management (std::shared_ptr).
 */

#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include <iostream>
#include <memory>
#include <string>
#include "recipe.hpp"

 /**
  * @class LinkedList
  * @brief Singly linked list implementation for Recipe objects.
  */
class LinkedList {
private:
    // === Node Structure ===
    struct Node {
        std::shared_ptr<Recipe> recipe;   ///< Stored recipe
        std::shared_ptr<Node> next;       ///< Pointer to next node

        explicit Node(std::shared_ptr<Recipe> r)
            : recipe(std::move(r)), next(nullptr) {
        }
    };

    std::shared_ptr<Node> head;  ///< Head pointer of the list
    int count;                   ///< Total number of recipes

public:
    // === Constructor & Destructor ===
    LinkedList() : head(nullptr), count(0) {}
    ~LinkedList() = default;

    // === Core Operations ===

    /**
     * @brief Inserts a recipe at the head of the list.
     * @param recipe Shared pointer to the recipe.
     * @return True if insertion succeeded.
     */
    bool insertHead(const std::shared_ptr<Recipe>& recipe);

    /**
     * @brief Inserts a recipe at the tail of the list.
     * @param recipe Shared pointer to the recipe.
     * @return True if insertion succeeded.
     */
    bool insertTail(const std::shared_ptr<Recipe>& recipe);

    /**
     * @brief Removes a recipe by its ID.
     * @param id Recipe ID to remove.
     * @return Shared pointer to the removed recipe, or nullptr if not found.
     */
    std::shared_ptr<Recipe> remove(int id);

    /**
     * @brief Finds a recipe by its ID.
     * @param id Recipe ID to search for.
     * @return Shared pointer to the found recipe, or nullptr if not found.
     */
    std::shared_ptr<Recipe> find(int id) const;

    /**
     * @brief Displays all recipes in the list.
     */
    void display() const;

    /**
     * @brief Returns the total number of recipes.
     */
    int size() const { return count; }

    /**
     * @brief Checks whether the list is empty.
     */
    bool isEmpty() const { return head == nullptr; }

    /**
     * @brief Clears all nodes in the list.
     */
    void clear();
};

#endif // LINKED_LIST_HPP
