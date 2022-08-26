//
//  main0.c
//  C7_SmartCalc
//
//  Created by Joramun Sasin on 8/25/22.
//

#include <stdio.h>
#include <string.h>
#include <math.h>
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
        } else if ((check_result == TOK_OPERATOR_1) || (check_result == TOK_OPERATOR_2) || (check_result == TOK_POW) || (check_result == TOK_OPEN_BRACE)) {
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

    node *head = output_stack;
    node *stack_number = init_node();
    double operand_1 = 0, operand_2 = 0, result = 0;
    while (head) {
        if (head->type == TOK_NUM) {
            push(stack_number);
            find_last(stack_number)->value = head->value;
            find_last(stack_number)->type = TOK_NUM;
        } else if (head->type != 0){
            operand_2 = find_last(stack_number)->value;
            pop(stack_number);
            operand_1 = find_last(stack_number)->value;
            pop(stack_number);
            if (head->sign == '+') {
                result = operand_1 + operand_2;
            } else if (head->sign == '-') {
                result = operand_1 - operand_2;
            } else if (head->sign == '*') {
                result = operand_1 * operand_2;
            } else if (head->sign == '/') {
                result = operand_1 / operand_2;
            } else if (head->sign == '^') {
                result = powf(operand_1, operand_2);
            }
            push(stack_number);
            find_last(stack_number)->value = result;
            find_last(stack_number)->type = TOK_NUM;
        }
        head = head->next;
    }

    printf("Queue stack:\n");
    print_node(stack_number);

    clean(output_stack);
    clean(queue_stack);
    clean(stack_number);

    return 0;
}
