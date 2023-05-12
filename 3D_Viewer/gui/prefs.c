#include "prefs.h"
#include "window.h"
#include "utils.h"

#define SELECTED_NOTIFY_TEMPLATE(prop) \
  GSettings *settings = G_SETTINGS (data); \
  GtkDropDown *dropdown = GTK_DROP_DOWN (obj); \
  gint value = gtk_drop_down_get_selected (dropdown); \
  g_settings_set_enum (settings, prop, value);

#define RGBA_NOTIFY_TEMPLATE(prop) \
  GSettings *settings = G_SETTINGS (data); \
  GtkColorChooser *color_chooser = GTK_COLOR_CHOOSER (obj); \
  GdkRGBA *rgba = g_malloc (sizeof(GdkRGBA)); \
  gtk_color_chooser_get_rgba (color_chooser, rgba); \
  set_rgba_settings_prop (settings, prop, rgba); \
  gdk_rgba_free (rgba);

struct _VviewerAppPrefs
{
  GtkDialog parent;

  GSettings *settings;

  GtkDropDown *verticestype;
  GtkSpinButton *verticessize;
  GtkColorButton *verticescolor;

  GtkDropDown *projection;

  GtkDropDown *edgetype;
  GtkSpinButton *edgewidth;
  GtkColorButton *edgecolor;

  GtkColorButton *bgcolor;
};

G_DEFINE_TYPE (VviewerAppPrefs, vviewer_app_prefs, GTK_TYPE_DIALOG);

static void
vertices_type_notify (GObject *obj,
                      GParamSpec *pspec,
                      gpointer data)
{
  SELECTED_NOTIFY_TEMPLATE("vertices-type")
}

static void
vertices_color_notify (GObject *obj,
                       GParamSpec *pspec,
                       gpointer data)
{
  RGBA_NOTIFY_TEMPLATE("vertices-color")
}

static void
projection_type_notify (GObject *obj,
                        GParamSpec *pspec,
                        gpointer data)
{
  SELECTED_NOTIFY_TEMPLATE("projection")
}

static void
edge_type_notify (GObject *obj,
                  GParamSpec *pspec,
                  gpointer data)
{
  SELECTED_NOTIFY_TEMPLATE("edge-type")
}

static void
edge_color_notify (GObject *obj,
                   GParamSpec *pspec,
                   gpointer data)
{
  RGBA_NOTIFY_TEMPLATE("edge-color")
}

static void
bg_color_notify (GObject *obj,
                 GParamSpec *pspec,
                 gpointer data)
{
  RGBA_NOTIFY_TEMPLATE("background-color")
}

static void
vviewer_app_prefs_init (VviewerAppPrefs *prefs)
{
  gtk_widget_init_template (GTK_WIDGET (prefs));
  prefs->settings = g_settings_new ("com.github.Gwarek2.Viewer");

  g_settings_bind (prefs->settings, "vertices-size",
                   prefs->verticessize, "value",
                   G_SETTINGS_BIND_DEFAULT);
  g_settings_bind (prefs->settings, "edge-width",
                   prefs->edgewidth, "value",
                   G_SETTINGS_BIND_DEFAULT);

  gint vertices_type = g_settings_get_enum (prefs->settings, "vertices-type");
  GdkRGBA *vertices_color = get_rgba_settings_prop (prefs->settings,
                                                   "vertices-color");
  gint projection = g_settings_get_enum (prefs->settings, "projection");
  gint edge_type = g_settings_get_enum (prefs->settings, "edge-type");
  GdkRGBA *edge_color = get_rgba_settings_prop(prefs->settings,
                                               "edge-color");
  GdkRGBA *bg_color = get_rgba_settings_prop(prefs->settings,
                                             "background-color");

  gtk_drop_down_set_selected (prefs->verticestype, vertices_type);
  gtk_drop_down_set_selected (prefs->edgetype, edge_type);
  gtk_drop_down_set_selected (prefs->projection, projection);
  gtk_color_chooser_set_rgba (GTK_COLOR_CHOOSER (prefs->verticescolor),
                              vertices_color);
  gtk_color_chooser_set_rgba (GTK_COLOR_CHOOSER (prefs->edgecolor),
                              edge_color);
  gtk_color_chooser_set_rgba (GTK_COLOR_CHOOSER (prefs->bgcolor),
                              bg_color);

  g_signal_connect (prefs->verticestype, "notify::selected",
                    G_CALLBACK (vertices_type_notify), prefs->settings);
  g_signal_connect (prefs->projection, "notify::selected",
                    G_CALLBACK (projection_type_notify), prefs->settings);
  g_signal_connect (prefs->edgetype, "notify::selected",
                    G_CALLBACK (edge_type_notify), prefs->settings);
  g_signal_connect (prefs->verticescolor, "notify::rgba",
                    G_CALLBACK (vertices_color_notify), prefs->settings);
  g_signal_connect (prefs->edgecolor, "notify::rgba",
                    G_CALLBACK (edge_color_notify), prefs->settings);
  g_signal_connect (prefs->bgcolor, "notify::rgba",
                    G_CALLBACK (bg_color_notify), prefs->settings);

  gdk_rgba_free (vertices_color);
}

static void
vviewer_app_prefs_dispose (GObject *object)
{
  VviewerAppPrefs *prefs = VVIEWER_APP_PREFS (object);
  g_clear_object (&prefs->settings);
  G_OBJECT_CLASS (vviewer_app_prefs_parent_class)->dispose (object);
}

static void
vviewer_app_prefs_class_init (VviewerAppPrefsClass *class)
{
  G_OBJECT_CLASS (class)->dispose = vviewer_app_prefs_dispose;

  gtk_widget_class_set_template_from_resource (GTK_WIDGET_CLASS (class),
                                               "/com/github/Gwarek2/Viewer/gui/ui/prefs.ui");
  gtk_widget_class_bind_template_child (GTK_WIDGET_CLASS (class), VviewerAppPrefs, verticestype);
  gtk_widget_class_bind_template_child (GTK_WIDGET_CLASS (class), VviewerAppPrefs, verticessize);
  gtk_widget_class_bind_template_child (GTK_WIDGET_CLASS (class), VviewerAppPrefs, verticescolor);
  gtk_widget_class_bind_template_child (GTK_WIDGET_CLASS (class), VviewerAppPrefs, projection);
  gtk_widget_class_bind_template_child (GTK_WIDGET_CLASS (class), VviewerAppPrefs, edgetype);
  gtk_widget_class_bind_template_child (GTK_WIDGET_CLASS (class), VviewerAppPrefs, edgewidth);
  gtk_widget_class_bind_template_child (GTK_WIDGET_CLASS (class), VviewerAppPrefs, edgecolor);
  gtk_widget_class_bind_template_child (GTK_WIDGET_CLASS (class), VviewerAppPrefs, bgcolor);
}

VviewerAppPrefs *
vviewer_app_prefs_new (VviewerAppWindow *win)
{
  return g_object_new (VVIEWER_APP_PREFS_TYPE, "transient-for", win, "use-header-bar", TRUE, NULL);
}
