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

typedef struct credit_input {
    double sum;
    unsigned term;
    double rate;
    unsigned type;
} credit_input;

typedef struct credit_output {
    double total_sum;
    node *stack_of_payments;
    double overpaid;
} credit_output;

void handle_credit_calculator(credit_input input, credit_output *output);
int eval_annuity_credit(credit_input input, credit_output *output);
int eval_differentiated_credit(credit_input input, credit_output *output);

#endif /* credit_calculator_h */
