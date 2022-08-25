//
//  2main.c
//  C7_SmartCalc
//
//  Created by Joramun Sasin on 8/18/22.
//

#include <stdio.h>
#include <gtk/gtk.h>
#include <string.h>

//static int counter = 0;
//static char input_text[1024] = {0};

static void print_hello (GtkWidget *widget, gpointer data) {
//    if (counter++ < 2) {
//        strcat(input_text, "1");
//    }
    g_print("Hello World\n");
}


static void activate (GtkApplication *app, gpointer user_data) {
    GtkBuilder *builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, "builder.ui", NULL);

    GObject *window = gtk_builder_get_object(builder, "window");
    gtk_window_set_application(GTK_WINDOW (window), app);

    // ============= Numbers
    GObject *button = gtk_builder_get_object(builder, "button1");
    g_signal_connect (button, "clicked", G_CALLBACK (print_hello), "1");
    button = gtk_builder_get_object (builder, "button2");
    g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);
    button = gtk_builder_get_object (builder, "button3");
    g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);
    button = gtk_builder_get_object (builder, "button4");
    g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);
    button = gtk_builder_get_object (builder, "button5");
    g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);
    button = gtk_builder_get_object (builder, "button6");
    g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);
    button = gtk_builder_get_object (builder, "button7");
    g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);
    button = gtk_builder_get_object (builder, "button8");
    g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);
    button = gtk_builder_get_object (builder, "button9");
    g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);
    button = gtk_builder_get_object (builder, "buttonsign");
    g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);
    button = gtk_builder_get_object (builder, "button0");
    g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);
    button = gtk_builder_get_object (builder, "buttondot");
    g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);
        // ============== Operators
    button = gtk_builder_get_object (builder, "buttonsum");
    g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);
    button = gtk_builder_get_object (builder, "buttonsub");
    g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);
    button = gtk_builder_get_object (builder, "buttonmul");
    g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);
    button = gtk_builder_get_object (builder, "buttondiv");
    g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);
    // =============== Other
    button = gtk_builder_get_object (builder, "quit");
    g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_window_close), window);

    gtk_widget_show (GTK_WIDGET(window));
    g_object_unref(builder);
}

int main (int argc, char **argv) {
  GtkApplication *app;
  int status;

  app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}
