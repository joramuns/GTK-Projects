#include "affine_transformations.h"

/**
 * @brief Creates matrix that transforms model to perspective projection
 *
 * @param dest flat matrix with result transformation
 * @param near near clipping plane
 * @param far far clipping plane
 * @param right side clipping planes
 * @param top top and bottom clipping planes
 */
void perspectiveProjection(float *dest, float near, float far, float right, float top) {
  dest[0] = 1 / right;
  dest[5] = 1 / top;
  dest[10] = -2 / (far - near);
  dest[11] = - (far + near) / (far - near);
  dest[15] = 1;
}

/**
 * @brief Fills matrix that rotates model by X axis
 *
 * @param res flat matrix with result transformation
 * @param rotation_angles array with data from axes
 */
void fillXaxis(float *res, float *rotation_angles) {
  float x = rotation_angles[X_AXIS] * (M_PI / 180.f);
  float cos = cosf(x), sin = sinf(x);
  res[5] = cos;
  res[6] = sin;
  res[9] = -sin;
  res[10] = cos;
}

/**
 * @brief Fills matrix that rotates model by Y axis
 *
 * @param res flat matrix with result transformation
 * @param rotation_angles array with data from axes
 */
void fillYaxis(float *res, float *rotation_angles) {
  float y = rotation_angles[Y_AXIS] * (M_PI / 180.f);
  float cos = cosf(y), sin = sinf(y);
  res[0] = cos;
  res[2] = -sin;
  res[8] = sin;
  res[10] = cos;
}

/**
 * @brief Fills matrix that rotates model by Z axis
 *
 * @param res flat matrix with result transformation
 * @param rotation_angles array with data from axes
 */
void fillZaxis(float *res, float *rotation_angles) {
  float z = rotation_angles[Z_AXIS] * (M_PI / 180.f);
  float cos = cosf(z), sin = sinf(z);
  res[0] = cos;
  res[1] = sin;
  res[4] = -sin;
  res[5] = cos;
}

/**
 * @brief Fills matrix that moves model
 *
 * @param res flat matrix with result transformation
 * @param rotation_angles array with data from axes
 */
void fillMove(float *res, float *rotation_angles) {
  res[12] = rotation_angles[X_MOVE];
  res[13] = rotation_angles[Y_MOVE];
  res[14] = rotation_angles[Z_MOVE];
}

/**
 * @brief Fills matrix that scales model
 *
 * @param res flat matrix with result transformation
 * @param rotation_angles array with data from axes
 */
void fillScale(float *res, float *rotation_angles) {
  res[0] = rotation_angles[SCALE];
  res[5] = rotation_angles[SCALE];
  res[10] = rotation_angles[SCALE];
}

/**
 * @brief Fills identity matrix
 *
 * @param res flat matrix with result transformations
 */
void fillIdentityMatrix(float *res) {
  res[0] = 1.0;
  res[5] = 1.0;
  res[10] = 1.0;
  res[15] = 1.0;
}
