//
//  main0.c
//  C7_SmartCalc
//
//  Created by Joramun Sasin on 8/25/22.
//

#include <stdio.h>
#include <string.h>
#include "Calculation/calculator.h"
#include "Calculation/deposit_calculator.h"
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
    deposit_input cont = {0};
    cont.deposit = 300000;
    cont.rate = 0.24;
    cont.term = 179;
    cont.freq_payment = MONTHLY;
    cont.capitalization = 1;

    double temp_deposit = cont.deposit;
    for (unsigned term_count = 1; term_count <= cont.term; term_count++) {
        cont.daily_income = (cont.deposit * cont.rate) / YEARDAYS;
        cont.payout += cont.daily_income;
        if ((term_count % cont.freq_payment) == 0) {
            if (cont.capitalization) {
                cont.deposit += cont.payout;
                cont.payout = 0;
            } else {
                printf("Profit = %.2lf\n", cont.payout);
                cont.total_profit += cont.payout;
                cont.payout = 0;
            }
        }
    }
    if (cont.payout > 0) {
        if (cont.capitalization) {
            cont.deposit += cont.payout;
            cont.payout = 0;
            cont.total_profit = cont.deposit - temp_deposit; 
        } else {
            printf("Profit = %.2lf\n", cont.payout);
            cont.total_profit += cont.payout;
            cont.payout = 0;
        }
    }
    
    printf("Total profit = %.2lf\n", cont.total_profit);
    
    


    return ex_code;
}
