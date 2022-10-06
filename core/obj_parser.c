#include "obj_parser.h"

static void add_vertex(char * line_buffer, array_t vertices[]) {
  char * cursor = line_buffer;
  GLfloat x = strtod(cursor, &cursor);
  GLfloat y = strtod(cursor + 1, &cursor);
  GLfloat z = strtod(cursor + 1, &cursor);
  GLfloat w = strtod(cursor + 1, &cursor);
  if (w == 0) w = 1.0f;
  array_append_elem(vertices, &x, sizeof(GLfloat));
  array_append_elem(vertices, &y, sizeof(GLfloat));
  array_append_elem(vertices, &z, sizeof(GLfloat));
  array_append_elem(vertices, &w, sizeof(GLfloat));
}

static void add_faces(char * line_buffer, array_t faces[]) {
  char * cursor = line_buffer;
  GLuint vertex = strtod(cursor, &cursor);
  GLuint normal = strtod(cursor + 1, &cursor);
  GLuint texture = strtod(cursor + 1, &cursor);

  array_t * face_row = array_create(sizeof(GLuint), 0);
  array_append_elem(face_row, &vertex, sizeof(GLuint));
  array_append_elem(face_row, &normal, sizeof(GLuint));
  array_append_elem(face_row, &texture, sizeof(GLuint));

  array_append_elem(faces, face_row, sizeof(array_t*));
}

int parse_obj_file(const char * filename, array_t vertices[], array_t faces[]) {
  FILE * obj_file = fopen(filename, "r");
  if (obj_file == NULL) {
    return errno;
  }
  
  regex_t vertex_regex;
  regex_t face_regex;
  int status = regcomp(&vertex_regex, VERTEX_PAT, REG_NOSUB | REG_EXTENDED) ||
               regcomp(&face_regex, FACE_PAT, REG_NOSUB | REG_EXTENDED);
  if (status) {
    regfree(&vertex_regex);
    regfree(&face_regex);
    return 1;
  }

  char *line_buffer = NULL;
  size_t sz = 0;
  ssize_t line_len = 0;
  while ((line_len = getline(&line_buffer, &sz, obj_file)) != EOF) {
    if (!regexec(&vertex_regex, line_buffer, 0, NULL, 0)) {
      add_vertex(line_buffer + 2, vertices);
    } else if (!regexec(&face_regex, line_buffer, 0, NULL, 0)) {
      add_faces(line_buffer + 2, faces);
    }
    free(line_buffer);
    line_buffer = NULL;
  }
  regfree(&vertex_regex);
  regfree(&face_regex);
  return 0;
}
