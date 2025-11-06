/**
 * @file recipe.hpp
 * @brief Represents a Recipe entity in the Recipe & Nutrition Tracker (C++ version)
 * @details Each recipe contains a unique ID, name, category, calorie count,
 *          preparation time, ingredients, and preparation instructions.
 */

#ifndef RECIPE_HPP
#define RECIPE_HPP

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>

 /**
  * @class Recipe
  * @brief Encapsulates all information related to a single recipe.
  */
class Recipe {
private:
    int id;                           ///< Unique recipe ID
    std::string name;                 ///< Recipe name
    std::string category;             ///< Recipe category (e.g., "Dessert", "Main Course")
    int calories;                     ///< Calorie count
    int preparationTime;              ///< Preparation time in minutes
    std::vector<std::string> ingredients; ///< List of ingredients
    std::string instructions;         ///< Cooking instructions

public:
    // === Constructors & Destructor ===
    Recipe() = default;
    Recipe(int id, std::string name, std::string category, int calories, int prepTime);
    ~Recipe() = default;

    // === Getters ===
    int getId() const { return id; }
    const std::string& getName() const { return name; }
    const std::string& getCategory() const { return category; }
    int getCalories() const { return calories; }
    int getPreparationTime() const { return preparationTime; }
    const std::vector<std::string>& getIngredients() const { return ingredients; }
    const std::string& getInstructions() const { return instructions; }

    // === Setters ===
    void setName(const std::string& n) { name = n; }
    void setCategory(const std::string& c) { category = c; }
    void setCalories(int c) { calories = c; }
    void setPreparationTime(int t) { preparationTime = t; }
    void setInstructions(const std::string& instr) { instructions = instr; }

    // === Functional Methods ===

    /**
     * @brief Adds an ingredient to the recipe.
     * @param ingredient Ingredient name to add.
     */
    void addIngredient(const std::string& ingredient);

    /**
     * @brief Displays all recipe information to the console.
     */
    void display() const;

    /**
     * @brief Creates a deep copy of the current recipe.
     * @return std::shared_ptr<Recipe> pointing to the cloned recipe.
     */
    std::shared_ptr<Recipe> clone() const;

    // === Comparison Operators ===
    bool operator<(const Recipe& other) const { return calories < other.calories; }
    bool operator>(const Recipe& other) const { return calories > other.calories; }
    bool operator==(const Recipe& other) const { return id == other.id; }
};

#endif // RECIPE_HPP
