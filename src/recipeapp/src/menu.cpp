/**
 * @file menu.cpp
 * @brief Menu system for Recipe & Nutrition Tracker (C++ version).
 * @details Provides application context creation, data loading,
 *          and user-driven operations such as adding, viewing,
 *          sorting, and searching recipes.
 */

#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <limits>
#include <cstdlib>

#include "menu.h"
#include "recipe.h"

// =====================================================
//  Helper Utilities
// =====================================================

void clearConsole() {
#if defined(_WIN32) || defined(_WIN64)
    system("cls");
#else
    system("clear");
#endif
}

void waitForEnter() {
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

std::string safeStringInput(const std::string& prompt) {
    std::cout << prompt;
    std::string input;
    std::getline(std::cin, input);
    return input;
}

int safeIntInput(const std::string& prompt = "") {
    int value;
    while (true) {
        if (!prompt.empty()) std::cout << prompt;
        if (std::cin >> value) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        } else {
            std::cout << "Invalid input! Please enter a number.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

// =====================================================
//  Application Context Management
// =====================================================

std::unique_ptr<AppContext> app_context_create() {
    auto ctx = std::make_unique<AppContext>();
    ctx->hash_table    = hash_table_create(MAX_RECIPES);
    ctx->list          = list_create();
    ctx->stack         = stack_create();
    ctx->queue         = queue_create();
    ctx->graph         = graph_create();
    ctx->sparse_matrix = sparse_matrix_create();
    ctx->next_recipe_id = 1;

    if (!ctx->hash_table || !ctx->list || !ctx->stack ||
        !ctx->queue || !ctx->graph || !ctx->sparse_matrix) {
        app_context_destroy(ctx.get());
        return nullptr;
    }
    return ctx;
}

void app_context_destroy(AppContext* ctx) {
    if (!ctx) return;
    if (ctx->hash_table)    hash_table_destroy(ctx->hash_table);
    if (ctx->list)          list_destroy(ctx->list);
    if (ctx->stack)         stack_destroy(ctx->stack);
    if (ctx->queue)         queue_destroy(ctx->queue);
    if (ctx->graph)         graph_destroy(ctx->graph);
    if (ctx->sparse_matrix) sparse_matrix_destroy(ctx->sparse_matrix);
    delete ctx;
}

// =====================================================
//  Menu Class
// =====================================================

class Menu {
private:
    AppContext* ctx;

    static void safeSparseAddRecipe(AppContext* ctx, const Recipe* r) {
        if (!ctx || !ctx->sparse_matrix || !r) return;
        if (r->ingredient_count <= 0 || !r->ingredients) return;

        int limit = r->ingredient_count;
#ifdef MAX_INGREDIENTS
        if (limit > MAX_INGREDIENTS) limit = MAX_INGREDIENTS;
#endif
        for (int i = 0; i < limit; ++i) {
            const char* name = r->ingredients[i];
            if (name && name[0] != '\0') {
                sparse_matrix_add_entry(ctx->sparse_matrix, r->id, i, 1, name);
            }
        }
    }

public:
    explicit Menu(AppContext* context) : ctx(context) {}

    // ---------------------------------
    void display() const {
        std::cout << "\n=== RECIPE AND NUTRITION TRACKER ===\n\n"
                  << "  1.  Add New Recipe\n"
                  << "  2.  Edit Recipe\n"
                  << "  3.  Delete Recipe\n"
                  << "  4.  Search Recipes\n"
                  << "  5.  View All Recipes\n"
                  << "  6.  Sort Recipes by Calories\n"
                  << "  7.  Create Weekly Meal Plan\n"
                  << "  8.  View Recipe Dependencies\n"
                  << "  9.  Find Recipes by Ingredient\n"
                  << " 10.  Undo Last Operation\n"
                  << "  0.  Exit\n\n"
                  << "Your choice: ";
    }

    // ---------------------------------
    void loadSampleData() {
        std::cout << "Loading sample recipes...\n";

        Recipe* pizza = recipe_create(ctx->next_recipe_id++, "Pizza", "Lunch", 800, 45);
        recipe_add_ingredient(pizza, "Flour");
        recipe_add_ingredient(pizza, "Water");
        recipe_add_ingredient(pizza, "Yeast");
        recipe_add_ingredient(pizza, "Tomato sauce");
        recipe_add_ingredient(pizza, "Cheese");
        recipe_set_instructions(pizza, "Prepare the dough, spread the sauce, add toppings, bake at 200°C for 20 minutes.");

        hash_table_insert(ctx->hash_table, pizza);
        list_insert_tail(ctx->list, pizza);
        graph_add_vertex(ctx->graph, pizza->id);
        safeSparseAddRecipe(ctx, pizza);

        Recipe* salad = recipe_create(ctx->next_recipe_id++, "Caesar Salad", "Dinner", 350, 20);
        recipe_add_ingredient(salad, "Lettuce");
        recipe_add_ingredient(salad, "Chicken");
        recipe_add_ingredient(salad, "Croutons");
        recipe_add_ingredient(salad, "Parmesan");
        recipe_add_ingredient(salad, "Dressing");
        recipe_set_instructions(salad, "Wash lettuce, cook chicken, mix all ingredients together.");

        hash_table_insert(ctx->hash_table, salad);
        list_insert_tail(ctx->list, salad);
        graph_add_vertex(ctx->graph, salad->id);
        safeSparseAddRecipe(ctx, salad);

        Recipe* smoothie = recipe_create(ctx->next_recipe_id++, "Berry Smoothie", "Breakfast", 180, 5);
        recipe_add_ingredient(smoothie, "Strawberry");
        recipe_add_ingredient(smoothie, "Banana");
        recipe_add_ingredient(smoothie, "Yogurt");
        recipe_add_ingredient(smoothie, "Honey");
        recipe_set_instructions(smoothie, "Place all ingredients in a blender and mix until smooth.");

        hash_table_insert(ctx->hash_table, smoothie);
        list_insert_tail(ctx->list, smoothie);
        graph_add_vertex(ctx->graph, smoothie->id);
        safeSparseAddRecipe(ctx, smoothie);

        std::cout << "3 sample recipes loaded!\n";
    }

    // ---------------------------------
    void addRecipe() {
        clearConsole();
        std::cout << "\n=== ADD NEW RECIPE ===\n\n";

        std::string name = safeStringInput("Recipe name: ");
        std::string category = safeStringInput("Category: ");
        int calories = safeIntInput("Calories: ");
        int prepTime = safeIntInput("Preparation time (min): ");

        Recipe* r = recipe_create(ctx->next_recipe_id++, name.c_str(), category.c_str(), calories, prepTime);
        if (!r) { std::cout << "Memory error!\n"; return; }

        int n = safeIntInput("Number of ingredients: ");
        for (int i = 0; i < n; ++i) {
            std::string ingredient = safeStringInput("Ingredient " + std::to_string(i + 1) + ": ");
            recipe_add_ingredient(r, ingredient.c_str());
            sparse_matrix_add_entry(ctx->sparse_matrix, r->id, i, 1, ingredient.c_str());
        }

        std::string inst = safeStringInput("Instructions: ");
        recipe_set_instructions(r, inst.c_str());

        hash_table_insert(ctx->hash_table, r);
        list_insert_tail(ctx->list, r);
        graph_add_vertex(ctx->graph, r->id);
        stack_push(ctx->stack, OP_ADD, r);

        std::cout << "\nSuccessfully added! ID: " << r->id << "\n";
        waitForEnter();
    }

    // ---------------------------------
    void viewAllRecipes() {
        clearConsole();
        list_display(ctx->list);
        waitForEnter();
    }

    // ---------------------------------
    void sortByCalories() {
        clearConsole();
        if (list_is_empty(ctx->list)) {
            std::cout << "The list is empty!\n";
            waitForEnter();
            return;
        }

        int count = list_size(ctx->list);
        std::vector<Recipe*> arr;
        arr.reserve(count);

        ListNode* cur = ctx->list->head;
        while (cur) {
            arr.push_back(cur->recipe);
            cur = cur->next;
        }

        heap_sort_recipes(arr.data(), count);
        for (int i = 0; i < count; ++i)
            std::cout << i + 1 << ". " << arr[i]->name << " - " << arr[i]->calories << " kcal\n";

        waitForEnter();
    }

    // ---------------------------------
    void createWeeklyPlan() {
        clearConsole();
        while (!queue_is_empty(ctx->queue))
            queue_dequeue(ctx->queue);

        for (int d = 1; d <= 7; ++d) {
            int id = safeIntInput("Recipe ID for Day " + std::to_string(d) + ": ");
            Recipe* r = hash_table_search(ctx->hash_table, id);
            if (r) queue_enqueue(ctx->queue, r);
            else { std::cout << "Not found!\n"; --d; }
        }

        std::cout << "Weekly Plan:\n";
        queue_display(ctx->queue);
        waitForEnter();
    }

    // ---------------------------------
    void viewDependencies() {
        clearConsole();
        int id = safeIntInput("Starting Recipe ID: ");
        graph_reset_visited(ctx->graph);
        graph_display_dependencies(ctx->graph, id, 0);
        waitForEnter();
    }

    // ---------------------------------
    void findByIngredient() {
        clearConsole();
        std::string ing = safeStringInput("Ingredient: ");
        int ids[MAX_RECIPES];
        int found = sparse_matrix_find_recipes_by_ingredient(ctx->sparse_matrix, ing.c_str(), ids, MAX_RECIPES);

        if (found <= 0) std::cout << "No recipes found.\n";
        else {
            std::cout << found << " recipe(s) found:\n";
            for (int i = 0; i < found; ++i) {
                Recipe* r = hash_table_search(ctx->hash_table, ids[i]);
                if (r) std::cout << "  - " << r->name << " (ID:" << r->id << ")\n";
            }
        }
        waitForEnter();
    }

    // ---------------------------------
    void handleChoice(int choice) {
        switch (choice) {
        case 1:  addRecipe(); break;
        case 5:  viewAllRecipes(); break;
        case 6:  sortByCalories(); break;
        case 7:  createWeeklyPlan(); break;
        case 8:  viewDependencies(); break;
        case 9:  findByIngredient(); break;
        case 0:  std::cout << "Exiting...\n"; break;
        default: std::cout << "Invalid choice!\n"; waitForEnter(); break;
        }
    }
};

// =====================================================
//  Global Accessor (for main.cpp)
// =====================================================

Menu* createMenu(AppContext* ctx) {
    return new Menu(ctx);
}
