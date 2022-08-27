//
//  calculator.h
//  C7_SmartCalc
//
//  Created by Joramun Sasin on 8/27/22.
//

#ifndef calculator_h
#define calculator_h

#include <stdio.h>
#include "Validation/parser.h"
#include "Validation/nodes.h"
#include "Calculation/eval_func.h"

int calculate(char* expression, double *result);

#endif /* calculator_h */
