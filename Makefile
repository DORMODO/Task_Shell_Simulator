# Variables
CC = gcc
CFLAGS = -Iinclude -g `pkg-config --cflags gtk+-3.0`
LDFLAGS = `pkg-config --libs gtk+-3.0`
SRC_CLI = src/main.c src/command.c src/file.c src/manual.c
SRC_GUI = src/gui.c src/command.c src/file.c src/manual.c
OUT_CLI = task_cli
OUT_GUI = task_gui

# Default target (CLI mode)
all: $(OUT_CLI)

# Rule to build the CLI version
$(OUT_CLI): $(SRC_CLI)
	$(CC) $(CFLAGS) $(SRC_CLI) -o $(OUT_CLI)

# Rule to build the GUI version
gui: $(SRC_GUI)
	$(CC) $(CFLAGS) $(SRC_GUI) -o $(OUT_GUI) $(LDFLAGS)

# Clean up build artifacts
clean:
	rm -f $(OUT_CLI) $(OUT_GUI)