//
//  parser.h
//  C7_SmartCalc
//
//  Created by Joramun Sasin on 8/25/22.
//

#ifndef parser_h
#define parser_h

#include <stdio.h>
#include <string.h>
#include "nodes.h"

#define EXPRESSION_SIZE 100
#define ISDIGIT check_input_type(expression[*array_pos]) == TOK_NUM
#define ISDOT check_input_type(expression[*array_pos]) == TOK_DOT

// POW 7? what about braces?

enum parser_errors {
    TOO_LONG_EXPRESSION = 100,
    WRONG_LONG_OPERATOR = 101,
    EXPRESSION_TOO_SHORT,
    EXTRA_DOT_ERROR,
    BRACE_NOT_PAIRED,
};

enum input_type {
    EMPTY = 0,
    TOK_NUM = 1,
    TOK_DOT = 2,
    TOK_OPERATOR_1 = 3,
    TOK_OPERATOR_2 = 4,
    TOK_POW = 5,
    TOK_UNARY = 6,
    TOK_OPEN_BRACE = 7,
    TOK_CLOSE_BRACE = 8,
};

//  From 'A' to 'I'
#define CODE_MOD 37
enum parse_long_operators {
    CODE_ACOS = 65,
    CODE_ASIN = 66,
    CODE_ATAN = 67,
    CODE_SQRT = 68,
    CODE_SIN = 69,
    CODE_COS = 70,
    CODE_TAN = 71,
    CODE_LOG = 72,
    CODE_LN = 73
};

int validate_input(char *expression);
void parse_input(char *expression, node *output_stack);
int check_input_type(char input);
void parse_double(int *array_pos, char *expression, node *output_stack);
void handle_operator(char operator, node *output_stack, node *queue_stack, int input_type);
int parse_long_operator(char *expression, int *array_pos);
void hello9(void);

#endif /* parser_h */
