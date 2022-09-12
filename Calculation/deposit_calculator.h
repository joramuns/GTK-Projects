//
//  deposit_calculator.h
//  C7_SmartCalc
//
//  Created by Joramun Sasin on 9/8/22.
//

#ifndef deposit_calculator_h
#define deposit_calculator_h

#include <stdio.h>
#include <math.h>

#define YEARDAYS 365

enum frequency_payment {
    DAILY = 1,
    WEEKLY = 7,
    MONTHLY = 30, 
    QUARTERLY = 90,
    YEARLY = 365,
};

typedef struct deposit_input {
    double deposit;
    double rate;
    double payout;
    unsigned term;
    unsigned freq_payment;
    unsigned capitalization;
    double daily_income;
    double total_profit;
} deposit_input;

int handle_deposit_calc(deposit_input cont);

#endif /* deposit_calculator_h */
