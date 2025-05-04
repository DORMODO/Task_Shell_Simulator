#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"
#include "manual.h"
#include "command.h"

// Function to display the menu
void displayMenu() {
    printf("\nShell Simulator Menu:\n");
    printf("1. Execute DOS command\n");
    printf("2. View Manual\n");
    printf("3. Exit\n");
    printf("Enter your choice: ");
}


int main() {
    CommandMap *map = NULL;
    int num_mappings = loadCommandMappings("commands.txt", &map);
    if (num_mappings == -1) {
        return 1; // Exit if loading fails
    }

    int choice;
    while (1) {
        displayMenu();

        // Validate menu input
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n'); // Clear invalid input
            continue;
        }
        getchar(); // Consume leftover newline

        if (choice == 1) {
            executeCommand(map, num_mappings);
        } else if (choice == 2) {
            displayManual();
        } else if (choice == 3) {
            break;
        } else {
            printf("Invalid choice. Please try again.\n");
        }
    }

    free(map);
    return 0;
}
