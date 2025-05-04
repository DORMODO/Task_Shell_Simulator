#ifndef FILE_H
#define FILE_H

#include "command.h"

// Function declaration to load the command mappings from a file
int loadCommandMappings(const char *filename, CommandMap **map);

#endif
