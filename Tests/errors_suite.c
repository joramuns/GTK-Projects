
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
    int ex_code = calculate("(cos(1/3)*sin(1.352^^9/(4+3))/76.56)*log(150)", &result);
    ck_assert_int_gt(ex_code, 0);
}
END_TEST
//    (cos(1/3)*sin(1.3)52^9/(4+3))/76.56)*log(150) = ERROR (103)
START_TEST(s5) {
    double result = 0;
    int ex_code = calculate("(cos(1/3)*sin(1.3)52^9/(4+3))/76.56)*log(150)", &result);
    ck_assert_int_gt(ex_code, 0);
}
END_TEST
//    cos(1/3)*sin(1.352^9/(4+3))/76.56)*log(150) = ERROR (105)
START_TEST(s6) {
    double result = 0;
    int ex_code = calculate("cos(1/3)*sin(1.352^9/(4+3))/76.56)*log(150)", &result);
    ck_assert_int_gt(ex_code, 0);
}
END_TEST
//    (cos(1/3)*sin(1.352^9/4+3))/76.56)*log(150) = ERROR (105)
START_TEST(s7) {
    double result = 0;
    int ex_code = calculate("(cos(1/3)*sin(1.352^9/4+3))/76.56)*log(150)", &result);
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
    int ex_code = calculate("(cos(1/3)*sin(1.352^^9/(4+3))/76.56)*log(150)", &result);
    ck_assert_int_gt(ex_code, 0);
}
END_TEST
//    (cos(1/3)*sinsin(1.352^9/(4+3))/76.56)*log(150) = ERROR (106)
START_TEST(s10) {
    double result = 0;
    int ex_code = calculate("(cos(1/3)*sinsin(1.352^9/(4+3))/76.56)*log(150)", &result);
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

Suite *errors_suite(void) {
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
    /* tcase_add_test(tc, s20); */
    /* tcase_add_test(tc, s21); */
    /* tcase_add_test(tc, s22); */
    /* tcase_add_test(tc, s23); */
    /* tcase_add_test(tc, s24); */
    /* tcase_add_test(tc, s25); */

    suite_add_tcase(s, tc);

    return s;
}
