/**
 * @file menu.hpp
 * @brief Main application interface for the Recipe & Nutrition Tracker (C++ version)
 * @details Provides menu display, user input utilities, and centralized data context
 *          for managing recipes, dependencies, meal plans, and undo operations.
 */

#ifndef MENU_HPP
#define MENU_HPP

#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <cctype>

#include "heap.hpp"
#include "stack.hpp"
#include "linked_list.hpp"  
#include "queue.hpp"
#include "graph.hpp"
#include "sparse_matrix.hpp"
#include "hash_table.hpp"
#include "recipe.hpp"

constexpr int MAX_RECIPES = 100;

/**
 * @class AppContext
 * @brief Centralized structure for managing all application data structures.
 */
class AppContext {
public:
    std::unique_ptr<HashTable> hashTable;         ///< Hash table for fast recipe lookup
    std::unique_ptr<LinkedList> list;             ///< Linked list for displaying recipes
    std::unique_ptr<Stack> stack;                 ///< Stack for undo operations
    std::unique_ptr<Queue> queue;                 ///< Queue for weekly meal planning
    std::unique_ptr<Graph> graph;                 ///< Graph for recipe dependencies
    std::unique_ptr<SparseMatrix> sparseMatrix;   ///< Sparse matrix for ingredient indexing
    int nextRecipeId;                             ///< Next available recipe ID

    // === Constructor / Destructor ===
    AppContext();
    ~AppContext();

    // === Initialization ===
    static std::unique_ptr<AppContext> create();
};

/**
 * @class Menu
 * @brief Provides user interface operations for managing recipes.
 */
class Menu {
public:
    // === Console Utilities ===
    static void clearConsole();
    static void waitForEnter();
    static std::string safeStringInput(const std::string& prompt);
    static int safeIntInput(const std::string& prompt);

    // === Display ===
    static void displayMain();
    static void loadSampleData(AppContext& ctx);

    // === Menu Operations ===
    static void addRecipe(AppContext& ctx);
    static void editRecipe(AppContext& ctx);
    static void deleteRecipe(AppContext& ctx);

    static void searchRecipes(AppContext& ctx);
    static void searchByName(AppContext& ctx);
    static void searchByCategory(AppContext& ctx);
    static void searchByCalorieRange(AppContext& ctx);

    static void viewAllRecipes(AppContext& ctx);
    static void sortByCalories(AppContext& ctx);
    static void createWeeklyPlan(AppContext& ctx);
    static void viewDependencies(AppContext& ctx);
    static void findByIngredient(AppContext& ctx);
    static void undoLastOperation(AppContext& ctx);

    // === Main Dispatcher ===
    static void handleChoice(AppContext& ctx, int choice);
};

#endif // MENU_HPP
