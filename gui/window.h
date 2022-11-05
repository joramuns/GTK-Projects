#ifndef _GUI_WINDOW_H
#define _GUI_WINDOW_H

#define WIDTH 500
#define HEIGHT 500

#include "app.h"
#include <gtk/gtk.h>

enum {
  X_AXIS,
  Y_AXIS,
  Z_AXIS,
  X_MOVE,
  Y_MOVE,
  Z_MOVE,
  SCALE,

  N_AXIS
};

#define VVIEWER_APP_WINDOW_TYPE (vviewer_app_window_get_type ())
G_DECLARE_FINAL_TYPE (VviewerAppWindow, vviewer_app_window, VVIEWER, APP_WINDOW, GtkApplicationWindow)

VviewerAppWindow *vviewer_app_window_new (VviewerApp *app);
void vviewer_app_window_open (VviewerAppWindow *win, GFile *file);

#endif /* _GUI_WINDOW_H */
