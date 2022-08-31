//
//  2main.c
//  C7_SmartCalc
//
//  Created by Joramun Sasin on 8/18/22.
//

#include <stdio.h>
#include <gtk/gtk.h>
#include <string.h>
#include "main-gtk.h"

char* replace_var(char* str, char find, char replace){
    char *current_pos = strchr(str,find);
    while (current_pos) {
        *current_pos = replace;
        current_pos = strchr(current_pos,find);
    }
    return str;
}

static void draw_plot(gdouble clipX1, gdouble clipX2, cairo_t *cr, char *output) {
    char var_output[strlen(output)];
    for (gdouble x = clipX1; x < clipX2; x += 0.005) {
        strcpy(var_output, output);
        replace(var_output, 'X', )
        double y = 0;
        calculate(output, &y); // output, x
        double resultAtan = fabs(fabs(atan(y)) - M_PI_2);
        if (resultAtan <= 0.005 || isnan(y))
            cairo_new_sub_path(cr);
        else
            cairo_line_to(cr, x, y);
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
    gdouble dx = 2, dy = 2;
    gdouble i, clipX1 = 0.0, clipY1 = 0.0, clipX2 = 0.0, clipY2 = 0.0;
    cairo_set_source_rgba(cr, 0.55, 0.55, 0.91, 1);
    cairo_paint(cr);
    cairo_translate(cr, 800 / 2, 300 / 2);
    /* измениять scale для разных маштабов */
//    cairo_scale(cr, scaleX, -scaleY);
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
    cairo_set_source_rgba(cr, 0.99, 0.98, 1, 1);
    char *output = user_data;
    draw_plot(clipX1, clipX2, cr, output);
    cairo_stroke(cr);
}

void add_grid_plot(char *output) {
    GtkBuilder *build = gtk_builder_new_from_file("Style/plot-o.ui");
    GtkWidget *windowPlot = GTK_WIDGET(gtk_builder_get_object(build, "windowPlot"));
    GtkWidget *area = GTK_WIDGET(gtk_builder_get_object(build, "area"));
    gtk_drawing_area_set_draw_func(GTK_DRAWING_AREA(area), graph_draw, output, NULL);
    GtkWidget *overlay = GTK_WIDGET(gtk_builder_get_object(build, "overlay"));
    GtkWidget *gridPlot = GTK_WIDGET(gtk_builder_get_object(build, "gridPlot"));
    gtk_overlay_set_child(GTK_OVERLAY(overlay), area);
    gtk_overlay_add_overlay(GTK_OVERLAY(overlay), gridPlot);
    gtk_widget_show(windowPlot);
}

void quit_cb (GtkWindow *window)
{
  gtk_window_close (window);
}

void add_text(GtkButton *widget, gpointer data) {
    buttonData *current = data;
    GtkText *entry = current->entry;
    GtkEntryBuffer *entryBuffer = gtk_text_get_buffer(entry);
    size_t length_buf = strlen(gtk_entry_buffer_get_text(entryBuffer));
    char *output = (char *) malloc(1 + length_buf + strlen(current->value));
    strcpy(output, gtk_entry_buffer_get_text(entryBuffer));
    strcat(output, current->value);
    gtk_entry_buffer_set_text(entryBuffer, output, strlen(output));
    free(output);
}

void del_text(GtkButton *widget, gpointer data) {
    buttonData *current = data;
    GtkText *entry = current->entry;
    GtkEntryBuffer *entryBuffer = gtk_text_get_buffer(entry);
    size_t length_buf = strlen(gtk_entry_buffer_get_text(entryBuffer));
    char *output = (char *) malloc(1 + length_buf);
    if (length_buf > 0) {
        strcpy(output, gtk_entry_buffer_get_text(entryBuffer));
        output[length_buf - 1] = '\0';
        gtk_entry_buffer_set_text(entryBuffer, output, strlen(output));
    }
    free(output);
}

void get_result(GtkButton *widget, gpointer data) {
    buttonData *current = data;
    GtkText *entry = current->entry;
    GtkEntryBuffer *entryBuffer = gtk_text_get_buffer(entry);
    double result = 0;
    char *output = (char *)gtk_entry_buffer_get_text(entryBuffer);
    int ex_code = calculate(output, &result);
    char buffer[100] = {0};
    if (ex_code == 0) {
        sprintf(buffer, "%g", result);
    } else if (ex_code == VARIABLE_INSIDE) {
        
    } else {
        sprintf(buffer, "Error: %d", ex_code);
    }
    gtk_entry_buffer_set_text(entryBuffer, buffer, strlen(buffer));
}

void set_zero(GtkButton *widget, gpointer data) {
    buttonData *current = data;
    GtkText *entry = current->entry;
    GtkEntryBuffer *entryBuffer = gtk_text_get_buffer(entry);
    gtk_entry_buffer_set_text(entryBuffer, "", 0);
}

static void activate (GtkApplication *app, gpointer user_data) {
    GtkBuilder *builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, "Style/builder-o.ui", NULL);

    GObject *window = gtk_builder_get_object(builder, "window");
    gtk_window_set_application(GTK_WINDOW (window), app);

    /* style */
    GtkCssProvider *cssProvider = gtk_css_provider_new();
    GdkDisplay *display = gtk_widget_get_display(GTK_WIDGET(window));
//    gtk_css_provider_load_from_data(cssProvider, "text {background-color: white; font-family: monospace; font-size: 18pt;}", -1);
    gtk_css_provider_load_from_path(cssProvider, "Style/theme.css");
    gtk_style_context_add_provider_for_display(display, GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    g_object_unref(cssProvider);

    /* interface */
    buttonData *buttons = user_data;

    char *names[] = {"button0", "button1", "button2", "button3", "button4", "button5", "button6", "button7", "button8", "button9", "buttondot", "buttonsum", "buttonsub", "buttonmul", "buttondiv", "quit", "buttondel", "buttonres", "buttonzero", "buttonpow", "buttonopenbrace", "buttonclosebrace", "buttonacos", "buttonasin", "buttonatan", "buttonsqrt", "buttonsin", "buttoncos", "buttonmod", "buttontan", "buttonlog", "buttonln", "buttonvar"};
    char *values[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", ".", "+", "-", "*", "/", NULL, NULL, NULL, NULL, "^", "(", ")", "acos(", "asin(", "atan(", "sqrt(", "sin(", "cos(", "mod", "tan(", "log(", "ln(", "X"};

    for (int i = 0; i < 33; ++i) {
            buttons[i].name = names[i];
            buttons[i].value = values[i];
            buttons[i].entry = (GtkText *) gtk_builder_get_object(builder, "entry");
            buttons[i].button = (GtkButton *) gtk_builder_get_object(builder, names[i]);
            if (values[i] != NULL) {
                g_signal_connect(buttons[i].button, "clicked", G_CALLBACK(add_text), &buttons[i]);
            } else if (i == 18) {
                g_signal_connect(buttons[i].button, "clicked", G_CALLBACK(set_zero), &buttons[i]);
            } else if (i == 17) {
                g_signal_connect(buttons[i].button, "clicked", G_CALLBACK(get_result), &buttons[i]);
            } else if (i == 16) {
            g_signal_connect(buttons[i].button, "clicked", G_CALLBACK(del_text), &buttons[i]);
            } else if (i == 15) {
                g_signal_connect_swapped (buttons[i].button, "clicked", G_CALLBACK (quit_cb), window);
            }
    }


    gtk_widget_show (GTK_WIDGET(window));
    g_object_unref(builder);
}

int main (int argc, char **argv) {
    GtkApplication *app;
    int status;


    buttonData *buttons[32*sizeof(buttonData)] = {0};

    app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
    g_signal_connect (app, "activate", G_CALLBACK (activate), &buttons);
    status = g_application_run (G_APPLICATION (app), argc, argv);
    g_object_unref (app);

  return status;
}
