#include "s21_test_matrix.h"

START_TEST(s21_inverse_0) {
  matrix_t A = {};
  matrix_t result = {};
  ck_assert_int_eq(s21_inverse_matrix(&A, &result), INCORRECT_MATRIX);
}
END_TEST

START_TEST(s21_inverse_1) {
  matrix_t A = {};
  matrix_t result = {};
  s21_create_matrix(3, 3, &A);
  init_matrix(&A, 1, 1);
  ck_assert_int_eq(s21_inverse_matrix(&A, &result), CALC_ERROR);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_inverse_2) {
  matrix_t A = {};
  matrix_t result = {};
  s21_create_matrix(5, 3, &A);
  init_matrix(&A, 1, 1);
  ck_assert_int_eq(s21_inverse_matrix(&A, &result), CALC_ERROR);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_inverse_3) {
  matrix_t A = {};
  matrix_t result = {};
  matrix_t eq_matrix = {};
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &eq_matrix);
  A.matrix[0][0] = 10;
  eq_matrix.matrix[0][0] = 1.0 / 10.0;
  ck_assert_int_eq(s21_inverse_matrix(&A, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &eq_matrix), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&eq_matrix);
}
END_TEST

START_TEST(s21_inverse_4) {
  matrix_t A = {};
  matrix_t result = {};
  matrix_t eq_matrix = {};
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &eq_matrix);
  A.matrix[0][0] = 2, A.matrix[0][1] = 5, A.matrix[0][2] = 7;
  A.matrix[1][0] = 6, A.matrix[1][1] = 3, A.matrix[1][2] = 4;
  A.matrix[2][0] = 5, A.matrix[2][1] = -2, A.matrix[2][2] = -3;
  eq_matrix.matrix[0][0] = 1, eq_matrix.matrix[0][1] = -1,
  eq_matrix.matrix[0][2] = 1;
  eq_matrix.matrix[1][0] = -38, eq_matrix.matrix[1][1] = 41,
  eq_matrix.matrix[1][2] = -34;
  eq_matrix.matrix[2][0] = 27, eq_matrix.matrix[2][1] = -29,
  eq_matrix.matrix[2][2] = 24;
  ck_assert_int_eq(s21_inverse_matrix(&A, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &eq_matrix), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&eq_matrix);
}
END_TEST

START_TEST(s21_inverse_5) {
  matrix_t A = {};
  s21_create_matrix(3, 3, &A);
  init_matrix(&A, 1, 1);
  ck_assert_int_eq(s21_inverse_matrix(&A, NULL), INCORRECT_MATRIX);
  s21_remove_matrix(&A);
}
END_TEST

Suite *s21_test_inverse(void) {
  Suite *s = suite_create("s21_inverse_matrix tests");
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, s21_inverse_0);
  tcase_add_test(tc_core, s21_inverse_1);
  tcase_add_test(tc_core, s21_inverse_2);
  tcase_add_test(tc_core, s21_inverse_3);
  tcase_add_test(tc_core, s21_inverse_4);
  tcase_add_test(tc_core, s21_inverse_5);
  suite_add_tcase(s, tc_core);
  return s;
}