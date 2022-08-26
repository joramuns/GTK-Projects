//
//  simple_suite.c
//  C7_SmartCalc
//
//  Created by Joramun Sasin on 8/26/22.
//

#include "check_main.h"

START_TEST(first) {
//    4 + 4 * 2 / ( 1 - 5 )
//    4 + 4 * 2 / 1 - 5
//    4 + 4 * ( 2 / 1 - 5 )
//    4 + ( 4 * 2 / 1 - 5 )
//    4 + 4 * ( 2 /  1 ) - 5
//    4 + ( 4 * 2 / 1 ) - 5
//    ( 4 + 4 * 2 / 1 ) - 5
//    4 + ( 4 * 2 ) / 1 - 5
//    ( 4 + 4 * 2 ) / 1 - 5
//    8 * (7 + 6 * 4) + 3
//    2 / (3 + 2) * 5
    ck_assert_int_eq();
}
END_TEST

Suite *simple_suite(void) {
    Suite *s = suite_create("Simple math");
    TCase *tc = tcase_create("Simple math");

    tcase_add_loop_test(tc, first, 0, 10);

    suite_add_tcase(s, tc);

    return s;
}
