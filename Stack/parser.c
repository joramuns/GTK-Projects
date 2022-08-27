//
//  parser.c
//  C7_SmartCalc
//
//  Created by Joramun Sasin on 8/25/22.
//

#include "parser.h"
// stacks - output and queue?
int check_input_type(char input) {   // check type? enum? 0 - error ?
    int ex_code = 0;

    if (input > 47 && input < 58) {
        ex_code = TOK_NUM;
    } else if (input == '.') {
        ex_code = TOK_DOT;
    } else if (input == '+' || input == '-') {
        ex_code = TOK_OPERATOR_1;
    } else if (input == '/' || input == '*') {
        ex_code = TOK_OPERATOR_2;
    } else if (input == '^') {
        ex_code = TOK_POW;
    } else if (input == '(') {
        ex_code = TOK_OPEN_BRACE;
    } else if (input == ')') {
        ex_code = TOK_CLOSE_BRACE;
    } else if (input == 's' || input == 'c' || input == 't' || \
               input == 'a' || input == 'm' || input == 'l') {
        ex_code = TOK_UNARY;
    }

    return ex_code;
}

void parse_double(int *array_pos, char *expression, node *output_stack) {
    node *last = find_last(output_stack);
    last->type = TOK_NUM;
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

void handle_operator(char operator, node *output_stack, node *queue_stack, int input_type) {
    node *last_queue = find_last(queue_stack);
    while (last_queue->number > 0 && last_queue->type >= input_type && \
           last_queue->type < TOK_OPEN_BRACE &&\
           (last_queue->type != TOK_POW || input_type != TOK_POW)) {
        push_n_pop(output_stack, queue_stack);
        last_queue = find_last(queue_stack);
    }
    push(queue_stack);
    last_queue = find_last(queue_stack);
    last_queue->type = input_type;
    last_queue->sign = operator;
}
