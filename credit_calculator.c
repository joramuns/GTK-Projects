//
//  credit_calculator.c
//  C7_SmartCalc
//
//  Created by Joramun Sasin on 9/3/22.
//

#include "credit_calculator.h"

void handle_credit_calculator(credit_input input, credit_output *output) {
    input.rate = input.rate / 12;
    if (input.type == 0) {
        eval_annuity_credit(input, output);
    } else if (input.type == 1) {
        eval_differentiated_credit(input, output);
    }
}

int eval_annuity_credit(credit_input input, credit_output *output) {
    int ex_code = 0;
    output->stack_of_payments = init_node();
    double capitalize_rate = powf((1 + input.rate), input.term);

    double payment = input.sum * ((input.rate * capitalize_rate) / (capitalize_rate - 1));
    output->total_sum = payment * input.term;
    output->overpaid = output->total_sum - input.sum;
    while (input.term-- > 0) {
        push(output->stack_of_payments);
        find_last(output->stack_of_payments)->value = payment;
    }

    return ex_code;
}

int eval_differentiated_credit(credit_input input, credit_output *output) {
    int ex_code = 0;
    double debit_payment = input.sum / input.term;
    output->overpaid = input.sum;
    output->stack_of_payments = init_node();

    while (input.term-- > 0) {
        push(output->stack_of_payments);
        find_last(output->stack_of_payments)->value = input.sum * input.rate + debit_payment;
        input.sum -= debit_payment;
        output->total_sum += find_last(output->stack_of_payments)->value;
    }
    output->overpaid = output->total_sum - output->overpaid;

    return ex_code;
}
