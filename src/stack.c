/**
 * @file stack.c
 * @brief Stack implementation for undo operations
 * @details LIFO structure used for storing recipe operations
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

/**
 * @brief Creates and initializes an empty stack
 * @return Pointer to the created stack, or NULL on failure
 */
Stack* stack_create(void) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    if (!stack) {
        return NULL;
    }

    stack->top = -1;
    for (int i = 0; i < UNDO_STACK_SIZE; i++) {
        stack->operations[i].type = 0;
        stack->operations[i].recipe = NULL;
    }

    return stack;
}

/**
 * @brief Pushes a new operation onto the stack
 * @param stack Pointer to the stack
 * @param type Operation type
 * @param recipe Pointer to the recipe
 * @return 1 on success, 0 on failure
 */
int stack_push(Stack* stack, OperationType type, Recipe* recipe) {
    if (!stack || !recipe) {
        return 0;
    }

    if (stack_is_full(stack)) {
        // Remove oldest operation (shift all operations)
        for (int i = 0; i < UNDO_STACK_SIZE - 1; i++) {
            stack->operations[i] = stack->operations[i + 1];
        }
        stack->top = UNDO_STACK_SIZE - 2;
    }

    stack->top++;
    stack->operations[stack->top].type = (int)type;
    stack->operations[stack->top].recipe = recipe_copy(recipe);

    return 1;
}

/**
 * @brief Removes and returns the top operation from the stack
 * @param stack Pointer to the stack
 * @return Pointer to the top operation, or NULL if stack is empty
 */
StackOperation* stack_pop(Stack* stack) {
    if (!stack || stack_is_empty(stack)) {
        return NULL;
    }

    static StackOperation result;
    result = stack->operations[stack->top];
    stack->top--;

    return &result;
}

/**
 * @brief Returns the top operation without removing it
 * @param stack Pointer to the stack
 * @return Pointer to the top operation, or NULL if stack is empty
 */
StackOperation* stack_peek(Stack* stack) {
    if (!stack || stack_is_empty(stack)) {
        return NULL;
    }

    return &stack->operations[stack->top];
}

/**
 * @brief Checks if the stack is empty
 * @param stack Pointer to the stack
 * @return 1 if empty, 0 otherwise
 */
int stack_is_empty(Stack* stack) {
    return (stack && stack->top >= 0) ? 0 : 1;
}

/**
 * @brief Checks if the stack is full
 * @param stack Pointer to the stack
 * @return 1 if full, 0 otherwise
 */
int stack_is_full(Stack* stack) {
    return (stack && stack->top >= UNDO_STACK_SIZE - 1) ? 1 : 0;
}

/**
 * @brief Returns the number of elements currently in the stack
 * @param stack Pointer to the stack
 * @return Number of elements
 */
int stack_size(Stack* stack) {
    return (stack && stack->top >= 0) ? stack->top + 1 : 0;
}

/**
 * @brief Frees all memory used by the stack
 * @param stack Pointer to the stack
 */
void stack_destroy(Stack* stack) {
    if (!stack) {
        return;
    }

    // Free all recipe copies
    for (int i = 0; i <= stack->top; i++) {
        if (stack->operations[i].recipe) {
            recipe_destroy(stack->operations[i].recipe);
        }
    }

    free(stack);
}

/**
 * @brief Saves the stack to a binary file
 * @param stack Pointer to the stack
 * @param filename Name of the binary file
 * @return 1 on success, 0 on failure
 */
int stack_save_binary(const Stack* stack, const char* filename) {
    if (!stack || !filename) {
        return 0;
    }

    FILE* file = fopen(filename, "wb");
    if (!file) {
        return 0;
    }

    int size = stack_size(stack);
    if (fwrite(&size, sizeof(int), 1, file) != 1) {
        fclose(file);
        return 0;
    }

    for (int i = 0; i < size; i++) {
        if (fwrite(&stack->operations[i].type, sizeof(int), 1, file) != 1) {
            fclose(file);
            return 0;
        }
        if (stack->operations[i].recipe) {
            if (fwrite(stack->operations[i].recipe, sizeof(Recipe), 1, file) != 1) {
                fclose(file);
                return 0;
            }
        }
    }

    fclose(file);
    return 1;
}

/**
 * @brief Loads a stack from a binary file
 * @param filename Name of the binary file
 * @return Pointer to the loaded stack, or NULL on failure
 */
Stack* stack_load_binary(const char* filename) {
    if (!filename) {
        return NULL;
    }

    FILE* file = fopen(filename, "rb");
    if (!file) {
        return NULL;
    }

    Stack* stack = stack_create();
    if (!stack) {
        fclose(file);
        return NULL;
    }

    int size;
    if (fread(&size, sizeof(int), 1, file) != 1) {
        fclose(file);
        stack_destroy(stack);
        return NULL;
    }

    for (int i = 0; i < size && i < UNDO_STACK_SIZE; i++) {
        int type;
        if (fread(&type, sizeof(int), 1, file) != 1) {
            break;
        }

        Recipe* recipe = (Recipe*)malloc(sizeof(Recipe));
        if (!recipe) {
            break;
        }

        if (fread(recipe, sizeof(Recipe), 1, file) != 1) {
            free(recipe);
            break;
        }

        stack->operations[i].type = type;
        stack->operations[i].recipe = recipe;
        stack->top = i;
    }

    fclose(file);
    return stack;
}

