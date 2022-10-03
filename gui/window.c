/** \file window.c
 *  \brief Main application window implementation
 */
#include "app.h"
#include "window.h"

struct _VviewerAppWindow
{
  GtkApplicationWindow parent;

  GMenuModel *menu;
  GtkMenuButton *gears;
  GtkBox *view;
};

G_DEFINE_TYPE (VviewerAppWindow, vviewer_app_window,
               GTK_TYPE_APPLICATION_WINDOW);

static void
vviewer_app_window_init (VviewerAppWindow *win)
{
  gtk_widget_init_template (GTK_WIDGET (win));

  gtk_menu_button_set_menu_model (win->gears, G_MENU_MODEL (win->menu));
}

static void
vviewer_app_window_class_init (VviewerAppWindowClass *class)
{
  gtk_widget_class_set_template_from_resource (
      GTK_WIDGET_CLASS (class),
      "/com/github/Gwarek2/Viewer/gui/templates/window.ui");

  gtk_widget_class_bind_template_child (GTK_WIDGET_CLASS (class),
                                        VviewerAppWindow, menu);
  gtk_widget_class_bind_template_child (GTK_WIDGET_CLASS (class),
                                        VviewerAppWindow, gears);
  gtk_widget_class_bind_template_child (GTK_WIDGET_CLASS (class),
                                        VviewerAppWindow, view);
}

VviewerAppWindow *
vviewer_app_window_new (VviewerApp *app)
{
  return g_object_new (VVIEWER_APP_WINDOW_TYPE, "application", app, NULL);
}
