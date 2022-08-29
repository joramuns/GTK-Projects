//
//  main0.c
//  C7_SmartCalc
//
//  Created by Joramun Sasin on 8/25/22.
//

#include <stdio.h>
#include <string.h>
#include "calculator.h"

int main() {
    int ex_code = 0;
    char expression[EXPRESSION_SIZE + 1 + 1] = {0};
    fgets(expression, EXPRESSION_SIZE + 1 + 1, stdin);
    double result = 0;

    ex_code = calculate(expression, &result);

    printf("Answer: %lf\n", result);

    return ex_code;
}
