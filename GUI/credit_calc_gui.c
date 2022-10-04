//
//  credit_calc_gui.c
//  C7_SmartCalc
//
//  Created by Joramun Sasin on 9/3/22.
//

#include "../main-gtk.h"

void execute_credit_func(GtkButton *widget, gpointer data) {
  int ex_code = 0;
  entry_input *entry = data;

  GtkEntryBuffer *sum_entry_buf = gtk_entry_get_buffer(entry->sum_entry);
  char *output_sum = (char *)gtk_entry_buffer_get_text(sum_entry_buf);

  GtkEntryBuffer *term_entry_buf = gtk_entry_get_buffer(entry->term_entry);
  char *output_term = (char *)gtk_entry_buffer_get_text(term_entry_buf);

  GtkEntryBuffer *rate_entry_buf = gtk_entry_get_buffer(entry->rate_entry);
  char *output_rate = (char *)gtk_entry_buffer_get_text(rate_entry_buf);

  ex_code = validate_input_numbers(output_sum);
  if (ex_code == 0) ex_code = validate_input_numbers(output_term);
  if (ex_code == 0) ex_code = validate_input_numbers(output_rate);
  if (ex_code == 0)
    ex_code = (strchr(output_term, '.') == NULL) ? 0 : WRONG_SYMBOLS;
  if (ex_code == 0) ex_code = validate_extra_dot(output_sum);
  if (ex_code == 0) ex_code = validate_extra_dot(output_rate);

  credit_input test_case = {0};
  credit_output cont_output = {0};
  if (ex_code == 0) {
    sscanf(output_sum, "%lf", &test_case.sum);
    sscanf(output_term, "%u", &test_case.term);
    if (test_case.term == 0) ex_code = WRONG_SYMBOLS;
    sscanf(output_rate, "%lf", &test_case.rate);
    if (gtk_combo_box_get_active(GTK_COMBO_BOX(entry->term_cbt)))
      test_case.term *= 12;
    test_case.type =
        gtk_combo_box_get_active(GTK_COMBO_BOX(entry->type_credit_cbt));
    handle_credit_calculator(test_case, &cont_output);
  }

  GtkTextIter iter;
  gtk_text_buffer_get_start_iter(entry->result_buffer, &iter);

  if (ex_code == 0) {
    char *autobuffer = NULL;
    asprintf(&autobuffer, "Total paid: %.2lf\nOverpaid: %.2lf\n",
             cont_output.total_sum, cont_output.overpaid);
    gtk_text_buffer_insert(entry->result_buffer, &iter, autobuffer, -1);
    free(autobuffer);

    node *head = cont_output.stack_of_payments;
    while (find_last(head)->number != 0) {
      asprintf(&autobuffer, "Monthly payment: %.2lf\n", find_last(head)->value);
      gtk_text_buffer_insert(entry->result_buffer, &iter, autobuffer, -1);
      free(autobuffer);
      pop(head);
    }
  } else {
    gtk_text_buffer_insert(entry->result_buffer, &iter, "Invalid input!\n", -1);
  }
  clean(cont_output.stack_of_payments);
}

void credit_calc_window(GtkButton *widget, gpointer data) {
  GtkBuilder *builder = gtk_builder_new();
  gtk_builder_add_from_resource(builder, "/org/gtk/Style/credit-calc-o.ui",
                                NULL);
  GObject *window = gtk_builder_get_object(builder, "window_credit_calc");

  /* Comboboxes */
  GtkComboBoxText *percentage_cbt =
      (GtkComboBoxText *)gtk_builder_get_object(builder, "percents");
  gtk_combo_box_set_active(GTK_COMBO_BOX(percentage_cbt), 0);
  GtkComboBoxText *years_or_months =
      (GtkComboBoxText *)gtk_builder_get_object(builder, "years_or_months");
  gtk_combo_box_set_active(GTK_COMBO_BOX(years_or_months), 0);
  GtkComboBoxText *currency_cbt =
      (GtkComboBoxText *)gtk_builder_get_object(builder, "currency");
  gtk_combo_box_set_active(GTK_COMBO_BOX(currency_cbt), 0);
  GtkComboBoxText *type_choice =
      (GtkComboBoxText *)gtk_builder_get_object(builder, "type_choice");
  gtk_combo_box_set_active(GTK_COMBO_BOX(type_choice), 0);

  /* Result text */
  GtkTextView *result_tw =
      (GtkTextView *)gtk_builder_get_object(builder, "result");
  GtkTextBuffer *result_buffer = gtk_text_view_get_buffer(result_tw);

  /* Buttons */
  GtkButton *execute_button =
      (GtkButton *)gtk_builder_get_object(builder, "execute_credit_calc");

  entry_input *one = malloc(1 * sizeof(entry_input));

  one->sum_entry = (GtkEntry *)gtk_builder_get_object(builder, "sum_entry");
  one->term_entry = (GtkEntry *)gtk_builder_get_object(builder, "term_entry");
  one->rate_entry = (GtkEntry *)gtk_builder_get_object(builder, "rate_entry");
  one->term_cbt = years_or_months;
  one->type_credit_cbt = (GtkWidget *)type_choice;
  one->result_buffer = result_buffer;
  g_signal_connect(execute_button, "clicked", G_CALLBACK(execute_credit_func),
                   one);
  GtkButton *quit_button =
      (GtkButton *)gtk_builder_get_object(builder, "quit_credit_calc");
  g_signal_connect_swapped(quit_button, "clicked", G_CALLBACK(quit_window),
                           window);

  gtk_widget_show(GTK_WIDGET(window));
  g_object_unref(builder);
}
