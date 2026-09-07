#ifndef S21_MATRIX_TESTS_H
#define S21_MATRIX_TESTS_H

#include "../s21_matrix.h"
#include <check.h>
#include <stdio.h>

Suite *s21_test_create();
Suite *s21_test_remove();
Suite *s21_test_eq();
Suite *s21_test_sum();
Suite *s21_test_sub();
Suite *s21_test_mult_num();
Suite *s21_test_mult_mat();
Suite *s21_test_transpose();
Suite *s21_test_determinant();
Suite *s21_test_complements();
Suite *s21_test_inverse();

void init_matrix(matrix_t *A, double start, double iteration);

#endif