/** \file window.c
 *  \brief Main application window implementation
 */
#include "window.h"

#include "core/obj_parser.h"
#include "glibconfig.h"
#include "model.h"

struct _VviewerAppWindow
{
  GtkApplicationWindow parent;

  GMenuModel *menu;
  GtkMenuButton *gears;
  GtkButton *open_file_button;
  GtkBox *model_view;
};

G_DEFINE_TYPE (VviewerAppWindow, vviewer_app_window,
               GTK_TYPE_APPLICATION_WINDOW);

static void
open_dialog_response_cb (GtkNativeDialog *dialog, int response,
                         VviewerAppWindow *win)
{
  gtk_native_dialog_hide (dialog);
  if (response == GTK_RESPONSE_ACCEPT)
    {
      GtkWidget *old_model = gtk_widget_get_first_child (GTK_WIDGET(win->model_view));
      if (old_model != NULL)
        gtk_box_remove (win->model_view, GTK_WIDGET(old_model));

      gfloat color[4] = { 1, 1, 1, 0.5 };
      GFile *file = gtk_file_chooser_get_file (GTK_FILE_CHOOSER (dialog));
      GArray *vertices = g_array_sized_new (FALSE, TRUE, sizeof (GLuint), 100);
      GArray *indices = g_array_sized_new (FALSE, TRUE, sizeof (GLuint), 100);
      char *filename = g_file_get_path (file);

      parse_obj_file (filename, vertices, indices);
      ModelGLArea *model = model_gl_area_new (vertices, indices, color);
      gtk_box_append (win->model_view, GTK_WIDGET (model));

      g_free (filename);
      g_object_unref (G_OBJECT (file));
    }
  gtk_native_dialog_destroy (dialog);
}

static void
read_obj_file_cb (VviewerAppWindow *win, GtkButton *button)
{
  GtkFileChooserNative *dialog = gtk_file_chooser_native_new (
      "Select a file", win, GTK_FILE_CHOOSER_ACTION_OPEN, "_Open", "_Cancel");
  g_signal_connect (dialog, "response", G_CALLBACK (open_dialog_response_cb),
                    win);
  gtk_native_dialog_show (GTK_NATIVE_DIALOG (dialog));
}

static void
vviewer_app_window_init (VviewerAppWindow *win)
{
  gtk_widget_init_template (GTK_WIDGET (win));
  gtk_window_set_default_size (GTK_WINDOW (win), WIDTH, HEIGHT);

  gtk_menu_button_set_menu_model (win->gears, G_MENU_MODEL (win->menu));

  // g_signal_connect(win->open_file_button, "clicked",
  // G_CALLBACK(read_obj_file_cb), NULL);
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
                                        VviewerAppWindow, model_view);
  gtk_widget_class_bind_template_child (GTK_WIDGET_CLASS (class),
                                        VviewerAppWindow, open_file_button);
  gtk_widget_class_bind_template_callback (GTK_WIDGET_CLASS (class),
                                           read_obj_file_cb);
}

VviewerAppWindow *
vviewer_app_window_new (VviewerApp *app)
{
  return g_object_new (VVIEWER_APP_WINDOW_TYPE, "application", app, NULL);
}
