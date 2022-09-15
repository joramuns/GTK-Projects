//
//  input_handling.c
//  C7_SmartCalc
//
//  Created by Joramun Sasin on 9/1/22.
//

#include "../main-gtk.h"

void add_text(GtkButton *widget, gpointer data) {
    buttonData *current = data;
    GtkEntry *entry = current->entry;
    GtkEntryBuffer *entryBuffer = gtk_entry_get_buffer(entry);
    size_t length_buf = strlen(gtk_entry_buffer_get_text(entryBuffer));
    char *output = (char *) malloc(1 + length_buf + strlen(current->value));
    strcpy(output, gtk_entry_buffer_get_text(entryBuffer));
    strcat(output, current->value);
    gtk_entry_buffer_set_text(entryBuffer, output, strlen(output));
    free(output);
}

void del_text(GtkButton *widget, gpointer data) {
    buttonData *current = data;
    GtkEntry *entry = current->entry;
    GtkEntryBuffer *entryBuffer = gtk_entry_get_buffer(entry);
    size_t length_buf = strlen(gtk_entry_buffer_get_text(entryBuffer));
    char *output = (char *) malloc(1 + length_buf);
    if (length_buf > 0) {
        strcpy(output, gtk_entry_buffer_get_text(entryBuffer));
        output[length_buf - 1] = '\0';
        gtk_entry_buffer_set_text(entryBuffer, output, strlen(output));
    }
    free(output);
}

void get_result(GtkButton *widget, gpointer data) {
    buttonData *current = data;
    GtkEntry *entry = current->entry;
    GtkEntryBuffer *entryBuffer = gtk_entry_get_buffer(entry);
    GtkEntry *entry_res = current->entry_res;
    GtkEntryBuffer *entryBuffer_res = gtk_entry_get_buffer(entry_res);
    double result = 0;
    char *output = (char *)gtk_entry_buffer_get_text(entryBuffer);
    gboolean graph_status = gtk_toggle_button_get_active(current->toggle_button);

    GtkEntryBuffer *dom_min_buff = gtk_entry_get_buffer(current->x_min);
    char *dom_min_val = (char *)gtk_entry_buffer_get_text(dom_min_buff);
    if (strlen(dom_min_val) > 0) {
        sscanf(dom_min_val, "%lf", &x_min);
    }
    GtkEntryBuffer *dom_max_buff = gtk_entry_get_buffer(current->x_max);
    char *dom_max_val = (char *)gtk_entry_buffer_get_text(dom_max_buff);
    if (strlen(dom_max_val) > 0) {
        sscanf(dom_max_val, "%lf", &x_max);
    }
    GtkEntryBuffer *codom_min_buff = gtk_entry_get_buffer(current->y_min);
    char *codom_min_val = (char *)gtk_entry_buffer_get_text(codom_min_buff);
    if (strlen(codom_min_val) > 0) {
        sscanf(codom_min_val, "%lf", &y_min);
    }
    GtkEntryBuffer *codom_max_buff = gtk_entry_get_buffer(current->y_max);
    char *codom_max_val = (char *)gtk_entry_buffer_get_text(codom_max_buff);
    if (strlen(codom_max_val) > 0) {
        sscanf(codom_max_val, "%lf", &y_max);
    }

    int ex_code = calculate(output, &result);
    char buffer[100] = {0};
    if (ex_code == 0) {
        sprintf(buffer, "%g", result);
    } else if (ex_code == VARIABLE_INSIDE && (graph_status == 1) && (ex_code = calculate_var(output, &result, 1)) == 0) {
        gtk_drawing_area_set_draw_func(GTK_DRAWING_AREA(current->area), graph_draw, output, NULL);
        sprintf(buffer, "Graph");
    } else if (ex_code == VARIABLE_INSIDE && (graph_status == 0)) {
        ex_code = calculate_var(output, &result, x_min);
        if (ex_code == 0) {
            sprintf(buffer, "%g", result);
        } else {
            sprintf(buffer, "Error: %d", ex_code);
        }
    } else {
        sprintf(buffer, "Error: %d", ex_code);
    }
    gtk_entry_buffer_set_text(entryBuffer_res, buffer, strlen(buffer));
}

void set_zero(GtkButton *widget, gpointer data) {
    buttonData *current = data;
    GtkEntry *entry = current->entry;
    GtkEntryBuffer *entryBuffer = gtk_entry_get_buffer(entry);
    gtk_entry_buffer_set_text(entryBuffer, "", 0);
    entry = current->entry_res;
    entryBuffer = gtk_entry_get_buffer(entry);
    gtk_entry_buffer_set_text(entryBuffer, "", 0);
}
