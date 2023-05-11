//
//  2main.c
//  C7_SmartCalc
//
//  Created by Joramun Sasin on 8/18/22.
//

#include "main-gtk.h"

double x_min = -10;
double x_max = 10;
double y_min = -10;
double y_max = 10;

void quit_window(GtkWindow *window) { gtk_window_close(window); }

void toggle_graph_func(GtkToggleButton *togglebutton, gpointer user_data) {
  buttonData *current = user_data;
  gboolean status = gtk_toggle_button_get_active(togglebutton);

  gtk_editable_set_editable(GTK_EDITABLE(current->x_max), status);
  gtk_editable_set_text(GTK_EDITABLE(current->x_max), "");
  gtk_editable_set_text(GTK_EDITABLE(current->x_min), "");
  gtk_editable_set_editable(GTK_EDITABLE(current->y_min), status);
  gtk_editable_set_text(GTK_EDITABLE(current->y_min), "");
  gtk_editable_set_editable(GTK_EDITABLE(current->y_max), status);
  gtk_editable_set_text(GTK_EDITABLE(current->y_max), "");

  if (status) {
    gtk_entry_set_placeholder_text(current->x_min, "Dominant min");
    gtk_entry_set_placeholder_text(current->x_max, "Dominant max");
    gtk_entry_set_placeholder_text(current->y_min, "Codominant min");
    gtk_entry_set_placeholder_text(current->y_max, "Codominant max");
    x_min = -10;
    x_max = 10;
    y_min = -10;
    y_max = 10;
  } else {
    x_min = 0;
    gtk_entry_set_placeholder_text(current->x_min, "X value");
    gtk_entry_set_placeholder_text(current->x_max, "inactive");
    gtk_entry_set_placeholder_text(current->y_min, "inactive");
    gtk_entry_set_placeholder_text(current->y_max, "inactive");
  }
}

void activate(GtkApplication *app, gpointer user_data) {
  GtkBuilder *builder = gtk_builder_new();
  gtk_builder_add_from_resource(builder, "/org/gtk/Style/builder-o.ui", NULL);
  GObject *window = gtk_builder_get_object(builder, "window");
  gtk_window_set_application(GTK_WINDOW(window), app);

  /* style */
  GtkCssProvider *cssProvider = gtk_css_provider_new();
  GdkDisplay *display = gtk_widget_get_display(GTK_WIDGET(window));
  gtk_css_provider_load_from_resource(cssProvider, "/org/gtk/Style/theme.css");
  gtk_style_context_add_provider_for_display(
      display, GTK_STYLE_PROVIDER(cssProvider),
      GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
  g_object_unref(cssProvider);

  /* input */
  GtkEntry *entry_func;
  entry_func = (GtkEntry *)gtk_builder_get_object(builder, "entry_func");
  gtk_entry_set_max_length(GTK_ENTRY(entry_func), EXPRESSION_SIZE);
  /* output */
  GtkEntry *entry_res;
  entry_res = (GtkEntry *)gtk_builder_get_object(builder, "entry_res");
  /* codominant and dominant */
  GtkToggleButton *graph_check =
      (GtkToggleButton *)gtk_builder_get_object(builder, "check_box");
  gtk_toggle_button_set_active(graph_check, 1);
  GtkEntry *dom_min =
      (GtkEntry *)gtk_builder_get_object(builder, "entry_dom_min");
  gtk_entry_set_max_length(GTK_ENTRY(dom_min), EXPRESSION_SIZE);
  gtk_entry_set_placeholder_text(dom_min, "Dominant min");
  GtkEntry *dom_max =
      (GtkEntry *)gtk_builder_get_object(builder, "entry_dom_max");
  gtk_entry_set_max_length(GTK_ENTRY(dom_max), EXPRESSION_SIZE);
  gtk_entry_set_placeholder_text(dom_max, "Dominant max");
  GtkEntry *codom_min =
      (GtkEntry *)gtk_builder_get_object(builder, "entry_codom_min");
  gtk_entry_set_placeholder_text(codom_min, "Codominant min");
  gtk_entry_set_max_length(GTK_ENTRY(codom_min), EXPRESSION_SIZE);
  GtkEntry *codom_max =
      (GtkEntry *)gtk_builder_get_object(builder, "entry_codom_max");
  gtk_entry_set_placeholder_text(codom_max, "Codominant max");
  gtk_entry_set_max_length(GTK_ENTRY(codom_max), EXPRESSION_SIZE);

  /* buttons */
  buttonData *buttons = user_data;

  /* draw area */
  GtkWidget *area = GTK_WIDGET(gtk_builder_get_object(builder, "area"));
  gtk_drawing_area_set_draw_func(GTK_DRAWING_AREA(area), graph_draw, NULL,
                                 NULL);
  GtkWidget *overlay = GTK_WIDGET(gtk_builder_get_object(builder, "overlay"));
  GtkWidget *gridPlot = GTK_WIDGET(gtk_builder_get_object(builder, "gridPlot"));
  gtk_overlay_set_child(GTK_OVERLAY(overlay), area);
  gtk_overlay_add_overlay(GTK_OVERLAY(overlay), gridPlot);

  char *names[] = {
      "button0",         "button1",          "button2",      "button3",
      "button4",         "button5",          "button6",      "button7",
      "button8",         "button9",          "buttondot",    "buttonsum",
      "buttonsub",       "buttonmul",        "buttondiv",    "quit",
      "buttondel",       "buttonres",        "buttonzero",   "buttonpow",
      "buttonopenbrace", "buttonclosebrace", "buttonacos",   "buttonasin",
      "buttonatan",      "buttonsqrt",       "buttonsin",    "buttoncos",
      "buttonmod",       "buttontan",        "buttonlog",    "buttonln",
      "buttonvar",       "buttoncredit",     "buttondeposit"};
  const char *values[] = {
      "0",    "1",   "2",    "3",    "4",     "5",     "6",     "7",     "8",
      "9",    ".",   "+",    "-",    "*",     "/",     NULL,    NULL,    NULL,
      NULL,   "^",   "(",    ")",    "acos(", "asin(", "atan(", "sqrt(", "sin(",
      "cos(", "mod", "tan(", "log(", "ln(",   "X",     NULL,    NULL};

  for (int i = 0; i < 35; ++i) {
    buttons[i].name = names[i];
    buttons[i].value = (char *)values[i];
    buttons[i].entry = entry_func;
    buttons[i].entry_res = entry_res;
    buttons[i].button = (GtkButton *)gtk_builder_get_object(builder, names[i]);
    gtk_button_set_has_frame(buttons[i].button, 0);
    gtk_button_set_has_frame(buttons[i].button, 1);
    buttons[i].x_min = dom_min;
    buttons[i].x_max = dom_max;
    buttons[i].y_min = codom_min;
    buttons[i].y_max = codom_max;
    buttons[i].area = area;
    buttons[i].toggle_button = graph_check;
    if (values[i] != NULL) {
      g_signal_connect(buttons[i].button, "clicked", G_CALLBACK(add_text),
                       &buttons[i]);
    } else if (i == 18) {
      g_signal_connect(buttons[i].button, "clicked", G_CALLBACK(set_zero),
                       &buttons[i]);
    } else if (i == 17) {
      g_signal_connect(buttons[i].button, "clicked", G_CALLBACK(get_result),
                       &buttons[i]);
    } else if (i == 16) {
      g_signal_connect(buttons[i].button, "clicked", G_CALLBACK(del_text),
                       &buttons[i]);
    } else if (i == 15) {
      g_signal_connect_swapped(buttons[i].button, "clicked",
                               G_CALLBACK(quit_window), window);
    } else if (i == 33) {
      g_signal_connect(buttons[i].button, "clicked",
                       G_CALLBACK(credit_calc_window), &buttons[i]);
    } else if (i == 34) {
      g_signal_connect(buttons[i].button, "clicked",
                       G_CALLBACK(deposit_calc_window), &buttons[i]);
    }
  }
  g_signal_connect(graph_check, "toggled", G_CALLBACK(toggle_graph_func),
                   &buttons[0]);

  gtk_widget_show(GTK_WIDGET(window));
  g_object_unref(builder);
}

int main(int argc, char **argv) {
  GtkApplication *app;
  int status;

  buttonData *buttons[34 * sizeof(buttonData)] = {0};

  app = gtk_application_new("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect(app, "activate", G_CALLBACK(activate), &buttons);

  status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return status;
}
