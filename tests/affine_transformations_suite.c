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
    printf("%f\n", test[i]);
    printf("%f\n", expected[i]);
    ck_assert_float_eq_tol(test[i], expected[i], 1e-4);
  }
}
END_TEST

static TCase *affine_tc(void) {
  TCase *tc = tcase_create("affine_tests");
  tcase_add_test(tc, test_identity);
  tcase_add_test(tc, test_x_rotation);

  return tc;
}

Suite *affine_suite() {
  Suite *s = suite_create("affine_suite");

  suite_add_tcase(s, affine_tc());

  return s;
}
