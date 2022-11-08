#include "affine_transformations.h"

void perspective_projection(float *dest) {
  matrix_t projection_matrix;
  s21_create_matrix(4, 4, &projection_matrix);
  float near = 10;
  float far = 90;
  float right = 0.5;
  float top = 0.5;
  
  projection_matrix.matrix[0][0] = 1 / right;
  projection_matrix.matrix[1][1] = 1 / top;
  projection_matrix.matrix[2][2] = -2 / (far - near);
  projection_matrix.matrix[3][2] = - (far + near) / (far - near);
  projection_matrix.matrix[3][3] = 1;
  convert_matrix(projection_matrix, dest);
  
  s21_remove_matrix(&projection_matrix);
}

void compute_move(float *res, float *rotation_angles) {
  matrix_t affine_matrix[3], s21_res;

  /* if (iso_toggle) { */
  /*   affine(rotation_angles, &affine_matrix[1], AFF_TRANSLATION); */
  /*   affine(rotation_angles, &affine_matrix[0], AFF_ROTATION); */
  /* } else { */
    affine(rotation_angles, &affine_matrix[0], AFF_TRANSLATION);
    affine(rotation_angles, &affine_matrix[1], AFF_ROTATION);
  /* } */
  affine(rotation_angles, &affine_matrix[2], AFF_SCALE);
  mult_triple(affine_matrix, &s21_res);
  convert_matrix(s21_res, res);

  for (int i = 0; i < 3; i++) s21_remove_matrix(&affine_matrix[i]);
  s21_remove_matrix(&s21_res);
}

void fill_translation_matrices(matrix_t *matrices, const float *radians) {
  matrices[0].matrix[0][3] = radians[X_MOVE];
  matrices[1].matrix[1][3] = radians[Y_MOVE];
  matrices[2].matrix[2][3] = radians[Z_MOVE];
}

void fill_rotation_matrices(matrix_t *matrices, const float *radians) {
  float x = radians[X_AXIS] * (M_PI / 180.f);
  float y = radians[Y_AXIS] * (M_PI / 180.f);
  float z = radians[Z_AXIS] * (M_PI / 180.f);
  float c1 = cosf(x), s1 = sinf(x);
  float c2 = cosf(y), s2 = sinf(y);
  float c3 = cosf(z), s3 = sinf(z);
  /* apply all three rotations using the three matrices:
   *
   * ⎡  c3 s3 0 0 ⎤ ⎡ c2  0 -s2 ⎤ ⎡ 1   0  0 0 ⎤ ⎡ 1 0 0 xm ⎤
   * ⎢ -s3 c3 0 0 ⎥ ⎢  0  1   0 ⎥ ⎢ 0  c1 s1 0 ⎥ ⎢ 0 1 0 ym ⎥
   * ⎢   0  0 1 0 ⎥ ⎢ s2  0  c2 ⎥ ⎢ 0 -s1 c1 0 ⎥ ⎢ 0 0 1 zm ⎥
   * ⎣   0  0 0 1 ⎦ ⎣ s2  0  c2 ⎦ ⎣ 0   0  0 1 ⎦ ⎣ 0 0 0 1  ⎦
   */
  matrices[0].matrix[1][1] = c1;
  matrices[0].matrix[2][1] = -s1;
  matrices[0].matrix[1][2] = s1;
  matrices[0].matrix[2][2] = c1;

  matrices[1].matrix[0][0] = c2;
  matrices[1].matrix[2][0] = s2;
  matrices[1].matrix[0][2] = -s2;
  matrices[1].matrix[2][2] = c2;

  matrices[2].matrix[0][0] = c3;
  matrices[2].matrix[1][0] = s3;
  matrices[2].matrix[0][1] = -s3;
  matrices[2].matrix[1][1] = c3;
}

void fill_scale_matrices(matrix_t *matrices, const float *radians) {
  for (int i = 0; i < 3; i++) matrices[i].matrix[i][i] = radians[SCALE];
}

void fill_identity_matrix(matrix_t *matrix) {
  for (int i = 0; i < 4; i++) matrix->matrix[i][i] = 1;
}

void affine(const float *radians, matrix_t *result, const unsigned affine_type) {
  matrix_t matrices[3];

  for (int i = 0; i < 3; i++) {
    s21_create_matrix(4, 4, &matrices[i]);
    fill_identity_matrix(&matrices[i]);
  }

  switch (affine_type) {
    case AFF_TRANSLATION:
      fill_translation_matrices(matrices, radians);
      break;

    case AFF_ROTATION:
      fill_rotation_matrices(matrices, radians);
      break;

    case AFF_SCALE:
      fill_scale_matrices(matrices, radians);
      break;

    default:
      break;
  }

  mult_triple(matrices, result);

  for (int k = 0; k < 3; k++) s21_remove_matrix(&matrices[k]);
}

void convert_matrix(matrix_t src, float *dest) {
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++)
      dest[i + j * 4] = src.matrix[i][j];
}

void mult_triple(matrix_t *matrices, matrix_t *result) {
  matrix_t temp_result;
  s21_mult_matrix(&matrices[0], &matrices[1], &temp_result);
  s21_mult_matrix(&temp_result, &matrices[2], result);
  s21_remove_matrix(&temp_result);
}
