#ifndef _GUI_UTILS_H
#define _GUI_UTILS_H

#include <gtk/gtk.h>

GdkRGBA*
get_rgba_settings_prop (GSettings *settings,
                             const char *prop);

void
set_rgba_settings_prop (GSettings *settings,
                        const char *prop,
                        GdkRGBA* rgba);

#endif /** _GUI_UTILS_H **/
