//
//  check_main.h
//  C7_SmartCalc
//
//  Created by Joramun Sasin on 8/26/22.
//

#ifndef check_main_h
#define check_main_h
#include <check.h>
#include <stdio.h>

#include "../Calculation/calculator.h"
#include "../Calculation/credit_calculator.h"
#include "../Calculation/deposit_calculator.h"

#define TOL 1e-06
Suite *simple_suite(void);
Suite *errors_suite(void);
Suite *credit_suite(void);
Suite *deposit_suite(void);

#endif /* check_main_h */
