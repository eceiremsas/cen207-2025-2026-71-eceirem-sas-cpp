/**
 * @file queue.cpp
 * @brief Circular Queue implementation (C++ version)
 * @details FIFO structure for a 7-day weekly meal plan.
 */

#include "queue.hpp"
#include "recipe.hpp"

// === Queue Constructor ===
Queue::Queue() : front(0), rear(-1), count(0) {
}

// === Queue::enqueue ===
bool Queue::enqueue(const std::shared_ptr<Recipe>& recipe) {
    if (!recipe) return false;
    if (isFull()) {
        std::cout << "WARNING: Weekly plan is full (7 days)!\n";
        return false;
    }

    rear = (rear + 1) % WEEKLY_PLAN_SIZE;
    recipes[rear] = recipe;
    count++;
    return true;
}

// === Queue::dequeue ===
std::shared_ptr<Recipe> Queue::dequeue() {
    if (isEmpty()) return nullptr;

    auto recipe = recipes[front];
    front = (front + 1) % WEEKLY_PLAN_SIZE;
    count--;
    return recipe;
}

// === Queue::peek ===
std::shared_ptr<Recipe> Queue::peek() const {
    if (isEmpty()) return nullptr;
    return recipes[front];
}

// === Queue::isEmpty ===
bool Queue::isEmpty() const {
    return count == 0;
}

// === Queue::isFull ===
bool Queue::isFull() const {
    return count >= WEEKLY_PLAN_SIZE;
}

// === Queue::display ===
void Queue::display() const {
    if (isEmpty()) {
        std::cout << "\nWeekly meal plan is empty.\n";
        return;
    }

    std::cout << "\n=== 7-DAY WEEKLY MEAL PLAN ===\n";
    const char* days[] = {
        "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"
    };

    int index = front;
    for (int i = 0; i < count; i++) {
        std::cout << "\n" << days[i] << ":\n";
        if (recipes[index]) {
            std::cout << "  -> " << recipes[index]->getName() 
                      << " (" << recipes[index]->getCalories() << " kcal)\n";
        }
        index = (index + 1) % WEEKLY_PLAN_SIZE;
    }
    std::cout << "\n";
}

// === Queue::clear ===
void Queue::clear() {
    for (auto& r : recipes) {
        r.reset();
    }
    front = 0;
    rear = -1;
    count = 0;
}
