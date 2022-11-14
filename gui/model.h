#include <epoxy/gl.h>
#include <gtk/gtk.h>

#define MODEL_GL_AREA_TYPE (model_gl_area_get_type ())
G_DECLARE_FINAL_TYPE (ModelGLArea, model_gl_area, MODELGLAREA, GLAREA, GtkGLArea)


ModelGLArea * model_gl_area_new (GArray *vertices, GArray *indices);
