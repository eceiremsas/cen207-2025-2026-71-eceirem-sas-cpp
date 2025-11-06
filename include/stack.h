#ifndef STACK_H  // Include guard start
#define STACK_H  // Define STACK_H macro

#include "recipe.h"  // For the Recipe data structure

#define UNDO_STACK_SIZE 50  // Maximum number of undo operations stored in the stack

// === Enum Definitions ===

/**
 * @enum OperationType
 * @brief Represents the type of operation stored in the undo stack.
 */
typedef enum {
    OP_ADD,     // Recipe addition operation
    OP_EDIT,    // Recipe editing operation
    OP_DELETE   // Recipe deletion operation
} OperationType;

// === Structure Definitions ===

/**
 * @struct StackOperation
 * @brief Represents a single operation stored in the undo stack.
 * @details Each operation records its type and the related recipe.
 */
typedef struct {
    int type;          // Operation type (e.g., OP_ADD, OP_EDIT, OP_DELETE)
    Recipe* recipe;    // Pointer to the recipe affected by the operation
} StackOperation;

/**
 * @struct Stack
 * @brief Represents a fixed-size stack used for undo operations.
 * @details Stores a list of recent recipe operations.
 */
typedef struct {
    StackOperation operations[UNDO_STACK_SIZE];  // Array holding stored operations
    int top;                                     // Index of the top element (-1 if stack is empty)
} Stack;

// === Function Declarations ===

// Creates and initializes an empty stack
Stack* stack_create(void);

// Pushes a new operation onto the stack
int stack_push(Stack* stack, OperationType type, Recipe* recipe);

// Removes and returns the top operation from the stack
StackOperation* stack_pop(Stack* stack);

// Returns the top operation without removing it
StackOperation* stack_peek(Stack* stack);

// Checks if the stack is empty
int stack_is_empty(Stack* stack);

// Checks if the stack is full
int stack_is_full(Stack* stack);

// Returns the number of elements currently in the stack
int stack_size(Stack* stack);

// Frees all memory used by the stack
void stack_destroy(Stack* stack);

// === Binary File Operations ===

// Saves the stack to a binary file
int stack_save_binary(const Stack* stack, const char* filename);

// Loads a stack from a binary file
Stack* stack_load_binary(const char* filename);

#endif // STACK_H - Include guard end
