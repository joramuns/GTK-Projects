//
//  module_parser.c
//  C7_SmartCalc
//
//  Created by Joramun Sasin on 8/27/22.
//

#include "parser.h"

int check_input_type(char input) {
    int ex_code = 0;

    if ((input > 47 && input < 58) || input == 'X') {
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
    } else if (input == ' ') {
        ex_code = 0;
    } else {
        ex_code = WRONG_SYMBOLS;
    }

    return ex_code;
}

int check_variable(char *expression) {
    int ex_code = 0, array_pos = 0, check_backward = 0;
    size_t len = strlen(expression);
    while (array_pos++ < len) {
        if (expression[array_pos] == 'X') {
            if (array_pos > 0) {
                check_backward = check_input_type(expression[array_pos - 1]);
                if (check_backward == TOK_NUM || check_backward == TOK_DOT || check_backward == TOK_CLOSE_BRACE) {
                    ex_code = SURROUNDING_VARIABLE;
                }
            }
            int check_forward = check_input_type(expression[array_pos + 1]);
            if (check_forward == TOK_NUM || check_forward == TOK_DOT || \
                check_forward == TOK_UNARY ||\
                check_forward == TOK_OPEN_BRACE) {
                ex_code = SURROUNDING_VARIABLE;
            }
        }
    }

    return ex_code;
}

int parse_double(size_t *array_pos, char *expression, node *output_stack) {
    int ex_code = 0;
    push(output_stack);
    node *last = find_last(output_stack);
    last->type = TOK_NUM;
    if (expression[*array_pos] == 'X') {
        last->sign = 'X';
        *array_pos += 1;
    } else {
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
                ex_code = EXTRA_DOT_ERROR;
                printf("ERROR_DOT\n");
            }
        }
    }

    return ex_code;
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

int parse_long_operator(char *expression, size_t *array_pos) {
    int ex_code = 0, position_move = 0;
    char *modified_expression = expression + *array_pos;
    size_t len = strlen(modified_expression);
    if (len > 4) {
        position_move = 4;
        if (strncmp(modified_expression, "acos", 4) == 0) {
            ex_code = CODE_ACOS;
        } else if (strncmp(modified_expression, "asin", 4) == 0) {
            ex_code = CODE_ASIN;
        } else if (strncmp(modified_expression, "atan", 4) == 0) {
            ex_code = CODE_ATAN;
        } else if (strncmp(modified_expression, "sqrt", 4) == 0) {
            ex_code = CODE_SQRT;
        }
    }
    if (len > 3 && ex_code == 0) {
        position_move = 3;
        if (strncmp(modified_expression, "sin", 3) == 0) {
            ex_code = CODE_SIN;
        } else if (strncmp(modified_expression, "cos", 3) == 0) {
            ex_code = CODE_COS;
        } else if (strncmp(modified_expression, "tan", 3) == 0) {
            ex_code = CODE_TAN;
        } else if (strncmp(modified_expression, "mod", 3) == 0) {
            ex_code = CODE_MOD;
        } else if (strncmp(modified_expression, "log", 3) == 0) {
            ex_code = CODE_LOG;
        }
    }
    if (len > 2 && ex_code == 0) {
        position_move = 2;
        if (strncmp(modified_expression, "ln", 2) == 0) {
            ex_code = CODE_LN;
        } else {
            position_move = 0;
            ex_code = WRONG_LONG_OPERATOR;
        }
    }
    if (len <= 2) {
        ex_code = EXPRESSION_TOO_SHORT;
    } else if (ex_code < 100) {
        *array_pos += position_move;
        if (ex_code != CODE_MOD) {
            if (expression[*array_pos] != '(' || expression[(*array_pos) + 1] == ')' \
                || expression[(*array_pos) + 1] == '\0') {
                printf("LONG OPERATOR BRACE ERROR\n");
                ex_code = LONG_OPERATOR_BRACE_ERROR;
            }
        }
    }

    return ex_code;
}

void handle_unary(const char *expression, size_t array_pos, node *output_stack) {
    if ((array_pos == 0) || (expression[array_pos - 1]) == '(') {
        push(output_stack);
        find_last(output_stack)->type = TOK_NUM;
        find_last(output_stack)->value = 0;
    }
}

int handle_close_brace(node *output_stack, node *queue_stack) {
    int ex_code = 0;

    node *last = find_last(queue_stack);
    while (last->type != TOK_OPEN_BRACE) {
        push_n_pop(output_stack, queue_stack);
        last = find_last(queue_stack);
        if (last->number == 0) {
            ex_code = BRACE_NUMBER;
            last->type = TOK_OPEN_BRACE;
        }
    }
    if (ex_code == 0) {
        pop(queue_stack);
    }

    return ex_code;
}

void clean_queue_stack(node *output_stack, node *queue_stack) {
    int check_queue = find_last(queue_stack)->number;
    while (check_queue > 0) {
        push_n_pop(output_stack, queue_stack);
        check_queue = find_last(queue_stack)->number;
    }
    clean(queue_stack);
}
