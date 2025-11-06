/**
 * @file main.c
 * @brief Main entry point for Recipe and Nutrition Tracker
 * @details Console-based application for managing recipes and nutrition data
 */

#include <stdio.h>
#include <stdlib.h>
#include "menu.h"

/**
 * @brief Main function
 * @return Exit status
 */
int main(void) {
    printf("\n=== RECIPE AND NUTRITION TRACKER ===\n");
    printf("Data Structures and Algorithms Project\n\n");

    AppContext* ctx = app_context_create();
    if (!ctx) {
        printf("ERROR: Failed to create application context!\n");
        return EXIT_FAILURE;
    }

    menu_load_sample_data(ctx);

    int choice = -1;
    while (choice != 0) {
        clear_console();
        menu_display();
        choice = safe_int_input();
        menu_handle_choice(ctx, choice);
        if (choice != 0) {
            wait_for_enter();
        }
    }

    app_context_destroy(ctx);
    printf("\nThank you for using the program!\n");
    return EXIT_SUCCESS;
}

