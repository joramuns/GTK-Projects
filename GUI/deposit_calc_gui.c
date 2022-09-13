//
//  credit_calc_gui.c
//  C7_SmartCalc
//
//  Created by Joramun Sasin on 9/3/22.
//

#include "../main-gtk.h"

void execute_deposit_func(GtkButton *widget, gpointer data) {
    entry_input *entry = data;

    GtkEntryBuffer *sum_entry_buf = gtk_entry_get_buffer(entry->sum_entry);
    char *output_sum = (char *)gtk_entry_buffer_get_text(sum_entry_buf);

    GtkEntryBuffer *term_entry_buf = gtk_entry_get_buffer(entry->term_entry);
    char *output_term = (char *)gtk_entry_buffer_get_text(term_entry_buf);

    GtkEntryBuffer *rate_entry_buf = gtk_entry_get_buffer(entry->rate_entry);
    char *output_rate = (char *)gtk_entry_buffer_get_text(rate_entry_buf);

    deposit_input cont = {0};
    sscanf(output_sum, "%lf", &cont.deposit);
    sscanf(output_term, "%u", &cont.term);
    sscanf(output_rate, "%lf", &cont.rate);
    unsigned input_term = gtk_combo_box_get_active(GTK_COMBO_BOX(entry->term_cbt));
    if (input_term == 1) {
        cont.term *= 30;
    } else if (input_term == 2) {
        cont.term *= 365;
    }
    unsigned input_period = gtk_combo_box_get_active(GTK_COMBO_BOX(entry->type_payouts));
    if (input_period == 0) {
        cont.freq_payment = DAILY;
    } else if (input_period == 1) {
        cont.freq_payment = WEEKLY;
    } else if (input_period == 2) {
        cont.freq_payment = MONTHLY;
    } else if (input_period == 3) {
        cont.freq_payment = QUARTERLY;
    } else if (input_period == 4) {
        cont.freq_payment = YEARLY;
    }
    /* cont.capitalization = gtk_combo_box_get_active(GTK_COMBO_BOX(entry->type_credit_cbt)); */
    cont.capitalization = gtk_check_button_get_active(GTK_CHECK_BUTTON(entry->type_credit_cbt));
    deposit_output cont_output = {0};
    handle_deposit_calc(cont, &cont_output);

    GtkTextIter iter;
    gtk_text_buffer_get_start_iter(entry->result_buffer, &iter);

    char *autobuffer = NULL;

    asprintf(&autobuffer, "Deposit sum: %.2lf, term of deposit: %u, interest rate: %g\n", cont.deposit, cont.term, cont.rate);
    gtk_text_buffer_insert(entry->result_buffer, &iter, autobuffer, -1);
    free(autobuffer);

    asprintf(&autobuffer, "Earned by deposit: %.2lf\n", cont_output.total_profit);
    gtk_text_buffer_insert(entry->result_buffer, &iter, autobuffer, -1);
    free(autobuffer);
    
    node *head = cont_output.stack_of_payouts;
    while (find_last(head)->number != 0) {
        asprintf(&autobuffer, "Periodic payout: %g\n", find_last(head)->value);
        gtk_text_buffer_insert(entry->result_buffer, &iter, autobuffer, -1);
        free(autobuffer);
        pop(head);
    }
    clean(cont_output.stack_of_payouts);

}

void add_withdrawal_func(GtkButton *button, gpointer data_struct) {
    wd_cont *withdrawal_cont = data_struct; 
    GtkWidget *test_button = gtk_button_new();
    g_print("window %p\n", withdrawal_cont->withdrawal_window);
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(withdrawal_cont->withdrawal_window), GTK_WIDGET(withdrawal_cont->entry_withdrawal));
}

void deposit_calc_window(GtkButton *widget, gpointer data) {
    GtkBuilder *builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, "./Style/deposit-calc-o.ui", NULL);
    GObject *window = gtk_builder_get_object(builder, "window_credit_calc");

    /* Comboboxes */
    GtkComboBoxText *percentage_cbt = (GtkComboBoxText *) gtk_builder_get_object(builder, "percents");
    gtk_combo_box_set_active(GTK_COMBO_BOX(percentage_cbt), 0);
    GtkComboBoxText *years_or_months = (GtkComboBoxText *) gtk_builder_get_object(builder, "years_or_months");
    gtk_combo_box_set_active(GTK_COMBO_BOX(years_or_months), 0);
    GtkComboBoxText *currency_cbt = (GtkComboBoxText *) gtk_builder_get_object(builder, "currency");
    gtk_combo_box_set_active(GTK_COMBO_BOX(currency_cbt), 0);
    GtkCheckButton *type_choice = (GtkCheckButton *) gtk_builder_get_object(builder, "type_choice");
    GtkComboBoxText *type_payouts = (GtkComboBoxText *) gtk_builder_get_object(builder, "type_payouts");
    gtk_combo_box_set_active(GTK_COMBO_BOX(type_payouts), 0);

    /* Withdrawal block */
    GtkButton *add_withdrawal = (GtkButton *) gtk_builder_get_object(builder, "withdrawal_plus");
    GtkEntry *entry_withdrawal = (GtkEntry *) gtk_builder_get_object(builder, "sum_withdrawal_entry");
    GtkScrolledWindow *withdrawal_window = (GtkScrolledWindow *) gtk_builder_get_object(builder, "withdrawal_list");
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    GtkTreeStore *store = gtk_tree_store_new (2, G_TYPE_STRING, G_TYPE_STRING);
    GtkWidget *view_list = gtk_tree_view_new_with_model(GTK_TREE_MODEL(store)); 

    renderer = gtk_cell_renderer_text_new();
    g_object_set (G_OBJECT (renderer), "foreground", "green", NULL);
    /* Create a column, associating the "text" attribute of the
    * cell_renderer to the first column of the model */
    column = gtk_tree_view_column_new_with_attributes ("Date", renderer, "text", 0, NULL);
    /* Add the column to the view. */
    gtk_tree_view_append_column (GTK_TREE_VIEW (view_list), column);
    column = gtk_tree_view_column_new_with_attributes ("Sum", renderer, "text", 1, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(view_list), column);

    /* Fill the table */
    GtkTreeIter iter;
    gtk_tree_store_append (store, &iter, NULL);  /* Acquire an iterator */
    gtk_tree_store_set (store, &iter, 0, "123", 1, "10000", -1);
    gtk_tree_store_append (store, &iter, NULL);  /* Acquire an iterator */
    gtk_tree_store_set (store, &iter, 0, "456", 1, "9999", -1);
    gtk_tree_store_append (store, &iter, NULL);  /* Acquire an iterator */
    gtk_tree_store_set (store, &iter, 0, "789", 1, "7980", -1);
    gtk_tree_store_append (store, &iter, NULL);  /* Acquire an iterator */
    gtk_tree_store_set (store, &iter, 0, "888", 1, "8888888", -1);
    gtk_tree_store_append (store, &iter, NULL);  /* Acquire an iterator */
    gtk_tree_store_set (store, &iter, 0, "456", 1, "9999", -1);
    gtk_tree_store_append (store, &iter, NULL);  /* Acquire an iterator */
    gtk_tree_store_set (store, &iter, 0, "789", 1, "7980", -1);
    gtk_tree_store_append (store, &iter, NULL);  /* Acquire an iterator */
    gtk_tree_store_set (store, &iter, 0, "888", 1, "8888888", -1);
    /* GtkTreeIter iter2; */
    /* gtk_tree_store_append (store, &iter2, &iter);  /1* Acquire a child iterator *1/ */
    /* gtk_tree_store_set (store, &iter2, 0, "Volume 1: Fundamental Algorithms", -1); */
    /* gtk_tree_view_set_model(view_list, GTK_TREE_MODEL(store)); */
    gtk_scrolled_window_set_child(withdrawal_window, GTK_WIDGET(view_list));

    g_print("1 window %p\n", withdrawal_window);
    wd_cont *withdrawal_cont = malloc(1*sizeof(wd_cont));
    withdrawal_cont->withdrawal_window = withdrawal_window;
    withdrawal_cont->entry_withdrawal = entry_withdrawal;
    g_signal_connect(add_withdrawal, "clicked", G_CALLBACK(add_withdrawal_func), withdrawal_cont);

    /* Result text */
    GtkTextView *result_tw = (GtkTextView *) gtk_builder_get_object(builder, "result");
    GtkTextBuffer *result_buffer = gtk_text_view_get_buffer(result_tw);
    /* GtkTextIter iter; */
    /* GtkTextMark *mark = gtk_text_buffer_get_insert(result_buffer); */
    /* gtk_text_buffer_get_iter_at_mark(result_buffer, &iter, mark); */
    /* gtk_text_buffer_insert(result_buffer, &iter, "text", 5); */
    /* gtk_text_view_set_buffer(result_tw, result_buffer); */
    
    /* Buttons */
    GtkButton *execute_button = (GtkButton *) gtk_builder_get_object(builder, "execute_credit_calc");

    entry_input *one = malloc(1*sizeof(entry_input));

    one->sum_entry = (GtkEntry *) gtk_builder_get_object(builder, "sum_entry");
    one->term_entry = (GtkEntry *) gtk_builder_get_object(builder, "term_entry");
    one->rate_entry = (GtkEntry *) gtk_builder_get_object(builder, "rate_entry");
    one->term_cbt = years_or_months;
    one->type_credit_cbt = (GtkWidget *) type_choice;
    one->result_buffer = result_buffer;
    one->type_payouts = type_payouts;
    g_signal_connect(execute_button, "clicked", G_CALLBACK(execute_deposit_func), one);
    GtkButton *quit_button = (GtkButton *) gtk_builder_get_object(builder, "quit_credit_calc");
    g_signal_connect_swapped(quit_button, "clicked", G_CALLBACK(quit_window), window);

    gtk_widget_show (GTK_WIDGET(window));
    g_object_unref(builder);
}


