//
//  main_check.c
//  C7_SmartCalc
//
//  Created by Joramun Sasin on 8/26/22.
//

#include "check_main.h"

int main() {
    Suite *suites_calc[] = {
        simple_suite(),
        errors_suite(),
        credit_suite(),
        deposit_suite(),
    };

    SRunner *sr = srunner_create(suites_calc[0]);
    srunner_set_fork_status(sr, CK_NOFORK);

    for (size_t i = 1; i < 4; i++) srunner_add_suite(sr, suites_calc[i]);

    srunner_run_all(sr, CK_NORMAL);
    int nf = srunner_ntests_failed(sr);
    srunner_free(sr);

    return nf == 0 ? 0 : 1;
}
