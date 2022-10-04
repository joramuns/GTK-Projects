#include "deposit_calculator.h"

void handle_deposit_calc(deposit_input cont, deposit_output *cont_output) {
  cont.rate /= 100.0;
  cont_output->stack_of_payouts = init_node();
  double temp_deposit = cont.deposit;
  for (unsigned term_count = 1; term_count <= cont.term; term_count++) {
    cont.deposit += cont.account_movement[term_count - 1];
    temp_deposit += cont.account_movement[term_count - 1];
    cont.daily_income = (cont.deposit * cont.rate) / YEARDAYS;
    cont.payout += cont.daily_income;
    if ((term_count % cont.freq_payment) == 0) {
      cont.payout = bank_rounding(cont.payout);
      cont.total_profit += cont.payout;
      if (cont.capitalization) {
        cont.deposit += cont.payout;
        cont.payout = 0;
      } else {
        push(cont_output->stack_of_payouts);
        find_last(cont_output->stack_of_payouts)->value = cont.payout;
        cont.payout = 0;
      }
    }
  }
  if (cont.payout > 0) {
    if (cont.capitalization) {
      cont.deposit += cont.payout;
      cont.total_profit = cont.deposit - temp_deposit;
    } else {
      cont.total_profit += cont.payout;
    }
  }
  cont_output->total_profit = bank_rounding(cont.total_profit);
  cont_output->deposit = cont.deposit;
}
