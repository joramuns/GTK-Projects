#include <check.h>
#include <stdio.h>

#include "core/affine_transformations.h"

START_TEST(test_identity) {
  float test[16] = {0}, expected[16] = {0};
  expected[0] = 1;
  expected[5] = 1;
  expected[10] = 1;
  expected[15] = 1;
  fillIdentityMatrix(test);
  for (int i = 0; i < 16; i++) {
    ck_assert_float_eq_tol(test[i], expected[i], 1e-6);
  }
}
END_TEST

START_TEST(test_x_rotation) {
  float axis[N_AXIS], test[16] = {0}, expected[16] = {0};
  fillIdentityMatrix(test);
  fillIdentityMatrix(expected);
  expected[5] = 0.9785;
  expected[6] = 0.2062;
  expected[9] = -0.2062;
  expected[10] = 0.9785;
  
  axis[X_AXIS] = 3251.9;
  fillXaxis(test, axis);
  for (int i = 0; i < 16; i++) {
    ck_assert_float_eq_tol(test[i], expected[i], 1e-4);
  }
}
END_TEST

START_TEST(test_y_rotation) {
  float axis[N_AXIS], test[16] = {0}, expected[16] = {0};
  fillIdentityMatrix(test);
  fillIdentityMatrix(expected);
  expected[0] = 0.8755;
  expected[2] = -0.4833;
  expected[8] = 0.4833;
  expected[10] = 0.8755;
  
  axis[Y_AXIS] = 1828.9;
  fillYaxis(test, axis);
  for (int i = 0; i < 16; i++) {
    ck_assert_float_eq_tol(test[i], expected[i], 1e-4);
  }
}
END_TEST

START_TEST(test_z_rotation) {
  float axis[N_AXIS], test[16] = {0}, expected[16] = {0};
  fillIdentityMatrix(test);
  fillIdentityMatrix(expected);
  expected[0] = 0.1719;
  expected[1] = -0.9851;
  expected[4] = 0.9851;
  expected[5] = 0.1719;
  
  axis[Z_AXIS] = 999.9;
  fillZaxis(test, axis);
  for (int i = 0; i < 16; i++) {
    ck_assert_float_eq_tol(test[i], expected[i], 1e-4);
  }
}
END_TEST

START_TEST(test_move) {
  float axis[N_AXIS], test[16] = {0}, expected[16] = {0};
  fillIdentityMatrix(test);
  fillIdentityMatrix(expected);
  
  axis[X_MOVE] = 887.2;
  axis[Y_MOVE] = 89.8;
  axis[Z_MOVE] = 123.5;

  expected[12] = 887.2;
  expected[13] = 89.8;
  expected[14] = 123.5;
  fillMove(test, axis);
  for (int i = 0; i < 16; i++) {
    ck_assert_float_eq_tol(test[i], expected[i], 1e-4);
  }
}
END_TEST

START_TEST(test_scale) {
  float axis[N_AXIS], test[16] = {0}, expected[16] = {0};
  fillIdentityMatrix(test);
  fillIdentityMatrix(expected);
  
  axis[SCALE] = 324.41;

  expected[0] = 324.41;
  expected[5] = 324.41;
  expected[10] = 324.41;
  fillScale(test, axis);
  for (int i = 0; i < 16; i++) {
    ck_assert_float_eq_tol(test[i], expected[i], 1e-4);
  }
}
END_TEST

START_TEST(test_projection) {
  float test[16] = {0}, expected[16] = {0};
  fillIdentityMatrix(test);
  fillIdentityMatrix(expected);

  float near = 1.31, far = 129, right = 0.04, top = 0.9;
  expected[0] = 25;
  expected[5] = 1.1111;
  expected[10] = -0.0156;
  expected[11] = -1.0205;
  expected[15] = 1;
  perspectiveProjection(test, near, far, right, top);
  for (int i = 0; i < 16; i++) {
    ck_assert_float_eq_tol(test[i], expected[i], 1e-4);
  }
}
END_TEST

static TCase *affine_tc(void) {
  TCase *tc = tcase_create("affine_tests");
  tcase_add_test(tc, test_identity);
  tcase_add_test(tc, test_x_rotation);
  tcase_add_test(tc, test_y_rotation);
  tcase_add_test(tc, test_z_rotation);
  tcase_add_test(tc, test_move);
  tcase_add_test(tc, test_scale);
  tcase_add_test(tc, test_projection);

  return tc;
}

Suite *affine_suite() {
  Suite *s = suite_create("affine_suite");

  suite_add_tcase(s, affine_tc());

  return s;
}
