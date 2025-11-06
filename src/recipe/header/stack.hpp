/**
 * @file stack.hpp
 * @brief Undo Stack implementation for Recipe operations (C++ version)
 * @details Provides a Last-In-First-Out (LIFO) structure to support undo functionality.
 */

#ifndef STACK_HPP
#define STACK_HPP

#include <iostream>
#include <vector>
#include <memory>
#include "recipe.hpp"

constexpr int UNDO_STACK_SIZE = 50;

/**
 * @enum OperationType
 * @brief Represents the type of operation recorded for undo functionality.
 */
enum class OperationType {
    Add,     ///< Recipe addition
    Edit,    ///< Recipe modification
    Delete   ///< Recipe deletion
};

/**
 * @struct StackOperation
 * @brief Represents a single recorded operation for undo purposes.
 */
struct StackOperation {
    OperationType type;                   ///< Type of the operation (Add/Edit/Delete)
    std::shared_ptr<Recipe> recipe;       ///< Recipe involved in the operation

    StackOperation(OperationType t, std::shared_ptr<Recipe> r)
        : type(t), recipe(std::move(r)) {
    }
};

/**
 * @class Stack
 * @brief Represents a fixed-size stack used for undo operations.
 * @details Implements standard LIFO behavior for tracking recent actions.
 */
class Stack {
private:
    std::vector<StackOperation> operations;   ///< Dynamic array of operations
    int top;                                 ///< Index of the top element (-1 if empty)

public:
    // === Constructor / Destructor ===
    Stack();
    ~Stack() = default;

    // === Core Operations ===

    /**
     * @brief Pushes a new operation onto the stack.
     * @param type Type of the operation.
     * @param recipe Recipe associated with the operation.
     * @return True if operation successfully added; false otherwise.
     */
    bool push(OperationType type, const std::shared_ptr<Recipe>& recipe);

    /**
     * @brief Pops (removes) the most recent operation from the stack.
     * @return Shared pointer to the popped StackOperation, or nullptr if empty.
     */
    std::shared_ptr<StackOperation> pop();

    /**
     * @brief Returns the top operation without removing it.
     * @return Shared pointer to the top StackOperation, or nullptr if empty.
     */
    std::shared_ptr<StackOperation> peek() const;

    // === Status Queries ===
    bool isEmpty() const;
    bool isFull() const;
    int size() const { return top + 1; }

    // === Utility ===
    void clear();
};

#endif // STACK_HPP
