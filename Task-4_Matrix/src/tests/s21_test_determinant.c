#include "s21_test_matrix.h"

START_TEST(s21_determinant_0) {
  matrix_t A = {};
  double determinant = 0.0f;
  ck_assert_int_eq(s21_determinant(&A, &determinant), INCORRECT_MATRIX);
}
END_TEST

START_TEST(s21_determinant_1) {
  matrix_t A = {};
  double determinant = 0.0f;
  s21_create_matrix(3, 2, &A);
  init_matrix(&A, 1, 1);
  ck_assert_int_eq(s21_determinant(&A, &determinant), CALC_ERROR);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_determinant_2) {
  matrix_t A = {};
  double determinant = 0.0f;
  s21_create_matrix(3, 3, &A);
  init_matrix(&A, 1, 1);
  ck_assert_int_eq(s21_determinant(&A, &determinant), OK);
  ck_assert_double_eq(determinant, 0);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_determinant_3) {
  matrix_t A = {};
  double determinant = 0.0f;
  s21_create_matrix(2, 2, &A);
  init_matrix(&A, 3, 3);
  ck_assert_int_eq(s21_determinant(&A, &determinant), OK);
  ck_assert_double_eq_tol(determinant, -18.0, EQ_LIMIT);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_determinant_4) {
  matrix_t A = {};
  double determinant = 0.0f;
  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 21;
  ck_assert_int_eq(s21_determinant(&A, &determinant), OK);
  ck_assert_double_eq_tol(determinant, 21, EQ_LIMIT);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_determinant_5) {
  matrix_t A = {};
  double determinant = 0.0f;
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 2;
  A.matrix[0][1] = 3;
  A.matrix[1][0] = 2;
  A.matrix[1][1] = 1;
  ck_assert_int_eq(s21_determinant(&A, &determinant), OK);
  ck_assert_double_eq_tol(determinant, -4, EQ_LIMIT);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_determinant_6) {
  matrix_t A = {};
  double determinant = 0.0f;
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 8, A.matrix[0][1] = 0, A.matrix[0][2] = 1;
  A.matrix[1][0] = 3, A.matrix[1][1] = 2, A.matrix[1][2] = 5;
  A.matrix[2][0] = 6, A.matrix[2][1] = 6, A.matrix[2][2] = 2;
  ck_assert_int_eq(s21_determinant(&A, &determinant), OK);
  ck_assert_double_eq_tol(determinant, -202.0, EQ_LIMIT);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_determinant_7) {
  matrix_t A = {};
  double determinant = 0.0f;
  s21_create_matrix(6, 6, &A);
  A.matrix[0][0] = 8, A.matrix[0][1] = 0, A.matrix[0][2] = 1;
  A.matrix[0][3] = 5, A.matrix[0][4] = 6, A.matrix[0][5] = 7;

  A.matrix[1][0] = 3, A.matrix[1][1] = 2, A.matrix[1][2] = 5;
  A.matrix[1][3] = 9, A.matrix[1][4] = 11, A.matrix[1][5] = 33;

  A.matrix[2][0] = 6, A.matrix[2][1] = 6, A.matrix[2][2] = 2;
  A.matrix[2][3] = 13, A.matrix[2][4] = 0, A.matrix[2][5] = 0;

  A.matrix[3][0] = -2, A.matrix[3][1] = 9, A.matrix[3][2] = 34;
  A.matrix[3][3] = 12, A.matrix[3][4] = 5, A.matrix[3][5] = 77;

  A.matrix[4][0] = 3, A.matrix[4][1] = -9, A.matrix[4][2] = 3;
  A.matrix[4][3] = 1, A.matrix[4][4] = -12, A.matrix[4][5] = -6;

  A.matrix[5][0] = 11, A.matrix[5][1] = -10, A.matrix[5][2] = 50;
  A.matrix[5][3] = -1, A.matrix[5][4] = 1, A.matrix[5][5] = 6;

  ck_assert_int_eq(s21_determinant(&A, &determinant), OK);
  ck_assert_double_eq_tol(determinant, 28874572.0, EQ_LIMIT);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_determinant_8) {
  matrix_t A = {};
  double determinant = 0.0f;
  s21_create_matrix(4, 4, &A);
  A.matrix[0][0] = 8, A.matrix[0][1] = 0;
  A.matrix[0][2] = 1, A.matrix[0][3] = 5;

  A.matrix[1][0] = 3, A.matrix[1][1] = 2;
  A.matrix[1][2] = 5, A.matrix[1][3] = 9;

  A.matrix[2][0] = 6, A.matrix[2][1] = 6;
  A.matrix[2][1] = 2, A.matrix[2][3] = 13;

  A.matrix[3][0] = -2, A.matrix[3][1] = 9;
  A.matrix[3][2] = 34, A.matrix[3][3] = 12;

  ck_assert_int_eq(s21_determinant(&A, &determinant), OK);
  ck_assert_double_eq_tol(determinant, 1161, EQ_LIMIT);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_determinant_9) {
  double determinant = 0.0f;
  ck_assert_int_eq(s21_determinant(NULL, &determinant), INCORRECT_MATRIX);
}
END_TEST

Suite *s21_test_determinant(void) {
  Suite *s = suite_create("s21_determinant tests");
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, s21_determinant_0);
  tcase_add_test(tc_core, s21_determinant_1);
  tcase_add_test(tc_core, s21_determinant_2);
  tcase_add_test(tc_core, s21_determinant_3);
  tcase_add_test(tc_core, s21_determinant_4);
  tcase_add_test(tc_core, s21_determinant_5);
  tcase_add_test(tc_core, s21_determinant_6);
  tcase_add_test(tc_core, s21_determinant_7);
  tcase_add_test(tc_core, s21_determinant_8);
  tcase_add_test(tc_core, s21_determinant_9);
  suite_add_tcase(s, tc_core);
  return s;
}