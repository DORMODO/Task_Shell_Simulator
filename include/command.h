#ifndef COMMAND_H
#define COMMAND_H

#define MAX_CMD_LEN 256

// Structure to hold the DOS and Linux command mapping
typedef struct {
    char dos_cmd[MAX_CMD_LEN];
    char linux_cmd[MAX_CMD_LEN];
} CommandMap;

// Function declarations
void executeCommand(CommandMap *map, int num_mappings);

#endif
