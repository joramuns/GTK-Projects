//
//  draw_func.c
//  C7_SmartCalc
//
//  Created by Joramun Sasin on 9/1/22.
//

#include "main-gtk.h"
#define SCREENSIZE 185

static void draw_plot(gdouble clipX1, gdouble clipX2, cairo_t *cr, char *output) {
    int ex_code = 0;
    if (output != NULL) {
        for (gdouble x = x_min; x < x_max && ex_code == 0; x += (x_max - x_min)/1000) {
            double y = 0;
            ex_code = calculate_var(output, &y, x);
            double resultAtan = fabs(fabs(atan(y)) - M_PI_2);
            if (resultAtan <= (x_max - x_min)/1000 || isnan(y))
                cairo_new_sub_path(cr);
            else
                cairo_line_to(cr, x, y);
        }
    }
}

static void draw_grid(int width, int height, cairo_t *cr, gdouble dx) {
    cairo_set_source_rgba(cr, 0.99, 0.98, 1, 0.2);
    cairo_set_line_width(cr, dx);
//    for (double i = 0; i < width; i += 1) {
//        cairo_move_to(cr, -width / 2, i);
//        cairo_line_to(cr, width / 2, i);
//    }
//    for (double i = 0; fabs(i) < width; i -= 1) {
//        cairo_move_to(cr, -width / 2, i);
//        cairo_line_to(cr, width / 2, i);
//    }
//    for (double i = 0; i < height; i += 1) {
//        cairo_move_to(cr, i, -height / 2);
//        cairo_line_to(cr, i, height / 2);
//    }
//    for (double i = 0; fabs(i) < height; i -= 1) {
//        cairo_move_to(cr, i, -height / 2);
//        cairo_line_to(cr, i, height / 2);
//    }
    cairo_stroke(cr);
}

void graph_draw(GtkDrawingArea *area, cairo_t *cr, int width, int height, gpointer user_data) {
    gdouble dx = 2, dy = 2;
    gdouble i, clipX1 = 0.0, clipY1 = 0.0, clipX2 = 0.0, clipY2 = 0.0;
    cairo_set_source_rgba(cr, 0.1, 0.1, 0.8, 0.8);
    cairo_paint(cr);
    // TRY
    double x_range = (x_max - x_min)/2;
    double x_offset = (x_min + x_max)/2;
    double y_range = (y_max - y_min)/2;
    double y_offset = (y_min + y_max)/2;
    // задана область значений -1 до 1 -> mod(-1) + mod(1) = 2 - ширина видимости, -1 + 1 = 0 - сдвиг видимости
//    (50, 50) & (50, -50)
    // -2 - 2 -> mod(-2) + mod(2) = 4, -2 + 2 = 0
    // 150, 150 & 75, -75 -> 150, 150 - screen size / domain(4)/2 = 75
    // -3, 3 -> mod(-3) + mod(3) = 6, -3+3=0
    // 150 / (6/3), -150 / (6/3)
    // -6, 0 -> mod(-6) + mod(0) = 6 -6+0=-6
//    cairo_translate(cr, 150 - ((-6/2)*(150/(6/2))), 150);
    cairo_translate(cr, SCREENSIZE - (x_offset*(SCREENSIZE/x_range)), SCREENSIZE - (y_offset*(SCREENSIZE/-y_range)));
    /* измениять scale для разных маштабов */
//    cairo_scale(cr, scaleX, -scaleY);
//    cairo_scale(cr, 150 / (6/2), - 150 / (6/2));
    cairo_scale(cr, SCREENSIZE / x_range, - SCREENSIZE / y_range);
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
