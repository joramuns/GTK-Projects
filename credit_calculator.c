//
//  credit_calculator.c
//  C7_SmartCalc
//
//  Created by Joramun Sasin on 9/3/22.
//

#include "credit_calculator.h"

int eval_annuity_credit(credit_input input) {
    int ex_code = 0;
    double monthly_rate = input.rate / 12;
    double capitalize_rate = powf((1 + monthly_rate), input.term);

    double payment = input.sum * ((monthly_rate * capitalize_rate) / (capitalize_rate - 1));
    double total_sum = payment * input.term;
    double overpaid = total_sum - input.sum;
    printf("Payment = %.2f\nTotal sum = %.2f\nOverpaid = %.2f\n", payment, total_sum, overpaid);

    return ex_code;
}

int eval_differentiated_credit(credit_input input) {
    int ex_code = 0;

    double debit_payment = input.sum / input.term;
    double monthly_payment = 0;
    double monthly_rate = input.rate / 12;
    double total_payment = 0;
    double overpaid = input.sum;

    while (input.term-- > 0) {
        monthly_payment = input.sum * monthly_rate + debit_payment;
        input.sum -= debit_payment;
        printf("Month %d payment: %.2f\n", input.term, monthly_payment);
        total_payment += monthly_payment;
    }
    overpaid = total_payment - overpaid;
    printf("Total paid: %.2f\nOverpaid: %.2f\n", total_payment, overpaid);

    return ex_code;
}
