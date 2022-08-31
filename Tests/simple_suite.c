//
//  simple_suite.c
//  C7_SmartCalc
//
//  Created by Joramun Sasin on 8/26/22.
//

#include "check_main.h"

START_TEST(first) {
//    4 + 4 * 2 / ( 1 - 5 ) = 2
//    4 + 4 * 2 / 1 - 5 = 7
//    4 + 4 * ( 2 / 1 - 5 ) = -8
//    4 + ( 4 * 2 / 1 - 5 ) = 7
//    4 + 4 * ( 2 /  1 ) - 5 = 7
//    4 + ( 4 * 2 / 1 ) - 5 = 7
//    ( 4 + 4 * 2 / 1 ) - 5 = 7
//    4 + ( 4 * 2 ) / 1 - 5 = 7
//    ( 4 + 4 * 2 ) / 1 - 5 = 7
//    8 * (7 + 6 * 4) + 3 = 251
//    2 / (3 + 2) * 5 = 2
//    2+9.3-8^3/4+56.2 = -60.5
//    2+9.3-8^3/(4+56.2) = 2.795017
//    2^3^2 = 512
//    2^(3^2) = 512
//    (2^3)^2 = 64
//    cos(431.2*2^2/8) = -0.390250
//    3*sin(4+5) = 1.236355
//    431.2*2^2/8 = 215.6
//    cos(sin(2+9*6^1.2-tan(1))) = 0.742186 (0.742182?)
//    sqrt(cos(sin(2+9*6^1.2-tan(1)))) = 0.861502 (0.861500?)
//    sqrt(cos(sin(2+9*6^1.2-tan(1))))mod0.1 = 0.061502 (0.061500?)
//    sqrt(2^2)*5/(4-3mod2)*(4-sqrt(81)) = -16.666667
//    cos(1/3)*sin(1.352^9/(4+3)) = 0.787603
//    (cos(1/3)*sin(1.352^9/(4+3))/76.56)*log(150) = 0.022386
//    sinn(20) = ERROR (106)
//    2,2+2 = ERROR (103)
//    2.2+9,2 = ERROR (103)
//    (cos(1/3)*sin(1.352^^9/(4+3))/76.56)*log(150) = ERROR (108)
//    (cos(1/3)*sin(1.3)52^9/(4+3))/76.56)*log(150) = ERROR (103)
//    cos(1/3)*sin(1.352^9/(4+3))/76.56)*log(150) = ERROR (105)
//    (cos(1/3)*sin(1.352^9/4+3))/76.56)*log(150) = ERROR (105)
//    2^^2 = ERROR (108)
//    (cos(1/3)*sin(1.352^^9/(4+3))/76.56)*log(150) = ERROR (108)
//    (cos(1/3)*sinsin(1.352^9/(4+3))/76.56)*log(150) = ERROR (106)
//    sinsin(1) = ERROR (106)
//    sin() = ERROR (106)
//    sin( = ERROR (106)
//    sinn = ERROR (106)
//    si = ERROR (102)
//    si(1) = ERROR (101)
//    si(()) = ERROR (101)
//    sin(()) = ERROR (107)
//    2+(-(-(-(-1))) = ERROR (105)
//    2+(-(-(-(-1)))) = 3
//    .4+.4
//    2.2.2.2
//    .sin(3)
//    sin(3).
//    3X
//    XX
//    8*XX
//    X8
//    8*X.
//    8*Xsin(4)
//    sin(X)
//    sin(X*6)
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
