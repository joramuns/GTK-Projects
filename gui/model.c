#include "model.h"
#include "include/gifenc.h"
#include "enums.h"
#include <epoxy/gl.h>
#include "core/obj_parser.h"
#include "utils.h"
#include "window.h"

#define DASH_SIZE 10
#define GAP_SIZE 10

const char *v_shader_path
    = "/com/github/Gwarek2/Viewer/gui/shaders/v_shader.glsl";
const char *f_shader_polygon_path
    = "/com/github/Gwarek2/Viewer/gui/shaders/f_shader_polygon.glsl";
const char *f_shader_point_path
    = "/com/github/Gwarek2/Viewer/gui/shaders/f_shader_point.glsl";

struct _ModelGLArea
{
  GtkGLArea parent;

  GSettings *prefs;

  GArray *vertices;
  GArray *indices;

  GLuint VAO, VBO, EBO;
  GLuint polygon_shader_prog;
  GLuint point_shader_prog;

  guint vertices_type;
  GLdouble vertices_size;
  GdkRGBA *vertices_color;
  guint projection;
  guint edge_type;
  GdkRGBA *edge_color;
  GLdouble edge_width;
  GdkRGBA *bg_color;
  GLfloat *rotation_angles;

  ge_GIF *gif_pointer;
};

G_DEFINE_TYPE (ModelGLArea, model_gl_area, GTK_TYPE_GL_AREA);

GdkPixbuf* get_pixbuf(GtkWidget *model) {
  GdkGLContext *context = gtk_gl_area_get_context(GTK_GL_AREA(model));
  gdk_gl_context_make_current(context);
  int width = gtk_widget_get_width(model) * 2;
  int height = gtk_widget_get_height(model) * 2;
  guchar *image = g_malloc (width * height * sizeof(guchar) * 4);
  glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, image);

  GdkPixbuf* image_pixbuf = gdk_pixbuf_new_from_data(image, GDK_COLORSPACE_RGB, TRUE, 8, width, height, height * 4, NULL, NULL);
  GdkPixbuf* image_pixbuf_swap = gdk_pixbuf_flip(image_pixbuf, FALSE);
  g_free(image);
  g_object_unref(image_pixbuf);

  return image_pixbuf_swap;
}

static GLuint
create_shader (GLint type, const char *src)
{
  GLuint shader = glCreateShader (type);
  glShaderSource (shader, 1, &src, NULL);
  glCompileShader (shader);

  int status;
  char info_log[512];
  glGetShaderiv (shader, GL_COMPILE_STATUS, &status);
  if (status == GL_FALSE)
    {
      glGetProgramInfoLog (shader, 512, NULL, info_log);
      g_print ("Shader creation %s\n", info_log);
      return 0;
    }

  return shader;
}

static void
init_shaders (GLuint *shader_program, const char *v_shader_path, const char *f_shader_path)
{
  GBytes *vertex_source
      = g_resources_lookup_data (v_shader_path, 0, NULL);
  GBytes *fragment_source
      = g_resources_lookup_data (f_shader_path, 0, NULL);

  GLuint vertex_shader = create_shader (
      GL_VERTEX_SHADER, g_bytes_get_data (vertex_source, NULL));
  GLuint fragment_shader = create_shader (
      GL_FRAGMENT_SHADER, g_bytes_get_data (fragment_source, NULL));
  g_bytes_unref (vertex_source);
  g_bytes_unref (fragment_source);

  *shader_program = glCreateProgram ();
  glAttachShader (*shader_program, vertex_shader);
  glAttachShader (*shader_program, fragment_shader);
  glLinkProgram (*shader_program);

  int status;
  char info_log[512];
  glGetProgramiv (*shader_program, GL_LINK_STATUS, &status);
  if (!status)
    {
      glGetProgramInfoLog (*shader_program, 512, NULL, info_log);
      g_print ("Shader program %s\n", info_log);
    }
}

static void
realize (ModelGLArea *area)
{
  gtk_gl_area_make_current (GTK_GL_AREA (area));
  GError *err = gtk_gl_area_get_error (GTK_GL_AREA (area));
  if (err != NULL)
    {
      g_print ("%s\n", err->message);
      return;
    }

  init_shaders (&area->polygon_shader_prog, v_shader_path, f_shader_polygon_path);
  init_shaders (&area->point_shader_prog, v_shader_path, f_shader_point_path);
}

static void
unrealize (ModelGLArea *area)
{
  gtk_gl_area_make_current (GTK_GL_AREA (area));
  GError *err = gtk_gl_area_get_error (GTK_GL_AREA (area));
  if (err != NULL)
    {
      g_print ("%s\n", err->message);
      return;
    }
  glDeleteVertexArrays (1, &area->VAO);
  glDeleteBuffers (1, &area->VBO);
  glDeleteBuffers (1, &area->EBO);
  glDeleteProgram (area->polygon_shader_prog);
  glDeleteProgram (area->point_shader_prog);
}

static void
draw_polygons (ModelGLArea *area)
{
  int width = gtk_widget_get_width (GTK_WIDGET (area));
  int height = gtk_widget_get_height (GTK_WIDGET (area));

  glEnable (GL_LINE_SMOOTH);
  glLineWidth (area->edge_width);
  glUseProgram (area->polygon_shader_prog);
  int polygon_color = glGetUniformLocation (area->polygon_shader_prog, "color");
  int dashed_line = glGetUniformLocation (area->polygon_shader_prog, "dashedLine");
  int dash_size = glGetUniformLocation (area->polygon_shader_prog, "dashSize");
  int gap_size = glGetUniformLocation (area->polygon_shader_prog, "gapSize");
  int resolution = glGetUniformLocation (area->polygon_shader_prog, "resolution");
  affineTransform(area->polygon_shader_prog, area->rotation_angles, area->projection == PROJECTION_CENTRAL);
  glUniform4f (polygon_color, area->edge_color->red,
                              area->edge_color->green,
                              area->edge_color->blue,
                              area->edge_color->alpha);
  glUniform1ui (dashed_line, area->edge_type == EDGE_DASHED);
  glUniform1f (dash_size, DASH_SIZE);
  glUniform1f (gap_size, GAP_SIZE);
  glUniform2f (resolution,  width, height);
  glPolygonMode (GL_FRONT_AND_BACK, GL_LINE);
  glDrawElements (GL_TRIANGLES, area->indices->len, GL_UNSIGNED_INT, 0);
}

static void
draw_points (ModelGLArea *area)
{
  glUseProgram (area->point_shader_prog);
  int point_color = glGetUniformLocation (area->point_shader_prog, "color");
  int rounded = glGetUniformLocation (area->point_shader_prog, "roundVertices");
  affineTransform(area->point_shader_prog, area->rotation_angles, area->projection == PROJECTION_CENTRAL);
  glPointSize (area->vertices_size);
  glUniform4f (point_color, area->vertices_color->red,
                            area->vertices_color->green,
                            area->vertices_color->blue,
                            area->vertices_color->alpha);
  glUniform1ui (rounded, area->vertices_type == VERTICES_ROUNDED);
  glDrawElements (GL_POINTS, area->indices->len, GL_UNSIGNED_INT, 0);
}

static gboolean
render (ModelGLArea *area, GdkGLContext *context)
{
  glClearColor (area->bg_color->red,
                area->bg_color->green,
                area->bg_color->blue,
                area->bg_color->alpha);
  glClear (GL_COLOR_BUFFER_BIT);

  glGenVertexArrays (1, &area->VAO);
  glGenBuffers (1, &area->VBO);
  glGenBuffers (1, &area->EBO);

  glBindVertexArray (area->VAO);

  glBindBuffer (GL_ARRAY_BUFFER, area->VBO);
  glBufferData (GL_ARRAY_BUFFER, area->vertices->len * sizeof (GLfloat),
                (GLfloat *)area->vertices->data, GL_STATIC_DRAW);

  glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, area->EBO);
  glBufferData (GL_ELEMENT_ARRAY_BUFFER, area->indices->len * sizeof (GLuint),
                (GLuint *)area->indices->data, GL_STATIC_DRAW);

  glVertexAttribPointer (0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof (GLfloat),
                         (void *)0);
  glEnableVertexAttribArray (0);

  draw_polygons (area);
  if (area->vertices_type != VERTICES_NONE) {
    draw_points(area);
  }
  int width = 1000; //gtk_widget_get_width(area) * 2;
  int height = 1000; //gtk_widget_get_height(area) * 2;
    g_print("%lf\n", area->rotation_angles[GIFCOUNT]);
  if (area->rotation_angles[GIFCOUNT] == 50) {
    area->rotation_angles[GIFCOUNT]--;
    area->gif_pointer = ge_new_gif(
        "kek.gif",  /* file name */
        width, height,           /* canvas size */
        (uint8_t []) {  /* palette */
        0x00, 0x00, 0x00, /* 0 -> black */ 
        0xFF, 0x00, 0x00, /* 1 -> red */ 
        0x00, 0xFF, 0x00, /* 2 -> green */ 
        0x00, 0x00, 0xFF, /* 3 -> blue */
        },
        2,              /* palette depth == log2(# of colors) */
        -1,             /* no transparency */
        0               /* infinite loop */
    );
  } else if (area->rotation_angles[GIFCOUNT] > 1) {
    if (area->gif_pointer) {
      area->rotation_angles[GIFCOUNT]--;
      GdkPixbuf *pixbuf = get_pixbuf(GTK_WIDGET(area));
      guchar *image = gdk_pixbuf_get_pixels(pixbuf);

      uint8_t image_gif[width*height];
      for (int i = 0; i < width*height; i++) {
        guchar red = (image[i * 4] * 8) / 256;
        guchar green = (image[i * 4 + 1] * 8) / 256;
        guchar blue = (image[i * 4 + 2] * 4) / 256;
        image_gif[i] = (red << 5) | (green << 2) | blue;
      }
      memcpy(area->gif_pointer->frame, image_gif, sizeof(image_gif));
      ge_add_frame(area->gif_pointer, 6);

      g_object_unref(pixbuf);
    } else {
      area->rotation_angles[GIFCOUNT] = 0.0;
    }
  } else if (area->rotation_angles[GIFCOUNT] == 1) {
    area->rotation_angles[GIFCOUNT]--;
    ge_close_gif(area->gif_pointer);
    area->gif_pointer = NULL;
  }

  glFlush ();
  gtk_gl_area_queue_render (GTK_GL_AREA (area));
  return TRUE;
}

static void
apply_settings (GSettings *settings,
                gchar *key,
                gpointer user_data)
{
  ModelGLArea *area = MODELGLAREA_GLAREA(user_data);
  area->vertices_size = g_settings_get_double(settings, "vertices-size");
  area->edge_width = g_settings_get_double(settings, "edge-width");
  area->vertices_type = g_settings_get_enum (settings, "vertices-type");
  area->projection = g_settings_get_enum (settings, "projection");
  area->edge_type = g_settings_get_enum (settings, "edge-type");

  area->vertices_color = get_rgba_settings_prop (settings, "vertices-color");
  area->edge_color = get_rgba_settings_prop(settings, "edge-color");
  area->bg_color = get_rgba_settings_prop(settings, "background-color");

  gtk_gl_area_queue_render(GTK_GL_AREA (area));
}

static void
model_gl_area_init (ModelGLArea *self)
{
  gtk_widget_init_template (GTK_WIDGET (self));

  g_signal_connect (self, "realize", G_CALLBACK (realize), NULL);
  g_signal_connect (self, "unrealize", G_CALLBACK (unrealize), NULL);
  g_signal_connect (self, "render", G_CALLBACK (render), NULL);

  self->prefs = g_settings_new ("com.github.Gwarek2.Viewer");
  g_signal_connect (self->prefs, "changed",
                   G_CALLBACK(apply_settings), self);

  apply_settings(self->prefs, NULL, self);
}

static void
model_gl_area_class_init (ModelGLAreaClass *class)
{
  gtk_widget_class_set_template_from_resource (
      GTK_WIDGET_CLASS (class),
      "/com/github/Gwarek2/Viewer/gui/ui/model.ui");
}

ModelGLArea *
model_gl_area_new (GArray *vertices, GArray *indices, GLfloat *rotation_angles)
{
  ModelGLArea *self = g_object_new (MODEL_GL_AREA_TYPE, NULL);
  self->vertices = vertices;
  self->indices = indices;
  if (!rotation_angles[SCALE]) rotation_angles[SCALE] = 1;
  self->rotation_angles = rotation_angles;
  return self;
}
