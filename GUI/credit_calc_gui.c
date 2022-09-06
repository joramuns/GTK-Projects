//
//  credit_calc_gui.c
//  C7_SmartCalc
//
//  Created by Joramun Sasin on 9/3/22.
//

#include "main-gtk.h"

void execute_credit_func(GtkButton *widget, gpointer data) {
    entry_input *entry = data;

    GtkEntryBuffer *sum_entry_buf = gtk_entry_get_buffer(entry->sum_entry);
    char *output_sum = (char *)gtk_entry_buffer_get_text(sum_entry_buf);

    GtkEntryBuffer *term_entry_buf = gtk_entry_get_buffer(entry->term_entry);
    char *output_term = (char *)gtk_entry_buffer_get_text(term_entry_buf);

    GtkEntryBuffer *rate_entry_buf = gtk_entry_get_buffer(entry->rate_entry);
    char *output_rate = (char *)gtk_entry_buffer_get_text(rate_entry_buf);

    credit_input test_case = {0};
    sscanf(output_sum, "%lf", &test_case.sum);
    sscanf(output_term, "%u", &test_case.term);
    sscanf(output_rate, "%lf", &test_case.rate);
    test_case.type = 1;
    credit_output test = {0};
    g_print("%g\n", test_case.sum);
    g_print("%u\n", test_case.term);
    handle_credit_calculator(test_case, &test);

    printf("Total paid: %g\nOverpaid: %g\n", test.total_sum, test.overpaid);
    node *head = test.stack_of_payments;
    while (find_last(head)->number != 0) {
        g_print("Monthly payment: %g\n", find_last(head)->value);
        pop(head);
    }
    free(test.stack_of_payments);

}

void credit_calc_window(GtkButton *widget, gpointer data) {
    GtkBuilder *builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, "./Style/credit-calc-o.ui", NULL);
    GObject *window = gtk_builder_get_object(builder, "window_credit_calc");

    GtkButton *execute_button = (GtkButton *) gtk_builder_get_object(builder, "execute_credit_calc");

    entry_input *one = malloc(1*sizeof(entry_input));

    one->sum_entry = (GtkEntry *) gtk_builder_get_object(builder, "sum_entry");
    one->term_entry = (GtkEntry *) gtk_builder_get_object(builder, "term_entry");
    one->rate_entry = (GtkEntry *) gtk_builder_get_object(builder, "rate_entry");
    g_signal_connect(execute_button, "clicked", G_CALLBACK(execute_credit_func), one);
//    GtkEntry *entry[3*sizeof(GtkEntry *)] = {0};
//    GtkEntry *entry = (GtkEntry *) gtk_builder_get_object(builder, "sum_entry");
//    *entry[0] = (GtkEntry *) gtk_builder_get_object(builder, "sum_entry");
//    *entry[1] = (GtkEntry *) gtk_builder_get_object(builder, "term_entry");
//    *entry[2] = (GtkEntry *) gtk_builder_get_object(builder, "rate_entry");
//    g_signal_connect(execute_button, "clicked", G_CALLBACK(execute_credit_func), entry);
    GtkButton *quit_button = (GtkButton *) gtk_builder_get_object(builder, "quit_credit_calc");
    g_signal_connect_swapped(quit_button, "clicked", G_CALLBACK(quit_window), window);

    gtk_widget_show (GTK_WIDGET(window));
    g_object_unref(builder);
}

//buttonData *buttons = user_data;
//buttonData *buttons[33*sizeof(buttonData)] = {0}
