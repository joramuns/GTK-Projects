#include <gtk/gtk.h>
#include "s21_matrix.h"

enum {
  AFF_TRANSLATION,
  AFF_ROTATION,
  AFF_SCALE
};

enum {
  X_AXIS,
  Y_AXIS,
  Z_AXIS,
  X_MOVE,
  Y_MOVE,
  Z_MOVE,
  SCALE,

  N_AXIS
};

void compute_move(float *res, float *rotation_angles);
void fill_identity_matrix(matrix_t *matrix);
void affine(const float *radians, matrix_t *result, const unsigned affine_type);
void convert_matrix(matrix_t src, float *dest);
void mult_triple(matrix_t *matrices, matrix_t *result);
void perspective_projection(matrix_t *frustum);
