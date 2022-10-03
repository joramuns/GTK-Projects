#ifndef _GUI_APP_H
#define _GUI_APP_H

#include <gtk/gtk.h>

#define VVIEWER_APP_TYPE (vviewer_app_get_type ())
G_DECLARE_FINAL_TYPE (VviewerApp, vviewer_app, VVIEWER, APP,
                      GtkApplication)

VviewerApp *vviewer_app_new (void);

#endif /* _GUI_APP_H */
