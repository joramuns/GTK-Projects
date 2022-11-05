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
  GtkBox *axis_box;
  GLfloat *rotation_angles[N_AXIS];
};

G_DEFINE_TYPE (VviewerAppWindow, vviewer_app_window,
               GTK_TYPE_APPLICATION_WINDOW);

static void axis_change_cb (GtkAdjustment *adjustment, gpointer data) {
  int axis = GPOINTER_TO_INT(data);

  g_assert(axis >= 0 && axis < N_AXIS);

  /* Update the rotation angle */
  /* rotation_angles[axis] = gtk_adjustment_get_value(adjustment); */

  /* for (int i = 0; i < N_AXIS; i++) { */
  /* g_print("%i = %f\n", i, rotation_angles[i]); */
  /* } */

  /* g_print("Color: %f %f %f %f\n", background_color.red, background_color.green, background_color.blue, background_color.alpha); */
  /* g_print("Color: %f %f %f %f\n", fragment_color.red, fragment_color.green, fragment_color.blue, fragment_color.alpha); */
  /* /1* Update the contents of the GL drawing area *1/ */
  /* gtk_widget_queue_draw(gl_area); */
}
GtkWidget *create_axis_slider(int axis) {
  GtkWidget *box, *label, *slider, *spinbutton;
  GtkAdjustment *adj;
  const char *text;

  box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);

  switch (axis) {
    case X_AXIS: text = "X axis"; break;

    case Y_AXIS: text = "Y axis"; break;

    case Z_AXIS: text = "Z axis"; break;

    case X_MOVE: text = "X move"; break;

    case Y_MOVE: text = "Y move"; break;

    case Z_MOVE: text = "Z move"; break;

    case SCALE: text = "Scale"; break;

    default: g_assert_not_reached();
  }

  label = gtk_label_new(text);
  gtk_box_append(GTK_BOX(box), label);
  gtk_widget_show(label);

  if (axis < X_MOVE) {
    adj = gtk_adjustment_new(0.0, 0.0, 360.0, 1.0, 12.0, 0.0);
  } else if (axis == SCALE) {
    adj = gtk_adjustment_new(0, -1.0, 5.0, 0.1, 12.0, 0.0);
  } else {
    adj = gtk_adjustment_new(0.0, -1.0, 1.0, 0.1, 12.0, 0.0);
  }
  g_signal_connect(adj, "value-changed", G_CALLBACK(axis_change_cb),
                   GINT_TO_POINTER(axis));
  slider = gtk_scale_new(GTK_ORIENTATION_HORIZONTAL, adj);
  spinbutton = gtk_spin_button_new(adj, 1, 1);
  gtk_box_append(GTK_BOX(box), slider);
  gtk_box_append(GTK_BOX(box), spinbutton);
  gtk_widget_set_size_request(spinbutton, 120, 10);
  gtk_widget_set_hexpand(slider, TRUE);
  gtk_widget_show(slider);

  return box;
}

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
      "Select a file", GTK_WINDOW(win), GTK_FILE_CHOOSER_ACTION_OPEN, "_Open", "_Cancel");
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

  for (int i = 0; i < N_AXIS; i++)
    gtk_box_append (GTK_BOX (win->axis_box), create_axis_slider (i));
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
                                        VviewerAppWindow, axis_box);
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
