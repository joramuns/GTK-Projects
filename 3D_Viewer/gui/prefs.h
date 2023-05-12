#ifndef _GUI_VVIEWER_PREFS
#define _GUI_VVIEWER_PREFS

#include <gtk/gtk.h>
#include "window.h"


#define VVIEWER_APP_PREFS_TYPE (vviewer_app_prefs_get_type ())
G_DECLARE_FINAL_TYPE (VviewerAppPrefs, vviewer_app_prefs, VVIEWER, APP_PREFS, GtkDialog)

VviewerAppPrefs *vviewer_app_prefs_new (VviewerAppWindow *win);

#endif /* _GUI_VVIEWER_PREFS */
