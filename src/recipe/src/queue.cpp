/**
 * @file queue.c
 * @brief Circular Queue implementation – FIFO structure for a 7-day weekly meal plan.
 */

#include "queue.h"  // Queue header

 // Creates and initializes an empty queue
Queue* queue_create(void) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    if (queue == NULL) {
        printf("ERROR: Failed to create queue!\n");
        return NULL;
    }
    queue->front = 0;    // First element starts at index 0
    queue->rear = -1;    // No elements yet (-1 = empty)
    queue->count = 0;    // Initially empty
    return queue;
}

// Adds a recipe to the queue (enqueue)
int queue_enqueue(Queue* queue, Recipe* recipe) {
    if (queue == NULL || recipe == NULL) {
        return 0;
    }

    if (queue_is_full(queue)) {
        printf("WARNING: Weekly plan is full (7 days)!\n");
        return 0;
    }

    // Circular logic – increment rear (wrap around after reaching 7)
    queue->rear = (queue->rear + 1) % WEEKLY_PLAN_SIZE;
    queue->recipes[queue->rear] = recipe;
    queue->count++;

    return 1;
}

// Removes a recipe from the queue (dequeue)
Recipe* queue_dequeue(Queue* queue) {
    if (queue == NULL || queue_is_empty(queue)) {
        return NULL;
    }

    Recipe* recipe = queue->recipes[queue->front];  // Get the front recipe
    queue->front = (queue->front + 1) % WEEKLY_PLAN_SIZE;  // Move front forward (circular)
    queue->count--;

    return recipe;
}

// Returns the recipe at the front without removing it (peek)
Recipe* queue_peek(Queue* queue) {
    if (queue == NULL || queue_is_empty(queue)) {
        return NULL;
    }
    return queue->recipes[queue->front];
}

// Checks if the queue is empty
int queue_is_empty(Queue* queue) {
    return (queue == NULL || queue->count == 0);
}

// Checks if the queue is full
int queue_is_full(Queue* queue) {
    return (queue != NULL && queue->count == WEEKLY_PLAN_SIZE);
}

// Displays the 7-day weekly meal plan
void queue_display(Queue* queue) {
    if (queue == NULL) {
        printf("ERROR: Invalid queue!\n");
        return;
    }

    if (queue_is_empty(queue)) {
        printf("\nWeekly meal plan is empty.\n");
        return;
    }

    printf("\n=== 7-DAY WEEKLY MEAL PLAN ===\n");

    // Array of day names
    const char* days[] = {
        "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"
    };

    // Display each recipe in the queue in order
    int index = queue->front;
    for (int i = 0; i < queue->count; i++) {
        printf("\n%s:\n", days[i]);
        printf("  -> %s (%d kcal)\n",
            queue->recipes[index]->name,
            queue->recipes[index]->calories);
        index = (index + 1) % WEEKLY_PLAN_SIZE;
    }
    printf("\n");
}

// Returns the current number of recipes in the queue
int queue_size(Queue* queue) {
    return (queue != NULL) ? queue->count : 0;
}

// Frees all memory used by the queue
void queue_destroy(Queue* queue) {
    if (queue != NULL) {
        free(queue);  // Only free the queue structure (recipes are managed elsewhere)
    }
}
