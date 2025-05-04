#include "file.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Function to load the command mappings from a file
int loadCommandMappings(const char *filename, CommandMap **map) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file %s\n", filename);
        return -1;  // Return error code if file can't be opened
    }

    int num_mappings = 0;
    char line[MAX_CMD_LEN];
    
    // Count the number of lines (command mappings) in the file
    while (fgets(line, sizeof(line), file)) {
        num_mappings++;
    }

    // Allocate memory for the mapping table
    *map = malloc(num_mappings * sizeof(CommandMap));
    if (*map == NULL) {
        printf("Memory allocation error\n");
        fclose(file);
        return -1;  // Return error if memory allocation fails
    }

    // Rewind the file to the beginning to read the lines
    rewind(file);
    int i = 0;
    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%s %s", (*map)[i].dos_cmd, (*map)[i].linux_cmd) != 2) {
            printf("Error parsing line: %s\n", line);
            free(*map);
            fclose(file);
            return -1;
        }
        i++;
    }

    fclose(file);  // Close the file after reading
    return num_mappings;  // Return the number of mappings loaded
}
