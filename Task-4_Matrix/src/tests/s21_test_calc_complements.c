#include "s21_test_matrix.h"

START_TEST(s21_complements_0) {
  matrix_t A = {0};
  s21_create_matrix(3, 3, &A);
  ck_assert_int_eq(s21_calc_complements(&A, NULL), INCORRECT_MATRIX);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_complements_1) {
  matrix_t A = {0};
  matrix_t result = {0};
  s21_create_matrix(1, 3, &A);
  init_matrix(&A, 1, 3);
  ck_assert_int_eq(s21_calc_complements(&A, &result), CALC_ERROR);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_complements_2) {
  matrix_t A = {0};
  s21_create_matrix(3, 3, &A);
  init_matrix(&A, 1, 3);
  ck_assert_int_eq(s21_calc_complements(&A, NULL), INCORRECT_MATRIX);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_complements_3) {
  ck_assert_int_eq(s21_calc_complements(NULL, NULL), INCORRECT_MATRIX);
}
END_TEST

START_TEST(s21_complements_4) {
  matrix_t result = {0};
  ck_assert_int_eq(s21_calc_complements(NULL, &result), INCORRECT_MATRIX);
}
END_TEST

START_TEST(s21_complements_5) {
  // success with task reference values
  matrix_t A = {0};
  matrix_t result = {};
  matrix_t eq_matrix = {};
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &eq_matrix);
  A.matrix[0][0] = 1, A.matrix[0][1] = 2, A.matrix[0][2] = 3;
  A.matrix[1][0] = 0, A.matrix[1][1] = 4, A.matrix[1][2] = 2;
  A.matrix[2][0] = 5, A.matrix[2][1] = 2, A.matrix[2][2] = 1;
  ck_assert_int_eq(s21_calc_complements(&A, &result), OK);
  eq_matrix.matrix[0][0] = 0, eq_matrix.matrix[0][1] = 10,
  eq_matrix.matrix[0][2] = -20;
  eq_matrix.matrix[1][0] = 4, eq_matrix.matrix[1][1] = -14,
  eq_matrix.matrix[1][2] = 8;
  eq_matrix.matrix[2][0] = -8, eq_matrix.matrix[2][1] = -2,
  eq_matrix.matrix[2][2] = 4;
  ck_assert_int_eq(s21_eq_matrix(&result, &eq_matrix), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&eq_matrix);
}
END_TEST

Suite *s21_test_complements(void) {
  Suite *s = suite_create("s21_calc_complements tests");
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, s21_complements_0);
  tcase_add_test(tc_core, s21_complements_1);
  tcase_add_test(tc_core, s21_complements_2);
  tcase_add_test(tc_core, s21_complements_3);
  tcase_add_test(tc_core, s21_complements_4);
  tcase_add_test(tc_core, s21_complements_5);
  suite_add_tcase(s, tc_core);
  return s;
}