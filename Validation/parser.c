//
//  parser.c
//  C7_SmartCalc
//
//  Created by Joramun Sasin on 8/25/22.
//

#include "parser.h"

void parse_input(char *expression, node *output_stack) {
    int array_pos = 0;
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
                    printf("BRACE ERROR\n");
                    break;
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
                printf("LONG OPERATOR ERROR\n");
                break;
            }
        } else {
            array_pos++;
        }
    }
    int check_queue = find_last(queue_stack)->number;
    while (check_queue > 0) {
        push_n_pop(output_stack, queue_stack);
        check_queue = find_last(queue_stack)->number;
    }

    clean(queue_stack);
}
