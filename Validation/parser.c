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
    if (strspn(expression, "1234567890sincosatanmodsqrtlnlog()+-*/^.") != input_len) {
        ex_code = WRONG_SYMBOLS;
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
        if (check_result == TOK_NUM) {
            push(output_stack);
            parse_double(&array_pos, expression, output_stack);
        } else if ((check_result == TOK_OPERATOR_1) || (check_result == TOK_OPERATOR_2) \
                   || (check_result == TOK_POW) || (check_result == TOK_OPEN_BRACE)) {
            handle_operator(expression[array_pos], output_stack, queue_stack, check_result);
            array_pos++;
        } else if (check_result == TOK_CLOSE_BRACE) {
            array_pos++;
            node *last = find_last(queue_stack);
            while (last->type != TOK_OPEN_BRACE) {
                push_n_pop(output_stack, queue_stack);
                last = find_last(queue_stack);
                if (last->number == 0) {
                    ex_code = EXTRA_CLOSE_BRACE;
                    printf("BRACE ERROR\n");
                    array_pos = input_len;
                    last->type = TOK_OPEN_BRACE;
                }
            }
            if (last->type == TOK_OPEN_BRACE) {
                pop(queue_stack);
            }
        } else if (check_result == TOK_UNARY) {
            int type_unary = parse_long_operator(expression, &array_pos);
            if (type_unary == CODE_MOD) {
                handle_operator(type_unary, output_stack, queue_stack, TOK_OPERATOR_2);
            } else if (type_unary >= CODE_ACOS && type_unary <= CODE_LN) {
                handle_operator(type_unary, output_stack, queue_stack, TOK_UNARY);
            } else {
                ex_code = WRONG_LONG_OPERATOR;
                printf("LONG OPERATOR ERROR\n");
                array_pos = input_len;
            }
        } else {
            array_pos = input_len;
            ex_code = check_result;
        }
    }
    int check_queue = find_last(queue_stack)->number;
    while (check_queue > 0) {
        push_n_pop(output_stack, queue_stack);
        check_queue = find_last(queue_stack)->number;
    }

    clean(queue_stack);
    return ex_code;
}
