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

#define EXPRESSION_SIZE 255
#define EXPRESSION_SYMBOLS "1234567890acdgilmnoqrst()+-*/^. X"
#define EXPRESSION_SYMBOLS_NUMBERS "1234567890."
#define ISDIGIT check_input_type(expression[*array_pos]) == TOK_NUM
#define ISDOT check_input_type(expression[*array_pos]) == TOK_DOT

/**
 * @brief The enumeration of errors in expression parsing
 */
enum parser_errors {
  TOO_LONG_EXPRESSION =
      100, /**< Expression exceeds defined max number of symbols */
  WRONG_LONG_OPERATOR = 101,  /**< Mistake in arithmetical operator */
  EXPRESSION_TOO_SHORT = 102, /**< Expression lacks some arguments */
  WRONG_SYMBOLS = 103,        /**< Wrong spelling of operator */
  EXTRA_DOT_ERROR = 104,      /**< Explicit dot in number input */
  BRACE_NUMBER = 105,         /**< Lack of opening or closing brace */
  LONG_OPERATOR_BRACE_ERROR =
      106,               /**< Arithmetical operator mistake with braces */
  EMPTY_BRACES = 107,    /**< Empty braces error */
  EXTRA_SIGNS = 108,     /**< Explicit operator in expression */
  VARIABLE_INSIDE = 109, /**< A variable found in expression */
  SURROUNDING_VARIABLE =
      110, /**< A variable surrounded with wrong members of stack */
};

/**
 * @brief The enumeration of stack member types
 */
enum input_type {
  EMPTY = 0,          /**< Empty type */
  TOK_NUM = 1,        /**< Number member */
  TOK_DOT = 2,        /**< Dot for number */
  TOK_OPERATOR_1 = 3, /**< Operator of first priority - plus or minus */
  TOK_OPERATOR_2 = 4, /**< Operator of second priority - divide or multiply */
  TOK_POW = 5,        /**< Power operator */
  TOK_UNARY =
      6, /**< Unary operator - minus, plus or long mathematical expression */
  TOK_OPEN_BRACE = 7,  /**< Open brace */
  TOK_CLOSE_BRACE = 8, /**< Close brace */
};

//  Code for MOD
#define CODE_MOD 37
/**
 * @brief The enumeration of mathematical operators, uses char code from A to I
 */
enum parse_long_operators {
  CODE_ACOS = 65, /**< Acos */
  CODE_ASIN = 66, /**< Asin */
  CODE_ATAN = 67, /**< Atan */
  CODE_SQRT = 68, /**< Square */
  CODE_SIN = 69,  /**< Sin */
  CODE_COS = 70,  /**< Cos */
  CODE_TAN = 71,  /**< Tan */
  CODE_LOG = 72,  /**< Ten-based logarithm */
  CODE_LN = 73    /**< Natural logarithm */
};

/**
 * @brief A function to validate expression
 *
 * @param expression Array of chars from GUI with expression
 *
 * @return Error code, parser_error enum or 0 if everything is OK
 */
int validate_input(char *expression);
/**
 * @brief A function to validate expression for deposit or credit calculator,
 * where no variables are possible
 *
 * @param expression Array of chars from GUI with expression
 *
 * @return Error code, parser_error enum or 0 if everything is OK
 */
int validate_input_numbers(char *expression);
/**
 * @brief A function to search for extra dot in expression
 *
 * @param expression Array of chars from GUI with expression
 *
 * @return Error code, parser_error enum or 0 if everything is OK
 */
int validate_extra_dot(char *expression);
/**
 * @brief A function to parse the array of chars with expression to linked list
 * stack
 *
 * @param expression Array of chars from GUI with expression
 * @param output_stack A pointer to head of linked list stack with expression in
 * reverse polish notation
 *
 * @return Error code, parser_error enum or 0 if everything is OK
 */
int parse_input(char *expression, node *output_stack);
/**
 * @brief A function to check type of operator
 *
 * @param input A char from operator
 *
 * @return Type code of operator from input_type enum
 */
int check_input_type(char input);
/**
 * @brief A function to parse value from string representation to double
 *
 * @param array_pos A pointer to counter for position in array
 * @param expression Array of chars from GUI with expression
 * @param output_stack A pointer to head of linked list stack with expression in
 * reverse polish notation
 *
 * @return Error code from parse_errors enum
 */
int parse_double(size_t *array_pos, char *expression, node *output_stack);
/**
 * @brief A function to handle operator between queue stack and output stack
 * depending on its priority
 *
 * @param operator_tok Char that indicates which operator to put in linked list
 * stack
 * @param output_stack A pointer to head of linked list stack with expression in
 * reverse polish notation
 * @param queue_stack A pointer to head of linked list stack with queue of
 * operators
 * @param input_type Type code of operator from input_type enum
 */
void handle_operator(char operator_tok, node *output_stack, node *queue_stack,
                     int input_type);
/**
 * @brief A function to parse long mathematical operator (sin, cos, tan, etc.)
 *
 * @param expression Array of chars from GUI with expression
 * @param array_pos A pointer to counter for position in array
 *
 * @return Error code from parse_errors enum
 */
int parse_long_operator(char *expression, size_t *array_pos);
/**
 * @brief A function to validate final stack in reverse polish notation, counts
 * the quantity of operators and operands
 *
 * @param output_stack A pointer to head of linked list stack with expression in
 * reverse polish notation
 *
 * @return Error code, parser_error enum or 0 if everything is OK
 */
int validate_stack(node *output_stack);
/**
 * @brief A function to handle unary plus or minus
 *
 * @param expression Array of chars from GUI with expression
 * @param array_pos A pointer to counter for position in array
 * @param output_stack A pointer to head of linked list stack with expression in
 * reverse polish notation
 */
void handle_unary(const char *expression, size_t array_pos, node *output_stack);
/**
 * @brief A function to handle close brace and check for errors
 *
 * @param output_stack A pointer to head of linked list stack with expression in
 * reverse polish notation
 * @param queue_stack A pointer to head of linked list stack with queue of
 * operators
 *
 * @return Error code, parser_error enum or 0 if everything is OK
 */
int handle_close_brace(node *output_stack, node *queue_stack);
/**
 * @brief Destroy linked list stack with queue of operators
 *
 * @param output_stack A pointer to head of linked list stack with expression in
 * reverse polish notation
 * @param queue_stack A pointer to head of linked list stack with queue of
 * operators
 */
void clean_queue_stack(node *output_stack, node *queue_stack);
/**
 * @brief A function to check for errors expression with variable inside
 *
 * @param expression Array of chars from GUI with expression
 *
 * @return Error code, parser_error enum or 0 if everything is OK
 */
int check_variable(char *expression);
/**
 * @brief A function to remove spaces from expression given in GUI
 *
 * @param string Array of chars from GUI with expression
 *
 * @return New array of chars without spaces, needs to be freed
 */
char *remove_spaces(char *string);

#endif /* parser_h */
