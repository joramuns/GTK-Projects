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
/**
 * @brief A suite of check.h tests with simple calculations
 *
 * @return a suite to use further in tests
 */
Suite *simple_suite(void);
/**
 * @brief A suite of check.h tests with errors handling
 *
 * @return a suite to use further in tests
 */
Suite *errors_suite(void);
/**
 * @brief A suite of check.h tests with credit calculation cases
 *
 * @return a suite to use further in tests
 */
Suite *credit_suite(void);
/**
 * @brief A suite of check.h tests with deposit calculation cases
 *
 * @return a suite to use further in tests
 */
Suite *deposit_suite(void);

#endif /* check_main_h */
