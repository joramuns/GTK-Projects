/** \file app.c
 *  \brief 3DViewer application class implementation.
 */
#include "app.h"
#include "prefs.h"
#include "window.h"

static void
quit_app (GSimpleAction *action, GVariant *param, gpointer app)
{
  g_application_quit (G_APPLICATION (app));
}

static void
open_preferences (GSimpleAction *action, GVariant *param, gpointer app)
{
  GtkWindow *win = gtk_application_get_active_window (GTK_APPLICATION (app));
  VviewerAppPrefs *prefs = vviewer_app_prefs_new(VVIEWER_APP_WINDOW (win));
  gtk_window_present (GTK_WINDOW (prefs));
}

struct _VviewerApp
{
  GtkApplication parent;

  GtkApplicationWindow *win;
};

G_DEFINE_TYPE (VviewerApp, vviewer_app, GTK_TYPE_APPLICATION);

static GActionEntry app_entries[] = {
  { "preferences", open_preferences, NULL, NULL, NULL },
  { "quit", quit_app, NULL, NULL, NULL },
};

const char *quit_accels[2] = { "<Ctrl>q", NULL };

static void
vviewer_app_init (VviewerApp *app)
{
}

static void
vviewer_app_activate (GApplication *app)
{
  VviewerAppWindow *win = vviewer_app_window_new (VVIEWER_APP (app));
  gtk_window_present (GTK_WINDOW (win));
  g_action_map_add_action_entries (G_ACTION_MAP (app), app_entries,
                                   G_N_ELEMENTS (app_entries), app);
  gtk_application_set_accels_for_action (GTK_APPLICATION (app), "app.quit",
                                         quit_accels);

  /* GtkCssProvider *provider = gtk_css_provider_new (); */
  /* gtk_css_provider_load_from_resource ( */
  /*     provider, "/com/github/Gwarek2/smartcalc/gui/styles/styles.css"); */
  /* gtk_style_context_add_provider_for_display ( */
  /*     gdk_display_get_default (), GTK_STYLE_PROVIDER (provider), */
  /*     GTK_STYLE_PROVIDER_PRIORITY_APPLICATION); */
  /* g_object_unref (provider); */
}

static void
vviewer_app_class_init (VviewerAppClass *class)
{
  G_APPLICATION_CLASS (class)->activate = vviewer_app_activate;
}

VviewerApp *
vviewer_app_new (void)
{
  return g_object_new (VVIEWER_APP_TYPE, "application-id",
                       "com.github.Gwarek2.Viewer", "flags",
                       G_APPLICATION_HANDLES_OPEN, NULL);
}
