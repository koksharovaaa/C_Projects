#include "tests.h"

START_TEST(get_game_0) {
  TetrisInfo_t *game_ptr = get_game();
  TetrisInfo_t check = {0};
  init_field(game_ptr);
  h_fill_field(game_ptr, 1);
  generate_next(game_ptr);
  h_set_parameters(game_ptr);
  h_set_parameters(&check);
  int res_1 = h_is_field_empty(game_ptr);
  int res_2 = h_check_next(game_ptr);
  int res_3 = h_parameters_eq(game_ptr, &check);
  remove_field(game_ptr);
  ck_assert_int_eq(res_1, FAILURE);
  ck_assert_int_eq(res_2, SUCCESS);
  ck_assert_int_eq(res_3, SUCCESS);
  ck_assert_ptr_eq(game_ptr->field, NULL);
  ck_assert_ptr_eq(game_ptr->next, NULL);
}
END_TEST

START_TEST(userInput_0) {
  TetrisInfo_t *game_ptr = get_game();
  init_field(game_ptr);
  h_fill_field(game_ptr, 1);
  generate_next(game_ptr);
  userInput(Terminate, false);
  ck_assert_ptr_eq(game_ptr->field, NULL);
  ck_assert_ptr_eq(game_ptr->next, NULL);
}
END_TEST

START_TEST(userInput_1) {
  FILE *file = fopen(FIELDS_FILE, "r");
  if (file) {
    TetrisInfo_t *game_ptr = get_game();
    TetrisInfo_t check = {0};
    init_field(game_ptr);
    init_field(&check);
    h_set_parameters(game_ptr);
    h_set_parameters(&check);
    h_get_field(game_ptr, &file, "movement_3");
    fseek(file, 0, SEEK_SET);
    h_get_field(&check, &file, "movement_3");
    game_ptr->figure = (figure_t){7, 16, 1, 0x6C00};
    check.figure = (figure_t){7, 16, 1, 0x6C00};
    check.pause = PAUSE;
    userInput(Pause, false);
    userInput(Down, false);
    int res_1 = h_parameters_eq(game_ptr, &check);
    int res_2 = h_fields_eq(game_ptr, &check);
    remove_field(game_ptr);
    remove_field(&check);
    fclose(file);
    file = NULL;
    ck_assert_int_eq(res_1, SUCCESS);
    ck_assert_int_eq(res_2, SUCCESS);
  }
}
END_TEST

START_TEST(userInput_2) {
  TetrisInfo_t *game_ptr = get_game();
  game_ptr->pause = PLAY;
  userInput(Pause, false);
  userInput(Pause, false);
  ck_assert_int_eq(game_ptr->pause, PLAY);
}
END_TEST

START_TEST(userInput_3) {
  FILE *file = fopen(FIELDS_FILE, "r");
  if (file) {
    TetrisInfo_t *game_ptr = get_game();
    init_field(game_ptr);
    set_values(game_ptr);
    h_get_field(game_ptr, &file, "user_input_down");
    game_ptr->figure = (figure_t){7, 13, 0, 0x6C00};
    figure_t f = (figure_t){7, 14, 0, 0x6C00};
    game_ptr->state = tetris_fall;
    userInput(Down, false);
    int res_1 = h_test_field(game_ptr, &file);
    int res_2 = h_figures_eq(game_ptr->figure, f);
    int res_3 = game_ptr->state;
    remove_field(game_ptr);
    fclose(file);
    file = NULL;
    ck_assert_int_eq(res_1, SUCCESS);
    ck_assert_int_eq(res_2, SUCCESS);
    ck_assert_int_eq(res_3, tetris_collision);
  }
}
END_TEST

START_TEST(userInput_4) {
  FILE *file = fopen(FIELDS_FILE, "r");
  if (file) {
    TetrisInfo_t *game_ptr = get_game();
    init_field(game_ptr);
    set_values(game_ptr);
    h_get_field(game_ptr, &file, "user_input_action");
    game_ptr->figure = (figure_t){7, 13, 0, 0x6C00};
    figure_t f = (figure_t){7, 13, 0, 0x4620};
    game_ptr->state = tetris_fall;
    userInput(Action, false);
    int res_1 = h_test_field(game_ptr, &file);
    int res_2 = h_figures_eq(game_ptr->figure, f);
    int res_3 = game_ptr->state;
    remove_field(game_ptr);
    fclose(file);
    file = NULL;
    ck_assert_int_eq(res_1, SUCCESS);
    ck_assert_int_eq(res_2, SUCCESS);
    ck_assert_int_eq(res_3, tetris_fall);
  }
}
END_TEST

START_TEST(userInput_5) {
  TetrisInfo_t *game_ptr = get_game();
  game_ptr->state = tetris_start;
  game_ptr->pause = STAND_BY;
  userInput(Start, false);
  game_ptr->high_score = 10;
  TetrisInfo_t check = {0};
  check.speed = 10;
  check.level = 1;
  check.state = tetris_spawn;
  check.high_score = 10;
  check.pause = PLAY;
  int res_1 = h_is_field_empty(game_ptr);
  int res_2 = h_check_next(game_ptr);
  int res_3 = h_parameters_eq(game_ptr, &check);
  remove_field(game_ptr);
  ck_assert_int_eq(res_1, SUCCESS);
  ck_assert_int_eq(res_2, SUCCESS);
  ck_assert_int_eq(res_3, SUCCESS);
}
END_TEST

START_TEST(userInput_6) {
  TetrisInfo_t *game_ptr = get_game();
  userInput(Start, false);
  userInput(Down, false);
  int res_1 = h_is_field_empty(game_ptr);
  int res_2 = h_check_next(game_ptr);
  int res_3 = game_ptr->state;
  remove_field(game_ptr);
  ck_assert_int_eq(res_1, FAILURE);
  ck_assert_int_eq(res_2, SUCCESS);
  ck_assert_int_eq(res_3, tetris_fall);
}
END_TEST

START_TEST(userInput_7) {
  TetrisInfo_t *game_ptr = get_game();
  init_field(game_ptr);
  set_values(game_ptr);
  h_fill_field(game_ptr, 2);
  game_ptr->state = tetris_gameover;
  userInput(Down, false);
  int res_1 = game_ptr->pause;
  int res_2 = game_ptr->state;
  remove_field(game_ptr);
  ck_assert_int_eq(res_1, GAME_OVER);
  ck_assert_int_eq(res_2, tetris_gameover);
}
END_TEST

START_TEST(userInput_8) {
  TetrisInfo_t *game_ptr = get_game();
  init_field(game_ptr);
  // set_values(game_ptr);
  h_fill_field(game_ptr, 1);
  game_ptr->state = tetris_start;
  game_ptr->pause = GAME_OVER;
  userInput(Start, false);
  int res_1 = game_ptr->pause;
  int res_2 = game_ptr->state;
  int res_3 = h_is_field_empty(game_ptr);
  int res_4 = h_check_next(game_ptr);
  remove_field(game_ptr);
  ck_assert_int_eq(res_1, PLAY);
  ck_assert_int_eq(res_2, tetris_spawn);
  ck_assert_int_eq(res_3, SUCCESS);
  ck_assert_int_eq(res_4, SUCCESS);
}
END_TEST

START_TEST(userInput_9) {
  FILE *file = fopen(FIELDS_FILE, "r");
  if (file) {
    TetrisInfo_t *game_ptr = get_game();
    init_field(game_ptr);
    set_values(game_ptr);
    h_get_field(game_ptr, &file, "user_input_collision_1");
    game_ptr->figure = (figure_t){7, 13, 0, 0x4620};
    figure_t f = (figure_t){7, 13, 0, 0x0460};
    game_ptr->state = tetris_collision;
    userInput(Down, true);
    int res_1 = h_test_field(game_ptr, &file);
    int res_2 = h_figures_eq(game_ptr->figure, f);
    int res_3 = game_ptr->state;
    remove_field(game_ptr);
    fclose(file);
    file = NULL;
    ck_assert_int_eq(res_1, SUCCESS);
    ck_assert_int_eq(res_2, SUCCESS);
    ck_assert_int_eq(res_3, tetris_spawn);
  }
}
END_TEST

START_TEST(userInput_10) {
  FILE *file = fopen(FIELDS_FILE, "r");
  if (file) {
    TetrisInfo_t *game_ptr = get_game();
    init_field(game_ptr);
    set_values(game_ptr);
    h_get_field(game_ptr, &file, "user_input_collision_2");
    game_ptr->figure = (figure_t){1, 14, 0, 0x4444};
    figure_t f = (figure_t){1, 15, 0, 0x0004};
    game_ptr->state = tetris_collision;
    userInput(Down, true);
    int res_1 = h_test_field(game_ptr, &file);
    int res_2 = h_figures_eq(game_ptr->figure, f);
    int res_3 = game_ptr->state;
    remove_field(game_ptr);
    fclose(file);
    file = NULL;
    ck_assert_int_eq(res_1, SUCCESS);
    ck_assert_int_eq(res_2, SUCCESS);
    ck_assert_int_eq(res_3, tetris_spawn);
  }
}
END_TEST

START_TEST(userInput_11) {
  FILE *file = fopen(FIELDS_FILE, "r");
  if (file) {
    TetrisInfo_t *game_ptr = get_game();
    init_field(game_ptr);
    set_values(game_ptr);
    h_get_field(game_ptr, &file, "user_input_collision_3");
    game_ptr->figure = (figure_t){1, 1, 3, 0x0F00};
    figure_t f = (figure_t){1, 1, 3, 0x0F00};
    game_ptr->state = tetris_collision;
    userInput(Down, true);
    int res_1 = game_ptr->state;
    int res_2 = h_figures_eq(game_ptr->figure, f);
    remove_field(game_ptr);
    fclose(file);
    file = NULL;
    ck_assert_int_eq(res_1, tetris_gameover);
    ck_assert_int_eq(res_2, SUCCESS);
  }
}
END_TEST

START_TEST(userInput_12) {
  TetrisInfo_t *game_ptr = get_game();
  init_field(game_ptr);
  // set_values(game_ptr);
  h_fill_field(game_ptr, 2);
  game_ptr->state = tetris_gameover;
  game_ptr->pause = GAME_OVER;
  userInput(Start, false);
  int res_1 = game_ptr->state;
  userInput(Start, false);
  int res_2 = game_ptr->pause;
  int res_3 = h_is_field_empty(game_ptr);
  remove_field(game_ptr);
  ck_assert_int_eq(res_1, tetris_start);
  ck_assert_int_eq(res_2, PLAY);
  ck_assert_int_eq(res_3, true);
}
END_TEST

START_TEST(updateCurrentState_0) {
  TetrisInfo_t *game_ptr = get_game();
  init_field(game_ptr);
  set_values(game_ptr);
  h_fill_field(game_ptr, 2);
  h_set_parameters(game_ptr);
  GameInfo_t check = updateCurrentState();
  int result_parameters = game_ptr->score == check.score &&
                          game_ptr->high_score == check.high_score &&
                          game_ptr->level == check.level &&
                          game_ptr->speed == check.speed &&
                          game_ptr->pause == check.pause;
  ck_assert_int_eq(result_parameters, SUCCESS);
  int result_next = FAILURE;
  figure_t all[] = {{I}, {L}, {J}, {T}, {O}, {Z}, {S}};
  for (int index = 0; index < F_COUNT && !result_next; index++) {
    result_next = SUCCESS;
    for (int i = 0; i < F_SIDE && result_next; i++) {
      for (int j = 0; j < F_SIDE && result_next; j++) {
        if ((!!check.next[i][j]) ^ get_mask(i, j, all[index])) {
          result_next = FAILURE;
        }
      }
    }
  }
  ck_assert_int_eq(result_next, SUCCESS);
  ck_assert_ptr_eq(&(game_ptr->field[H_SPAWN]), check.field);
  ck_assert_ptr_eq(game_ptr->next, check.next);
  remove_field(game_ptr);
}
END_TEST

Suite *fsm_tests(void) {
  Suite *s = suite_create("FSM TESTS");
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, get_game_0);  // get_game

  tcase_add_test(tc_core, userInput_0);  // userInput
  tcase_add_test(tc_core, userInput_1);
  tcase_add_test(tc_core, userInput_2);
  tcase_add_test(tc_core, userInput_3);
  tcase_add_test(tc_core, userInput_4);
  tcase_add_test(tc_core, userInput_5);
  tcase_add_test(tc_core, userInput_6);
  tcase_add_test(tc_core, userInput_7);
  tcase_add_test(tc_core, userInput_8);
  tcase_add_test(tc_core, userInput_9);
  tcase_add_test(tc_core, userInput_10);
  tcase_add_test(tc_core, userInput_11);
  tcase_add_test(tc_core, userInput_12);

  tcase_add_test(tc_core, updateCurrentState_0);  // updateCurrentState_0

  suite_add_tcase(s, tc_core);
  return s;
}
