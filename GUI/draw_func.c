//
//  draw_func.c
//  C7_SmartCalc
//
//  Created by Joramun Sasin on 9/1/22.
//

#include "../main-gtk.h"
#define SCREENSIZE 185

static void draw_plot(cairo_t *cr, char *output) {
  if (output != NULL) {
    int ex_code = 0;
    for (double x = x_min; x < x_max && ex_code == 0;
         x += (x_max - x_min) / 1000) {
      double y = 0;
      ex_code = calculate_var(output, &y, x);
      double resultAtan = fabs(fabs(atan(y)) - M_PI_2);
      if (resultAtan <= (x_max - x_min) / 1000 || isnan(y))
        cairo_new_sub_path(cr);
      else
        cairo_line_to(cr, x, -y);
    }
  }
}

static void draw_grid(double width, double height, cairo_t *cr, gdouble dx) {
  cairo_set_source_rgba(cr, 0.99, 0.98, 1, 0.2);
  cairo_set_line_width(cr, dx);
  cairo_select_font_face(cr, "monospace", CAIRO_FONT_SLANT_NORMAL,
                         CAIRO_FONT_WEIGHT_NORMAL);
  cairo_move_to(cr, 0, 0);
  double iterator_x = (fabs(x_min) + fabs(x_max)) / 10;
  double iterator_y = (fabs(y_min) + fabs(y_max)) / 10;
  cairo_set_font_size(cr, iterator_x / 2.5);
  cairo_show_text(cr, "0");
  char *autobuffer = NULL;
  for (double i = 0; i < width; i += iterator_x) {
    cairo_move_to(cr, i, -height / 2);
    cairo_line_to(cr, i, height / 2);
    cairo_move_to(cr, -i, -height / 2);
    cairo_line_to(cr, -i, height / 2);
    if (i != 0) {
      cairo_move_to(cr, i, -y_min);
      asprintf(&autobuffer, "%g", i);
      cairo_show_text(cr, autobuffer);
      free(autobuffer);
      cairo_move_to(cr, -i, -y_min);
      asprintf(&autobuffer, "%g", -i);
      cairo_show_text(cr, autobuffer);
      free(autobuffer);
    }
  }
  for (double i = 0; i < height; i += iterator_y) {
    cairo_move_to(cr, -width / 2, i);
    cairo_line_to(cr, width / 2, i);
    cairo_move_to(cr, -width / 2, -i);
    cairo_line_to(cr, width / 2, -i);
    if (i != 0) {
      cairo_move_to(cr, x_min, i);
      asprintf(&autobuffer, "%g", -i);
      cairo_show_text(cr, autobuffer);
      free(autobuffer);
      cairo_move_to(cr, x_min, -i);
      asprintf(&autobuffer, "%g", i);
      cairo_show_text(cr, autobuffer);
      free(autobuffer);
    }
  }
  cairo_stroke(cr);
}

void graph_draw(GtkDrawingArea *area, cairo_t *cr, int width, int height,
                gpointer user_data) {
  gdouble dx = 2, dy = 2;
  gdouble clipX1 = 0.0, clipY1 = 0.0, clipX2 = 0.0, clipY2 = 0.0;
  cairo_set_source_rgba(cr, 0.29, 0.58, 0.45, 1);
  cairo_paint(cr);
  double x_range = (x_max - x_min) / 2;
  double x_offset = (x_min + x_max) / 2;
  double y_range = (y_max - y_min) / 2;
  double y_offset = (y_min + y_max) / 2;
  cairo_translate(cr, SCREENSIZE - (x_offset * (SCREENSIZE / x_range)),
                  SCREENSIZE - (y_offset * (SCREENSIZE / -y_range)));
  cairo_scale(cr, SCREENSIZE / x_range, SCREENSIZE / y_range);
  cairo_device_to_user_distance(cr, &dx, &dy);
  cairo_clip_extents(cr, &clipX1, &clipY1, &clipX2, &clipY2);
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
    draw_plot(cr, user_data);
  }
  cairo_stroke(cr);
}
