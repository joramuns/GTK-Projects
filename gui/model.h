#ifndef _GUI_MODEL_H

#define _GUI_MODEL_H

#include <epoxy/gl.h>
#include <gtk/gtk.h>

#define MODEL_GL_AREA_TYPE (model_gl_area_get_type ())
G_DECLARE_FINAL_TYPE (ModelGLArea, model_gl_area, MODELGLAREA, GLAREA, GtkGLArea)


GdkPixbuf* get_pixbuf(GtkWidget *model);
ModelGLArea * model_gl_area_new (GArray *vertices, GArray *indices, GLfloat *rotation_angles);

#endif  /** _GUI_MODEL_H **/
