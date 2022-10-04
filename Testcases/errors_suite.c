
#include "check_main.h"

//    sinn(20) = ERROR (106)
START_TEST(s1) {
  double result = 0;
  int ex_code = calculate("sinn(20)", &result);
  ck_assert_int_gt(ex_code, 0);
}
END_TEST

//    2,2+2 = ERROR (103)
START_TEST(s2) {
  double result = 0;
  int ex_code = calculate("2,2+2", &result);
  ck_assert_int_gt(ex_code, 0);
}
END_TEST
//    2.2+9,2 = ERROR (103)
START_TEST(s3) {
  double result = 0;
  int ex_code = calculate("2.2+9,2", &result);
  ck_assert_int_gt(ex_code, 0);
}
END_TEST
//    (cos(1/3)*sin(1.352^^9/(4+3))/76.56)*log(150) = ERROR (108)
START_TEST(s4) {
  double result = 0;
  int ex_code =
      calculate("(cos(1/3)*sin(1.352^^9/(4+3))/76.56)*log(150)", &result);
  ck_assert_int_gt(ex_code, 0);
}
END_TEST
//    (cos(1/3)*sin(1.3)52^9/(4+3))/76.56)*log(150) = ERROR (103)
START_TEST(s5) {
  double result = 0;
  int ex_code =
      calculate("(cos(1/3)*sin(1.3)52^9/(4+3))/76.56)*log(150)", &result);
  ck_assert_int_gt(ex_code, 0);
}
END_TEST
//    cos(1/3)*sin(1.352^9/(4+3))/76.56)*log(150) = ERROR (105)
START_TEST(s6) {
  double result = 0;
  int ex_code =
      calculate("cos(1/3)*sin(1.352^9/(4+3))/76.56)*log(150)", &result);
  ck_assert_int_gt(ex_code, 0);
}
END_TEST
//    (cos(1/3)*sin(1.352^9/4+3))/76.56)*log(150) = ERROR (105)
START_TEST(s7) {
  double result = 0;
  int ex_code =
      calculate("(cos(1/3)*sin(1.352^9/4+3))/76.56)*log(150)", &result);
  ck_assert_int_gt(ex_code, 0);
}
END_TEST
//    2^^2 = ERROR (108)
START_TEST(s8) {
  double result = 0;
  int ex_code = calculate("2^^2", &result);
  ck_assert_int_gt(ex_code, 0);
}
END_TEST
//    (cos(1/3)*sin(1.352^^9/(4+3))/76.56)*log(150) = ERROR (108)
START_TEST(s9) {
  double result = 0;
  int ex_code =
      calculate("(cos(1/3)*sin(1.352^^9/(4+3))/76.56)*log(150)", &result);
  ck_assert_int_gt(ex_code, 0);
}
END_TEST
//    (cos(1/3)*sinsin(1.352^9/(4+3))/76.56)*log(150) = ERROR (106)
START_TEST(s10) {
  double result = 0;
  int ex_code =
      calculate("(cos(1/3)*sinsin(1.352^9/(4+3))/76.56)*log(150)", &result);
  ck_assert_int_gt(ex_code, 0);
}
END_TEST
//    sinsin(1) = ERROR (106)
START_TEST(s11) {
  double result = 0;
  int ex_code = calculate("sinsin(1)", &result);
  ck_assert_int_gt(ex_code, 0);
}
END_TEST
//    sin() = ERROR (106)
START_TEST(s12) {
  double result = 0;
  int ex_code = calculate("sin()", &result);
  ck_assert_int_gt(ex_code, 0);
}
END_TEST
//    sin( = ERROR (106)
START_TEST(s13) {
  double result = 0;
  int ex_code = calculate("sin(", &result);
  ck_assert_int_gt(ex_code, 0);
}
END_TEST
//    sinn = ERROR (106)
START_TEST(s14) {
  double result = 0;
  int ex_code = calculate("sinn", &result);
  ck_assert_int_gt(ex_code, 0);
}
END_TEST
//    si = ERROR (102)
START_TEST(s15) {
  double result = 0;
  int ex_code = calculate("si", &result);
  ck_assert_int_gt(ex_code, 0);
}
END_TEST
//    si(1) = ERROR (101)
START_TEST(s16) {
  double result = 0;
  int ex_code = calculate("si(1)", &result);
  ck_assert_int_gt(ex_code, 0);
}
END_TEST
//    si(()) = ERROR (101)
START_TEST(s17) {
  double result = 0;
  int ex_code = calculate("si(())", &result);
  ck_assert_int_gt(ex_code, 0);
}
END_TEST
//    sin(()) = ERROR (107)
START_TEST(s18) {
  double result = 0;
  int ex_code = calculate("sin(())", &result);
  ck_assert_int_gt(ex_code, 0);
}
END_TEST
//    2+(-(-(-(-1))) = ERROR (105)
START_TEST(s19) {
  double result = 0;
  int ex_code = calculate("2+(-(-(-(-1)))", &result);
  ck_assert_int_gt(ex_code, 0);
}
END_TEST

//    2.2.2.2
START_TEST(s20) {
  double result = 0;
  int ex_code = calculate("2.2.2.2", &result);
  ck_assert_int_gt(ex_code, 0);
}
END_TEST
//    .sin(3)
START_TEST(s21) {
  double result = 0;
  int ex_code = calculate(".sin(3)", &result);
  ck_assert_int_gt(ex_code, 0);
}
END_TEST
//    sin(3).
START_TEST(s22) {
  double result = 0;
  int ex_code = calculate("sin(3).", &result);
  ck_assert_int_gt(ex_code, 0);
}
END_TEST
//    3X
START_TEST(s23) {
  double result = 0;
  int ex_code = calculate("3X", &result);
  ck_assert_int_gt(ex_code, 0);
  ck_assert_int_ne(ex_code, 109);
}
END_TEST
//    XX
START_TEST(s24) {
  double result = 0;
  int ex_code = calculate("XX", &result);
  ck_assert_int_gt(ex_code, 0);
  ck_assert_int_ne(ex_code, 109);
}
END_TEST
//    8*XX
START_TEST(s25) {
  double result = 0;
  int ex_code = calculate("8*XX", &result);
  ck_assert_int_gt(ex_code, 0);
  ck_assert_int_ne(ex_code, 109);
}
END_TEST
//    X8
START_TEST(s26) {
  double result = 0;
  int ex_code = calculate_var("X8", &result, 4);
  ck_assert_int_gt(ex_code, 0);
  ck_assert_int_ne(ex_code, 109);
}
END_TEST
//    8*X.
START_TEST(s27) {
  double result = 0;
  int ex_code = calculate("8*X.", &result);
  ck_assert_int_gt(ex_code, 0);
  ck_assert_int_ne(ex_code, 109);
}
END_TEST
//    8*Xsin(4)
START_TEST(s28) {
  double result = 0;
  int ex_code = calculate("8*Xsin(4)", &result);
  ck_assert_int_gt(ex_code, 0);
  ck_assert_int_ne(ex_code, 109);
}
END_TEST

//    Xcos((
START_TEST(s29) {
  double result = 0;
  int ex_code = calculate_var("Xcos((", &result, 0);
  ck_assert_int_gt(ex_code, 0);
  ck_assert_int_ne(ex_code, 109);
}
END_TEST
//    X5
START_TEST(s30) {
  double result = 0;
  int ex_code = calculate_var("X5", &result, 0);
  ck_assert_int_gt(ex_code, 0);
  ck_assert_int_ne(ex_code, 109);
}
END_TEST
//    1sin(3)
START_TEST(s31) {
  double result = 0;
  int ex_code = calculate("1sin(3)", &result);
  ck_assert_int_gt(ex_code, 0);
  ck_assert_int_ne(ex_code, 109);
}
END_TEST
//    sin(3)6
START_TEST(s32) {
  double result = 0;
  int ex_code = calculate("sin(3)6", &result);
  ck_assert_int_gt(ex_code, 0);
  ck_assert_int_ne(ex_code, 109);
}
END_TEST
//    sin(3.3.3)
START_TEST(s33) {
  double result = 0;
  int ex_code = calculate("sin(3.3.3)", &result);
  ck_assert_int_gt(ex_code, 0);
  ck_assert_int_ne(ex_code, 109);
}
END_TEST

START_TEST(s34) {
  char test[] = "";
  int ex_code = validate_input_numbers(test);
  ck_assert_int_eq(ex_code, EXPRESSION_TOO_SHORT);
}
END_TEST

START_TEST(s35) {
  char test[] = "-123";
  int ex_code = validate_input_numbers(test);
  ck_assert_int_eq(ex_code, WRONG_SYMBOLS);
}
END_TEST

START_TEST(s36) {
  char test[] = "1.12.3";
  int ex_code = validate_extra_dot(test);
  ck_assert_int_eq(ex_code, WRONG_SYMBOLS);
}
END_TEST

//    (2)3
//    2(3)
//    mod*cos(8)
//    3modmod2

Suite *errors_suite(void) {
  Suite *s = suite_create("Error test");
  TCase *tc = tcase_create("Error test");

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
  tcase_add_test(tc, s34);
  tcase_add_test(tc, s35);
  tcase_add_test(tc, s36);

  suite_add_tcase(s, tc);

  return s;
}
