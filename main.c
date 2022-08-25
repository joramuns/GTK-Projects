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
#define EXPRESSION_SIZE 100
#define ISDIGIT check_digit(expression[*array_pos]) == 1
#define ISDOT check_digit(expression[*array_pos]) == 2
enum input_type {
    EMPTY = 0,
    TOK_NUM,
    TOK_OPERATOR,
    TOK_BRACE,
    TOK_UNARY
};

int check_digit(char input) {   // check type? enum? 0 - error ?
    int ex_code = 0;

    if (input > 47 && input <58) {
        ex_code = 1;
    } else if (input == '.') {
        ex_code = 2;
    }

    return ex_code;
}

static void parse_double(int *array_pos, char *expression, node *num_stack) {
    node *last = find_last(num_stack);
    last->type = 1;
    while (ISDIGIT) {
        last->value = last->value * 10.0 + (expression[*array_pos] - '0');
        *array_pos += 1;
    }
    if (ISDOT) {
        *array_pos += 1;
        double parse_divider = 1.0;
        while (ISDIGIT) {
            parse_divider /= 10.0;
            last->value = (expression[*array_pos] - '0') * parse_divider + last->value;
            *array_pos += 1;
        }
        if (ISDOT) {
            printf("ERROR_DOT\n");
        }
    }
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
        if (check_digit(expression[array_pos]) == 1) {
            parse_double(&array_pos, expression, num_stack);
            push(num_stack);
        }
        array_pos++;
    }
    print_node(num_stack);
    

    clean(num_stack);
    clean(oper_stack);

    return 0;
}
