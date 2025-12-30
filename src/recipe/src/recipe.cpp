/**
 * @file recipe.cpp
 * @brief Recipe class implementation (C++ version)
 * @details Represents a single recipe with ingredients, instructions,
 *          and nutrition data (calories, prep time, etc.).
 */

#include "recipe.hpp"
#include <iostream>
#include <iomanip>
#include <algorithm>

constexpr int MAX_INGREDIENTS = 20;

// === Recipe Constructor ===
Recipe::Recipe(int id, std::string name, std::string category, int calories, int prepTime)
    : id(id), name(std::move(name)), category(std::move(category)),
      calories(calories), preparationTime(prepTime) {
}

// === Add Ingredient ===
void Recipe::addIngredient(const std::string& ingredient) {
    if (ingredients.size() < MAX_INGREDIENTS) {
        ingredients.push_back(ingredient);
    }
}

// === Display Recipe ===
void Recipe::display() const {
    std::cout << "Recipe #" << id << ": " << name << "\n"
              << "Category: " << category << "\n"
              << "Calories: " << calories << " kcal\n"
              << "Preparation Time: " << preparationTime << " min\n"
              << "Ingredients:\n";
    for (const auto& ing : ingredients)
        std::cout << "  - " << ing << "\n";
    std::cout << "Instructions: " << instructions << "\n";
}

// === Clone Recipe ===
std::shared_ptr<Recipe> Recipe::clone() const {
    return std::make_shared<Recipe>(*this);
}
