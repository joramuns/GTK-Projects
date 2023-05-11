#include "check_main.h"

START_TEST(s1) {
  deposit_input test_case = {0};
  deposit_output test_result = {0};
  test_case.deposit = 10000.0;
  test_case.term = 181.0;
  test_case.rate = 7.0;
  test_case.freq_payment = 30;
  test_case.account_movement = malloc(sizeof(double) * test_case.term);
  for (unsigned i = 0; i < test_case.term; i++)
    test_case.account_movement[i] = 0;
  handle_deposit_calc(test_case, &test_result);
  clean(test_result.stack_of_payouts);
  free(test_case.account_movement);
  double result_deposit = test_result.total_profit;
  ck_assert_double_eq_tol(result_deposit, 347.11, 1e-02);
}
END_TEST

START_TEST(s2) {
  deposit_input test_case = {0};
  deposit_output test_result = {0};
  test_case.deposit = 10000;
  test_case.term = 181.0;
  test_case.rate = 7.0;
  test_case.freq_payment = 1;
  test_case.capitalization = 1;
  test_case.account_movement = malloc(sizeof(double) * test_case.term);
  for (unsigned i = 0; i < test_case.term; i++)
    test_case.account_movement[i] = 0;
  handle_deposit_calc(test_case, &test_result);
  clean(test_result.stack_of_payouts);
  free(test_case.account_movement);
  double result_deposit = test_result.total_profit;
  ck_assert_double_eq_tol(result_deposit, 353.16, 1e-02);
}
END_TEST

Suite *deposit_suite(void) {
  Suite *s = suite_create("Deposit calc test");
  TCase *tc = tcase_create("Deposit calc test");

  tcase_add_test(tc, s1);
  tcase_add_test(tc, s2);

  suite_add_tcase(s, tc);

  return s;
}
