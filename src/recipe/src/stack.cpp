/**
 * @file stack.cpp
 * @brief Stack implementation (C++ version)
 * @details LIFO structure used for undo operations in the Recipe & Nutrition Tracker.
 */

#include "stack.hpp"
#include "recipe.hpp"

// === Stack Constructor ===
Stack::Stack() : top(-1) {
    operations.reserve(UNDO_STACK_SIZE);
}

// === Stack::push ===
bool Stack::push(OperationType type, const std::shared_ptr<Recipe>& recipe) {
    if (!recipe) return false;

    if (isFull()) {
        std::cout << "WARNING: Undo stack is full – oldest operation will be removed.\n";
        operations.erase(operations.begin());
        top = static_cast<int>(operations.size()) - 1;
    }

    operations.emplace_back(type, recipe);
    top++;
    return true;
}

// === Stack::pop ===
std::shared_ptr<StackOperation> Stack::pop() {
    if (isEmpty()) return nullptr;

    auto op = std::make_shared<StackOperation>(operations[top]);
    operations.pop_back();
    top--;
    return op;
}

// === Stack::peek ===
std::shared_ptr<StackOperation> Stack::peek() const {
    if (isEmpty()) return nullptr;
    return std::make_shared<StackOperation>(operations[top]);
}

// === Stack::isEmpty ===
bool Stack::isEmpty() const {
    return top == -1;
}

// === Stack::isFull ===
bool Stack::isFull() const {
    return static_cast<int>(operations.size()) >= UNDO_STACK_SIZE;
}

// === Stack::clear ===
void Stack::clear() {
    operations.clear();
    top = -1;
}
