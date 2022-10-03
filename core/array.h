#ifndef _CORE_ARRAY_H

#define _CORE_ARRAY_H

#include <errno.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#define MIN_LEN 100

typedef struct {
  size_t len;
  size_t len_limit;
  size_t elem_size;
  int type;
  void * data;
} array_t;

array_t * array_create(size_t sizeof_elem, int type);
int array_append_elem(array_t *dst, void *data, size_t size);
int array_get_elem(array_t * arr, void * buffer, size_t index);
int array_set_elem(array_t * arr, void * new_data, size_t index);
void array_destroy(array_t * arr);

#endif /** _CORE_ARRAY_H **/
