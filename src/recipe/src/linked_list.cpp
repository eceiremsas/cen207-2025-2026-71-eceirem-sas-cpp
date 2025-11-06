/**
 * @file linked_list.cpp
 * @brief Singly linked list implementation for storing Recipe objects (C++ version).
 */

#include <iostream>
#include <memory>
#include "recipe.h"  // Must define struct/class Recipe with id, name, etc.

// === List Node Definition ===
struct ListNode {
    std::shared_ptr<Recipe> recipe;
    std::shared_ptr<ListNode> next;

    explicit ListNode(std::shared_ptr<Recipe> r)
        : recipe(std::move(r)), next(nullptr) {}
};

// === Linked List Class ===
class LinkedList {
private:
    std::shared_ptr<ListNode> head;
    int count;

public:
    // === Constructor / Destructor ===
    LinkedList() : head(nullptr), count(0) {}
    ~LinkedList() = default;

    // === Insert at Head (O(1)) ===
    bool insertHead(std::shared_ptr<Recipe> recipe) {
        if (!recipe) return false;
        auto newNode = std::make_shared<ListNode>(recipe);
        newNode->next = head;
        head = newNode;
        count++;
        return true;
    }

    // === Insert at Tail (O(n)) ===
    bool insertTail(std::shared_ptr<Recipe> recipe) {
        if (!recipe) return false;
        auto newNode = std::make_shared<ListNode>(recipe);

        if (!head) {
            head = newNode;
        } else {
            auto current = head;
            while (current->next) {
                current = current->next;
            }
            current->next = newNode;
        }
        count++;
        return true;
    }

    // === Remove Recipe by ID (returns pointer to removed recipe) ===
    std::shared_ptr<Recipe> remove(int id) {
        if (!head) return nullptr;

        std::shared_ptr<ListNode> current = head;
        std::shared_ptr<ListNode> prev = nullptr;

        while (current) {
            if (current->recipe && current->recipe->id == id) {
                if (prev) {
                    prev->next = current->next;
                } else {
                    head = current->next;
                }
                count--;
                return current->recipe;
            }
            prev = current;
            current = current->next;
        }
        return nullptr;  // Not found
    }

    // === Find Recipe by ID ===
    std::shared_ptr<Recipe> find(int id) const {
        auto current = head;
        while (current) {
            if (current->recipe && current->recipe->id == id) {
                return current->recipe;
            }
            current = current->next;
        }
        return nullptr;
    }

    // === Display All Recipes ===
    void display() const {
        if (!head) {
            std::cout << "\nThe list is empty – no recipes available.\n";
            return;
        }

        std::cout << "\n=== RECIPE LIST (" << count << " recipes) ===\n";
        int index = 1;
        auto current = head;

        while (current) {
            std::cout << "\n" << index++ << ". ";
            recipe_display(current->recipe.get());  // Assuming C-style display
            current = current->next;
        }
    }

    // === Get List Size ===
    int size() const { return count; }

    // === Check if Empty ===
    bool isEmpty() const { return head == nullptr; }

    // === Clear List (RAII auto-cleans nodes) ===
    void clear() {
        head.reset();
        count = 0;
    }
};
