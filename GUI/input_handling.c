//
//  input_handling.c
//  C7_SmartCalc
//
//  Created by Joramun Sasin on 9/1/22.
//

#include "main-gtk.h"

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
    int ex_code = calculate(output, &result);
    char buffer[100] = {0};
    if (ex_code == 0) {
        sprintf(buffer, "%g", result);
    } else if (ex_code == VARIABLE_INSIDE) {
        char *output_malloced = malloc(strlen(output) + 1);
        strcpy(output_malloced, output);
        add_grid_plot(output_malloced);
        //
//        GtkBuilder *builder = gtk_builder_new();
//        gtk_builder_add_from_file(builder, "./Style/builder-o.ui", NULL);
//        GtkWidget *area = GTK_WIDGET(gtk_builder_get_object(builder, "area"));
//        gtk_drawing_area_set_draw_func(GTK_DRAWING_AREA(area), graph_draw, output_malloced, NULL);
//        GtkWidget *overlay = GTK_WIDGET(gtk_builder_get_object(builder, "overlay"));
//        GtkWidget *gridPlot = GTK_WIDGET(gtk_builder_get_object(builder, "gridPlot"));
//        gtk_overlay_set_child(GTK_OVERLAY(overlay), area);
//        gtk_overlay_add_overlay(GTK_OVERLAY(overlay), gridPlot);
//        g_object_unref(builder);
        //
        free(output_malloced);
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
