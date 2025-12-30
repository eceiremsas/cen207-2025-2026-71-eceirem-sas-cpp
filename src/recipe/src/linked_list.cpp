/**
 * @file linked_list.cpp
 * @brief Singly linked list implementation for storing Recipe objects (C++ version).
 */

#include "linked_list.hpp"
#include "recipe.hpp"

// === LinkedList::insertHead ===
bool LinkedList::insertHead(const std::shared_ptr<Recipe>& recipe) {
    if (!recipe) return false;
    auto newNode = std::make_shared<Node>(recipe);
    newNode->next = head;
    head = newNode;
    count++;
    return true;
}

// === LinkedList::insertTail ===
bool LinkedList::insertTail(const std::shared_ptr<Recipe>& recipe) {
    if (!recipe) return false;
    auto newNode = std::make_shared<Node>(recipe);

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

// === LinkedList::remove ===
std::shared_ptr<Recipe> LinkedList::remove(int id) {
    if (!head) return nullptr;

    std::shared_ptr<Node> current = head;
    std::shared_ptr<Node> prev = nullptr;

    while (current) {
        if (current->recipe && current->recipe->getId() == id) {
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
    return nullptr;
}

// === LinkedList::find ===
std::shared_ptr<Recipe> LinkedList::find(int id) const {
    auto current = head;
    while (current) {
        if (current->recipe && current->recipe->getId() == id) {
            return current->recipe;
        }
        current = current->next;
    }
    return nullptr;
}

// === LinkedList::display ===
void LinkedList::display() const {
    if (!head) {
        std::cout << "\nThe list is empty – no recipes available.\n";
        return;
    }

    std::cout << "\n=== RECIPE LIST (" << count << " recipes) ===\n";
    int index = 1;
    auto current = head;

    while (current) {
        std::cout << "\n" << index++ << ". ";
        current->recipe->display();
        current = current->next;
    }
}

// === LinkedList::clear ===
void LinkedList::clear() {
    head.reset();
    count = 0;
}
