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
    char *output = (char *) malloc(1 + strlen(gtk_entry_buffer_get_text(entryBuffer)) + strlen(current->value));
    strcpy(output, gtk_entry_buffer_get_text(entryBuffer));
    strcat(output, current->value);
    gtk_entry_buffer_set_text(entryBuffer, output, (int) strlen(output));
    free(output);
}

void del_text(GtkButton *widget, gpointer data) {
    buttonData *current = data;
    GtkText *entry = current->entry;
    GtkEntryBuffer *entryBuffer = gtk_text_get_buffer(entry);
    int length = (int) strlen(gtk_entry_buffer_get_text(entryBuffer));
    if (length > 0) {
        char output[--length];
        for (int i = 0; i < length; ++i)
            output[i] = gtk_entry_buffer_get_text(entryBuffer)[i];
        gtk_entry_buffer_set_text(entryBuffer, output, length);
    }
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

//    buttonex = gtk_builder_get_object (builder, "quit");
//      g_signal_connect_swapped (buttonex, "clicked", G_CALLBACK (quit_cb), window);


    buttonData *buttons = user_data;

    char *names[] = {"button0", "button1", "button2", "button3", "button4", "button5", "button6", "button7", "button8", "button9", "buttondot", "buttonsum", "buttonsub", "buttonmul", "buttondiv", "quit", "buttondel", "buttonres", "buttonzero", "buttonpow", "buttonopenbrace", "buttonclosebrace", "buttonacos", "buttonasin", "buttonatan", "buttonsqrt", "buttonsin", "buttoncos", "buttonmod", "buttontan", "buttonlog", "buttonln"};
    char *values[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", ".", "+", "-", "*", "/", NULL, NULL, NULL, NULL, "^", "(", ")", "acos(", "asin(", "atan(", "sqrt(", "sin(", "cos(", "mod", "tan(", "log(", "ln("};
//

//    buttons[0].name = names[0];
//    buttons[0].value = values[0];
//    buttons[0].entry = (GtkText *) gtk_builder_get_object(builder, "entry");
//    buttons[0].button = (GtkButton *) gtk_builder_get_object(builder, names[0]);
//    g_signal_connect_swapped (buttons[0].button, "clicked", G_CALLBACK (quit_cb), window);
//    buttons[1].name = names[1];
//    buttons[1].value = values[1];
//    buttons[1].entry = (GtkText *) gtk_builder_get_object(builder, "entry");
//    buttons[1].button = (GtkButton *) gtk_builder_get_object(builder, names[1]);
//    g_signal_connect_swapped (buttons[1].button, "clicked", G_CALLBACK (quit_cb), window);
//    buttons[2].name = names[2];
//    buttons[2].value = values[2];
//    buttons[2].entry = (GtkText *) gtk_builder_get_object(builder, "entry");
//    buttons[2].button = (GtkButton *) gtk_builder_get_object(builder, names[2]);
//    g_signal_connect_swapped (buttons[2].button, "clicked", G_CALLBACK (quit_cb), window);
//    buttons[3].name = names[3];
//    buttons[3].value = values[3];
//    buttons[3].entry = (GtkText *) gtk_builder_get_object(builder, "entry");
//    buttons[3].button = (GtkButton *) gtk_builder_get_object(builder, names[3]);
//    g_signal_connect_swapped (buttons[3].button, "clicked", G_CALLBACK (quit_cb), window);
//    buttons[5].name = names[5];
//    buttons[5].value = values[5];
//    buttons[5].entry = (GtkText *) gtk_builder_get_object(builder, "entry");
//    buttons[5].button = (GtkButton *) gtk_builder_get_object(builder, names[5]);
//    g_signal_connect_swapped (buttons[5].button, "clicked", G_CALLBACK (quit_cb), window);
//    buttons[15].name = names[15];
//    buttons[15].value = values[15];
//    buttons[15].entry = (GtkText *) gtk_builder_get_object(builder, "entry");
//    buttons[15].button = (GtkButton *) gtk_builder_get_object(builder, "quit");
//    g_signal_connect_swapped (buttons[15].button, "clicked", G_CALLBACK (quit_cb), window);
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
