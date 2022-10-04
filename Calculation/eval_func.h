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

/**
 * @brief A function that makes all evaluations after parsing and searching for
 * errors
 *
 * @param output_stack Ready for evaluation stack of operators and operands
 * after all checks
 *
 * @return Final value
 */
double evaluate(node *output_stack);
/**
 * @brief A function that evaluates binary operation
 *
 * @param head A node list stack with operators
 * @param stack_number A node list stack with operands
 *
 * @return Result value of operation
 */
double handle_binary_operator(node *head, node *stack_number);
/**
 * @brief A function that evalueates unary operation
 *
 * @param head A node list stack with operators
 * @param stack_number A node list stack with operands
 *
 * @return Result value of operation
 */
double handle_unary_operator(node *head, node *stack_number);

#endif /* eval_func_h */
