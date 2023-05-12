#ifndef _GUI_WINDOW_H
#define _GUI_WINDOW_H

#define WIDTH 500
#define HEIGHT 500
#define GIFWIDTH 640
#define GIFHEIGHT 480

#include "app.h"
#include "../core/affine_transformations.h"
#include <gtk/gtk.h>

#define VVIEWER_APP_WINDOW_TYPE (vviewer_app_window_get_type ())
G_DECLARE_FINAL_TYPE (VviewerAppWindow, vviewer_app_window, VVIEWER, APP_WINDOW, GtkApplicationWindow)

VviewerAppWindow *vviewer_app_window_new (VviewerApp *app);
void vviewer_app_window_open (VviewerAppWindow *win, GFile *file);

#endif /* _GUI_WINDOW_H */
