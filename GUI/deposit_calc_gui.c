//
//  credit_calc_gui.c
//  C7_SmartCalc
//
//  Created by Joramun Sasin on 9/3/22.
//

#include "../main-gtk.h"

void execute_deposit_func(GtkButton *widget, gpointer data) {
    int ex_code = 0;
    entry_input *entry = data;
    double tax_rate = 0;

    GtkEntryBuffer *sum_entry_buf = gtk_entry_get_buffer(entry->sum_entry);
    char *output_sum = (char *)gtk_entry_buffer_get_text(sum_entry_buf);

    GtkEntryBuffer *term_entry_buf = gtk_entry_get_buffer(entry->term_entry);
    char *output_term = (char *)gtk_entry_buffer_get_text(term_entry_buf);

    GtkEntryBuffer *rate_entry_buf = gtk_entry_get_buffer(entry->rate_entry);
    char *output_rate = (char *)gtk_entry_buffer_get_text(rate_entry_buf);

    GtkEntryBuffer *tax_rate_entry_buf = gtk_entry_get_buffer(entry->tax_rate_entry);
    char *tax_output_rate = (char *)gtk_entry_buffer_get_text(tax_rate_entry_buf);

    ex_code = validate_input_numbers(output_sum); 
    if (ex_code == 0) ex_code = validate_input_numbers(output_term);
    if (ex_code == 0) ex_code = validate_input_numbers(output_rate);
    if (ex_code == 0) ex_code = validate_input_numbers(tax_output_rate);
    if (ex_code == 0) ex_code = (strchr(output_term, '.') == NULL) ? 0 : WRONG_SYMBOLS;
    if (ex_code == 0) ex_code = validate_extra_dot(output_sum);
    if (ex_code == 0) ex_code = validate_extra_dot(output_rate);
    if (ex_code == 0) ex_code = validate_extra_dot(tax_output_rate);
    deposit_input cont = {0};
    if (ex_code == 0) {
        sscanf(output_sum, "%lf", &cont.deposit);
        sscanf(output_term, "%u", &cont.term);
        sscanf(output_rate, "%lf", &cont.rate);
        sscanf(tax_output_rate, "%lf", &tax_rate);
    }
    if (tax_rate > 0) {
        tax_rate /= 100;
    } else {
        tax_rate = 0;
    }
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

    /* Get withdrawal list */
    GtkTreeStore *store = entry->withdrawal_window;
    GtkTreeView *tree_view = (GtkTreeView *) entry->wd_tree_view;
    GtkTreeSelection *tree_selection = gtk_tree_view_get_selection(tree_view);
    GtkTreeIter iter_wd;
    gboolean valid_iter;
    cont.account_movement = malloc(cont.term * sizeof(double));
    for (int i_am = 0; i_am < cont.term; i_am++) cont.account_movement[i_am] = 0;
    valid_iter = gtk_tree_model_get_iter_first(GTK_TREE_MODEL(store), &iter_wd);
    int i_ams = 0;
    double value_ams = 0;
    while (valid_iter) {
        gchararray day;
        gchararray sum;
        gtk_tree_model_get(GTK_TREE_MODEL(store), &iter_wd, 0, &day, 1, &sum, -1);
        sscanf(day, "%d", &i_ams);
        sscanf(sum, "%lf", &value_ams);
        if (i_ams < cont.term) {
            cont.account_movement[i_ams] += value_ams;
        }
        g_free(day);
        g_free(sum);
        valid_iter = gtk_tree_model_iter_next(GTK_TREE_MODEL(store), &iter_wd);
    }

    cont.capitalization = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(entry->type_credit_cbt));
    deposit_output cont_output = {0};

    if (ex_code == 0) {
        handle_deposit_calc(cont, &cont_output);
    }

    free(cont.account_movement);

    GtkTextIter iter;
    gtk_text_buffer_get_start_iter(entry->result_buffer, &iter);

    char *autobuffer = NULL;
    
    if (ex_code == 0) {
        asprintf(&autobuffer, "%.2lf rubles was deposited into account.\nThe term of deposit: %u days\nAt %.2lf%% rate\nFinal account balance after replenishments, withdrawals and gained profit: %.2lf\n", cont.deposit, cont.term, cont.rate, cont_output.deposit);
        gtk_text_buffer_insert(entry->result_buffer, &iter, autobuffer, -1);
        free(autobuffer);

        asprintf(&autobuffer, "Earned by deposit: %.2lf\nTax assesed on profit: %.2lf\n", cont_output.total_profit, cont_output.total_profit * tax_rate);
        gtk_text_buffer_insert(entry->result_buffer, &iter, autobuffer, -1);
        free(autobuffer);
        
        node *head = cont_output.stack_of_payouts;
        while (find_last(head)->number != 0) {
            asprintf(&autobuffer, "Periodic payout: %g\n", find_last(head)->value);
            gtk_text_buffer_insert(entry->result_buffer, &iter, autobuffer, -1);
            free(autobuffer);
            pop(head);
        }
    } else {
        gtk_text_buffer_insert(entry->result_buffer, &iter, "Invalid input!\n", -1);
    }
    clean(cont_output.stack_of_payouts);

}

void add_withdrawal_func(GtkButton *button, gpointer data_struct) {
    wd_cont *withdrawal_cont = data_struct; 
    GtkTreeStore *store = withdrawal_cont->withdrawal_window;
    GtkEntryBuffer *sum_buf = gtk_entry_get_buffer(withdrawal_cont->entry_withdrawal);
    char *sum_char = (char *)gtk_entry_buffer_get_text(sum_buf);
    GtkEntryBuffer *date_buf = gtk_entry_get_buffer(withdrawal_cont->date_withdrawal);
    char *date_char = (char *)gtk_entry_buffer_get_text(date_buf);
    if (*sum_char && *date_char) {
        if (*sum_char == '-') sum_char++;
        int ex_code = validate_input_numbers(sum_char);
        if (ex_code == 0) ex_code = validate_extra_dot(sum_char);
        if (ex_code == 0) ex_code = validate_input_numbers(date_char);
        if (ex_code == 0) ex_code = (strchr(date_char, '.') == NULL) ? 0 : WRONG_SYMBOLS;
        if (ex_code == 0) {
            GtkTreeIter iter;
            sum_char = (char *) gtk_entry_buffer_get_text(sum_buf);
            gtk_tree_store_append (store, &iter, NULL);  /* Acquire an iterator */
            gtk_tree_store_set (store, &iter, 0, date_char, 1, sum_char, -1);
            gtk_editable_set_text(GTK_EDITABLE(withdrawal_cont->entry_withdrawal), "");
            gtk_editable_set_text(GTK_EDITABLE(withdrawal_cont->date_withdrawal), "");
        }
    }
}

void del_withdrawal_func(GtkButton *button, gpointer data_struct) {
    gboolean valid_iter;
    wd_cont *withdrawal_cont = data_struct; 
    GtkTreeStore *store = withdrawal_cont->withdrawal_window;
    GtkTreeView *tree_view = (GtkTreeView *) withdrawal_cont->wd_tree_view;
    GtkTreeSelection *tree_selection = gtk_tree_view_get_selection(tree_view);
    GtkTreeIter iter;
    valid_iter = gtk_tree_selection_get_selected(tree_selection, NULL, &iter);
    if (valid_iter) gtk_tree_store_remove(store, &iter);
}

void deposit_calc_window(GtkButton *widget, gpointer data) {
    GtkBuilder *builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, "./Style/deposit-calc-o.ui", NULL);
    GObject *window = gtk_builder_get_object(builder, "window_credit_calc");

    /* Comboboxes */
    GtkComboBoxText *percentage_cbt = (GtkComboBoxText *) gtk_builder_get_object(builder, "percents");
    gtk_combo_box_set_active(GTK_COMBO_BOX(percentage_cbt), 0);
    GtkComboBoxText *tax_percentage_cbt = (GtkComboBoxText *) gtk_builder_get_object(builder, "tax_percents");
    gtk_combo_box_set_active(GTK_COMBO_BOX(tax_percentage_cbt), 0);
    GtkComboBoxText *years_or_months = (GtkComboBoxText *) gtk_builder_get_object(builder, "years_or_months");
    gtk_combo_box_set_active(GTK_COMBO_BOX(years_or_months), 0);
    GtkComboBoxText *currency_cbt = (GtkComboBoxText *) gtk_builder_get_object(builder, "currency");
    gtk_combo_box_set_active(GTK_COMBO_BOX(currency_cbt), 0);
    GtkCheckButton *type_choice = (GtkCheckButton *) gtk_builder_get_object(builder, "type_choice");
    GtkComboBoxText *type_payouts = (GtkComboBoxText *) gtk_builder_get_object(builder, "type_payouts");
    gtk_combo_box_set_active(GTK_COMBO_BOX(type_payouts), 0);

    /* Withdrawal block */
    GtkButton *add_withdrawal = (GtkButton *) gtk_builder_get_object(builder, "withdrawal_plus");
    GtkButton *del_withdrawal = (GtkButton *) gtk_builder_get_object(builder, "withdrawal_minus");
    GtkEntry *entry_withdrawal = (GtkEntry *) gtk_builder_get_object(builder, "sum_withdrawal_entry");
    gtk_entry_set_placeholder_text(entry_withdrawal, "Replenish or withdraw");
    GtkEntry *date_withdrawal = (GtkEntry *) gtk_builder_get_object(builder, "sum_withdrawal_date");
    gtk_entry_set_placeholder_text(date_withdrawal, "Day:");
    GtkScrolledWindow *withdrawal_window = (GtkScrolledWindow *) gtk_builder_get_object(builder, "withdrawal_list");
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    GtkTreeStore *store = gtk_tree_store_new (2, G_TYPE_STRING, G_TYPE_STRING);
    GtkWidget *view_list = gtk_tree_view_new_with_model(GTK_TREE_MODEL(store)); 

    renderer = gtk_cell_renderer_text_new();
    g_object_set (G_OBJECT (renderer), "background", "green", NULL);
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
    gtk_scrolled_window_set_child(withdrawal_window, GTK_WIDGET(view_list));

    wd_cont *withdrawal_cont = malloc(1*sizeof(wd_cont));
    withdrawal_cont->withdrawal_window = store;
    withdrawal_cont->entry_withdrawal = entry_withdrawal;
    withdrawal_cont->date_withdrawal = date_withdrawal;
    withdrawal_cont->wd_tree_view = view_list;
    g_signal_connect(add_withdrawal, "clicked", G_CALLBACK(add_withdrawal_func), withdrawal_cont);
    g_signal_connect(del_withdrawal, "clicked", G_CALLBACK(del_withdrawal_func), withdrawal_cont);

    /* Result text */
    GtkTextView *result_tw = (GtkTextView *) gtk_builder_get_object(builder, "result");
    GtkTextBuffer *result_buffer = gtk_text_view_get_buffer(result_tw);
    
    /* Buttons */
    GtkButton *execute_button = (GtkButton *) gtk_builder_get_object(builder, "execute_credit_calc");

    entry_input *one = malloc(1*sizeof(entry_input));
    one->sum_entry = (GtkEntry *) gtk_builder_get_object(builder, "sum_entry");
    one->term_entry = (GtkEntry *) gtk_builder_get_object(builder, "term_entry");
    one->rate_entry = (GtkEntry *) gtk_builder_get_object(builder, "rate_entry");
    one->tax_rate_entry = (GtkEntry *) gtk_builder_get_object(builder, "tax_rate_entry");
    gtk_editable_set_text(GTK_EDITABLE(one->tax_rate_entry), "0");
    one->term_cbt = years_or_months;
    one->type_credit_cbt = (GtkWidget *) type_choice;
    one->result_buffer = result_buffer;
    one->type_payouts = type_payouts;
    one->wd_tree_view = view_list;
    one->withdrawal_window = store;
    g_signal_connect(execute_button, "clicked", G_CALLBACK(execute_deposit_func), one);

    GtkButton *quit_button = (GtkButton *) gtk_builder_get_object(builder, "quit_credit_calc");
    g_signal_connect_swapped(quit_button, "clicked", G_CALLBACK(quit_window), window);

    gtk_widget_show (GTK_WIDGET(window));
    g_object_unref(builder);
}


