#ifndef QUEUE_H  // Include guard start
#define QUEUE_H  // Define QUEUE_H macro

#include "recipe.h"  // For the Recipe data structure

#define WEEKLY_PLAN_SIZE 7  // Number of days in the weekly plan

// === Structure Definition ===

/**
 * @struct Queue
 * @brief Circular queue structure used for weekly meal planning.
 * @details Each element represents one day of the week.
 */
typedef struct {
    Recipe* recipes[WEEKLY_PLAN_SIZE];  // Array holding recipes (each element represents a day)
    int front;                          // Index of the front element in the queue
    int rear;                           // Index of the rear element in the queue
    int count;                          // Current number of elements in the queue
} Queue;

// === Function Declarations ===

// Creates and initializes an empty queue
Queue* queue_create(void);

// Adds a recipe to the rear of the queue
int queue_enqueue(Queue* queue, Recipe* recipe);

// Removes and returns a recipe from the front of the queue
Recipe* queue_dequeue(Queue* queue);

// Returns the recipe at the front without removing it
Recipe* queue_peek(Queue* queue);

// Checks if the queue is empty
int queue_is_empty(Queue* queue);

// Checks if the queue is full
int queue_is_full(Queue* queue);

// Displays all recipes currently in the queue
void queue_display(Queue* queue);

// Returns the number of elements in the queue
int queue_size(Queue* queue);

// Frees all memory associated with the queue
void queue_destroy(Queue* queue);

// === Binary File Operations ===

// Saves the queue to a binary file
int queue_save_binary(const Queue* queue, const char* filename);

// Loads a queue from a binary file
Queue* queue_load_binary(const char* filename);

#endif // QUEUE_H - Include guard end
