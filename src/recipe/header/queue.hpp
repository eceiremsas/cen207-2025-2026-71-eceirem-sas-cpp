/**
 * @file queue.hpp
 * @brief Circular Queue for Weekly Meal Planning (C++ version)
 * @details Fixed-size queue (7 days) where each element represents one recipe per day.
 */

#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <iostream>
#include <array>
#include <memory>
#include <string>
#include "recipe.hpp"

constexpr int WEEKLY_PLAN_SIZE = 7;

/**
 * @class Queue
 * @brief Implements a circular queue structure for managing weekly meal plans.
 * @details Each element represents one day of the week (Monday–Sunday).
 */
class Queue {
private:
    std::array<std::shared_ptr<Recipe>, WEEKLY_PLAN_SIZE> recipes;  ///< Circular storage for recipes
    int front;      ///< Index of the front element
    int rear;       ///< Index of the rear element
    int count;      ///< Number of elements currently in the queue

public:
    // === Constructor / Destructor ===
    Queue();
    ~Queue() = default;

    // === Core Operations ===

    /**
     * @brief Adds a recipe to the end of the queue.
     * @param recipe Shared pointer to the recipe.
     * @return True if the recipe was added successfully.
     */
    bool enqueue(const std::shared_ptr<Recipe>& recipe);

    /**
     * @brief Removes and returns the recipe at the front of the queue.
     * @return Shared pointer to the removed recipe, or nullptr if empty.
     */
    std::shared_ptr<Recipe> dequeue();

    /**
     * @brief Returns the recipe at the front without removing it.
     * @return Shared pointer to the recipe, or nullptr if empty.
     */
    std::shared_ptr<Recipe> peek() const;

    // === Status Checks ===
    bool isEmpty() const;
    bool isFull() const;
    int size() const { return count; }

    // === Display ===
    void display() const;

    // === Reset / Clear ===
    void clear();
};

#endif // QUEUE_HPP
