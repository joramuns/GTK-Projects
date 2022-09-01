//
//  eval_func.h
//  C7_SmartCalc
//
//  Created by Joramun Sasin on 8/27/22.
//

#ifndef eval_func_h
#define eval_func_h

#include <math.h>

#include "../Validation/nodes.h"
#include "../Validation/parser.h"

double evaluate(node *output_stack);
double handle_binary_operator(node *head, node *stack_number);
double handle_unary_operator(node *head, node *stack_number);

#endif /* eval_func_h */
