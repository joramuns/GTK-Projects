//
//  main.h
//  C7_SmartCalc
//
//  Created by Joramun Sasin on 8/29/22.
//

#ifndef main_h
#define main_h

#include <stdio.h>
#include <gtk/gtk.h>
#include <string.h>
#include "Calculation/calculator.h"
#include "Calculation/credit_calculator.h"
#include "Calculation/deposit_calculator.h"

extern double x_min;
extern double x_max;
extern double y_min;
extern double y_max;

typedef struct {
    GtkButton *button;
    GtkEntry *entry;
    GtkEntry *entry_res;
    char *value;
    char *name;
    GtkEntry *x_min;
    GtkEntry *x_max;
    GtkEntry *y_min;
    GtkEntry *y_max;
    GtkWidget *area;
    GtkToggleButton *toggle_button;
} buttonData;

typedef struct entry_input {
    GtkEntry *sum_entry;
    GtkEntry *term_entry;
    GtkEntry *rate_entry;
    GtkEntry *tax_rate_entry;
    GtkComboBoxText *term_cbt;
    GtkWidget *type_credit_cbt;
    GtkTextBuffer *result_buffer;
    GtkComboBoxText *type_payouts;
    GtkWidget *wd_tree_view;
    GtkTreeStore *withdrawal_window;
} entry_input;

typedef struct wd_cont {
    GtkWidget *wd_tree_view;
    GtkTreeStore *withdrawal_window;
    GtkEntry *entry_withdrawal;
    GtkEntry *date_withdrawal;
} wd_cont;

void quit_window (GtkWindow *window);

/*                          drawing graph                                       */
static void draw_plot(gdouble clipX1, gdouble clipX2, cairo_t *cr, char *output);
static void draw_grid(int width, int height, cairo_t *cr, gdouble dx);
void graph_draw(GtkDrawingArea *area, cairo_t *cr, int width, int height, gpointer user_data);

/*                          input handling                                      */
void add_text(GtkButton *widget, gpointer data);
void del_text(GtkButton *widget, gpointer data);
void get_result(GtkButton *widget, gpointer data);
void set_zero(GtkButton *widget, gpointer data);

/*                         credit calculator                                    */
void credit_calc_window(GtkButton *widget, gpointer data);
void deposit_calc_window(GtkButton *widget, gpointer data);

#endif /* main_h */
