#include "s21_test_matrix.h"

START_TEST(s21_create_matrix_0) {
  matrix_t A = {};
  ck_assert_int_eq(s21_create_matrix(10, 10, &A), OK);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_create_matrix_1) {
  ck_assert_int_eq(s21_create_matrix(10, 10, NULL), INCORRECT_MATRIX);
}
END_TEST

START_TEST(s21_create_matrix_2) {
  matrix_t A = {};
  ck_assert_int_eq(s21_create_matrix(10, 0, &A), INCORRECT_MATRIX);
}
END_TEST

START_TEST(s21_create_matrix_3) {
  matrix_t A = {};
  ck_assert_int_eq(s21_create_matrix(-1, -1, &A), INCORRECT_MATRIX);
}
END_TEST

START_TEST(s21_create_matrix_4) {
  ck_assert_int_eq(s21_create_matrix(-1, 1, NULL), INCORRECT_MATRIX);
}
END_TEST

Suite *s21_test_create(void) {
  Suite *s = suite_create("s21_create_matrix tests");
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, s21_create_matrix_0);
  tcase_add_test(tc_core, s21_create_matrix_1);
  tcase_add_test(tc_core, s21_create_matrix_2);
  tcase_add_test(tc_core, s21_create_matrix_3);
  tcase_add_test(tc_core, s21_create_matrix_4);
  suite_add_tcase(s, tc_core);
  return s;
}
