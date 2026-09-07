#include "tests.h"

START_TEST(init_field_0) {
  TetrisInfo_t G = {0};
  int result = init_field(&G);
  remove_field(&G);
  ck_assert_int_eq(result, GAME_OK);
}
END_TEST

START_TEST(set_values_0) {
  // zero field
  TetrisInfo_t G = {0};
  TetrisInfo_t check = {0};
  init_field(&G);
  set_values(&G);
  G.high_score = 0;

  init_field(&check);
  check.figure = (figure_t){0};
  check.state = tetris_spawn;
  check.line_count = 0;
  check.score = 0;
  check.level = 1;
  check.speed = 10;
  check.pause = PLAY;
  int res_1 = h_parameters_eq(&G, &check);
  int res_2 = h_fields_eq(&G, &check);
  int res_3 = h_check_next(&G);
  remove_field(&G);
  remove_field(&check);
  ck_assert_int_eq(res_1, SUCCESS);
  ck_assert_int_eq(res_2, SUCCESS);
  ck_assert_int_eq(res_3, SUCCESS);
}
END_TEST

START_TEST(set_values_1) {
  // non-zero field
  TetrisInfo_t G = {0};
  TetrisInfo_t check = {0};
  init_field(&G);
  h_fill_field(&G, 1);
  set_values(&G);
  G.high_score = 0;

  init_field(&check);
  h_fill_field(&check, 1);
  memset(&check.figure, 0, sizeof(figure_t));
  check.state = tetris_spawn;
  check.line_count = 0;
  check.score = 0;
  check.level = 1;
  check.speed = 10;
  check.pause = PLAY;

  int res_1 = h_parameters_eq(&G, &check);
  int res_2 = h_fields_eq(&G, &check);
  int res_3 = h_check_next(&G);
  remove_field(&G);
  remove_field(&check);
  ck_assert_int_eq(res_1, SUCCESS);
  ck_assert_int_eq(res_2, SUCCESS);
  ck_assert_int_eq(res_3, SUCCESS);
}
END_TEST

START_TEST(set_values_2) {
  // score_specific
  TetrisInfo_t G = {0};
  init_field(&G);
  set_values(&G);
  G.high_score = 50000000;
  remove_field(&G);
  init_field(&G);
  set_values(&G);
  int res = G.high_score;
  remove_field(&G);
  ck_assert_int_eq(res, 50000000);
}
END_TEST

START_TEST(set_values_3) {
  // garbage
  TetrisInfo_t G = {0};
  init_field(&G);
  FILE *file = fopen(TETRIS_SCORES, "w");
  if (file) {
    fprintf(file, "123aaaaaaa");
    fclose(file);
  }
  set_values(&G);
  int res = G.high_score;
  file = fopen(TETRIS_SCORES, "w");
  if (file) {
    fprintf(file, "2");
    fclose(file);
  }
  remove_field(&G);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(clean_field_0) {
  // non-zero field
  TetrisInfo_t G = {0};
  init_field(&G);
  h_fill_field(&G, 1);
  clean_field(&G);
  int res = h_is_field_empty(&G);
  remove_field(&G);
  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

START_TEST(clean_field_1) {
  // zero field
  TetrisInfo_t G = {0};
  init_field(&G);
  clean_field(&G);
  int res = h_is_field_empty(&G);
  remove_field(&G);
  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

START_TEST(remove_field_0) {
  TetrisInfo_t G = {0};
  init_field(&G);
  G.high_score = 10;
  remove_field(&G);
  ck_assert_ptr_eq(G.field, NULL);
  ck_assert_ptr_eq(G.next, NULL);
}
END_TEST

START_TEST(remove_field_1) {
  TetrisInfo_t G = {0};
  init_field(&G);
  G.high_score = 10;
  FILE *file = fopen(TETRIS_SCORES, "w");
  if (file) {
    fprintf(file, "123aaaaaaa");
    fclose(file);
  }
  remove_field(&G);
  file = fopen(TETRIS_SCORES, "w");
  if (file) {
    fprintf(file, "0");
    fclose(file);
  }
  ck_assert_ptr_eq(G.field, NULL);
  ck_assert_ptr_eq(G.next, NULL);
}
END_TEST

START_TEST(overflow_0) {
  FILE *file = fopen(FIELDS_FILE, "r");
  if (file) {
    TetrisInfo_t G = {0};
    init_field(&G);
    h_get_field(&G, &file, "overflow_0");
    int result = overflow(&G);
    remove_field(&G);
    fclose(file);
    file = NULL;
    ck_assert_int_eq(result, true);
  }
}
END_TEST

START_TEST(overflow_1) {
  FILE *file = fopen(FIELDS_FILE, "r");
  if (file) {
    TetrisInfo_t G = {0};
    init_field(&G);
    h_get_field(&G, &file, "overflow_1");
    int result = overflow(&G);
    remove_field(&G);
    fclose(file);
    file = NULL;
    ck_assert_int_eq(result, true);
  }
}
END_TEST

START_TEST(overflow_2) {
  FILE *file = fopen(FIELDS_FILE, "r");
  if (file) {
    TetrisInfo_t G = {0};
    init_field(&G);
    h_get_field(&G, &file, "overflow_2");
    int result = overflow(&G);
    remove_field(&G);
    fclose(file);
    file = NULL;
    ck_assert_int_eq(result, true);
  }
}
END_TEST

START_TEST(overflow_3) {
  FILE *file = fopen(FIELDS_FILE, "r");
  if (file) {
    TetrisInfo_t G = {0};
    init_field(&G);
    h_get_field(&G, &file, "overflow_3");
    bool result = overflow(&G);
    remove_field(&G);
    fclose(file);
    file = NULL;
    ck_assert_int_eq(result, false);
  }
}
END_TEST

START_TEST(overflow_4) {
  TetrisInfo_t G = {0};
  init_field(&G);
  int result = overflow(&G);
  remove_field(&G);
  ck_assert_int_eq(result, false);
}
END_TEST

START_TEST(clear_rows_0) {
  FILE *file = fopen(FIELDS_FILE, "r");
  if (file) {
    TetrisInfo_t G = {0};
    init_field(&G);
    h_get_field(&G, &file, "clear_rows_0");
    clear_rows(&G);
    int result = h_test_field(&G, &file);
    fclose(file);
    file = NULL;
    remove_field(&G);
    ck_assert_int_eq(result, 1);
  }
}
END_TEST

START_TEST(clear_rows_1) {
  FILE *file = fopen(FIELDS_FILE, "r");
  if (file) {
    TetrisInfo_t G = {0};
    init_field(&G);
    h_get_field(&G, &file, "clear_rows_1");
    clear_rows(&G);
    int result = h_test_field(&G, &file);
    fclose(file);
    file = NULL;
    remove_field(&G);
    ck_assert_int_eq(result, 1);
  }
}
END_TEST

START_TEST(clear_rows_2) {
  FILE *file = fopen(FIELDS_FILE, "r");
  if (file) {
    TetrisInfo_t G = {0};
    init_field(&G);
    h_get_field(&G, &file, "clear_rows_2");
    clear_rows(&G);
    int result = h_test_field(&G, &file);
    fclose(file);
    file = NULL;
    remove_field(&G);
    ck_assert_int_eq(result, 1);
  }
}
END_TEST

START_TEST(clear_rows_3) {
  FILE *file = fopen(FIELDS_FILE, "r");
  if (file) {
    TetrisInfo_t G = {0};
    init_field(&G);
    h_get_field(&G, &file, "clear_rows_3");
    clear_rows(&G);
    int result = h_test_field(&G, &file);
    fclose(file);
    file = NULL;
    remove_field(&G);
    ck_assert_int_eq(result, SUCCESS);
  }
}
END_TEST

START_TEST(increase_score_0) {
  TetrisInfo_t G = {0};
  TetrisInfo_t check = {0};
  check.level = 1;
  G.level = 1;
  check.speed = 10;
  G.speed = 10;
  increase_score(&G, 0);
  ck_assert_int_eq(h_parameters_eq(&G, &check), SUCCESS);
}
END_TEST

START_TEST(increase_score_1) {
  TetrisInfo_t G = {0};
  G.line_count = 9;
  G.score = 900;
  G.level = 2;
  G.speed = 20;
  TetrisInfo_t check = {0};
  check.score = 1000;
  check.high_score = 1000;
  check.line_count = 10;
  check.level = 2;
  check.speed = 20;

  increase_score(&G, 1);
  ck_assert_int_eq(h_parameters_eq(&G, &check), SUCCESS);
}
END_TEST

START_TEST(increase_score_2) {
  TetrisInfo_t G = {0};
  G.score = 1600;
  G.line_count = 16;
  G.level = 2;
  G.speed = 20;

  TetrisInfo_t check = {0};
  check.score = 4700;
  check.high_score = 4700;
  check.line_count = 21;
  check.level = 8;
  check.speed = 80;

  increase_score(&G, 5);
  ck_assert_int_eq(h_parameters_eq(&G, &check), SUCCESS);
}
END_TEST

START_TEST(increase_score_3) {
  TetrisInfo_t G = {0};
  G.score = 1600;
  G.high_score = 1600;
  G.line_count = 16;
  G.level = 3;
  G.speed = 30;

  TetrisInfo_t check = {0};
  check.score = 1600;
  check.high_score = 1600;
  check.line_count = 16;
  check.level = 3;
  check.speed = 30;

  increase_score(&G, 0);
  ck_assert_int_eq(h_parameters_eq(&G, &check), SUCCESS);
}
END_TEST

START_TEST(increase_score_4) {
  TetrisInfo_t G = {0};
  G.speed = 10;
  G.level = 1;
  TetrisInfo_t check = {0};
  check.score = 300;
  check.high_score = 300;
  check.line_count = 2;
  check.level = 1;
  check.speed = 10;

  increase_score(&G, 2);
  ck_assert_int_eq(h_parameters_eq(&G, &check), SUCCESS);
}
END_TEST

START_TEST(increase_score_5) {
  TetrisInfo_t G = {0};
  G.speed = 10;
  G.level = 1;
  TetrisInfo_t check = {0};
  check.score = 700;
  check.high_score = 700;
  check.line_count = 3;
  check.level = 2;
  check.speed = 20;

  increase_score(&G, 3);
  ck_assert_int_eq(h_parameters_eq(&G, &check), SUCCESS);
}
END_TEST

START_TEST(increase_score_6) {
  TetrisInfo_t G = {0};
  G.speed = 10;
  G.level = 1;
  TetrisInfo_t check = {0};
  check.score = 1500;
  check.high_score = 1500;
  check.line_count = 4;
  check.speed = 30;
  check.level = 3;

  increase_score(&G, 4);
  ck_assert_int_eq(h_parameters_eq(&G, &check), SUCCESS);
}
END_TEST

Suite *field_tests(void) {
  Suite *s = suite_create("FIELD TESTS");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, init_field_0);  // init_field

  tcase_add_test(tc_core, set_values_0);  // set_values
  tcase_add_test(tc_core, set_values_1);
  tcase_add_test(tc_core, set_values_2);
  tcase_add_test(tc_core, set_values_3);

  tcase_add_test(tc_core, clean_field_0);  // clean_field
  tcase_add_test(tc_core, clean_field_1);

  tcase_add_test(tc_core, remove_field_0);  // remove_field
  tcase_add_test(tc_core, remove_field_1);

  tcase_add_test(tc_core, overflow_0);  // overflow
  tcase_add_test(tc_core, overflow_1);
  tcase_add_test(tc_core, overflow_2);
  tcase_add_test(tc_core, overflow_3);
  tcase_add_test(tc_core, overflow_4);

  tcase_add_test(tc_core, clear_rows_0);  // clear_rows
  tcase_add_test(tc_core, clear_rows_1);  // no parameters
  tcase_add_test(tc_core, clear_rows_2);
  tcase_add_test(tc_core, clear_rows_3);
  // tcase_add_test(tc_core, clear_rows_4);

  tcase_add_test(tc_core, increase_score_0);  // increase_score
  tcase_add_test(tc_core, increase_score_1);
  tcase_add_test(tc_core, increase_score_2);
  tcase_add_test(tc_core, increase_score_3);
  tcase_add_test(tc_core, increase_score_4);
  tcase_add_test(tc_core, increase_score_5);
  tcase_add_test(tc_core, increase_score_6);

  suite_add_tcase(s, tc_core);
  return s;
}