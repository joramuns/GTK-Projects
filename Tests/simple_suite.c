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
//    2+9.3-8^3/4+56.2
//    2+9.3-8^3/(4+56.2)
//    2^3^2
//    2^(3^2)
//    (2^3)^2
//    =cos(431.2*2^2/8)
//    3*sin(4+5)
//    431.2*2^2/8
//    cos(sin(2+9*6^1.2-tan(1)))
//    sqrt(cos(sin(2+9*6^1.2-tan(1))))
//    sqrt(cos(sin(2+9*6^1.2-tan(1))))mod0.1
//    sqrt(2^2)*5/(4-3mod2)*(4-sqrt(81))
//    cos(1/3)*sin(1.352^9/(4+3))
//    (cos(1/3)*sin(1.352^9/(4+3))/76.56)*log(150)
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
