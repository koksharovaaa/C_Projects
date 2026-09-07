#include "s21_test_matrix.h"

START_TEST(s21_eq_matrix_0) {
  matrix_t A = {};
  matrix_t B = {};
  s21_create_matrix(10, 10, &A);
  s21_create_matrix(10, 10, &B);
  init_matrix(&A, 21, 21);
  init_matrix(&B, 21, 21);
  ck_assert_int_eq(s21_eq_matrix(&A, &B), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_eq_matrix_1) {
  matrix_t A = {};
  matrix_t B = {};
  s21_create_matrix(10, 10, &A);
  s21_create_matrix(10, 10, &B);
  ck_assert_int_eq(s21_eq_matrix(&A, &B), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_eq_matrix_2) {
  matrix_t A = {};
  matrix_t B = {};
  s21_create_matrix(10, 10, &A);
  s21_create_matrix(10, 10, &B);
  init_matrix(&A, 1, 0.00000001);
  init_matrix(&B, 1, 0.000000011);
  ck_assert_int_eq(s21_eq_matrix(&A, &B), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_eq_matrix_3) {
  matrix_t A = {};
  matrix_t B = {};
  s21_create_matrix(10, 10, &A);
  s21_create_matrix(10, 10, &B);
  init_matrix(&A, 1, 0.00000001);
  init_matrix(&B, 1, 0.00000002);
  ck_assert_int_eq(s21_eq_matrix(&A, &B), FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_eq_matrix_4) {
  // failure with different dimensions of matrices
  matrix_t A = {};
  matrix_t B = {};
  s21_create_matrix(5, 5, &A);
  s21_create_matrix(3, 4, &B);
  ck_assert_int_eq(s21_eq_matrix(&A, &B), FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_eq_matrix_5) {
  matrix_t A = {};
  matrix_t B = {};
  s21_create_matrix(5, 5, &A);
  s21_create_matrix(5, 4, &B);
  ck_assert_int_eq(s21_eq_matrix(&A, &B), FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_eq_matrix_6) {
  matrix_t A = {};
  matrix_t B = {};
  s21_create_matrix(5, 5, &A);
  ck_assert_int_eq(s21_eq_matrix(&A, &B), FAILURE);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_eq_matrix_7) {
  matrix_t A = {};
  matrix_t B = {};
  s21_create_matrix(5, 5, &A);
  s21_create_matrix(5, 5, &B);
  init_matrix(&A, 21, 1);
  init_matrix(&B, 42, 1);
  ck_assert_int_eq(s21_eq_matrix(&A, &B), FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_eq_matrix_8) {
  ck_assert_int_eq(s21_eq_matrix(NULL, NULL), FAILURE);
}
END_TEST

START_TEST(s21_eq_matrix_9) {
  matrix_t A = {0};
  matrix_t B = {0};
  ck_assert_int_eq(s21_eq_matrix(&A, &B), FAILURE);
}
END_TEST

START_TEST(s21_eq_matrix_10) {
  matrix_t A = {0};
  s21_create_matrix(5, 5, &A);
  init_matrix(&A, 21, 1);
  ck_assert_int_eq(s21_eq_matrix(&A, NULL), FAILURE);
  s21_remove_matrix(&A);
}
END_TEST

Suite *s21_test_eq(void) {
  Suite *s = suite_create("s21_eq_matrix tests");
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, s21_eq_matrix_0);
  tcase_add_test(tc_core, s21_eq_matrix_1);
  tcase_add_test(tc_core, s21_eq_matrix_2);
  tcase_add_test(tc_core, s21_eq_matrix_3);
  tcase_add_test(tc_core, s21_eq_matrix_4);
  tcase_add_test(tc_core, s21_eq_matrix_5);
  tcase_add_test(tc_core, s21_eq_matrix_6);
  tcase_add_test(tc_core, s21_eq_matrix_7);
  tcase_add_test(tc_core, s21_eq_matrix_8);
  tcase_add_test(tc_core, s21_eq_matrix_9);
  tcase_add_test(tc_core, s21_eq_matrix_10);
  suite_add_tcase(s, tc_core);
  return s;
}