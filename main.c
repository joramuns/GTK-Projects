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
    credit_output test = {0};

    handle_credit_calculator(test_case, &test);

    printf("Total paid: %lf\nOverpaid: %lf\n", test.total_sum, test.overpaid);
    node *head = test.stack_of_payments;
    while (find_last(head)->number != 0) {
        printf("Monthly payment: %lf\n", find_last(head)->value);
        pop(head);
    }
    free(test.stack_of_payments);

    return ex_code;
}
