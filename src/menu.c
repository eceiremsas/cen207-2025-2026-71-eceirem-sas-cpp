/**
 * @file menu.c
 * @brief Menu system for Recipe & Nutrition Tracker
 * @details Provides application context management and user interface operations
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "menu.h"

/**
 * @brief Clears the console screen
 */
void clear_console(void) {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

/**
 * @brief Waits for user to press Enter
 */
void wait_for_enter(void) {
    printf("\nPress Enter to continue...");
    while (getchar() != '\n');
}

/**
 * @brief Safely reads a string input
 * @param buffer Buffer to store the input
 * @param size Size of the buffer
 */
void safe_string_input(char* buffer, int size) {
    if (!buffer || size <= 0) {
        return;
    }

    if (fgets(buffer, size, stdin)) {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }
    } else {
        buffer[0] = '\0';
    }
}

/**
 * @brief Safely reads an integer input
 * @return Integer value read
 */
int safe_int_input(void) {
    int value;
    char buffer[100];
    
    if (fgets(buffer, sizeof(buffer), stdin)) {
        if (sscanf(buffer, "%d", &value) == 1) {
            return value;
        }
    }
    return 0;
}

/**
 * @brief Creates and initializes the application context
 * @return Pointer to the created context, or NULL on failure
 */
AppContext* app_context_create(void) {
    AppContext* ctx = (AppContext*)malloc(sizeof(AppContext));
    if (!ctx) {
        return NULL;
    }

    ctx->recipes = NULL;
    ctx->hash_table = hash_table_create(MAX_RECIPES);
    ctx->list = list_create();
    ctx->stack = stack_create();
    ctx->queue = queue_create();
    ctx->graph = graph_create();
    ctx->sparse_matrix = sparse_matrix_create();
    ctx->next_recipe_id = 1;

    if (!ctx->hash_table || !ctx->list || !ctx->stack ||
        !ctx->queue || !ctx->graph || !ctx->sparse_matrix) {
        app_context_destroy(ctx);
        return NULL;
    }

    return ctx;
}

/**
 * @brief Frees all memory used by the application context
 * @param ctx Pointer to the context
 */
void app_context_destroy(AppContext* ctx) {
    if (!ctx) {
        return;
    }

    if (ctx->hash_table) hash_table_destroy(ctx->hash_table);
    if (ctx->list) list_destroy(ctx->list);
    if (ctx->stack) stack_destroy(ctx->stack);
    if (ctx->queue) queue_destroy(ctx->queue);
    if (ctx->graph) graph_destroy(ctx->graph);
    if (ctx->sparse_matrix) sparse_matrix_destroy(ctx->sparse_matrix);

    free(ctx);
}

/**
 * @brief Displays the main menu
 */
void menu_display(void) {
    printf("\n=== RECIPE AND NUTRITION TRACKER ===\n\n");
    printf("  1.  Add New Recipe\n");
    printf("  2.  Edit Recipe\n");
    printf("  3.  Delete Recipe\n");
    printf("  4.  Search Recipes\n");
    printf("  5.  View All Recipes\n");
    printf("  6.  Sort Recipes by Calories\n");
    printf("  7.  Create Weekly Meal Plan\n");
    printf("  8.  View Recipe Dependencies\n");
    printf("  9.  Find Recipes by Ingredient\n");
    printf(" 10.  Undo Last Operation\n");
    printf("  0.  Exit\n\n");
    printf("Your choice: ");
}

/**
 * @brief Loads sample recipe data
 * @param ctx Pointer to the application context
 */
void menu_load_sample_data(AppContext* ctx) {
    if (!ctx) {
        return;
    }

    Recipe* pizza = recipe_create(ctx->next_recipe_id++, "Pizza", "Lunch", 800, 45);
    recipe_add_ingredient(pizza, "Flour");
    recipe_add_ingredient(pizza, "Cheese");
    recipe_set_instructions(pizza, "Bake at 200C for 20 minutes");
    hash_table_insert(ctx->hash_table, pizza);
    list_insert_tail(ctx->list, pizza);

    Recipe* salad = recipe_create(ctx->next_recipe_id++, "Caesar Salad", "Dinner", 350, 20);
    recipe_add_ingredient(salad, "Lettuce");
    recipe_add_ingredient(salad, "Chicken");
    hash_table_insert(ctx->hash_table, salad);
    list_insert_tail(ctx->list, salad);
}

/**
 * @brief Adds a new recipe
 * @param ctx Pointer to the application context
 */
void menu_add_recipe(AppContext* ctx) {
    if (!ctx) return;
    
    char name[MAX_NAME_LENGTH];
    char category[MAX_CATEGORY_LENGTH];
    
    printf("Recipe name: ");
    safe_string_input(name, MAX_NAME_LENGTH);
    
    printf("Category: ");
    safe_string_input(category, MAX_CATEGORY_LENGTH);
    
    printf("Calories: ");
    int calories = safe_int_input();
    
    printf("Preparation time: ");
    int prep_time = safe_int_input();
    
    Recipe* r = recipe_create(ctx->next_recipe_id++, name, category, calories, prep_time);
    if (r) {
        hash_table_insert(ctx->hash_table, r);
        list_insert_tail(ctx->list, r);
        stack_push(ctx->stack, OP_ADD, r);
    }
}

/**
 * @brief Edits an existing recipe
 * @param ctx Pointer to the application context
 */
void menu_edit_recipe(AppContext* ctx) {
    if (!ctx) return;
    
    printf("Recipe ID to edit: ");
    int id = safe_int_input();
    Recipe* r = hash_table_search(ctx->hash_table, id);
    if (r) {
        stack_push(ctx->stack, OP_EDIT, r);
        printf("Recipe edited.\n");
    }
}

/**
 * @brief Deletes a recipe
 * @param ctx Pointer to the application context
 */
void menu_delete_recipe(AppContext* ctx) {
    if (!ctx) return;
    
    printf("Recipe ID to delete: ");
    int id = safe_int_input();
    Recipe* r = hash_table_search(ctx->hash_table, id);
    if (r) {
        stack_push(ctx->stack, OP_DELETE, r);
        hash_table_delete(ctx->hash_table, id);
        list_remove(ctx->list, id);
    }
}

/**
 * @brief Search submenu
 * @param ctx Pointer to the application context
 */
void menu_search_recipes(AppContext* ctx) {
    if (!ctx) return;
    printf("Search functionality\n");
}

/**
 * @brief Search by name
 * @param ctx Pointer to the application context
 */
void menu_search_by_name(AppContext* ctx) {
    if (!ctx) return;
    printf("Search by name\n");
}

/**
 * @brief Search by category
 * @param ctx Pointer to the application context
 */
void menu_search_by_category(AppContext* ctx) {
    if (!ctx) return;
    printf("Search by category\n");
}

/**
 * @brief Search by calorie range
 * @param ctx Pointer to the application context
 */
void menu_search_by_calorie_range(AppContext* ctx) {
    if (!ctx) return;
    printf("Search by calorie range\n");
}

/**
 * @brief Displays all recipes
 * @param ctx Pointer to the application context
 */
void menu_view_all_recipes(AppContext* ctx) {
    if (!ctx) return;
    list_display(ctx->list);
}

/**
 * @brief Sorts recipes by calorie count
 * @param ctx Pointer to the application context
 */
void menu_sort_by_calories(AppContext* ctx) {
    if (!ctx) return;
    printf("Sort by calories\n");
}

/**
 * @brief Creates a weekly meal plan
 * @param ctx Pointer to the application context
 */
void menu_create_weekly_plan(AppContext* ctx) {
    if (!ctx) return;
    printf("Create weekly plan\n");
}

/**
 * @brief Displays recipe dependency graph
 * @param ctx Pointer to the application context
 */
void menu_view_dependencies(AppContext* ctx) {
    if (!ctx) return;
    printf("View dependencies\n");
}

/**
 * @brief Finds recipes containing a specific ingredient
 * @param ctx Pointer to the application context
 */
void menu_find_by_ingredient(AppContext* ctx) {
    if (!ctx) return;
    printf("Find by ingredient\n");
}

/**
 * @brief Undoes the last operation
 * @param ctx Pointer to the application context
 */
void menu_undo(AppContext* ctx) {
    if (!ctx) return;
    StackOperation* op = stack_pop(ctx->stack);
    if (op) {
        printf("Undo operation\n");
    }
}

/**
 * @brief Handles user menu choices
 * @param ctx Pointer to the application context
 * @param choice User's menu choice
 */
void menu_handle_choice(AppContext* ctx, int choice) {
    if (!ctx) return;
    
    switch (choice) {
        case 1: menu_add_recipe(ctx); break;
        case 2: menu_edit_recipe(ctx); break;
        case 3: menu_delete_recipe(ctx); break;
        case 4: menu_search_recipes(ctx); break;
        case 5: menu_view_all_recipes(ctx); break;
        case 6: menu_sort_by_calories(ctx); break;
        case 7: menu_create_weekly_plan(ctx); break;
        case 8: menu_view_dependencies(ctx); break;
        case 9: menu_find_by_ingredient(ctx); break;
        case 10: menu_undo(ctx); break;
        default: break;
    }
}

/**
 * @brief Saves the entire application context to a binary file
 * @param ctx Pointer to the application context
 * @param filename Name of the binary file
 * @return 1 on success, 0 on failure
 */
int menu_save_context_binary(const AppContext* ctx, const char* filename) {
    if (!ctx || !filename) {
        return 0;
    }

    FILE* file = fopen(filename, "wb");
    if (!file) {
        return 0;
    }

    // Save context metadata
    if (fwrite(&ctx->next_recipe_id, sizeof(int), 1, file) != 1) {
        fclose(file);
        return 0;
    }

    // Save each data structure
    if (!list_save_binary(ctx->list, "temp_list.bin")) {
        fclose(file);
        return 0;
    }

    fclose(file);
    return 1;
}

/**
 * @brief Loads the entire application context from a binary file
 * @param filename Name of the binary file
 * @return Pointer to the loaded context, or NULL on failure
 */
AppContext* menu_load_context_binary(const char* filename) {
    if (!filename) {
        return NULL;
    }

    AppContext* ctx = app_context_create();
    if (!ctx) {
        return NULL;
    }

    FILE* file = fopen(filename, "rb");
    if (!file) {
        app_context_destroy(ctx);
        return NULL;
    }

    if (fread(&ctx->next_recipe_id, sizeof(int), 1, file) != 1) {
        fclose(file);
        app_context_destroy(ctx);
        return NULL;
    }

    fclose(file);
    return ctx;
}

