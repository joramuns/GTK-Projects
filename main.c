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
#define ISDIGIT check_input_type(expression[*array_pos]) == 1
#define ISDOT check_input_type(expression[*array_pos]) == 2
enum input_type {
    EMPTY = 0,
    TOK_NUM,
    TOK_OPERATOR,
    TOK_BRACE,
    TOK_UNARY
};
// stacks - output and queue?
int check_input_type(char input) {   // check type? enum? 0 - error ?
    int ex_code = 0;

    if (input > 47 && input <58) {
        ex_code = 1;
    } else if (input == '.') {
        ex_code = 2;
    } else if (input == '+' || input == '-') {
        ex_code = 3;
    } else if (input == '/' || input == '*') {
        ex_code = 4;
    } else if (input == '^') {
        ex_code = 5;
    } else if (input == 's' || input == 'c' || input == 't' || input == 'a' || input == 's' || input == 'l') {
        ex_code = 6;
    }

    return ex_code;
}

static void parse_double(int *array_pos, char *expression, node *output_stack) {
    node *last = find_last(output_stack);
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
    node *output_stack = init_node();
    node *queue_stack = init_node();

    int array_pos = 0;

    while (array_pos < input_len) {
        int check_result = check_input_type(expression[array_pos]);
        if (check_result == 1) {
            parse_double(&array_pos, expression, output_stack);
            push(output_stack);
        } else if (check_result == 3) {
            queue_stack->type = 3;
            queue_stack->sign = expression[array_pos];
            push(queue_stack);
            array_pos++;
        } else {
            array_pos++;
        }
    }
    print_node(output_stack);
    print_node(queue_stack);
    

    clean(output_stack);
    clean(queue_stack);

    return 0;
}
