//
//  calculator.c
//  C7_SmartCalc
//
//  Created by Joramun Sasin on 8/27/22.
//

#include "calculator.h"

int calculate(char* expression, double *result) {
    int ex_code = 0;

    node *output_stack = init_node();
    ex_code = validate_input(expression);
    if (ex_code == 0) ex_code = parse_input(expression, output_stack);
    if (ex_code == 0) ex_code = validate_stack(output_stack);
    if (ex_code == 0) *result = evaluate(output_stack);
    clean(output_stack);

    return ex_code;
}

void replace_variable(node *output_stack, double var) {
    node *head = output_stack;
    while (head) {
        if (head->type == TOK_NUM && head->sign == 'X') {
            head->value = var;
        }
        head = head->next;
    }
}

int calculate_var(char* expression, double *result, double var) {
    int ex_code = 0;

    node *output_stack = init_node();
    ex_code = validate_input(expression);
    if (ex_code == VARIABLE_INSIDE) ex_code = parse_input(expression, output_stack);
    if (ex_code == 0) ex_code = validate_stack(output_stack);
    if (ex_code == 0) {
        replace_variable(output_stack, var);
        *result = evaluate(output_stack);
    }
    clean(output_stack);

    return ex_code;
}
