//
//  main0.c
//  C7_SmartCalc
//
//  Created by Joramun Sasin on 8/25/22.
//

#include <stdio.h>
#include <string.h>
#include "Stack/parser.h"
#include "Stack/nodes.h"
#define EXPRESSION_SIZE 10
enum input_type {
    TOK_OPERATOR = 0,
    TOK_BRACE = 1,
    TOK_UNARY = 2
};

int check_digit(char input) {
    int ex_code = 0;

    if (input > 47 && input <58) {
        ex_code = 1;
    } else if (input == '.') {
        ex_code = 2;
    }

    return ex_code;
}

int main() {
    char expression[EXPRESSION_SIZE + 1 + 1] = {0};
    fgets(expression, EXPRESSION_SIZE + 1 + 1, stdin);
    size_t input_len = strlen(expression);
    if (input_len > 0 && expression[input_len - 1] == '\n') {
        expression[input_len - 1] = '\0';
        input_len--;
    }
    if (input_len > EXPRESSION_SIZE) {
        printf("ERROR\n");
    } else {
        printf("We have: %s\n", expression);
    }
    node *num_stack = init_node();
    node *oper_stack = init_node();

    int array_pos = 0;

    while (array_pos < input_len) {
        if (check_digit(expression[array_pos])) {
            while (check_digit(expression[array_pos]) == 1) {
                num_stack->value = num_stack->value * 10.0 + (expression[array_pos] - '0');
                array_pos++;
            }
            if (check_digit(expression[array_pos]) == 2) {
                array_pos++;
                double parse_divider = 1.0;
                while (check_digit(expression[array_pos]) == 1) {
                    parse_divider /= 10.0;
                    num_stack->value = (expression[array_pos] - '0') * parse_divider + num_stack->value;
                    array_pos++;
                }
            }
            printf("%lf\n", num_stack->value);
            num_stack = push(num_stack);
        }
        array_pos++;
    }


    clean(num_stack);
    clean(oper_stack);

    return 0;
}
