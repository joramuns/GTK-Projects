#include "check_main.h"

START_TEST(s1) {
  credit_input test_case = {0};
  credit_output test_result = {0};
  test_case.sum = 10000;
  test_case.term = 6;
  test_case.rate = 7;
  handle_credit_calculator(test_case, &test_result);
  double result_sum = find_last(test_result.stack_of_payments)->value;
  ck_assert_double_eq_tol(result_sum, 1700.86, 1e-02);
  ck_assert_double_eq_tol(test_result.total_sum, 10205.16, 1e-02);
  clean(test_result.stack_of_payments);
}
END_TEST

START_TEST(s2) {
  credit_input test_case = {0};
  credit_output test_result = {0};
  test_case.sum = 10000;
  test_case.term = 6;
  test_case.rate = 7;
  test_case.type = 1;
  handle_credit_calculator(test_case, &test_result);
  double result_sum = find_last(test_result.stack_of_payments)->value;
  ck_assert_double_eq_tol(result_sum, 1676.39, 1e-02);
  ck_assert_double_eq_tol(test_result.total_sum, 10204.17, 1e-02);
  clean(test_result.stack_of_payments);
}
END_TEST

START_TEST(s3) {
  credit_input test_case = {0};
  credit_output test_result = {0};
  test_case.sum = 897908;
  test_case.term = 9;
  test_case.rate = 2.3;
  test_case.type = 1;
  handle_credit_calculator(test_case, &test_result);
  double result_sum = find_last(test_result.stack_of_payments)->value;
  ck_assert_double_eq_tol(result_sum, 99958.78, 1e-02);
  ck_assert_double_eq_tol(test_result.total_sum, 906512.95, 1e-02);
  clean(test_result.stack_of_payments);
}
END_TEST

START_TEST(s4) {
  credit_input test_case = {0};
  credit_output test_result = {0};
  test_case.sum = 897908;
  test_case.term = 9;
  test_case.rate = 2.3;
  test_case.type = 0;
  handle_credit_calculator(test_case, &test_result);
  double result_sum = find_last(test_result.stack_of_payments)->value;
  ck_assert_double_eq_tol(result_sum, 100726.10, 1e-02);
  ck_assert_double_eq_tol(test_result.total_sum, 906534.90, 1e-02);
  clean(test_result.stack_of_payments);
}
END_TEST

Suite *credit_suite(void) {
  Suite *s = suite_create("Credit calc test");
  TCase *tc = tcase_create("Credit calc test");

  tcase_add_test(tc, s1);
  tcase_add_test(tc, s2);
  tcase_add_test(tc, s3);
  tcase_add_test(tc, s4);

  suite_add_tcase(s, tc);

  return s;
}
