#include "array.h"

array_t * array_create(size_t sizeof_elem, int type) {
  if (sizeof_elem == 0) return NULL;

  array_t * arr = malloc(sizeof(array_t));
  arr->len = 0;
  arr->len_limit = MIN_LEN;
  arr->type = type;
  arr->elem_size = sizeof_elem;
  arr->data = calloc(MIN_LEN, sizeof_elem);
  if (arr->data == NULL)
    exit(errno);

  return arr;
}

int array_append_elem(array_t *arr, void *data, size_t size) {
  if (size != arr->elem_size || data == NULL) return 1;

  if (arr->len == arr->len_limit) {
    arr->len_limit *= 2;
    void *new_data = realloc(arr->data, arr->len_limit * arr->elem_size);
    if (new_data == NULL) exit(errno);
    arr->data = new_data;
  }
  memcpy((char*) arr->data + arr->len * arr->elem_size, data, size);
  arr->len++;

  return 0;
}

int array_get_elem(array_t * arr, void * buffer, size_t index) {
  if (index >= arr->len) return 1;
  memcpy(buffer, (char*) arr->data + index * arr->elem_size, arr->elem_size);

  return 0;
}

int array_set_elem(array_t * arr, void * new_data, size_t index) {
  if (index >= arr->len) return 1;
  memcpy((char*) arr->data + index * arr->elem_size, new_data, arr->elem_size);

  return 0;
}

void array_destroy(array_t * arr) {
  free(arr->data);
  arr->data = NULL;
  free(arr);
  arr = NULL;
}
