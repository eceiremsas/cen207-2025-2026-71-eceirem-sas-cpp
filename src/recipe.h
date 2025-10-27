#ifndef RECIPE_H
#define RECIPE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define MAX_CATEGORY_LENGTH 30
#define MAX_INGREDIENTS 20
#define MAX_INGREDIENT_LENGTH 40
#define MAX_INSTRUCTIONS 200

typedef struct {
    int id;
    char name[MAX_NAME_LENGTH];
    char category[MAX_CATEGORY_LENGTH];
    int calories;
    int preparation_time;
    int ingredient_count;
    char ingredients[MAX_INGREDIENTS][MAX_INGREDIENT_LENGTH];
    char instructions[MAX_INSTRUCTIONS];
} Recipe;

// Fonksiyon bildirimi
Recipe* recipe_create(int id, const char* name, const char* category, int calories, int preparation_time);
void recipe_destroy(Recipe* recipe);
void recipe_display(Recipe* recipe);
void recipe_add_ingredient(Recipe* recipe, const char* ingredient);
void recipe_set_instructions(Recipe* recipe, const char* instructions);
int recipe_compare_by_calories(const Recipe* a, const Recipe* b);

#endif
