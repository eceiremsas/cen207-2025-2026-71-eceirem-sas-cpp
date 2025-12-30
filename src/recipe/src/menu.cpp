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

#include "menu.hpp"
#include "recipe.hpp"

// =====================================================
//  Helper Utilities (moved to Menu static methods)
// =====================================================

// =====================================================
//  Application Context Management
// =====================================================

// AppContext Constructor
AppContext::AppContext() 
    : hashTable(std::make_unique<HashTable>(MAX_RECIPES)),
      list(std::make_unique<LinkedList>()),
      stack(std::make_unique<Stack>()),
      queue(std::make_unique<Queue>()),
      graph(std::make_unique<Graph>()),
      sparseMatrix(std::make_unique<SparseMatrix>()),
      nextRecipeId(1) {
}

// AppContext Destructor
AppContext::~AppContext() = default;

// AppContext::create() static method
std::unique_ptr<AppContext> AppContext::create() {
    try {
        auto ctx = std::make_unique<AppContext>();
        if (!ctx->hashTable || !ctx->list || !ctx->stack ||
            !ctx->queue || !ctx->graph || !ctx->sparseMatrix) {
            return nullptr;
        }
        return ctx;
    } catch (...) {
        return nullptr;
    }
}

// Legacy C-style function for compatibility
std::unique_ptr<AppContext> app_context_create() {
    return AppContext::create();
}

void app_context_destroy(AppContext* ctx) {
    // No-op: unique_ptr handles cleanup automatically
    (void)ctx;
}

// =====================================================
//  Menu Class - Static Methods Implementation
// =====================================================

void Menu::clearConsole() {
#if defined(_WIN32) || defined(_WIN64)
    system("cls");
#else
    system("clear");
#endif
}

void Menu::waitForEnter() {
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

std::string Menu::safeStringInput(const std::string& prompt) {
    std::cout << prompt;
    std::string input;
    std::getline(std::cin, input);
    return input;
}

int Menu::safeIntInput(const std::string& prompt) {
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

void Menu::displayMain() {
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
              << "  0.  Exit\n\n";
}

void Menu::loadSampleData(AppContext& ctx) {
    std::cout << "Loading sample recipes...\n";

    // Create Pizza recipe
    auto pizza = std::make_shared<Recipe>(ctx.nextRecipeId++, "Pizza", "Lunch", 800, 45);
    pizza->addIngredient("Flour");
    pizza->addIngredient("Water");
    pizza->addIngredient("Yeast");
    pizza->addIngredient("Tomato sauce");
    pizza->addIngredient("Cheese");
    pizza->setInstructions("Prepare the dough, spread the sauce, add toppings, bake at 200°C for 20 minutes.");

    ctx.hashTable->insert(pizza);
    ctx.list->insertTail(pizza);
    ctx.graph->addVertex(pizza->getId());
    for (size_t i = 0; i < pizza->getIngredients().size(); ++i) {
        ctx.sparseMatrix->addEntry(pizza->getId(), static_cast<int>(i), 1, pizza->getIngredients()[i]);
    }

    // Create Caesar Salad recipe
    auto salad = std::make_shared<Recipe>(ctx.nextRecipeId++, "Caesar Salad", "Dinner", 350, 20);
    salad->addIngredient("Lettuce");
    salad->addIngredient("Chicken");
    salad->addIngredient("Croutons");
    salad->addIngredient("Parmesan");
    salad->addIngredient("Dressing");
    salad->setInstructions("Wash lettuce, cook chicken, mix all ingredients together.");

    ctx.hashTable->insert(salad);
    ctx.list->insertTail(salad);
    ctx.graph->addVertex(salad->getId());
    for (size_t i = 0; i < salad->getIngredients().size(); ++i) {
        ctx.sparseMatrix->addEntry(salad->getId(), static_cast<int>(i), 1, salad->getIngredients()[i]);
    }

    // Create Berry Smoothie recipe
    auto smoothie = std::make_shared<Recipe>(ctx.nextRecipeId++, "Berry Smoothie", "Breakfast", 180, 5);
    smoothie->addIngredient("Strawberry");
    smoothie->addIngredient("Banana");
    smoothie->addIngredient("Yogurt");
    smoothie->addIngredient("Honey");
    smoothie->setInstructions("Place all ingredients in a blender and mix until smooth.");

    ctx.hashTable->insert(smoothie);
    ctx.list->insertTail(smoothie);
    ctx.graph->addVertex(smoothie->getId());
    for (size_t i = 0; i < smoothie->getIngredients().size(); ++i) {
        ctx.sparseMatrix->addEntry(smoothie->getId(), static_cast<int>(i), 1, smoothie->getIngredients()[i]);
    }

    std::cout << "3 sample recipes loaded!\n";
}

void Menu::viewAllRecipes(AppContext& ctx) {
    clearConsole();
    ctx.list->display();
    waitForEnter();
}

void Menu::handleChoice(AppContext& ctx, int choice) {
    switch (choice) {
    case 1:  addRecipe(ctx); break;
    case 5:  viewAllRecipes(ctx); break;
    case 6:  sortByCalories(ctx); break;
    case 7:  createWeeklyPlan(ctx); break;
    case 8:  viewDependencies(ctx); break;
    case 9:  findByIngredient(ctx); break;
    case 0:  std::cout << "Exiting...\n"; break;
    default: std::cout << "Invalid choice!\n"; waitForEnter(); break;
    }
}

// Placeholder implementations for other Menu methods
void Menu::addRecipe(AppContext& ctx) {
    clearConsole();
    std::cout << "\n=== ADD NEW RECIPE ===\n\n";
    std::cout << "Feature not yet fully implemented.\n";
    waitForEnter();
}

void Menu::editRecipe(AppContext& ctx) {
    clearConsole();
    std::cout << "\n=== EDIT RECIPE ===\n\n";
    std::cout << "Feature not yet fully implemented.\n";
    waitForEnter();
}

void Menu::deleteRecipe(AppContext& ctx) {
    clearConsole();
    std::cout << "\n=== DELETE RECIPE ===\n\n";
    std::cout << "Feature not yet fully implemented.\n";
    waitForEnter();
}

void Menu::searchRecipes(AppContext& ctx) {
    clearConsole();
    std::cout << "\n=== SEARCH RECIPES ===\n\n";
    std::cout << "Feature not yet fully implemented.\n";
    waitForEnter();
}

void Menu::searchByName(AppContext& ctx) {
    clearConsole();
    std::cout << "\n=== SEARCH BY NAME ===\n\n";
    std::cout << "Feature not yet fully implemented.\n";
    waitForEnter();
}

void Menu::searchByCategory(AppContext& ctx) {
    clearConsole();
    std::cout << "\n=== SEARCH BY CATEGORY ===\n\n";
    std::cout << "Feature not yet fully implemented.\n";
    waitForEnter();
}

void Menu::searchByCalorieRange(AppContext& ctx) {
    clearConsole();
    std::cout << "\n=== SEARCH BY CALORIE RANGE ===\n\n";
    std::cout << "Feature not yet fully implemented.\n";
    waitForEnter();
}

void Menu::sortByCalories(AppContext& ctx) {
    clearConsole();
    if (ctx.list->isEmpty()) {
        std::cout << "The list is empty!\n";
        waitForEnter();
        return;
    }
    std::cout << "Sorting by calories feature not yet fully implemented.\n";
    waitForEnter();
}

void Menu::createWeeklyPlan(AppContext& ctx) {
    clearConsole();
    std::cout << "\n=== CREATE WEEKLY PLAN ===\n\n";
    std::cout << "Feature not yet fully implemented.\n";
    waitForEnter();
}

void Menu::viewDependencies(AppContext& ctx) {
    clearConsole();
    int id = safeIntInput("Starting Recipe ID: ");
    ctx.graph->resetVisited();
    ctx.graph->displayDependencies(id, 0);
    waitForEnter();
}

void Menu::findByIngredient(AppContext& ctx) {
    clearConsole();
    std::string ing = safeStringInput("Ingredient: ");
    auto recipeIds = ctx.sparseMatrix->findRecipesByIngredient(ing);
    
    if (recipeIds.empty()) {
        std::cout << "No recipes found.\n";
    } else {
        std::cout << recipeIds.size() << " recipe(s) found:\n";
        for (int id : recipeIds) {
            auto r = ctx.hashTable->search(id);
            if (r) {
                std::cout << "  - " << r->getName() << " (ID:" << r->getId() << ")\n";
            }
        }
    }
    waitForEnter();
}

void Menu::undoLastOperation(AppContext& ctx) {
    clearConsole();
    std::cout << "\n=== UNDO LAST OPERATION ===\n\n";
    std::cout << "Feature not yet fully implemented.\n";
    waitForEnter();
}

// Legacy compatibility - remove old Menu class implementation


