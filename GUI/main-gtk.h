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
#include "../calculator.h"

typedef struct {
    GtkButton *button;
    GtkEntry *entry;
    GtkEntry *entry_res;
    char *value;
    char *name;
} buttonData;

/*                          drawing graph                                       */
static void draw_plot(gdouble clipX1, gdouble clipX2, cairo_t *cr, char *output);
static void draw_grid(int width, int height, cairo_t *cr, gdouble dx);
void graph_draw(GtkDrawingArea *area, cairo_t *cr, int width, int height, gpointer user_data);
void add_grid_plot(char *output);

/*                          input handling                                      */
void add_text(GtkButton *widget, gpointer data);
void del_text(GtkButton *widget, gpointer data);
void get_result(GtkButton *widget, gpointer data);
void set_zero(GtkButton *widget, gpointer data);

#endif /* main_h */
