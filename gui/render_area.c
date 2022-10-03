#include "render_area.h"

struct _RenderareaBox
{
  GtkBox parent;

  GtkGLArea *area;
};

G_DEFINE_TYPE (RenderareaBox, renderarea_box, GTK_TYPE_BOX);

static void
renderarea_box_init(RenderareaBox *box)
{
}

static void
renderarea_box_class_init(RenderareaBoxClass *class)
{
  gtk_widget_class_set_template_from_resource (
      GTK_WIDGET_CLASS (class),
      "/com/github/Gwarek2/Viewer/gui/templates/render_area.ui");

  gtk_widget_class_bind_template_child (GTK_WIDGET_CLASS (class), RenderareaBox, area);
}

RenderareaBox *
renderarea_box_new ()
{
  return g_object_new (RENDERAREA_BOX_TYPE, NULL);
}
