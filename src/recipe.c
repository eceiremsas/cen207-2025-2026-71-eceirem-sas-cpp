#include "recipe.h"
#include <stdlib.h>
#include <string.h>

Recipe* recipe_copy(const Recipe* original) {
    if (!original) return NULL;

    Recipe* copy = (Recipe*)malloc(sizeof(Recipe));
    if (!copy) return NULL;

    // Tüm alanları kopyala
    copy->id = original->id;
    strncpy(copy->name, original->name, MAX_NAME_LENGTH);
    strncpy(copy->category, original->category, MAX_CATEGORY_LENGTH);
    copy->calories = original->calories;
    copy->preparation_time = original->preparation_time;

    // Malzemeleri kopyala
    copy->ingredient_count = original->ingredient_count;
    for (int i = 0; i < original->ingredient_count; i++) {
        strncpy(copy->ingredients[i], original->ingredients[i], MAX_INGREDIENT_LENGTH);
    }

    // Talimatları kopyala
    strncpy(copy->instructions, original->instructions, MAX_INSTRUCTIONS);

    return copy;
}
Recipe* recipe_create(int id, const char* name, const char* category, int calories, int preparation_time) {
    Recipe* recipe = (Recipe*)malloc(sizeof(Recipe));
    if (recipe == NULL) return NULL;

    recipe->id = id;
    strncpy(recipe->name, name, MAX_NAME_LENGTH);
    strncpy(recipe->category, category, MAX_CATEGORY_LENGTH);
    recipe->calories = calories;
    recipe->preparation_time = preparation_time;
    recipe->ingredient_count = 0;
    strcpy(recipe->instructions, "");
    return recipe;
}

void recipe_destroy(Recipe* recipe) {
    if (recipe != NULL)
        free(recipe);
}

void recipe_add_ingredient(Recipe* recipe, const char* ingredient) {
    if (recipe->ingredient_count < MAX_INGREDIENTS) {
        strncpy(recipe->ingredients[recipe->ingredient_count++], ingredient, MAX_INGREDIENT_LENGTH);
    }
}

void recipe_set_instructions(Recipe* recipe, const char* instructions) {
    strncpy(recipe->instructions, instructions, MAX_INSTRUCTIONS);
}

void recipe_display(Recipe* recipe) {
    if (recipe == NULL) return;
    printf("Tarif #%d: %s\n", recipe->id, recipe->name);
    printf("Kategori: %s\n", recipe->category);
    printf("Kalori: %d kcal\n", recipe->calories);
    printf("Hazırlık Süresi: %d dk\n", recipe->preparation_time);
    printf("Malzemeler:\n");
    for (int i = 0; i < recipe->ingredient_count; i++)
        printf("  - %s\n", recipe->ingredients[i]);
    printf("Talimatlar: %s\n", recipe->instructions);
}

int recipe_compare_by_calories(const Recipe* a, const Recipe* b) {
    return a->calories - b->calories;
}
