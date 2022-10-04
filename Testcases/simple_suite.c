//
//  simple_suite.c
//  C7_SmartCalc
//
//  Created by Joramun Sasin on 8/26/22.
//

#include "check_main.h"

//    4 + 4 * 2 / ( 1 - 5 ) = 2
START_TEST(s1) {
  double result = 0;
  int ex_code = calculate("4 + 4 * 2 / ( 1 - 5 )", &result);
  ck_assert_double_eq_tol(result, 2, TOL);
  ck_assert_int_eq(ex_code, 0);
}
END_TEST

//    4 + 4 * 2 / 1 - 5 = 7
START_TEST(s2) {
  double result = 0;
  int ex_code = calculate("4 + 4 * 2 / 1 - 5", &result);
  ck_assert_double_eq_tol(result, 7, TOL);
  ck_assert_int_eq(ex_code, 0);
}
END_TEST

//    4 + 4 * ( 2 / 1 - 5 ) = -8
START_TEST(s3) {
  double result = 0;
  int ex_code = calculate("4 + 4 * ( 2 / 1 - 5 )", &result);
  ck_assert_double_eq_tol(result, -8, TOL);
  ck_assert_int_eq(ex_code, 0);
}
END_TEST

//    4 + ( 4 * 2 / 1 - 5 ) = 7
START_TEST(s4) {
  double result = 0;
  int ex_code = calculate("4 + ( 4 * 2 / 1 - 5 )", &result);
  ck_assert_double_eq_tol(result, 7, TOL);
  ck_assert_int_eq(ex_code, 0);
}
END_TEST

//    4 + 4 * ( 2 /  1 ) - 5 = 7
START_TEST(s5) {
  double result = 0;
  double expected = 7;
  int ex_code = calculate("4 + 4 * ( 2 /  1 ) - 5", &result);
  ck_assert_int_eq(ex_code, 0);
  ck_assert_double_eq_tol(result, expected, TOL);
}
END_TEST

//    4 + ( 4 * 2 / 1 ) - 5 = 7
START_TEST(s6) {
  double result = 0;
  int ex_code = calculate("4 + ( 4 * 2 / 1 ) - 5", &result);
  ck_assert_double_eq_tol(result, 7, TOL);
  ck_assert_int_eq(ex_code, 0);
}
END_TEST

//    ( 4 + 4 * 2 / 1 ) - 5 = 7
START_TEST(s7) {
  double result = 0;
  int ex_code = calculate("( 4 + 4 * 2 / 1 ) - 5", &result);
  ck_assert_double_eq_tol(result, 7, TOL);
  ck_assert_int_eq(ex_code, 0);
}
END_TEST

//    4 + ( 4 * 2 ) / 1 - 5 = 7
START_TEST(s8) {
  double result = 0;
  int ex_code = calculate("4 + ( 4 * 2 ) / 1 - 5", &result);
  ck_assert_double_eq_tol(result, 7, TOL);
  ck_assert_int_eq(ex_code, 0);
}
END_TEST

//    ( 4 + 4 * 2 ) / 1 - 5 = 7
START_TEST(s9) {
  double result = 0;
  int ex_code = calculate("( 4 + 4 * 2 ) / 1 - 5", &result);
  ck_assert_double_eq_tol(result, 7, TOL);
  ck_assert_int_eq(ex_code, 0);
}
END_TEST

//    8 * (7 + 6 * 4) + 3 = 251
START_TEST(s10) {
  double result = 0;
  int ex_code = calculate("8 * (7 + 6 * 4) + 3", &result);
  ck_assert_double_eq_tol(result, 251, TOL);
  ck_assert_int_eq(ex_code, 0);
}
END_TEST

//    2 / (3 + 2) * 5 = 2
START_TEST(s11) {
  double result = 0;
  int ex_code = calculate("2 / (3 + 2) * 5", &result);
  ck_assert_double_eq_tol(result, 2, TOL);
  ck_assert_int_eq(ex_code, 0);
}
END_TEST

//    2+9.3-8^3/4+56.2 = -60.5
START_TEST(s12) {
  double result = 0;
  int ex_code = calculate("2+9.3-8^3/4+56.2", &result);
  ck_assert_double_eq_tol(result, -60.5, TOL);
  ck_assert_int_eq(ex_code, 0);
}
END_TEST

//    2+9.3-8^3/(4+56.2) = 2.795017
START_TEST(s13) {
  double result = 0;
  int ex_code = calculate("2+9.3-8^3/(4+56.2)", &result);
  ck_assert_double_eq_tol(result, 2.795017, TOL);
  ck_assert_int_eq(ex_code, 0);
}
END_TEST

//    2^3^2 = 512
START_TEST(s14) {
  double result = 0;
  int ex_code = calculate("2^3^2", &result);
  ck_assert_double_eq_tol(result, 512, TOL);
  ck_assert_int_eq(ex_code, 0);
}
END_TEST

//    2^(3^2) = 512
START_TEST(s15) {
  double result = 0;
  int ex_code = calculate("2^(3^2)", &result);
  ck_assert_double_eq_tol(result, 512, TOL);
  ck_assert_int_eq(ex_code, 0);
}
END_TEST

//    (2^3)^2 = 64
START_TEST(s16) {
  double result = 0;
  int ex_code = calculate("(2^3)^2", &result);
  ck_assert_double_eq_tol(result, 64, TOL);
  ck_assert_int_eq(ex_code, 0);
}
END_TEST

//    cos(431.2*2^2/8) = -0.390250
START_TEST(s17) {
  double result = 0;
  int ex_code = calculate("cos(431.2*2^2/8)", &result);
  ck_assert_double_eq_tol(result, -0.390250, TOL);
  ck_assert_int_eq(ex_code, 0);
}
END_TEST

//    3*sin(4+5) = 1.236355
START_TEST(s18) {
  double result = 0;
  int ex_code = calculate("3*sin(4+5)", &result);
  ck_assert_double_eq_tol(result, 1.236355, TOL);
  ck_assert_int_eq(ex_code, 0);
}
END_TEST

//    431.2*2^2/8 = 215.6
START_TEST(s19) {
  double result = 0;
  int ex_code = calculate("431.2*2^2/8", &result);
  ck_assert_double_eq_tol(result, 215.6, TOL);
  ck_assert_int_eq(ex_code, 0);
}
END_TEST

//    cos(sin(2+9*6^1.2-tan(1))) = 0.742186 (0.742182?)
START_TEST(s20) {
  double result = 0;
  int ex_code = calculate("cos(sin(2+9*6^1.2-tan(1)))", &result);
  ck_assert_double_eq_tol(result, 0.742182, TOL);
  ck_assert_int_eq(ex_code, 0);
}
END_TEST

//    sqrt(cos(sin(2+9*6^1.2-tan(1)))) = 0.861502 (0.861500?)
START_TEST(s21) {
  double result = 0;
  int ex_code = calculate("sqrt(cos(sin(2+9*6^1.2-tan(1))))", &result);
  ck_assert_double_eq_tol(result, 0.861500, TOL);
  ck_assert_int_eq(ex_code, 0);
}
END_TEST

//    sqrt(cos(sin(2+9*6^1.2-tan(1))))mod0.1 = 0.061502 (0.061500?)
START_TEST(s22) {
  double result = 0;
  int ex_code = calculate("sqrt(cos(sin(2+9*6^1.2-tan(1))))mod0.1", &result);
  ck_assert_double_eq_tol(result, 0.06150, TOL);
  ck_assert_int_eq(ex_code, 0);
}
END_TEST

//    sqrt(2^2)*5/(4-3mod2)*(4-sqrt(81)) = -16.666667
START_TEST(s23) {
  double result = 0;
  int ex_code = calculate("sqrt(2^2)*5/(4-3mod2)*(4-sqrt(81))", &result);
  ck_assert_double_eq_tol(result, -16.666667, TOL);
  ck_assert_int_eq(ex_code, 0);
}
END_TEST

//    cos(1/3)*sin(1.352^9/(4+3)) = 0.787603
START_TEST(s24) {
  double result = 0;
  int ex_code = calculate("cos(1/3)*sin(1.352^9/(4+3))", &result);
  ck_assert_double_eq_tol(result, 0.787603, TOL);
  ck_assert_int_eq(ex_code, 0);
}
END_TEST

//    (cos(1/3)*sin(1.352^9/(4+3))/76.56)*log(150) = 0.022386
START_TEST(s25) {
  double result = 0;
  int ex_code =
      calculate("(cos(1/3)*sin(1.352^9/(4+3))/76.56)*log(150)", &result);
  ck_assert_double_eq_tol(result, 0.022386, TOL);
  ck_assert_int_eq(ex_code, 0);
}
END_TEST

//    2+(-(-(-(-1)))) = 3
START_TEST(s26) {
  double result = 0;
  int ex_code = calculate("2+(-(-(-(-1))))", &result);
  ck_assert_double_eq_tol(result, 3, TOL);
  ck_assert_int_eq(ex_code, 0);
}
END_TEST
//    .4+.4
START_TEST(s27) {
  double result = 0;
  int ex_code = calculate(".4+.4", &result);
  ck_assert_double_eq_tol(result, 0.8, TOL);
  ck_assert_int_eq(ex_code, 0);
}
END_TEST

// asin(X)* log(9.4 - 9) + (atan(X^2) - acos(0.9  )) ; var = 1
START_TEST(s28) {
  double result = 0;
  int ex_code = calculate_var(
      "asin(X)* log(9.4 - 9) + (atan(X^2) - acos(0.9  ))", &result, 1);
  ck_assert_int_eq(ex_code, 0);
  ck_assert_double_eq_tol(result, -0.290711, TOL);
}
END_TEST
//    sin(2)*6
START_TEST(s29) {
  double result = 0;
  int ex_code = calculate("sin(2)* 6", &result);
  ck_assert_int_eq(ex_code, 0);
  ck_assert_double_eq_tol(result, 5.455785, TOL);
}
END_TEST
//    cos(6*3)/5
START_TEST(s30) {
  double result = 0;
  int ex_code = calculate("cos(6*3)/5", &result);
  ck_assert_int_eq(ex_code, 0);
  ck_assert_double_eq_tol(result, 0.132063, TOL);
}
END_TEST
//    sin(X)
START_TEST(s31) {
  double result = 0;
  int ex_code = calculate_var("sin(X)", &result, 1);
  ck_assert_int_eq(ex_code, 0);
  ck_assert_double_eq_tol(result, 0.841471, TOL);
}
END_TEST
//    ln(X)mod1
START_TEST(s32) {
  double result = 0;
  int ex_code = calculate_var("ln(X)mod1", &result, 3);
  ck_assert_int_eq(ex_code, 0);
  ck_assert_double_eq_tol(result, 0.098612, TOL);
}
END_TEST
//    sin(X*6)
START_TEST(s33) {
  double result = 0;
  int ex_code = calculate_var("sin(X*6)", &result, 9);
  ck_assert_int_eq(ex_code, 0);
  ck_assert_double_eq_tol(result, -0.558789, TOL);
}
END_TEST

Suite *simple_suite(void) {
  Suite *s = suite_create("Simple math");
  TCase *tc = tcase_create("Simple math");

  tcase_add_test(tc, s1);
  tcase_add_test(tc, s2);
  tcase_add_test(tc, s3);
  tcase_add_test(tc, s4);
  tcase_add_test(tc, s5);
  tcase_add_test(tc, s6);
  tcase_add_test(tc, s7);
  tcase_add_test(tc, s8);
  tcase_add_test(tc, s9);
  tcase_add_test(tc, s10);
  tcase_add_test(tc, s11);
  tcase_add_test(tc, s12);
  tcase_add_test(tc, s13);
  tcase_add_test(tc, s14);
  tcase_add_test(tc, s15);
  tcase_add_test(tc, s16);
  tcase_add_test(tc, s17);
  tcase_add_test(tc, s18);
  tcase_add_test(tc, s19);
  tcase_add_test(tc, s20);
  tcase_add_test(tc, s21);
  tcase_add_test(tc, s22);
  tcase_add_test(tc, s23);
  tcase_add_test(tc, s24);
  tcase_add_test(tc, s25);
  tcase_add_test(tc, s26);
  tcase_add_test(tc, s27);
  tcase_add_test(tc, s28);
  tcase_add_test(tc, s29);
  tcase_add_test(tc, s30);
  tcase_add_test(tc, s31);
  tcase_add_test(tc, s32);
  tcase_add_test(tc, s33);

  suite_add_tcase(s, tc);

  return s;
}
