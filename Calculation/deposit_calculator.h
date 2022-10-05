//
//  deposit_calculator.h
//  C7_SmartCalc
//
//  Created by Joramun Sasin on 9/8/22.
//

#ifndef deposit_calculator_h
#define deposit_calculator_h

#include <math.h>
#include <stdio.h>

#include "../Validation/nodes.h"
#include "../Validation/parser.h"
#include "bank_rounding.h"

#define YEARDAYS 365

/**
 * @brief The enumeration of frequency payments for deposit
 */
enum frequency_payment {
  DAILY = 1,      /**< Payout every day */
  WEEKLY = 7,     /**< Payout every month */
  MONTHLY = 30,   /**< Payout every month */
  QUARTERLY = 90, /**< Payout every quarter */
  YEARLY = 365,   /**< Payout every year */
};

/**
 * @brief A structure to store data from GUI before evaluation
 */
typedef struct deposit_input {
  double deposit; /**< Amount of money to deposit */
  double rate;    /**< Interest rate of deposit, in percents */
  double payout;  /**< Amount of interest paid at the moment */
  unsigned
      term; /**< Amount of days to be deposited, different types of input as
               monthes, quarters or years evaluates the number of days */
  unsigned freq_payment;   /**< Frequency of payment, uses enum as argument */
  unsigned capitalization; /**< Selected type of deposit: 0 - without
                              capitalization, 1 - with capitalization */
  double daily_income;     /**< Daily profit */
  double
      total_profit; /**< Total amount of money earned by the end of contract*/
  double *account_movement; /**< An array from GUI that may store a positive or
                               negative value depends on type of operation -
                               withdrawal or replenishment */
} deposit_input;

/**
 * @brief A structure to generate after evaluation of deposit conditions
 */
typedef struct deposit_output {
  double
      total_profit; /**< Total amount of money earned by the end of contract */
  double deposit;   /**< Final amount of money in account after all payouts and
                       withdrawals */
  node *stack_of_payouts; /**< Stores a node list with periodical payouts by
                             deposit, needs to be freed*/
} deposit_output;

/**
 * @brief A function to calculate needed data on loan conditions for ANNUITY
 * credit
 *
 * @param cont Input data from GUI
 * @param cont_output Final values after all payouts and withdrawals
 *
 * @return Error code
 */
int handle_deposit_calc(deposit_input cont, deposit_output *cont_output);

#endif /* deposit_calculator_h */
