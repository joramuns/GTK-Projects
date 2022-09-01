//
//  2main.c
//  C7_SmartCalc
//
//  Created by Joramun Sasin on 8/18/22.
//

#include "main-gtk.h"

void quit_cb (GtkWindow *window)
{
  gtk_window_close (window);
}



static void activate (GtkApplication *app, gpointer user_data) {
    GtkBuilder *builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, "./Style/builder-o.ui", NULL);
    GObject *window = gtk_builder_get_object(builder, "window");
    gtk_window_set_application(GTK_WINDOW (window), app);

    /* style */
    GtkCssProvider *cssProvider = gtk_css_provider_new();
    GdkDisplay *display = gtk_widget_get_display(GTK_WIDGET(window));
    gtk_css_provider_load_from_path(cssProvider, "./Style/theme.css");
    gtk_style_context_add_provider_for_display(display, GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    g_object_unref(cssProvider);

    /* input */
    GtkEntry *entry_func;
    entry_func = (GtkEntry *) gtk_builder_get_object(builder, "entry_func");
    gtk_entry_set_alignment(GTK_ENTRY(entry_func), 1);
    gtk_entry_set_max_length(GTK_ENTRY(entry_func), EXPRESSION_SIZE);
    /* output*/
    GtkEntry *entry_res;
    entry_res = (GtkEntry *) gtk_builder_get_object(builder, "entry_res");
    gtk_entry_set_alignment(GTK_ENTRY(entry_res), 1);

    /* buttons */
    buttonData *buttons = user_data;

    char *names[] = {"button0", "button1", "button2", "button3", "button4", "button5", "button6", "button7", "button8", "button9", "buttondot", "buttonsum", "buttonsub", "buttonmul", "buttondiv", "quit", "buttondel", "buttonres", "buttonzero", "buttonpow", "buttonopenbrace", "buttonclosebrace", "buttonacos", "buttonasin", "buttonatan", "buttonsqrt", "buttonsin", "buttoncos", "buttonmod", "buttontan", "buttonlog", "buttonln", "buttonvar"};
    char *values[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", ".", "+", "-", "*", "/", NULL, NULL, NULL, NULL, "^", "(", ")", "acos(", "asin(", "atan(", "sqrt(", "sin(", "cos(", "mod", "tan(", "log(", "ln(", "X"};

    for (int i = 0; i < 33; ++i) {
        buttons[i].name = names[i];
        buttons[i].value = values[i];
        buttons[i].entry = entry_func;
        buttons[i].entry_res = entry_res;
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

//    GtkWidget *area = GTK_WIDGET(gtk_builder_get_object(builder, "area"));
//    gtk_drawing_area_set_draw_func(GTK_DRAWING_AREA(area), graph_draw, NULL, NULL);
//    GtkWidget *overlay = GTK_WIDGET(gtk_builder_get_object(builder, "overlay"));
//    GtkWidget *gridPlot = GTK_WIDGET(gtk_builder_get_object(builder, "gridPlot"));
//    gtk_overlay_set_child(GTK_OVERLAY(overlay), area);
//    gtk_overlay_add_overlay(GTK_OVERLAY(overlay), gridPlot);

    gtk_widget_show (GTK_WIDGET(window));
    g_object_unref(builder);
}

int main (int argc, char **argv) {
    GtkApplication *app;
    int status;

    buttonData *buttons[32*sizeof(buttonData)] = {0};

    app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
    g_signal_connect (app, "activate", G_CALLBACK (activate), &buttons);

    status = g_application_run (G_APPLICATION (app), argc, argv);
    g_object_unref (app);

  return status;
}
