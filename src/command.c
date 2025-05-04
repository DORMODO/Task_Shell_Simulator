#include "command.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void executeCommand(CommandMap *map, int num_mappings) {
    char dos_command[MAX_CMD_LEN], args[MAX_CMD_LEN];

    printf("Enter DOS command: ");
    fgets(dos_command, MAX_CMD_LEN, stdin);
    dos_command[strcspn(dos_command, "\n")] = 0; // Remove newline

    // Check if the command is empty
    if (strlen(dos_command) == 0) {
        printf("Error: No command entered. Please try again.\n");
        return;
    }

    // Check if the command exists in the mapping table
    int command_found = 0;
    int command_index = -1;
    for (int i = 0; i < num_mappings; i++) {
        if (strcmp(dos_command, map[i].dos_cmd) == 0) {
            command_found = 1;
            command_index = i;
            break;
        }
    }

    if (!command_found) {
        printf("Error: Command '%s' is not supported.\n", dos_command);
        return;
    }

    // Prompt for arguments only if the command is valid
    printf("Enter arguments (if any): ");
    fgets(args, MAX_CMD_LEN, stdin);
    args[strcspn(args, "\n")] = 0;

    // Ensure the concatenated command fits within the buffer
    if (strlen(map[command_index].linux_cmd) + strlen(args) + 1 >= MAX_CMD_LEN) {
        printf("Error: Command and arguments are too long to execute.\n");
        return;
    }

    // Execute the command
    char linux_command[MAX_CMD_LEN];
    snprintf(linux_command, sizeof(linux_command), "%s %s", map[command_index].linux_cmd, args);
    printf("Executing Linux command: %s\n", linux_command); // Confirmation message
    system(linux_command);
}
