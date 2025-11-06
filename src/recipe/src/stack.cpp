/**
 * @file stack.cpp
 * @brief Stack implementation (C++ version)
 * @details LIFO structure used for undo operations in the Recipe & Nutrition Tracker.
 */

#include <iostream>
#include <vector>
#include <memory>
#include "recipe.h"

constexpr int UNDO_STACK_SIZE = 10;  // same as in original C version

// ============================================================
//  Enum: OperationType
// ============================================================
enum class OperationType {
    OP_ADD,
    OP_EDIT,
    OP_DELETE
};

// ============================================================
//  Struct: StackOperation
// ============================================================
struct StackOperation {
    OperationType type;
    std::shared_ptr<Recipe> recipe;

    StackOperation(OperationType t, std::shared_ptr<Recipe> r)
        : type(t), recipe(std::move(r)) {}
};

// ============================================================
//  Class: Stack
// ============================================================
class Stack {
private:
    std::vector<StackOperation> operations;
    int top;

public:
    // === Constructor ===
    Stack() : top(-1) {
        operations.reserve(UNDO_STACK_SIZE);
    }

    // === Push an Operation ===
    bool push(OperationType type, const std::shared_ptr<Recipe>& recipe) {
        if (!recipe) return false;

        if (isFull()) {
            std::cout << "WARNING: Undo stack is full – oldest operation will be removed.\n";
            // Remove oldest operation (FIFO behavior inside LIFO)
            operations.erase(operations.begin());
            top = static_cast<int>(operations.size()) - 1;
        }

        operations.emplace_back(type, std::make_shared<Recipe>(*recipe));  // deep copy
        top++;
        return true;
    }

    // === Pop Last Operation ===
    std::shared_ptr<StackOperation> pop() {
        if (isEmpty()) return nullptr;

        auto op = std::make_shared<StackOperation>(operations[top]);
        operations.pop_back();
        top--;
        return op;
    }

    // === Peek (View Last Operation) ===
    std::shared_ptr<StackOperation> peek() const {
        if (isEmpty()) return nullptr;
        return std::make_shared<StackOperation>(operations[top]);
    }

    // === Utility Functions ===
    bool isEmpty() const { return top == -1; }
    bool isFull() const { return static_cast<int>(operations.size()) >= UNDO_STACK_SIZE; }
    int size() const { return static_cast<int>(operations.size()); }

    // === Clear the Stack ===
    void clear() {
        operations.clear();
        top = -1;
    }

    // === Display Stack Content (Debug) ===
    void display() const {
        if (isEmpty()) {
            std::cout << "\nUndo stack is empty.\n";
            return;
        }
        std::cout << "\n--- Undo Stack (Top to Bottom) ---\n";
        for (int i = top; i >= 0; --i) {
            const auto& op = operations[i];
            std::cout << "[" << i << "] "
                      << (op.type == OperationType::OP_ADD ? "ADD" :
                          op.type == OperationType::OP_EDIT ? "EDIT" : "DELETE")
                      << " -> Recipe #" << op.recipe->id
                      << " (" << op.recipe->name << ")\n";
        }
    }
};
