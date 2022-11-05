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
  GtkButton *reset_axis;
  GtkBox *axis_box;
  GLfloat *rotation_angles;
  GtkAdjustment *axises[N_AXIS];
};

G_DEFINE_TYPE (VviewerAppWindow, vviewer_app_window,
               GTK_TYPE_APPLICATION_WINDOW);

static void axis_change_cb (GtkAdjustment *adjustment, gpointer data) {
  VviewerAppWindow *win = (VviewerAppWindow *) data;
  for (int i = 0; i < N_AXIS; i++) {
    win->rotation_angles[i] = gtk_adjustment_get_value(win->axises[i]);
    g_print("%f\n", win->rotation_angles[i]);
    g_print("%p\n", win);
  }   
}

static void reset_axis_cb (VviewerAppWindow *win, GtkButton *button) {
  for (int i = 0; i < N_AXIS; i++) {
   win->rotation_angles[i] = 0;
   gtk_adjustment_set_value(win->axises[i], 0);
  }
}

GtkWidget *create_axis_slider(int axis, VviewerAppWindow *win) {
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
    adj = gtk_adjustment_new(0, -0.9, 5.0, 0.1, 12.0, 0.0);
  } else {
    adj = gtk_adjustment_new(0.0, -1.0, 1.0, 0.1, 12.0, 0.0);
  }
  win->axises[axis] = adj;
  g_signal_connect(adj, "value-changed", G_CALLBACK(axis_change_cb), win);
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
  win->rotation_angles = g_malloc(N_AXIS * sizeof(GLfloat));

  gtk_menu_button_set_menu_model (win->gears, G_MENU_MODEL (win->menu));

  for (int i = 0; i < N_AXIS; i++)
    gtk_box_append (GTK_BOX (win->axis_box), create_axis_slider (i, win));
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
  gtk_widget_class_bind_template_child (GTK_WIDGET_CLASS (class),
                                        VviewerAppWindow, reset_axis);
  gtk_widget_class_bind_template_callback (GTK_WIDGET_CLASS (class),
                                           reset_axis_cb);
}

VviewerAppWindow *
vviewer_app_window_new (VviewerApp *app)
{
  return g_object_new (VVIEWER_APP_WINDOW_TYPE, "application", app, NULL);
}
