//
//  calculator.h
//  C7_SmartCalc
//
//  Created by Joramun Sasin on 8/27/22.
//

#ifndef calculator_h
#define calculator_h

#include <stdio.h>

#include "../Validation/nodes.h"
#include "../Validation/parser.h"
#include "eval_func.h"

int calculate(char *expression, double *result);
void replace_variable(node *output_stack, double var);
int calculate_var(char *expression, double *result, double var);

#endif /* calculator_h */
