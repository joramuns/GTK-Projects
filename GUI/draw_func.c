//
//  draw_func.c
//  C7_SmartCalc
//
//  Created by Joramun Sasin on 9/1/22.
//

#include "main-gtk.h"

static void draw_plot(gdouble clipX1, gdouble clipX2, cairo_t *cr, char *output) {
    int ex_code = 0;
    if (output != NULL) {
        for (gdouble x = clipX1; x < clipX2 && ex_code == 0; x += 0.005) {
            double y = 0;
            ex_code = calculate_var(output, &y, x);
            double resultAtan = fabs(fabs(atan(y)) - M_PI_2);
            if (resultAtan <= 0.005 || isnan(y))
                cairo_new_sub_path(cr);
            else
                cairo_line_to(cr, x, y);
        }
    }
}

static void draw_grid(int width, int height, cairo_t *cr, gdouble dx) {
    cairo_set_source_rgba(cr, 0.99, 0.98, 1, 0.2);
    cairo_set_line_width(cr, dx);
    for (double i = 0; i < width; i += 1) {
        cairo_move_to(cr, -width / 2, i);
        cairo_line_to(cr, width / 2, i);
    }
    for (double i = 0; fabs(i) < width; i -= 1) {
        cairo_move_to(cr, -width / 2, i);
        cairo_line_to(cr, width / 2, i);
    }
    for (double i = 0; i < height; i += 1) {
        cairo_move_to(cr, i, -height / 2);
        cairo_line_to(cr, i, height / 2);
    }
    for (double i = 0; fabs(i) < height; i -= 1) {
        cairo_move_to(cr, i, -height / 2);
        cairo_line_to(cr, i, height / 2);
    }
    cairo_stroke(cr);
}

void graph_draw(GtkDrawingArea *area, cairo_t *cr, int width, int height, gpointer user_data) {
    g_print("TEST\n");
    gdouble dx = 2, dy = 2;
    gdouble i, clipX1 = 0.0, clipY1 = 0.0, clipX2 = 0.0, clipY2 = 0.0;
    cairo_set_source_rgba(cr, 0.1, 0.1, 0.8, 0.8);
    cairo_paint(cr);
    cairo_translate(cr, 300 / 2, 300 / 2);
    /* измениять scale для разных маштабов */
//    cairo_scale(cr, scaleX, -scaleY);
    cairo_scale(cr, 50, -50);
    /* определить границы графика */
    cairo_device_to_user_distance(cr, &dx, &dy);
    cairo_clip_extents(cr, &clipX1, &clipY1, &clipX2, &clipY2);
    /* рисую оси X и Y */
    cairo_set_line_width(cr, dx);
    cairo_set_source_rgba(cr, 0.99, 0.98, 1, 0.5);
    cairo_move_to(cr, clipX1, 0.0);
    cairo_line_to(cr, clipX2, 0.0);
    cairo_move_to(cr, 0.0, clipY1);
    cairo_line_to(cr, 0.0, clipY2);
    cairo_stroke(cr);
    draw_grid(width, height, cr, dx);
    //
    cairo_set_line_width(cr, dx);
    cairo_set_source_rgba(cr, 1, 0, 0, 1);
    if (user_data != NULL) {
        draw_plot(clipX1, clipX2, cr, user_data);
    }
    cairo_stroke(cr);
}

void add_grid_plot(char *output) {
    GtkBuilder *build = gtk_builder_new_from_file("./Style/plot-o.ui");
    GtkWidget *windowPlot = GTK_WIDGET(gtk_builder_get_object(build, "windowPlot"));
    GtkWidget *area = GTK_WIDGET(gtk_builder_get_object(build, "area"));
    char *output_malloced = NULL;
    if (output) {
        output_malloced = malloc(strlen(output) + 1);
        strcpy(output_malloced, output);
    }
    gtk_drawing_area_set_draw_func(GTK_DRAWING_AREA(area), graph_draw, output_malloced, NULL);
    GtkWidget *overlay = GTK_WIDGET(gtk_builder_get_object(build, "overlay"));
    GtkWidget *gridPlot = GTK_WIDGET(gtk_builder_get_object(build, "gridPlot"));
    gtk_overlay_set_child(GTK_OVERLAY(overlay), area);
    gtk_overlay_add_overlay(GTK_OVERLAY(overlay), gridPlot);
    gtk_widget_show(windowPlot);
//    free(output_malloced);
}
