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
        if (check_result == TOK_NUM) {
            push(output_stack);
            parse_double(&array_pos, expression, output_stack);
        } else if ((check_result == TOK_OPERATOR_1) || (check_result == TOK_OPERATOR_2) || (check_result == TOK_OPEN_BRACE)) {
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
        } else {
            array_pos++;
        }
    }
    int check_queue = find_last(queue_stack)->number;
    while (check_queue > 0) {
        push_n_pop(output_stack, queue_stack);
        check_queue = find_last(queue_stack)->number;
    }
    printf("Output stack:\n");
    print_node(output_stack);
    printf("Queue stack:\n");
    print_node(queue_stack);
    

    clean(output_stack);
    clean(queue_stack);

    return 0;
}
