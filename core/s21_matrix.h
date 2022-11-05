//
//  s21_matrix.h
//  s21_matrix
//
//  Created by Joramun Sasin on 8/16/22.
//

#ifndef SRC_S21_MATRIX_H_
#define SRC_S21_MATRIX_H_

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define TOLERANCE 1e-07
#define EVERY_ROW for (int i_row = 0; i_row < A->rows; i_row++) {
#define EVERY_COLUMN for (int i_column = 0; i_column < A->columns; i_column++) {
enum Comparison {
    FAILURE = 0,
    SUCCESS = 1
};

enum Exit_Code {
    OK = 0,
    M_ERROR = 1,        // Incorrect matrix
    C_ERROR = 2         // Calculation error
};

typedef struct matrix_struct {
    double** matrix;
    int rows;
    int columns;
} matrix_t;

/*                      Main matrix engine                                      */
int     s21_create_matrix(int rows, int columns, matrix_t *result);
void    s21_remove_matrix(matrix_t *A);

/*                      Simple mathematics                                      */
int     s21_eq_matrix(matrix_t *A, matrix_t *B);
int     s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int     s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int     s21_mult_number(matrix_t *A, double number, matrix_t *result);

/*                  Specific matrix mathematics                                 */
int     s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int     s21_transpose(matrix_t *A, matrix_t *result);
int     s21_calc_complements(matrix_t *A, matrix_t *result);
int     s21_determinant(matrix_t *A, double *result);
int     s21_inverse_matrix(matrix_t *A, matrix_t *result);

/*                Additional supportive functions                               */
int     s21_check_matrix(matrix_t A);
int     s21_compare_matrix_sizes(matrix_t A, matrix_t B);
void    s21_determinant_cofactor\
        (matrix_t *A, matrix_t *temp_matrix, int cross_row, int cross_column, int depth);

#endif  // SRC_S21_MATRIX_H_
