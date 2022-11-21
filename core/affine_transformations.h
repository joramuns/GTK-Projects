#include <epoxy/gl.h>
#include <math.h>

#define NEAR 10
#define FAR 90
#define RIGHT 0.5
#define TOP 0.5

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

  N_AXIS,
  GIFCOUNT,
  END
};

void affineTransform(GLuint shaderProgram, float *rotationAngles, bool is_orthogonal);
void perspectiveProjection(float *dest, float near, float far, float right, float top);
void fillXaxis(float *res, float *rotation_angles);
void fillYaxis(float *res, float *rotation_angles);
void fillZaxis(float *res, float *rotation_angles);
void fillMove(float *res, float *rotation_angles);
void fillScale(float *res, float *rotation_angles);
void fillIdentityMatrix(float *res);
