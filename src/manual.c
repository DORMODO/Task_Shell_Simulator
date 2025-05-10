#include "manual.h"
#include <stdio.h>

void displayManual() {
    printf("\nManual for Task Shell Simulator:\n");
    printf("This program maps DOS commands to Linux commands.\n");
    printf("Supported Commands:\n");
    printf("  dir  -> ls\n");
    printf("  copy -> cp\n");
    printf("  del  -> rm\n");
    printf("  type -> cat\n");
    printf("  cls  -> clear\n");
}
