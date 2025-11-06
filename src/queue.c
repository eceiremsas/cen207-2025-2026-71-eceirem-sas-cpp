/**
 * @file queue.c
 * @brief Circular Queue implementation for weekly meal planning
 * @details FIFO structure for managing a 7-day weekly meal plan
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

/**
 * @brief Creates and initializes an empty queue
 * @return Pointer to the created queue, or NULL on failure
 */
Queue* queue_create(void) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    if (!queue) {
        return NULL;
    }

    queue->front = 0;
    queue->rear = -1;
    queue->count = 0;
    
    for (int i = 0; i < WEEKLY_PLAN_SIZE; i++) {
        queue->recipes[i] = NULL;
    }

    return queue;
}

/**
 * @brief Adds a recipe to the rear of the queue
 * @param queue Pointer to the queue
 * @param recipe Pointer to the recipe to add
 * @return 1 on success, 0 on failure
 */
int queue_enqueue(Queue* queue, Recipe* recipe) {
    if (!queue || !recipe) {
        return 0;
    }

    if (queue_is_full(queue)) {
        return 0;
    }

    queue->rear = (queue->rear + 1) % WEEKLY_PLAN_SIZE;
    queue->recipes[queue->rear] = recipe;
    queue->count++;

    return 1;
}

/**
 * @brief Removes and returns a recipe from the front of the queue
 * @param queue Pointer to the queue
 * @return Pointer to the removed recipe, or NULL if queue is empty
 */
Recipe* queue_dequeue(Queue* queue) {
    if (!queue || queue_is_empty(queue)) {
        return NULL;
    }

    Recipe* recipe = queue->recipes[queue->front];
    queue->front = (queue->front + 1) % WEEKLY_PLAN_SIZE;
    queue->count--;

    return recipe;
}

/**
 * @brief Returns the recipe at the front without removing it
 * @param queue Pointer to the queue
 * @return Pointer to the front recipe, or NULL if queue is empty
 */
Recipe* queue_peek(Queue* queue) {
    if (!queue || queue_is_empty(queue)) {
        return NULL;
    }

    return queue->recipes[queue->front];
}

/**
 * @brief Checks if the queue is empty
 * @param queue Pointer to the queue
 * @return 1 if empty, 0 otherwise
 */
int queue_is_empty(Queue* queue) {
    return (queue && queue->count > 0) ? 0 : 1;
}

/**
 * @brief Checks if the queue is full
 * @param queue Pointer to the queue
 * @return 1 if full, 0 otherwise
 */
int queue_is_full(Queue* queue) {
    return (queue && queue->count >= WEEKLY_PLAN_SIZE) ? 1 : 0;
}

/**
 * @brief Displays all recipes currently in the queue
 * @param queue Pointer to the queue
 */
void queue_display(Queue* queue) {
    if (!queue) {
        printf("Queue pointer is NULL.\n");
        return;
    }

    if (queue_is_empty(queue)) {
        printf("\nWeekly meal plan is empty.\n");
        return;
    }

    printf("\n=== 7-DAY WEEKLY MEAL PLAN ===\n");
    const char* days[] = {
        "Monday", "Tuesday", "Wednesday", "Thursday", 
        "Friday", "Saturday", "Sunday"
    };

    int index = queue->front;
    for (int i = 0; i < queue->count; i++) {
        printf("\n%s:\n", days[i]);
        if (queue->recipes[index]) {
            printf("  -> %s (%d kcal)\n",
                   queue->recipes[index]->name,
                   queue->recipes[index]->calories);
        }
        index = (index + 1) % WEEKLY_PLAN_SIZE;
    }
    printf("\n");
}

/**
 * @brief Returns the number of elements in the queue
 * @param queue Pointer to the queue
 * @return Number of elements
 */
int queue_size(Queue* queue) {
    return (queue) ? queue->count : 0;
}

/**
 * @brief Frees all memory associated with the queue
 * @param queue Pointer to the queue
 */
void queue_destroy(Queue* queue) {
    if (queue) {
        free(queue);
    }
}

/**
 * @brief Saves the queue to a binary file
 * @param queue Pointer to the queue
 * @param filename Name of the binary file
 * @return 1 on success, 0 on failure
 */
int queue_save_binary(const Queue* queue, const char* filename) {
    if (!queue || !filename) {
        return 0;
    }

    FILE* file = fopen(filename, "wb");
    if (!file) {
        return 0;
    }

    if (fwrite(&queue->front, sizeof(int), 1, file) != 1) {
        fclose(file);
        return 0;
    }
    if (fwrite(&queue->rear, sizeof(int), 1, file) != 1) {
        fclose(file);
        return 0;
    }
    if (fwrite(&queue->count, sizeof(int), 1, file) != 1) {
        fclose(file);
        return 0;
    }

    int index = queue->front;
    for (int i = 0; i < queue->count; i++) {
        if (queue->recipes[index]) {
            if (fwrite(queue->recipes[index], sizeof(Recipe), 1, file) != 1) {
                fclose(file);
                return 0;
            }
        }
        index = (index + 1) % WEEKLY_PLAN_SIZE;
    }

    fclose(file);
    return 1;
}

/**
 * @brief Loads a queue from a binary file
 * @param filename Name of the binary file
 * @return Pointer to the loaded queue, or NULL on failure
 */
Queue* queue_load_binary(const char* filename) {
    if (!filename) {
        return NULL;
    }

    FILE* file = fopen(filename, "rb");
    if (!file) {
        return NULL;
    }

    Queue* queue = queue_create();
    if (!queue) {
        fclose(file);
        return NULL;
    }

    if (fread(&queue->front, sizeof(int), 1, file) != 1) {
        fclose(file);
        queue_destroy(queue);
        return NULL;
    }
    if (fread(&queue->rear, sizeof(int), 1, file) != 1) {
        fclose(file);
        queue_destroy(queue);
        return NULL;
    }
    if (fread(&queue->count, sizeof(int), 1, file) != 1) {
        fclose(file);
        queue_destroy(queue);
        return NULL;
    }

    int index = queue->front;
    for (int i = 0; i < queue->count; i++) {
        Recipe* recipe = (Recipe*)malloc(sizeof(Recipe));
        if (!recipe) {
            break;
        }
        if (fread(recipe, sizeof(Recipe), 1, file) != 1) {
            free(recipe);
            break;
        }
        queue->recipes[index] = recipe;
        index = (index + 1) % WEEKLY_PLAN_SIZE;
    }

    fclose(file);
    return queue;
}

