#ifndef RECIPE_H
#define RECIPE_H

#include <stdio.h>
#include <stdlib.h>

#define MAX_NAME_LENGTH 100
#define MAX_CATEGORY_LENGTH 50
#define MAX_INGREDIENTS 50
#define MAX_INGREDIENT_LENGTH 50
#define MAX_INSTRUCTIONS 500

// === Structure Definition ===

/**
 * @struct Recipe
 * @brief Represents a recipe with its properties and related data.
 * @details Each recipe contains a unique ID, name, category, calorie count,
 *          preparation time, a list of ingredients, and preparation instructions.
 */
typedef struct {
    int id;                                         // Unique recipe ID
    char name[MAX_NAME_LENGTH];                     // Recipe name
    char category[MAX_CATEGORY_LENGTH];             // Recipe category (e.g., "Dessert", "Main Course")
    int calories;                                   // Calorie count
    int preparation_time;                           // Preparation time in minutes
    char ingredients[MAX_INGREDIENTS][MAX_INGREDIENT_LENGTH];  // Array of ingredient names
    int ingredient_count;                           // Number of ingredients
    char instructions[MAX_INSTRUCTIONS];            // Cooking instructions
} Recipe;

// === Function Declarations ===

// Creates and initializes a new recipe
Recipe* recipe_create(int id, const char* name, const char* category, int calories, int preparation_time);

// Adds an ingredient to the recipe
int recipe_add_ingredient(Recipe* recipe, const char* ingredient);

// Sets the preparation instructions for the recipe
void recipe_set_instructions(Recipe* recipe, const char* instructions);

// Displays all details of the recipe
void recipe_display(const Recipe* recipe);

// Creates and returns a deep copy of a recipe
Recipe* recipe_copy(const Recipe* recipe);

// Frees all memory associated with a recipe
void recipe_destroy(Recipe* recipe);

// Compares two recipes by their IDs
int recipe_compare_by_id(const Recipe* recipe1, const Recipe* recipe2);

// Compares two recipes by their calorie values
int recipe_compare_by_calories(const Recipe* recipe1, const Recipe* recipe2);

// === Binary File Operations ===

// Saves a recipe to a binary file
int recipe_save_binary(const Recipe* recipe, const char* filename);

// Loads a recipe from a binary file
Recipe* recipe_load_binary(const char* filename);

// Saves multiple recipes to a binary file
int recipe_save_array_binary(const Recipe* recipes, int count, const char* filename);

// Loads multiple recipes from a binary file
Recipe* recipe_load_array_binary(const char* filename, int* count);

#endif // RECIPE_H
