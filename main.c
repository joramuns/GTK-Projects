//
//  main0.c
//  C7_SmartCalc
//
//  Created by Joramun Sasin on 8/25/22.
//

#include <stdio.h>
#include <string.h>
#include "Validation/parser.h"
#include "Validation/nodes.h"
#include "Calculation/eval_func.h"
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
    parse_input(expression, output_stack);
    printf("Output stack:\n");
    print_node(output_stack);

    double result = evaluation(output_stack);
    printf("Answer:\n");
    printf("%lf\n", result);

    clean(output_stack);

    return 0;
}
