//
//  credit_calc_gui.c
//  C7_SmartCalc
//
//  Created by Joramun Sasin on 9/3/22.
//

#include "main-gtk.h"

void execute_credit_func(GtkButton *widget, gpointer data) {

}

void credit_calc_window(GtkButton *widget, gpointer data) {
    GtkBuilder *builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, "./Style/credit-calc-o.ui", NULL);
    GObject *window = gtk_builder_get_object(builder, "window_credit_calc");

    GtkButton *execute_button = (GtkButton *) gtk_builder_get_object(builder, "execute_credit_calc");
    g_signal_connect(execute_button, "clicked", G_CALLBACK(execute_credit_func), NULL);
    GtkButton *quit_button = (GtkButton *) gtk_builder_get_object(builder, "quit_credit_calc");
    g_signal_connect_swapped(quit_button, "clicked", G_CALLBACK(quit_window), window);

    gtk_widget_show (GTK_WIDGET(window));
    g_object_unref(builder);
}
