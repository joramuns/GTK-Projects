//
//  2main.c
//  C7_SmartCalc
//
//  Created by Joramun Sasin on 8/18/22.
//

#include <stdio.h>
#include <gtk/gtk.h>
#include <string.h>
#include "main-gtk.h"

void quit_cb (GtkWindow *window)
{
  gtk_window_close (window);
}

void add_text(GtkButton *widget, gpointer data) {
    buttonData *current = data;
    GtkText *entry = current->entry;
    GtkEntryBuffer *entryBuffer = gtk_text_get_buffer(entry);
    size_t length_buf = strlen(gtk_entry_buffer_get_text(entryBuffer));
    char *output = (char *) malloc(1 + length_buf + strlen(current->value));
    strcpy(output, gtk_entry_buffer_get_text(entryBuffer));
    strcat(output, current->value);
    gtk_entry_buffer_set_text(entryBuffer, output, strlen(output));
    free(output);
}

void del_text(GtkButton *widget, gpointer data) {
    buttonData *current = data;
    GtkText *entry = current->entry;
    GtkEntryBuffer *entryBuffer = gtk_text_get_buffer(entry);
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
    GtkText *entry = current->entry;
    GtkEntryBuffer *entryBuffer = gtk_text_get_buffer(entry);
    double result = 0;
    calculate((char *)gtk_entry_buffer_get_text(entryBuffer), &result);
    char buffer[100] = {0};
    sprintf(buffer, "%g", result);
    gtk_entry_buffer_set_text(entryBuffer, buffer, (int) strlen(buffer));
}

void set_zero(GtkButton *widget, gpointer data) {
    buttonData *current = data;
    GtkText *entry = current->entry;
    GtkEntryBuffer *entryBuffer = gtk_text_get_buffer(entry);
    gtk_entry_buffer_set_text(entryBuffer, "", 0);
}

static void activate (GtkApplication *app, gpointer user_data) {
    GtkBuilder *builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, "builder-o.ui", NULL);

    GObject *window = gtk_builder_get_object(builder, "window");
    gtk_window_set_application(GTK_WINDOW (window), app);

    /* style */
    GtkCssProvider *cssProvider = gtk_css_provider_new();
    GdkDisplay *display = gtk_widget_get_display(GTK_WIDGET(window));
//    gtk_css_provider_load_from_data(cssProvider, "text {background-color: white; font-family: monospace; font-size: 18pt;}", -1);
    gtk_css_provider_load_from_path(cssProvider, "theme.css");
    gtk_style_context_add_provider_for_display(display, GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    g_object_unref(cssProvider);

    /* interface */
    buttonData *buttons = user_data;

    char *names[] = {"button0", "button1", "button2", "button3", "button4", "button5", "button6", "button7", "button8", "button9", "buttondot", "buttonsum", "buttonsub", "buttonmul", "buttondiv", "quit", "buttondel", "buttonres", "buttonzero", "buttonpow", "buttonopenbrace", "buttonclosebrace", "buttonacos", "buttonasin", "buttonatan", "buttonsqrt", "buttonsin", "buttoncos", "buttonmod", "buttontan", "buttonlog", "buttonln"};
    char *values[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", ".", "+", "-", "*", "/", NULL, NULL, NULL, NULL, "^", "(", ")", "acos(", "asin(", "atan(", "sqrt(", "sin(", "cos(", "mod", "tan(", "log(", "ln("};

    for (int i = 0; i < 30; ++i) {
            buttons[i].name = names[i];
            buttons[i].value = values[i];
            buttons[i].entry = (GtkText *) gtk_builder_get_object(builder, "entry");
            buttons[i].button = (GtkButton *) gtk_builder_get_object(builder, names[i]);
            if (values[i] != NULL) {
                g_signal_connect(buttons[i].button, "clicked", G_CALLBACK(add_text), &buttons[i]);
            } else if (i == 18) {
                g_signal_connect(buttons[i].button, "clicked", G_CALLBACK(set_zero), &buttons[i]);
            } else if (i == 17) {
                g_signal_connect(buttons[i].button, "clicked", G_CALLBACK(get_result), &buttons[i]);
            } else if (i == 16) {
            g_signal_connect(buttons[i].button, "clicked", G_CALLBACK(del_text), &buttons[i]);
            } else if (i == 15) {
                g_signal_connect_swapped (buttons[i].button, "clicked", G_CALLBACK (quit_cb), window);
            }
    }

    gtk_widget_show (GTK_WIDGET(window));
    g_object_unref(builder);
}

int main (int argc, char **argv) {
    GtkApplication *app;
    int status;


    buttonData *buttons[30*sizeof(buttonData)] = {0};

    app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
    g_signal_connect (app, "activate", G_CALLBACK (activate), &buttons);
    status = g_application_run (G_APPLICATION (app), argc, argv);
    g_object_unref (app);

  return status;
}
