#include <check.h>

#include "core/affine_transformations.h"

START_TEST(test_x_rotation) {
  float axis[N_AXIS], test[16], expected[16] = {0};
  axis[X_AXIS] = 3251.9;
  fillXaxis(test, axis);
  for (int i = 0; i < 16; i++) {
    ck_assert_float_eq_tol(test[i], expected[i], 1e-6);
  }
}
END_TEST

static TCase *affine_tc(void) {
  TCase *tc = tcase_create("affine_tests");
  tcase_add_test(tc, test_x_rotation);

  return tc;
}

Suite *affine_suite() {
  Suite *s = suite_create("affine_suite");

  suite_add_tcase(s, affine_tc());

  return s;
}
