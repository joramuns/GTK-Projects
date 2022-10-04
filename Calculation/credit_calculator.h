//
//  credit_calculator.h
//  C7_SmartCalc
//
//  Created by Joramun Sasin on 9/3/22.
//

#ifndef credit_calculator_h
#define credit_calculator_h

#include <math.h>
#include <stdio.h>

#include "../Validation/nodes.h"
#include "../Validation/parser.h"
#include "bank_rounding.h"

/**
 * @brief A structure to represent data from GUI input
 */
typedef struct credit_input {
    double sum; /**< Sum of credit to evaluate */
    unsigned term; /**< Amount of monthes to be credited, different types of input as years evaluates the number of monthes */
    double rate; /**< Interest rate */
    unsigned type; /**< There are 2 different types of credit: 0 - for annuity, 1 - for differentiated */
} credit_input;

/**
 * @brief A structure to generate after evaluation of credit conditions
 */
typedef struct credit_output {
    double total_sum; /**< Outputs total sum that a client will pay */
    node *stack_of_payments; /**< Stores a node list with monthly payments for credit, needs to be freed */
    double overpaid; /**< Calculates the sum of overpayment due to interest rate */
} credit_output; /**< */

/**
 * @brief Main credit calculator function that heads in two ways depending on type of credit. It also converts interest rate in credit_input to real number and counts monthly interest rate
 *
 * @param input Input data from GUI
 * @param output Output data after all calculations
 */
void handle_credit_calculator(credit_input input, credit_output *output);
/**
 * @brief A function to calculate needed data on loan conditions for ANNUITY credit
 *
 * @param input Input data from GUI
 * @param output Output data after all calculations
 *
 * @return 
 */
int eval_annuity_credit(credit_input input, credit_output *output);
/**
 * @brief A function to calculate needed data on loan conditions for DIFFERENTIATED credit
 *
 * @param input Input data from GUI
 * @param output Output data after all calculations
 *
 * @return 
 */
int eval_differentiated_credit(credit_input input, credit_output *output);

#endif /* credit_calculator_h */
