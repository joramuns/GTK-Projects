//
//  parser.c
//  C7_SmartCalc
//
//  Created by Joramun Sasin on 8/25/22.
//

#include "parser.h"

int validate_input(char *expression) {
    int ex_code = 0;
    size_t input_len = strlen(expression);

    if (input_len > 0 && expression[input_len - 1] == '\n') {
        expression[input_len - 1] = '\0';
        input_len--;
    }
    if (input_len > EXPRESSION_SIZE) {
        ex_code = TOO_LONG_EXPRESSION;
    }
    if (strspn(expression, EXPRESSION_SYMBOLS) != input_len) {
        ex_code = WRONG_SYMBOLS;
    }
    if (strchr(expression, 'X') != 0) {
        ex_code = check_variable(expression);
        if (ex_code == 0) ex_code = VARIABLE_INSIDE;
    }

    return ex_code;
}

int parse_input(char *expression, node *output_stack) {
    int ex_code = 0;
    size_t array_pos = 0;
    node *queue_stack = init_node();
    size_t input_len = strlen(expression);
    while (array_pos < input_len) {
        int check_result = check_input_type(expression[array_pos]);
        if (check_result == TOK_NUM || check_result == TOK_DOT) {
            ex_code = parse_double(&array_pos, expression, output_stack);
        } else if ((check_result == TOK_OPERATOR_1) || (check_result == TOK_OPERATOR_2) ||
                   (check_result == TOK_POW) || (check_result == TOK_OPEN_BRACE)) {
            if (check_result == TOK_OPERATOR_1) handle_unary(expression, array_pos, output_stack);
            if (array_pos > 0 && check_result == TOK_OPEN_BRACE) {
                int before_brace = check_input_type(expression[array_pos - 1]);
                    if (before_brace != TOK_OPERATOR_1 && before_brace != TOK_OPERATOR_2 && before_brace != TOK_POW && before_brace != TOK_OPEN_BRACE) {
                        ex_code = WRONG_SYMBOLS;
                    }
            }
            handle_operator(expression[array_pos], output_stack, queue_stack, check_result);
            array_pos++;
        } else if (check_result == TOK_CLOSE_BRACE) {
            int after_brace = check_input_type(expression[array_pos + 1]);
            if (array_pos > 0 && expression[array_pos - 1] == '(') {
                ex_code = EMPTY_BRACES;
            } else if (after_brace != TOK_OPERATOR_1 && after_brace != TOK_OPERATOR_2 && after_brace != TOK_POW && after_brace != TOK_CLOSE_BRACE && expression[array_pos + 1] != '\0') {
                ex_code = WRONG_SYMBOLS;
            } else {
                array_pos++;
                ex_code = handle_close_brace(output_stack, queue_stack);
            }
        } else if (check_result == TOK_UNARY) {
            int type_unary = parse_long_operator(expression, &array_pos);
            if (type_unary == CODE_MOD) {
                handle_operator(type_unary, output_stack, queue_stack, TOK_OPERATOR_2);
            } else if (type_unary >= CODE_ACOS && type_unary <= CODE_LN) {
                handle_operator(type_unary, output_stack, queue_stack, TOK_UNARY);
            } else {
                ex_code = type_unary;
            }
        } else if (check_result == 0) {
            array_pos++;
        } else {
            ex_code = check_result;
        }
        if (ex_code >= 100) {
            array_pos = input_len;
        }
    }
    clean_queue_stack(output_stack, queue_stack);

    return ex_code;
}

int validate_stack(node *output_stack) {
    int ex_code = 0;
    int operator_number = 0, operand_number = 0, open_brace = 0, close_brace = 0;
    node *head = output_stack;

    while (head) {
        if (head->type == TOK_NUM) {
            operand_number++;
        } else if (head->type == TOK_OPERATOR_1 || head->type == TOK_OPERATOR_2 || head->type == TOK_POW) {
            operator_number++;
        } else if (head->type == TOK_OPEN_BRACE) {
            open_brace++;
        } else if (head->type == TOK_CLOSE_BRACE) {
            close_brace++;
        }
        head = head->next;
    }
    if (operator_number >= operand_number) {
        ex_code = EXTRA_SIGNS;
    } else if (open_brace != close_brace) {
        ex_code = BRACE_NUMBER;
    }

    return ex_code;
}
