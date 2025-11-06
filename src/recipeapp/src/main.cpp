/**
 * @file main.cpp
 * @brief Entry point for the Recipe and Nutrition Tracker (C++ version).
 * @details Demonstrates integration of all data structures:
 *          HashTable, LinkedList, Stack, Queue, Graph, and SparseMatrix.
 */

#include <iostream>
#include <memory>
#include <limits>
#include "menu.h"   // Contains AppContext, menu_display(), menu_handle_choice(), etc.

static bool validateContext(const std::unique_ptr<AppContext>& ctx) {
    if (!ctx) return false;
    return (ctx->recipes || ctx->hash_table || ctx->list ||
            ctx->stack || ctx->queue || ctx->graph || ctx->sparse_matrix);
}

// Clears console in a cross-platform way
void clearConsole() {
#if defined(_WIN32) || defined(_WIN64)
    system("cls");
#else
    system("clear");
#endif
}

// Safe integer input
int safeIntInput() {
    int value;
    while (true) {
        std::cout << "> ";
        if (std::cin >> value) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        } else {
            std::cout << "Invalid input. Please enter a number.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

int main() {
    std::cout << "\n=== RECIPE AND NUTRITION TRACKER ===\n";
    std::cout << "Data Structures and Algorithms Project\n\n";
    std::cout << "System is starting...\n\n";

    // === 1. CREATE APPLICATION CONTEXT ===
    std::cout << "[1/7] Creating application context...\n";
    std::unique_ptr<AppContext> ctx = app_context_create();

    if (!ctx) {
        std::cerr << "\nERROR: Insufficient memory! Failed to create AppContext.\n";
        return EXIT_FAILURE;
    }

    // === 2. VALIDATION CHECK ===
    if (!validateContext(ctx)) {
        std::cerr << "\nERROR: Data structures failed to initialize! Invalid context.\n";
        app_context_destroy(ctx.release()); // manual cleanup
        return EXIT_FAILURE;
    }

    std::cout << "[2/7] Hash Table created (for O(1) lookups)\n";
    std::cout << "[3/7] Linked List created (for dynamic listing)\n";
    std::cout << "[4/7] Stack created (for undo operations)\n";
    std::cout << "[5/7] Queue created (for weekly meal plan)\n";
    std::cout << "[6/7] Graph created (for dependency tracking)\n";
    std::cout << "[7/7] Sparse Matrix created (for ingredient search)\n\n";

    // === 3. LOAD SAMPLE DATA ===
    std::cout << "Loading sample data...\n";
    menu_load_sample_data(ctx.get());

    std::cout << "\nSystem is ready!\n\nPress Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // === 4. MAIN MENU LOOP ===
    int choice = -1;
    while (choice != 0) {
        clearConsole();
        menu_display();
        choice = safeIntInput();
        menu_handle_choice(ctx.get(), choice);
    }

    // === 5. SHUTDOWN ===
    std::cout << "\nShutting down program...\n";
    std::cout << "Cleaning up memory...\n";
    app_context_destroy(ctx.release());  // release() passes raw pointer for legacy destroy function
    std::cout << "Memory successfully released.\n\n";
    std::cout << "Thank you for using the program!\nGoodbye!\n\n";

    return EXIT_SUCCESS;
}
