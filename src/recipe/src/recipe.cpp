/**
 * @file recipe.cpp
 * @brief Recipe class implementation (C++ version)
 * @details Represents a single recipe with ingredients, instructions,
 *          and nutrition data (calories, prep time, etc.).
 */

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>

constexpr int MAX_INGREDIENTS = 20;

class Recipe {
public:
    int id{};
    std::string name;
    std::string category;
    int calories{};
    int preparation_time{};
    std::vector<std::string> ingredients;
    std::string instructions;

    // === Constructors ===
    Recipe() = default;
    Recipe(int id_, std::string name_, std::string category_, int cal, int prep)
        : id(id_), name(std::move(name_)), category(std::move(category_)),
          calories(cal), preparation_time(prep) {}

    // === Deep Copy ===
    std::shared_ptr<Recipe> clone() const {
        auto copy = std::make_shared<Recipe>(*this);
        return copy;
    }

    // === Add Ingredient ===
    bool addIngredient(const std::string& ingredient) {
        if (ingredients.size() >= MAX_INGREDIENTS) return false;
        ingredients.push_back(ingredient);
        return true;
    }

    // === Set Instructions ===
    void setInstructions(const std::string& text) {
        instructions = text;
    }

    // === Display Recipe ===
    void display() const {
        std::cout << "Recipe #" << id << ": " << name << "\n"
                  << "Category: " << category << "\n"
                  << "Calories: " << calories << " kcal\n"
                  << "Preparation Time: " << preparation_time << " min\n"
                  << "Ingredients:\n";
        for (const auto& ing : ingredients)
            std::cout << "  - " << ing << "\n";
        std::cout << "Instructions: " << instructions << "\n";
    }

    // === Static Comparator (for sorting) ===
    static int compareByCalories(const std::shared_ptr<Recipe>& a,
                                 const std::shared_ptr<Recipe>& b) {
        if (!a && !b) return 0;
        if (!a) return -1;
        if (!b) return 1;
        return a->calories - b->calories;
    }
};
