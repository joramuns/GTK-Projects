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
    validate_input(expression);
    parse_input(expression, output_stack);
    *result = evaluate(output_stack);
    clean(output_stack);

    return ex_code;
}
