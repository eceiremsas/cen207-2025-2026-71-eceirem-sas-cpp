/**
 * @file recipe.c
 * @brief Recipe data structure implementation
 * @details Manages recipe data including ingredients, instructions, and nutrition information
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "recipe.h"

/**
 * @brief Creates and initializes a new recipe
 * @param id Unique recipe identifier
 * @param name Recipe name
 * @param category Recipe category
 * @param calories Calorie count
 * @param preparation_time Preparation time in minutes
 * @return Pointer to the created recipe, or NULL on failure
 */
Recipe* recipe_create(int id, const char* name, const char* category, int calories, int preparation_time) {
    if (!name || !category) {
        return NULL;
    }

    Recipe* recipe = (Recipe*)malloc(sizeof(Recipe));
    if (!recipe) {
        return NULL;
    }

    recipe->id = id;
    strncpy(recipe->name, name, MAX_NAME_LENGTH - 1);
    recipe->name[MAX_NAME_LENGTH - 1] = '\0';
    
    strncpy(recipe->category, category, MAX_CATEGORY_LENGTH - 1);
    recipe->category[MAX_CATEGORY_LENGTH - 1] = '\0';
    
    recipe->calories = calories;
    recipe->preparation_time = preparation_time;
    recipe->ingredient_count = 0;
    recipe->instructions[0] = '\0';

    return recipe;
}

/**
 * @brief Adds an ingredient to the recipe
 * @param recipe Pointer to the recipe
 * @param ingredient Ingredient name to add
 * @return 1 on success, 0 on failure
 */
int recipe_add_ingredient(Recipe* recipe, const char* ingredient) {
    if (!recipe || !ingredient) {
        return 0;
    }

    if (recipe->ingredient_count >= MAX_INGREDIENTS) {
        return 0;
    }

    strncpy(recipe->ingredients[recipe->ingredient_count], ingredient, MAX_INGREDIENT_LENGTH - 1);
    recipe->ingredients[recipe->ingredient_count][MAX_INGREDIENT_LENGTH - 1] = '\0';
    recipe->ingredient_count++;

    return 1;
}

/**
 * @brief Sets the preparation instructions for the recipe
 * @param recipe Pointer to the recipe
 * @param instructions Instruction text
 */
void recipe_set_instructions(Recipe* recipe, const char* instructions) {
    if (!recipe || !instructions) {
        return;
    }

    strncpy(recipe->instructions, instructions, MAX_INSTRUCTIONS - 1);
    recipe->instructions[MAX_INSTRUCTIONS - 1] = '\0';
}

/**
 * @brief Displays all details of the recipe
 * @param recipe Pointer to the recipe to display
 */
void recipe_display(const Recipe* recipe) {
    if (!recipe) {
        printf("Recipe pointer is NULL.\n");
        return;
    }

    printf("\n=== Recipe #%d ===\n", recipe->id);
    printf("Name: %s\n", recipe->name);
    printf("Category: %s\n", recipe->category);
    printf("Calories: %d kcal\n", recipe->calories);
    printf("Preparation Time: %d minutes\n", recipe->preparation_time);
    printf("Ingredients (%d):\n", recipe->ingredient_count);
    
    for (int i = 0; i < recipe->ingredient_count; i++) {
        printf("  - %s\n", recipe->ingredients[i]);
    }
    
    printf("Instructions: %s\n", recipe->instructions);
}

/**
 * @brief Creates and returns a deep copy of a recipe
 * @param recipe Pointer to the recipe to copy
 * @return Pointer to the copied recipe, or NULL on failure
 */
Recipe* recipe_copy(const Recipe* recipe) {
    if (!recipe) {
        return NULL;
    }

    Recipe* copy = recipe_create(recipe->id, recipe->name, recipe->category,
                                recipe->calories, recipe->preparation_time);
    if (!copy) {
        return NULL;
    }

    copy->ingredient_count = recipe->ingredient_count;
    for (int i = 0; i < recipe->ingredient_count; i++) {
        strncpy(copy->ingredients[i], recipe->ingredients[i], MAX_INGREDIENT_LENGTH - 1);
        copy->ingredients[i][MAX_INGREDIENT_LENGTH - 1] = '\0';
    }

    strncpy(copy->instructions, recipe->instructions, MAX_INSTRUCTIONS - 1);
    copy->instructions[MAX_INSTRUCTIONS - 1] = '\0';

    return copy;
}

/**
 * @brief Frees all memory associated with a recipe
 * @param recipe Pointer to the recipe to destroy
 */
void recipe_destroy(Recipe* recipe) {
    if (recipe) {
        free(recipe);
    }
}

/**
 * @brief Compares two recipes by their IDs
 * @param recipe1 First recipe
 * @param recipe2 Second recipe
 * @return Negative if recipe1 < recipe2, positive if recipe1 > recipe2, 0 if equal
 */
int recipe_compare_by_id(const Recipe* recipe1, const Recipe* recipe2) {
    if (!recipe1 && !recipe2) return 0;
    if (!recipe1) return -1;
    if (!recipe2) return 1;
    return recipe1->id - recipe2->id;
}

/**
 * @brief Compares two recipes by their calorie values
 * @param recipe1 First recipe
 * @param recipe2 Second recipe
 * @return Negative if recipe1 < recipe2, positive if recipe1 > recipe2, 0 if equal
 */
int recipe_compare_by_calories(const Recipe* recipe1, const Recipe* recipe2) {
    if (!recipe1 && !recipe2) return 0;
    if (!recipe1) return -1;
    if (!recipe2) return 1;
    return recipe1->calories - recipe2->calories;
}

/**
 * @brief Saves a recipe to a binary file
 * @param recipe Pointer to the recipe to save
 * @param filename Name of the binary file
 * @return 1 on success, 0 on failure
 */
int recipe_save_binary(const Recipe* recipe, const char* filename) {
    if (!recipe || !filename) {
        return 0;
    }

    FILE* file = fopen(filename, "wb");
    if (!file) {
        return 0;
    }

    size_t written = fwrite(recipe, sizeof(Recipe), 1, file);
    fclose(file);

    return (written == 1) ? 1 : 0;
}

/**
 * @brief Loads a recipe from a binary file
 * @param filename Name of the binary file
 * @return Pointer to the loaded recipe, or NULL on failure
 */
Recipe* recipe_load_binary(const char* filename) {
    if (!filename) {
        return NULL;
    }

    FILE* file = fopen(filename, "rb");
    if (!file) {
        return NULL;
    }

    Recipe* recipe = (Recipe*)malloc(sizeof(Recipe));
    if (!recipe) {
        fclose(file);
        return NULL;
    }

    size_t read = fread(recipe, sizeof(Recipe), 1, file);
    fclose(file);

    if (read != 1) {
        free(recipe);
        return NULL;
    }

    return recipe;
}

/**
 * @brief Saves multiple recipes to a binary file
 * @param recipes Array of recipe pointers
 * @param count Number of recipes
 * @param filename Name of the binary file
 * @return 1 on success, 0 on failure
 */
int recipe_save_array_binary(const Recipe* recipes, int count, const char* filename) {
    if (!recipes || count <= 0 || !filename) {
        return 0;
    }

    FILE* file = fopen(filename, "wb");
    if (!file) {
        return 0;
    }

    // Write count first
    if (fwrite(&count, sizeof(int), 1, file) != 1) {
        fclose(file);
        return 0;
    }

    // Write all recipes
    size_t written = fwrite(recipes, sizeof(Recipe), count, file);
    fclose(file);

    return (written == count) ? 1 : 0;
}

/**
 * @brief Loads multiple recipes from a binary file
 * @param filename Name of the binary file
 * @param count Pointer to store the number of recipes loaded
 * @return Pointer to array of loaded recipes, or NULL on failure
 */
Recipe* recipe_load_array_binary(const char* filename, int* count) {
    if (!filename || !count) {
        return NULL;
    }

    FILE* file = fopen(filename, "rb");
    if (!file) {
        return NULL;
    }

    // Read count first
    if (fread(count, sizeof(int), 1, file) != 1) {
        fclose(file);
        return NULL;
    }

    if (*count <= 0) {
        fclose(file);
        return NULL;
    }

    Recipe* recipes = (Recipe*)malloc(sizeof(Recipe) * (*count));
    if (!recipes) {
        fclose(file);
        return NULL;
    }

    size_t read = fread(recipes, sizeof(Recipe), *count, file);
    fclose(file);

    if (read != *count) {
        free(recipes);
        return NULL;
    }

    return recipes;
}

