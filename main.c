//
//  main0.c
//  C7_SmartCalc
//
//  Created by Joramun Sasin on 8/25/22.
//

#include <math.h>
#include <stdio.h>
#include <string.h>
#include "Calculation/calculator.h"
#include "Calculation/deposit_calculator.h"

double bank_rounding(double value) {
    return roundf(value * 100) / 100;
}

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
    cont.freq_payment = DAILY;
    cont.capitalization = 0;
    int account_movement[cont.term];
    for (int i = 0; i < cont.term; i++) account_movement[i] = 0;

    /* Careful! Number of day and number of array! */
    account_movement[14] = -15000;
    account_movement[29] = 78787;
    account_movement[99] = -3000;

    double temp_deposit = cont.deposit;
    for (unsigned term_count = 1; term_count <= cont.term; term_count++) {
        cont.deposit += account_movement[term_count - 1];
        temp_deposit += account_movement[term_count - 1];
        cont.daily_income = (cont.deposit * cont.rate) / YEARDAYS;
        cont.payout += bank_rounding(cont.daily_income);
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
