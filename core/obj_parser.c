#include "obj_parser.h"

static void add_vertex(char *line_buffer, GArray *vertices) {
  char *cursor = line_buffer;
  GLfloat vertex[4] = {
      g_ascii_strtod(cursor, &cursor),
      g_ascii_strtod(cursor + 1, &cursor),
      g_ascii_strtod(cursor + 1, &cursor),
      g_ascii_strtod(cursor + 1, &cursor),
  };
  vertex[3] = vertex[3] == 0 ? 1.0 : vertex[3];
  g_array_append_vals(vertices, vertex, 4);
}

static void add_face(char *line_buffer, GArray *faces) {
  char *cursor = line_buffer;
  GArray *raw_faces = g_array_sized_new(FALSE, TRUE, sizeof(GLuint), 100);
  while (*cursor && *cursor != '\n') {
    GLuint v_index = g_ascii_strtod(cursor, &cursor);
    GLuint t_index = g_ascii_strtod(cursor + 1, &cursor);
    GLuint n_index = g_ascii_strtod(cursor + 1, &cursor);
    g_array_append_vals(raw_faces, &v_index, 1);
    cursor++;
  }

  GLuint *raw_faces_data = (GLuint *)raw_faces->data;
  GLuint start_index = raw_faces_data[0];
  for (size_t i = 2; i < raw_faces->len; i++) {
    GLuint polygon_indices[] = {
        start_index - 1,
        raw_faces_data[i - 1] - 1,
        raw_faces_data[i] - 1,
    };
    g_array_append_vals(faces, polygon_indices, 3);
  }
  g_array_unref(raw_faces);
}

int parse_obj_file(const char *filename, GArray *vertices, GArray *faces) {
  FILE *obj_file = fopen(filename, "r");
  if (obj_file == NULL) {
    return errno;
  }

  GRegex *vertex_regex = g_regex_new(VERTEX_PAT, G_REGEX_RAW, 0, NULL);
  GRegex *face_regex = g_regex_new(FACE_PAT, G_REGEX_RAW, 0, NULL);
  if (vertex_regex == NULL || face_regex == NULL) {
    return 1;
  }

  char *line_buffer = NULL;
  size_t sz = 0;
  ssize_t line_len = 0;
  while ((line_len = getline(&line_buffer, &sz, obj_file)) != EOF) {
    if (g_regex_match(vertex_regex, line_buffer, 0, NULL)) {
      add_vertex(line_buffer + 2, vertices);
    } else if (g_regex_match(face_regex, line_buffer, 0, NULL)) {
      add_face(line_buffer + 2, faces);
    }
    free(line_buffer);
    line_buffer = NULL;
  }
  free(line_buffer);
  g_regex_unref(vertex_regex);
  g_regex_unref(face_regex);
  fclose(obj_file);
  return 0;
}
