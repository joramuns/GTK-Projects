//
//  main.h
//  C7_SmartCalc
//
//  Created by Joramun Sasin on 8/29/22.
//

#ifndef main_h
#define main_h

#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>

#include "Calculation/calculator.h"
#include "Calculation/credit_calculator.h"
#include "Calculation/deposit_calculator.h"

extern double x_min; /*!< Global variable for graph: X minimum */
extern double x_max; /*!< Global variable for graph: X maximum */
extern double y_min; /*!< Global variable for graph: Y minimum */
extern double y_max; /*!< Global variable for graph: Y maximum */

/*! \mainpage S21 smart calculator v1.0
 * \section intro_sec Introduction
 *
 * S21 smart calculator v1.0
 * <br>A command-line program with GUI.
 *
 * \section Functionality
 *
 * \subsection A Calculator
 *
 * \subsubsection AA Evaluating simple mathematics
 *
 * Enter mathematical expression with keyboard or with the help of GUI buttons.
 * <br>Click "=" and get the result!
 *
 * \subsubsection AB Draw graphs
 *
 * Enter the same expression with a variable "X" in it.
 * <br>Click "=" and get the graph!
 *
 * Enter codominance and dominance to see specific part of graph.
 * <br>Be careful to respect the ratio!
 *
 * \subsubsection AC Evaluate functions
 *
 * Enter again expression with a variable "X" in it,  untoggle "Graph" button
 * and enter value to replace. <br>Click "=" and get the result with entered
 * value!
 *
 * \subsection B Credit calculator
 *
 * \subsubsection BA 2 types of credit
 *
 * Annuity - with equal payments during the term of credit. Percents first, main
 * debt last. <br>Differentiated - different amount of payment from time to time
 * due to decreasing main debt and percents on it.
 *
 * \subsubsection BB Show costs
 *
 * Enter sum, term and rate of credit and get full information about payments
 * and costs of credit.
 *
 * \subsection C Deposit calculator
 *
 * \subsubsection CA Capitalization of revenue
 *
 * Toggle button Capitalization to see the benefit.
 *
 * \subsubsection CB Show costs
 *
 * Enter tax rate to see the cost that you have to pay as resident.
 *
 * \subsubsection CC Replenish or withdraw
 *
 * Add account movement operations by the day of deposit to see the change of
 * income. <br>Enter positive number to replenish or negative number to
 * withdraw.
 *
 * \subsubsection CD Variety of payout options
 *
 * Choose whether to receive payouts daily or monthly or quarterly or yearly.
 *
 * \section install_sec Installation
 *
 * \subsection step1 Step 1: Install GTK4 with all dependencies
 *
 * Install GTK4 by "brew install gtk4" on macos or "apt-get install libgtk4-dev"
 * on other unix systems.
 *
 * \subsubsection step11 System requirements:
 *
 * Fedora 36
 * <br>Ubuntu 22.04+
 * <br>Debian bookworm+
 *
 * \subsection step2 Step 2: Enter "make install" in command line
 *
 * \subsection step3 Step 3: Run /s21_smart_calc_1_0/s21_smart_calc
 * etc...
 */

/**
 * @brief Main GUI structure to store pointers to widgets
 */
typedef struct {
  GtkButton *button;   /**< Array of pointers for buttons in main window */
  GtkEntry *entry;     /**< Pointer to entry text field */
  GtkEntry *entry_res; /**< Pointer to resut text field */
  char *value;         /**< String description and title for button */
  char *name;          /**< Name id for button to call it from GTK Builder */
  GtkEntry *x_min;     /**< Input of main graph variables: X minimum */
  GtkEntry *x_max;     /**< Input of main graph variables: X maximum */
  GtkEntry *y_min;     /**< Input of main graph variables: Y minimum */
  GtkEntry *y_max;     /**< Input of main graph variables: Y maximum */
  GtkWidget *area;     /**< Pointer to GTK drawing area */
  GtkToggleButton *toggle_button; /**< Pointer to toggle button Graph */
} buttonData;

/**
 * @brief Common structure for credit and deposit calculator
 */
typedef struct entry_input {
  GtkEntry *sum_entry;  /**< Sum of credit or deposit input */
  GtkEntry *term_entry; /**< Input for deposit or credit term */
  GtkEntry *
      rate_entry; /**< Input of interest rate in deposit or credit calculator */
  GtkEntry *tax_rate_entry;  /**< Input of tax rate in deposit calculator*/
  GtkComboBoxText *term_cbt; /**< Combo text button to choose days or monthes or
                                years, etc.  */
  GtkWidget *type_credit_cbt; /**< Input of choice between differentiated or
                                 annuity credit */
  GtkTextBuffer
      *result_buffer; /**< Pointer to text buffer with results of evaluating */
  GtkComboBoxText *type_payouts; /**< Combo text button to choose frequency of
                                    payouts in deposit calculator*/
  GtkWidget
      *wd_tree_view; /**< Pointer to Gtk Widget tree view for deposit calculator
                        to show withdrawals or replenishments */
  GtkTreeStore *withdrawal_window; /**< Contains structure with replenishments
                                      and withdrawals in deposit calculator */
} entry_input;

/**
 * @brief Withdrawals structure in deposit calculator, adds or removes list
 * items
 */
typedef struct wd_cont {
  GtkWidget
      *wd_tree_view; /**< Pointer to Gtk Widget tree view for deposit calculator
                        to show withdrawals or replenishments */
  GtkTreeStore *withdrawal_window; /**< Contains structure with replenishments
                                      and withdrawals in deposit calculator */
  GtkEntry *entry_withdrawal;      /**< Input text box for amount of money to
                                      withdraw or replenish from deposit,      use
                                      positive or negative numbers */
  GtkEntry *date_withdrawal; /**< Input text box for number of a day during
                                deposit to withdraw*/
} wd_cont;

/**
 * @brief Standart function closing window
 *
 * @param window Pointer to GtkWindow
 */
void quit_window(GtkWindow *window);

/*                          drawing graph */
/**
 * @brief A function draws graph in gtkarea by changing variable and evaluating
 * expression
 *
 * @param cr Cairo drawing pointer
 * @param output Array of chars with mathematical expression
 */
void draw_plot(cairo_t *cr, char *output);
/**
 * @brief A function draws grid in drawing area
 *
 * @param width Width of area
 * @param height Height of area
 * @param cr Cairo drawing pointer
 * @param dx System cairo value
 */
void draw_grid(double width, double height, cairo_t *cr, gdouble dx);
/**
 * @brief A function renders drawing area in window
 *
 * @param area Pointer to GtkDrawingArea
 * @param cr Cairo drawing pointer
 * @param width Width of area adjusted
 * @param height Height of area adjusted
 * @param user_data Pointer with mathematical expression from GUI
 */
void graph_draw(GtkDrawingArea *area, cairo_t *cr, int width, int height,
                gpointer user_data);

/*                          input handling */
/**
 * @brief A function to add clicked buttons values to input text area
 *
 * @param widget Pointer to clicked button
 * @param data Container with all pointers from main window render function
 * (entry_input)
 */
void add_text(const GtkButton *widget, gpointer data);
/**
 * @brief A function to delete symbols in input text area
 *
 * @param widget Pointer to clicked button
 * @param data Container with all pointers from main window render function
 * (entry_input)
 */
void del_text(const GtkButton *widget, gpointer data);
/**
 * @brief A function to get results from input data
 *
 * @param widget Pointer to clicked button
 * @param data Container with all pointers from main window render function
 * (entry_input)
 */
void get_result(const GtkButton *widget, gpointer data);
/**
 * @brief  A function to clear everything from input data
 *
 * @param widget Pointer to clicked button
 * @param data Container with all pointers from main window render function
 * (entry_input)
 */
void set_zero(const GtkButton *widget, gpointer data);

/*                         credit calculator */
/**
 * @brief A function to render credit calculator window
 *
 * (entry_input)
 */
void credit_calc_window();
/**
 * @brief A function to render deposit calculator window
 *
 */
void deposit_calc_window();

#endif /* main-gtk_h */
