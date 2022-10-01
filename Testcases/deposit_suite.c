#include "check_main.h"

START_TEST(s1) {
    deposit_input test_case = {0};
    deposit_output test_result = {0};
    test_case.deposit = 10000.0;
    test_case.term = 181.0;
    test_case.rate = 7.0;
    test_case.freq_payment = 30;
    test_case.account_movement = malloc(sizeof(double) * test_case.term);
    for (int i = 0; i < test_case.term; i++) test_case.account_movement[i] = 0;
    handle_deposit_calc(test_case, &test_result);
    clean(test_result.stack_of_payouts);
    free(test_case.account_movement);
    double result_deposit = test_result.total_profit;
    ck_assert_double_eq_tol(result_deposit, 347.11, 1e-02);
}
END_TEST

/* START_TEST(s2) { */
/*     deposit_input test_case = {0}; */
/*     deposit_output test_result = {0}; */
/*     test_case.deposit = 10000; */
/*     test_case.term = 6; */
/*     test_case.rate = 7; */
/*     test_case.capitalization = 1; */
/*     handle_deposit_calc(test_case, &test_result); */
/*     double result_deposit = test_result.total_profit; */
/*     ck_assert_double_eq_tol(result_deposit, 352.18, 1e-02); */
/*     /1* clean(test_result.stack_of_payouts); *1/ */
/* } */
/* END_TEST */

/* START_TEST(s3) { */
/*     deposit_input test_case = {0}; */
/*     deposit_output test_result = {0}; */
/*     test_case.deposit = 897908; */
/*     test_case.term = 9; */
/*     test_case.rate = 2.3; */
/*     test_case.capitalization = 0; */
/*     handle_deposit_calc(test_case, &test_result); */
/*     double result_deposit = test_result.total_profit; */
/*     ck_assert_double_eq_tol(result_deposit, 15446.51, 1e-02); */
/*     /1* clean(test_result.stack_of_payouts); *1/ */
/* } */
/* END_TEST */

/* START_TEST(s4) { */
/*     deposit_input test_case = {0}; */
/*     deposit_output test_result = {0}; */
/*     test_case.deposit = 897908; */
/*     test_case.term = 9; */
/*     test_case.rate = 2.3; */
/*     test_case.capitalization = 1; */
/*     handle_deposit_calc(test_case, &test_result); */
/*     double result_deposit = test_result.total_profit; */
/*     ck_assert_double_eq_tol(result_deposit, 15565.10, 1e-02); */
/*     /1* clean(test_result.stack_of_payouts); *1/ */
/* } */
/* END_TEST */

Suite *deposit_suite(void) {
    Suite *s = suite_create("Deposit calc test");
    TCase *tc = tcase_create("Deposit calc test");

    tcase_add_test(tc, s1);
    /* tcase_add_test(tc, s2); */
    /* tcase_add_test(tc, s3); */
    /* tcase_add_test(tc, s4); */
    /* tcase_add_test(tc, s5); */
    /* tcase_add_test(tc, s6); */
    /* tcase_add_test(tc, s7); */
    /* tcase_add_test(tc, s8); */
    /* tcase_add_test(tc, s9); */
    /* tcase_add_test(tc, s10); */
    /* tcase_add_test(tc, s11); */
    /* tcase_add_test(tc, s12); */
    /* tcase_add_test(tc, s13); */
    /* tcase_add_test(tc, s14); */
    /* tcase_add_test(tc, s15); */
    /* tcase_add_test(tc, s16); */
    /* tcase_add_test(tc, s17); */
    /* tcase_add_test(tc, s18); */
    /* tcase_add_test(tc, s19); */
    /* tcase_add_test(tc, s20); */
    /* tcase_add_test(tc, s21); */
    /* tcase_add_test(tc, s22); */
    /* tcase_add_test(tc, s23); */
    /* tcase_add_test(tc, s24); */
    /* tcase_add_test(tc, s25); */
    /* tcase_add_test(tc, s26); */
    /* tcase_add_test(tc, s27); */
    /* tcase_add_test(tc, s28); */
    /* tcase_add_test(tc, s29); */
    /* tcase_add_test(tc, s30); */
    /* tcase_add_test(tc, s31); */
    /* tcase_add_test(tc, s32); */
    /* tcase_add_test(tc, s33); */

    suite_add_tcase(s, tc);

    return s;
}
