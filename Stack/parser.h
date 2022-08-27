//
//  parser.h
//  C7_SmartCalc
//
//  Created by Joramun Sasin on 8/25/22.
//

#ifndef parser_h
#define parser_h
#define ISDIGIT check_input_type(expression[*array_pos]) == TOK_NUM
#define ISDOT check_input_type(expression[*array_pos]) == TOK_DOT

// POW 7? what about braces?

enum input_type {
    EMPTY = 0,
    TOK_NUM = 1,
    TOK_DOT = 2,
    TOK_OPERATOR_1 = 3,
    TOK_OPERATOR_2 = 4,
    TOK_POW = 5,
    TOK_OPEN_BRACE = 6,
    TOK_CLOSE_BRACE = 7,
    TOK_UNARY
};

#include <stdio.h>
#include "nodes.h"

int check_input_type(char input);
void parse_double(int *array_pos, char *expression, node *output_stack);
void handle_operator(char operator, node *output_stack, node *queue_stack, int input_type);

#endif /* parser_h */
