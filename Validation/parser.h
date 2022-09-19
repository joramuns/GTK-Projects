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
#define EXPRESSION_SYMBOLS "1234567890acdgilmnoqrst()+-*/^. X"
#define EXPRESSION_SYMBOLS_NUMBERS "1234567890."
#define ISDIGIT check_input_type(expression[*array_pos]) == TOK_NUM
#define ISDOT check_input_type(expression[*array_pos]) == TOK_DOT

enum parser_errors {
    TOO_LONG_EXPRESSION = 100,
    WRONG_LONG_OPERATOR = 101,
    EXPRESSION_TOO_SHORT = 102,
    WRONG_SYMBOLS = 103,
    EXTRA_DOT_ERROR = 104,
    BRACE_NUMBER = 105,
    LONG_OPERATOR_BRACE_ERROR = 106,
    EMPTY_BRACES = 107,
    EXTRA_SIGNS = 108,
    VARIABLE_INSIDE = 109,
    SURROUNDING_VARIABLE = 110,
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
int validate_input_numbers(char *expression);
int validate_extra_dot(char *expression);
int parse_input(char *expression, node *output_stack);
int check_input_type(char input);
int parse_double(size_t *array_pos, char *expression, node *output_stack);
void handle_operator(char operator_tok, node *output_stack, node *queue_stack, int input_type);
int parse_long_operator(char *expression, size_t *array_pos);
int validate_stack(node *output_stack);
void handle_unary(const char *expression, size_t array_pos, node *output_stack);
int handle_close_brace(node *output_stack, node *queue_stack);
void clean_queue_stack(node *output_stack, node *queue_stack);
int check_variable(char *expression);

#endif /* parser_h */
