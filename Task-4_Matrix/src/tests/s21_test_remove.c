#include "s21_test_matrix.h"

START_TEST(s21_remove_matrix_0) {
  matrix_t A = {};
  s21_create_matrix(10, 10, &A);
  s21_remove_matrix(&A);
  ck_assert_ptr_null(A.matrix);
}
END_TEST

START_TEST(s21_remove_matrix_1) {
  s21_remove_matrix(NULL);
  ck_assert_int_eq(1, 1);
}
END_TEST

START_TEST(s21_remove_matrix_2) {
  matrix_t A = {};
  s21_remove_matrix(&A);
  ck_assert_int_eq(1, 1);
}
END_TEST

START_TEST(s21_remove_matrix_3) {
  matrix_t A = {};
  s21_create_matrix(10, 10, &A);
  A.rows = -1;
  A.columns = -1;
  s21_remove_matrix(&A);
  A.rows = 10;
  A.columns = 10;
  s21_remove_matrix(&A);
  ck_assert_ptr_null(A.matrix);
}
END_TEST

Suite *s21_test_remove(void) {
  Suite *s = suite_create("s21_remove_matrix tests");
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, s21_remove_matrix_0);
  tcase_add_test(tc_core, s21_remove_matrix_1);
  tcase_add_test(tc_core, s21_remove_matrix_2);
  tcase_add_test(tc_core, s21_remove_matrix_3);
  suite_add_tcase(s, tc_core);
  return s;
}