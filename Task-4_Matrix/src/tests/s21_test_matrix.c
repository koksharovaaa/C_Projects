#include "s21_test_matrix.h"

void run_case(Suite(*test_case)) {
  SRunner *sr = srunner_create(test_case);
  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);
  srunner_free(sr);
}

void run_tests() {
  Suite *suite_cases[] = {
      s21_test_create(),      s21_test_remove(),    s21_test_eq(),
      s21_test_sum(),         s21_test_sub(),       s21_test_mult_num(),
      s21_test_mult_mat(),    s21_test_transpose(), s21_test_determinant(),
      s21_test_complements(), s21_test_inverse(),   NULL};

  for (Suite **test_case = suite_cases; *test_case != NULL; test_case++)
    run_case(*test_case);
}

int main() {
  run_tests();
  return 0;
}