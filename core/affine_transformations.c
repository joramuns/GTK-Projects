#include "affine_transformations.h"

void affineTransform(GLuint shaderProgram, float *rotationAngles) {
  GLuint uniform_location; 

  uniform_location = glGetUniformLocation(shaderProgram, "projection");
  float projection[16] = {0};
  perspectiveProjection(projection, NEAR, FAR, RIGHT, TOP);
  glUniformMatrix4fv(uniform_location, 1, GL_FALSE, &projection[0]);

  uniform_location = glGetUniformLocation(shaderProgram, "rotX");
  float rotX[16] = {0};
  fillIdentityMatrix(rotX);
  fillXaxis(rotX, rotationAngles);
  glUniformMatrix4fv(uniform_location, 1, GL_FALSE, &rotX[0]);

  uniform_location = glGetUniformLocation(shaderProgram, "rotY");
  float rotY[16] = {0};
  fillIdentityMatrix(rotY);
  fillYaxis(rotY, rotationAngles);
  glUniformMatrix4fv(uniform_location, 1, GL_FALSE, &rotY[0]);

  uniform_location = glGetUniformLocation(shaderProgram, "rotZ");
  float rotZ[16] = {0};
  fillIdentityMatrix(rotZ);
  fillZaxis(rotZ, rotationAngles);
  glUniformMatrix4fv(uniform_location, 1, GL_FALSE, &rotZ[0]);

  uniform_location = glGetUniformLocation(shaderProgram, "scale");
  float scale[16] = {0};
  fillIdentityMatrix(scale);
  fillScale(scale, rotationAngles);
  glUniformMatrix4fv(uniform_location, 1, GL_FALSE, &scale[0]);

  uniform_location = glGetUniformLocation(shaderProgram, "moveXYZ");
  float moveXYZ[16] = {0};
  fillIdentityMatrix(moveXYZ);
  fillMove(moveXYZ, rotationAngles);
  glUniformMatrix4fv(uniform_location, 1, GL_FALSE, &moveXYZ[0]);
}

void perspectiveProjection(float *dest, float near, float far, float right, float top) {
  dest[0] = 1 / right;
  dest[5] = 1 / top;
  dest[10] = -2 / (far - near);
  dest[11] = - (far + near) / (far - near);
  dest[15] = 1;
}

void fillXaxis(float *res, float *rotation_angles) {
  float x = rotation_angles[X_AXIS] * (M_PI / 180.f);
  float cos = cosf(x), sin = sinf(x);
  res[5] = cos;
  res[6] = sin;
  res[9] = -sin;
  res[10] = cos;
}

void fillYaxis(float *res, float *rotation_angles) {
  float y = rotation_angles[Y_AXIS] * (M_PI / 180.f);
  float cos = cosf(y), sin = sinf(y);
  res[0] = cos;
  res[2] = -sin;
  res[8] = sin;
  res[10] = cos;
}

void fillZaxis(float *res, float *rotation_angles) {
  float z = rotation_angles[Z_AXIS] * (M_PI / 180.f);
  float cos = cosf(z), sin = sinf(z);
  res[0] = cos;
  res[1] = sin;
  res[4] = -sin;
  res[5] = cos;
}

void fillMove(float *res, float *rotation_angles) {
  res[12] = rotation_angles[X_MOVE];
  res[13] = rotation_angles[Y_MOVE];
  res[14] = rotation_angles[Z_MOVE];
}

void fillScale(float *res, float *rotation_angles) {
  res[0] = rotation_angles[SCALE];
  res[5] = rotation_angles[SCALE];
  res[10] = rotation_angles[SCALE];
}

void fillIdentityMatrix(float *res) {
  res[0] = 1.0;
  res[5] = 1.0;
  res[10] = 1.0;
  res[15] = 1.0;
}
