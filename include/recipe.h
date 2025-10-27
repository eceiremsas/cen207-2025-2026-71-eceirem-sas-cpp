#ifndef RECIPE_H
#define RECIPE_H

#include <stdio.h>
#include <stdlib.h>

#define MAX_NAME_LENGTH 100
#define MAX_CATEGORY_LENGTH 50
#define MAX_INGREDIENTS 50
#define MAX_INGREDIENT_LENGTH 50
#define MAX_INSTRUCTIONS 500

typedef struct {
    int id;
    char name[MAX_NAME_LENGTH];
    char category[MAX_CATEGORY_LENGTH];
    int calories;
    int preparation_time;
    char ingredients[MAX_INGREDIENTS][MAX_INGREDIENT_LENGTH];
    int ingredient_count;
    char instructions[MAX_INSTRUCTIONS];
} Recipe;

// Fonksiyon bildirimleri
Recipe* recipe_create(int id, const char* name, const char* category, int calories, int preparation_time);
int recipe_add_ingredient(Recipe* recipe, const char* ingredient);
void recipe_set_instructions(Recipe* recipe, const char* instructions);
void recipe_display(const Recipe* recipe);
Recipe* recipe_copy(const Recipe* recipe);
void recipe_destroy(Recipe* recipe);
int recipe_compare_by_id(const Recipe* recipe1, const Recipe* recipe2);
int recipe_compare_by_calories(const Recipe* recipe1, const Recipe* recipe2);

#endif
