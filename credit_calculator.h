//
//  credit_calculator.h
//  C7_SmartCalc
//
//  Created by Joramun Sasin on 9/3/22.
//

#ifndef credit_calculator_h
#define credit_calculator_h

#include <stdio.h>
#include <math.h>

typedef struct credit_input {
    double sum;
    unsigned term;
    double rate;
    unsigned type;
} credit_input;

int eval_annuity_credit(credit_input input);
int eval_differentiated_credit(credit_input input);

#endif /* credit_calculator_h */
