#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>
#include "file.h"
#include "command.h"

CommandMap *map = NULL;
int num_mappings = 0;

void on_execute_clicked(GtkWidget *widget, gpointer data) {
    GtkWidget **entries = (GtkWidget **)data;
    const char *dos_command = gtk_entry_get_text(GTK_ENTRY(entries[0]));
    const char *args = gtk_entry_get_text(GTK_ENTRY(entries[1]));

    if (strlen(dos_command) == 0) {
        gtk_label_set_text(GTK_LABEL(entries[2]), "Error: No command entered.");
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
        gtk_label_set_text(GTK_LABEL(entries[2]), "Error: Command not supported.");
        return;
    }

    // Ensure the concatenated command fits within the buffer
    if (strlen(map[command_index].linux_cmd) + strlen(args) + 1 >= MAX_CMD_LEN) {
        gtk_label_set_text(GTK_LABEL(entries[2]), "Error: Command and arguments are too long.");
        return;
    }

    // Execute the command
    char linux_command[MAX_CMD_LEN];
    snprintf(linux_command, sizeof(linux_command), "%s %s", map[command_index].linux_cmd, args);
    system(linux_command);
    gtk_label_set_text(GTK_LABEL(entries[2]), "Command executed successfully.");
}

void on_manual_clicked(GtkWidget *widget, gpointer label) {
    gtk_label_set_text(GTK_LABEL(label),
        "Manual:\n"
        "dir -> ls\n"
        "copy -> cp\n"
        "del -> rm\n"
        "type -> cat\n"
        "cls -> clear\n"
);
}

void on_exit_clicked(GtkWidget *widget, gpointer data) {
    gtk_main_quit();
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    // Load command mappings
    num_mappings = loadCommandMappings("commands.txt", &map);
    if (num_mappings == -1) {
        printf("Error loading command mappings.\n");
        return 1;
    }

    // Create main window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Shell Simulator");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Create a vertical box layout to center the content
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_widget_set_halign(box, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(box, GTK_ALIGN_CENTER);
    gtk_container_add(GTK_CONTAINER(window), box);

    // Create widgets
    GtkWidget *dos_label = gtk_label_new("DOS Command:");
    GtkWidget *dos_entry = gtk_entry_new();
    GtkWidget *args_label = gtk_label_new("Arguments:");
    GtkWidget *args_entry = gtk_entry_new();
    GtkWidget *execute_button = gtk_button_new_with_label("Execute");
    GtkWidget *manual_button = gtk_button_new_with_label("Manual");
    GtkWidget *exit_button = gtk_button_new_with_label("Exit");
    GtkWidget *output_label = gtk_label_new("");

    // Add widgets to the box layout
    gtk_box_pack_start(GTK_BOX(box), dos_label, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(box), dos_entry, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(box), args_label, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(box), args_entry, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(box), execute_button, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(box), manual_button, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(box), exit_button, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(box), output_label, FALSE, FALSE, 5);

    // Connect signals
    GtkWidget *entries[] = {dos_entry, args_entry, output_label};
    g_signal_connect(execute_button, "clicked", G_CALLBACK(on_execute_clicked), entries);
    g_signal_connect(manual_button, "clicked", G_CALLBACK(on_manual_clicked), output_label);
    g_signal_connect(exit_button, "clicked", G_CALLBACK(on_exit_clicked), NULL);

    // Show all widgets
    gtk_widget_show_all(window);

    // Run the GTK main loop
    gtk_main();

    free(map);
    return 0;
}