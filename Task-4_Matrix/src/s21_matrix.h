#ifndef S21_MATRIX_H
#define S21_MATRIX_H

#include <math.h>
#include <stdlib.h>

#define OK 0
#define INCORRECT_MATRIX 1
#define CALC_ERROR 2

#define SUCCESS 1      // comparison equal
#define FAILURE 0      // comparison not equal
#define EQ_LIMIT 1e-7  // comparison limit

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

// Main functions
int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);

int s21_eq_matrix(matrix_t *A, matrix_t *B);
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

int s21_transpose(matrix_t *A, matrix_t *result);
int s21_determinant(matrix_t *A, double *result);
int s21_calc_complements(matrix_t *A, matrix_t *result);
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

// Secondary functions
void copy_matrix(const matrix_t *A, matrix_t *B);
int is_matrix_valid(const matrix_t *A);
int mult_num(const matrix_t *A, double number, matrix_t *result);
int mult_mat(const matrix_t *A, const matrix_t *B, matrix_t *result);
void transpose(const matrix_t *A, matrix_t *result);
double gauss(matrix_t *A);
void alg_complements(const matrix_t *A, matrix_t *result);

#endif
