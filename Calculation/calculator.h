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

/**
 * @brief Calculates value of given expression
 *
 * @param expression Char array with mathematical expression
 * @param result Result of calculation
 *
 * @return 
 */
int calculate(char *expression, double *result);
/**
 * @brief Replaces X variable in given stack
 * @param output_stack Parsed expression in node-like stack
 * @param var Value to replace in place of X variable
 */
void replace_variable(node *output_stack, double var);
/**
 * @brief Calculate value of given expression with X variable
 *
 * @param expression Char array with mathematical expression
 * @param result Result of calculation
 * @param var Value to replace in place of X variable
 *
 * @return 
 */
int calculate_var(char *expression, double *result, double var);

#endif /* calculator_h */
