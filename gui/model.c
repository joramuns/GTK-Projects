#include "model.h"

#include <epoxy/gl.h>
#include <epoxy/gl_generated.h>

#include "core/obj_parser.h"
#include "window.h"

const char *vertex_shader_path
    = "/com/github/Gwarek2/Viewer/gui/shaders/vertex_shader.glsl";
const char *fragment_shader_path
    = "/com/github/Gwarek2/Viewer/gui/shaders/fragment_shader.glsl";

struct _ModelGLArea
{
  GtkGLArea parent;

  GArray *vertices;
  GArray *indices;
  GLuint *VAO, *VBO, *EBO;
  GLuint *shader_program;
  GLfloat *color;
  GLfloat *rotation_angles;
};

G_DEFINE_TYPE (ModelGLArea, model_gl_area, GTK_TYPE_GL_AREA);

inline static GLuint
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

inline static void
init_shaders (GLuint *shader_program)
{
  GBytes *vertex_source
      = g_resources_lookup_data (vertex_shader_path, 0, NULL);
  GBytes *fragment_source
      = g_resources_lookup_data (fragment_shader_path, 0, NULL);

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

  area->shader_program = g_malloc (sizeof (GLuint));
  area->VAO = g_malloc (sizeof (GLuint));
  area->VBO = g_malloc (sizeof (GLuint));
  area->EBO = g_malloc (sizeof (GLuint));
  init_shaders (area->shader_program);
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
  glDeleteVertexArrays (1, area->VAO);
  glDeleteBuffers (1, area->VBO);
  glDeleteBuffers (1, area->EBO);
  glDeleteProgram (*area->shader_program);
  g_array_free (area->vertices, TRUE);
  g_array_free (area->indices, TRUE);
  g_free (area->shader_program);
  g_free (area->VAO);
  g_free (area->VBO);
  g_free (area->EBO);
}

static gboolean
render (ModelGLArea *area, GdkGLContext *context)
{
  float mvp[16];
  GLuint mvp_location = glGetUniformLocation(*area->shader_program, "mvp");
  compute_move(mvp, area->rotation_angles);
  glClearColor (0.0, 0.0, 0.0, 0.5);
  glClear (GL_COLOR_BUFFER_BIT);

  glGenVertexArrays (1, area->VAO);
  glGenBuffers (1, area->VBO);
  glGenBuffers (1, area->EBO);

  glBindVertexArray (*area->VAO);

  glBindBuffer (GL_ARRAY_BUFFER, *area->VBO);
  glBufferData (GL_ARRAY_BUFFER, area->vertices->len * sizeof (GLfloat),
                (GLfloat *)area->vertices->data, GL_STATIC_DRAW);

  glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, *area->EBO);
  glBufferData (GL_ELEMENT_ARRAY_BUFFER, area->indices->len * sizeof (GLuint),
                (GLuint *)area->indices->data, GL_STATIC_DRAW);

  glVertexAttribPointer (0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof (GLfloat),
                         (void *)0);
  glEnableVertexAttribArray (0);

  glUseProgram (*area->shader_program);
  glUniformMatrix4fv(mvp_location, 1, GL_FALSE, &mvp[0]);

  glPolygonMode (GL_FRONT_AND_BACK, GL_LINE);
  glDrawElements (GL_TRIANGLES, area->indices->len, GL_UNSIGNED_INT, 0);

  glFlush ();
  gtk_gl_area_queue_render (GTK_GL_AREA (area));
  return TRUE;
}

static void
model_gl_area_init (ModelGLArea *self)
{
  gtk_widget_init_template (GTK_WIDGET (self));
  g_signal_connect (self, "realize", G_CALLBACK (realize), NULL);
  g_signal_connect (self, "unrealize", G_CALLBACK (unrealize), NULL);
  g_signal_connect (self, "render", G_CALLBACK (render), NULL);
}

static void
model_gl_area_class_init (ModelGLAreaClass *class)
{
  gtk_widget_class_set_template_from_resource (
      GTK_WIDGET_CLASS (class),
      "/com/github/Gwarek2/Viewer/gui/templates/model.ui");
}

ModelGLArea *
model_gl_area_new (GArray *vertices, GArray *indices, gfloat color[4], GLfloat *rotation_angles)
{
  ModelGLArea *self = g_object_new (MODEL_GL_AREA_TYPE, NULL);
  self->vertices = vertices;
  self->indices = indices;
  self->color = (GLfloat *)color;
  if (!rotation_angles[SCALE]) rotation_angles[SCALE] = 1;
  self->rotation_angles = rotation_angles;
  return self;
}
