//
//  main0.c
//  C7_SmartCalc
//
//  Created by Joramun Sasin on 8/25/22.
//

#include <stdio.h>
#include <string.h>
#include "calculator.h"
#include "credit_calculator.h"
//Unary minus and plus
//Bracers handling - log(.. has no error
//Exit codes to finish
int main() {
    int ex_code = 0;
//    char expression[EXPRESSION_SIZE + 1 + 1] = {0};
//    fgets(expression, EXPRESSION_SIZE + 1 + 1, stdin);
//    double result = 0;
//
//    ex_code = calculate(expression, &result);
    credit_input test_case = {0};
    test_case.sum = 30000;
    test_case.term = 6;
    test_case.rate = 0.24;
    test_case.type = 1;

    eval_differentiated_credit(test_case);

//    printf("Answer: %lf\n", test_case.sum);

    return ex_code;
}
