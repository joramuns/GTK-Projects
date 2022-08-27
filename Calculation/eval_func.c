//
//  eval_func.c
//  C7_SmartCalc
//
//  Created by Joramun Sasin on 8/27/22.
//

#include "eval_func.h"

double evaluation(node *output_stack) {
    node *head = output_stack;
    node *stack_number = init_node();
    double result = 0;
    while (head) {
        if (head->type == TOK_NUM) {
            result = head->value;
        } else if (head->type == TOK_OPERATOR_1 || head->type == TOK_OPERATOR_2 \
                   || head->type == TOK_POW) {
            result = handle_binary_operator(head, stack_number);
        } else if (head->type == TOK_UNARY) {
            result = handle_unary_operator(head, stack_number);
        }
        push(stack_number);
        find_last(stack_number)->value = result;
        find_last(stack_number)->type = TOK_NUM;
        head = head->next;
    }
    clean(stack_number);

    return result;
}

double handle_binary_operator(node *head, node *stack_number) {
    double result = 0;

    double operand_2 = find_last(stack_number)->value;
    pop(stack_number);
    double operand_1 = find_last(stack_number)->value;
    pop(stack_number);
    if (head->sign == '+') {
        result = operand_1 + operand_2;
    } else if (head->sign == '-') {
        result = operand_1 - operand_2;
    } else if (head->sign == '*') {
        result = operand_1 * operand_2;
    } else if (head->sign == '/') {
        result = operand_1 / operand_2;
    } else if (head->sign == '%') {
        result = fmod(operand_1, operand_2);
    } else if (head->sign == '^') {
        result = powf(operand_1, operand_2);
    }

    return result;
}

double handle_unary_operator(node *head, node *stack_number) {
    double result = 0;

    double operand_1 = find_last(stack_number)->value;
    pop(stack_number);
    if (head->sign == CODE_ACOS) {
        result = acos(operand_1);
    } else if (head->sign == CODE_ASIN) {
        result = asin(operand_1);
    } else if (head->sign == CODE_ATAN) {
        result = atan(operand_1);
    } else if (head->sign == CODE_SQRT) {
        result = sqrt(operand_1);
    } else if (head->sign == CODE_SIN) {
        result = sin(operand_1);
    } else if (head->sign == CODE_COS) {
        result = cos(operand_1);
    } else if (head->sign == CODE_TAN) {
        result = tan(operand_1);
    } else if (head->sign == CODE_LOG) {
        result = log10(operand_1);
    } else if (head->sign == CODE_LN) {
        result = log(operand_1);
    }

    return result;
}
