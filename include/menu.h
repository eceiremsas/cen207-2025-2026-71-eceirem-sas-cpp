#ifndef MENU_H
#define MENU_H

#include "heap.h"
#include "stack.h"
#include "linked_list.h"
#include "queue.h"
#include "graph.h"
#include "sparse_matrix.h"
#include "hash_table.h"
#include "recipe.h"   // One-way dependency: menu -> recipe

#include <stdio.h>
#include <ctype.h>

#define MAX_RECIPES 100

// === Application-Wide Data Context ===
typedef struct {
    Recipe* recipes;             // All recipes (array or pointer to Recipe)
    HashTable* hash_table;       // Hash table for fast recipe search
    List* list;                  // Linked list for displaying recipes
    Stack* stack;                // Stack for undo operations
    Queue* queue;                // Queue for weekly meal planning
    Graph* graph;                // Graph representing recipe dependencies
    SparseMatrix* sparse_matrix; // Sparse matrix for ingredient relationships
    int next_recipe_id;          // Next available recipe ID for new entries
} AppContext;

// === Utility Functions ===

// Clears the console screen
void clear_console(void);

// Waits for user to press Enter
void wait_for_enter(void);

// Safely reads a string input
void safe_string_input(char* buffer, int size);

// Safely reads an integer input
int safe_int_input(void);

// === Context Management ===

// Creates and initializes the application context
AppContext* app_context_create(void);

// Frees all memory used by the application context
void app_context_destroy(AppContext* ctx);

// === Menu Operations ===

// Displays the main menu
void menu_display(void);

// Loads sample recipe data
void menu_load_sample_data(AppContext* ctx);

// 1. Adds a new recipe
void menu_add_recipe(AppContext* ctx);

// 2. Edits an existing recipe
void menu_edit_recipe(AppContext* ctx);

// 3. Deletes a recipe
void menu_delete_recipe(AppContext* ctx);

// 4. Search submenu
void menu_search_recipes(AppContext* ctx);
void menu_search_by_name(AppContext* ctx);
void menu_search_by_category(AppContext* ctx);
void menu_search_by_calorie_range(AppContext* ctx);

// 5. Displays all recipes
void menu_view_all_recipes(AppContext* ctx);

// 6. Sorts recipes by calorie count
void menu_sort_by_calories(AppContext* ctx);

// 7. Creates a weekly meal plan
void menu_create_weekly_plan(AppContext* ctx);

// 8. Displays recipe dependency graph
void menu_view_dependencies(AppContext* ctx);

// 9. Finds recipes containing a specific ingredient
void menu_find_by_ingredient(AppContext* ctx);

// 10. Undoes the last operation
void menu_undo(AppContext* ctx);

// Handles user menu choices
void menu_handle_choice(AppContext* ctx, int choice);

// === Binary File Operations ===

// Saves the entire application context to a binary file
int menu_save_context_binary(const AppContext* ctx, const char* filename);

// Loads the entire application context from a binary file
AppContext* menu_load_context_binary(const char* filename);

#endif // MENU_H
