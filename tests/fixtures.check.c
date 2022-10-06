#include <check.h>
#include "core/array.h"
#include <epoxy/gl.h>
#include <stdio.h>
#include "core/obj_parser.h"


#define TEST_EPS 1e-6

array_t * array_empty;

void array_empty_setup(void) {
  array_empty = array_create(sizeof(double), 0);
}

void array_empty_teardown(void) {
  array_destroy(array_empty);
}


array_t * array_small;
double data[] = { 54.5, 34.12, 9045.13, 4738, 3289.12 };

void array_small_setup(void) {
  array_small = array_create(sizeof(double), 0);
  for (size_t i = 0; i < 5; i++)
    array_append_elem(array_small, &data[i], sizeof(double));
}

void array_small_teardown(void) {
  array_destroy(array_small);
}


array_t * vertices;
array_t * faces;

void buffers_setup(void) {
  vertices = array_create(sizeof(GLfloat), 0);
  faces = array_create(sizeof(array_t*), 0); 
}

void buffers_teardown(void) {
  array_destroy(vertices);
  array_destroy(faces);
}

