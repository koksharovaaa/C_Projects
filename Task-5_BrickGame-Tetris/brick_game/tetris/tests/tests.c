#include "tests.h"

void run_case(Suite(*test_case)) {
  SRunner *sr = srunner_create(test_case);
  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);
  srunner_free(sr);
}

void run_tests() {
  Suite *suite_cases[] = {figure_tests(), mask_tests(), field_tests(),
                          fsm_tests(), NULL};

  for (Suite **test_case = suite_cases; *test_case != NULL; test_case++)
    run_case(*test_case);
}

int main(void) {
  run_tests();
  FILE *file = fopen(TETRIS_SCORES, "w");
  if (file) {
    fprintf(file, "0");
    fclose(file);
    file = NULL;
  }
  return 0;
}