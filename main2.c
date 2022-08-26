//
//  2main.c
//  C7_SmartCalc
//
//  Created by Joramun Sasin on 8/18/22.
//

#include <stdio.h>
#include <gtk/gtk.h>
#include <string.h>

static int counter = 0;
static char input_text[1024] = {"9"};

static void print_hello (GtkWidget *widget, gpointer data) {
    if (counter++ < 2) {
        strcat(input_text, "1");
    }
    g_print("Hello World %s\n", input_text);
}


static void activate (GtkApplication *app, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *button;

  /* create a new window, and set its title */
    window = gtk_application_window_new (app);
    gtk_window_set_title (GTK_WINDOW (window), "SmartCalc_v1.0");

  /* Here we construct the container that is going pack our buttons */
    grid = gtk_grid_new ();

  /* Pack the container in the window */
    gtk_window_set_child (GTK_WINDOW (window), grid);

    // ============= Numbers
    button = gtk_button_new_with_label ("1");
    g_signal_connect (button, "clicked", G_CALLBACK (print_hello), "1");
    gtk_grid_attach (GTK_GRID (grid), button, 0, 1, 1, 1);
    button = gtk_button_new_with_label ("2");
    g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);
    gtk_grid_attach (GTK_GRID (grid), button, 1, 1, 1, 1);
    button = gtk_button_new_with_label ("3");
    g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);
    gtk_grid_attach (GTK_GRID (grid), button, 2, 1, 1, 1);
    button = gtk_button_new_with_label ("4");
    g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);
    gtk_grid_attach (GTK_GRID (grid), button, 0, 2, 1, 1);
    button = gtk_button_new_with_label ("5");
    g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);
    gtk_grid_attach (GTK_GRID (grid), button, 1, 2, 1, 1);
    button = gtk_button_new_with_label ("6");
    g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);
    gtk_grid_attach (GTK_GRID (grid), button, 2, 2, 1, 1);
    button = gtk_button_new_with_label ("7");
    g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);
    gtk_grid_attach (GTK_GRID (grid), button, 0, 3, 1, 1);
    button = gtk_button_new_with_label ("8");
    g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);
    gtk_grid_attach (GTK_GRID (grid), button, 1, 3, 1, 1);
    button = gtk_button_new_with_label ("9");
    g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);
    gtk_grid_attach (GTK_GRID (grid), button, 2, 3, 1, 1);
    button = gtk_button_new_with_label ("±");
    g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);
    gtk_grid_attach (GTK_GRID (grid), button, 0, 4, 1, 1);
    button = gtk_button_new_with_label ("0");
    g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);
    gtk_grid_attach (GTK_GRID (grid), button, 1, 4, 1, 1);
    button = gtk_button_new_with_label (".");
    g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);
    gtk_grid_attach (GTK_GRID (grid), button, 2, 4, 1, 1);
    // ============== Operators
    button = gtk_button_new_with_label ("+");
    g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);
    gtk_grid_attach (GTK_GRID (grid), button, 3, 1, 1, 1);
    button = gtk_button_new_with_label ("-");
    g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);
    gtk_grid_attach (GTK_GRID (grid), button, 3, 2, 1, 1);
    button = gtk_button_new_with_label ("*");
    g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);
    gtk_grid_attach (GTK_GRID (grid), button, 3, 3, 1, 1);
    button = gtk_button_new_with_label ("/");
    g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);
    gtk_grid_attach (GTK_GRID (grid), button, 3, 4, 1, 1);

    button = gtk_button_new_with_label ("Quit");
    g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_window_destroy), window);
    gtk_grid_attach (GTK_GRID (grid), button, 0, 5, 4, 1);

    GtkWidget *view;
    GtkTextBuffer *buffer;
    GtkTextIter start, end;
    PangoFontDescription *font_desc;
    GdkRGBA rgba;
    GtkTextTag *tag;
    GtkCssProvider *provider;
    GtkStyleContext *context;

    view = gtk_text_view_new ();

    buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (view));

    gtk_text_buffer_set_text (buffer, "Hello, this is some text", -1);

    /* Change default font and color throughout the widget */
    provider = gtk_css_provider_new ();
    gtk_css_provider_load_from_data (provider,
                                     "textview {"
                                     " font: 15px serif;"
                                     "  color: green;"
                                     "}",
                                     -1);
    context = gtk_widget_get_style_context (view);
    gtk_style_context_add_provider (context,
                                    GTK_STYLE_PROVIDER (provider),
                                    GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    /* Change left margin throughout the widget */
    gtk_text_view_set_left_margin (GTK_TEXT_VIEW (view), 30);

    /* Use a tag to change the color for just one part of the widget */
    tag = gtk_text_buffer_create_tag (buffer, "blue_foreground",
                                      "foreground", "blue",
                                      NULL);
    gtk_text_buffer_get_iter_at_offset (buffer, &start, 7);
    gtk_text_buffer_get_iter_at_offset (buffer, &end, 12);
    gtk_text_buffer_apply_tag (buffer, tag, &start, &end);

    gtk_grid_attach (GTK_GRID (grid), view, 0, 0, 4, 1);

    gtk_widget_show (window);
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
