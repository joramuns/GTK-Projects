#include <gtk/gtk.h>

#define RENDERAREA_BOX_TYPE (renderarea_box_get_type ())
G_DECLARE_FINAL_TYPE (RenderareaBox, renderarea_box, RENDERAREA, BOX, GtkBox)

RenderareaBox *renderarea_box_new ();
