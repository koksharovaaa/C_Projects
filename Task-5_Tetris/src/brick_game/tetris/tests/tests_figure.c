#include "tests.h"

START_TEST(generate_next_0) {
  // empty next
  TetrisInfo_t G = {0};
  init_field(&G);
  generate_next(&G);
  int result = h_check_next(&G);
  remove_field(&G);
  ck_assert_int_eq(result, SUCCESS);
}
END_TEST

START_TEST(generate_next_1) {
  // non-empty next
  TetrisInfo_t G = {0};
  init_field(&G);
  for (int i = 0; i < F_SIDE; i++) {
    for (int j = 0; j < F_SIDE; j++) {
      G.next[i][j] = 1;
    }
  }
  generate_next(&G);
  int result = h_check_next(&G);
  remove_field(&G);
  ck_assert_int_eq(result, SUCCESS);
}
END_TEST

START_TEST(paste_figure_0) {
  // empty field
  FILE *file = fopen(FIELDS_FILE, "r");
  if (file) {
    TetrisInfo_t G = {0};
    init_field(&G);
    h_get_field(&G, &file, "paste_figure_0");
    h_set_next(&G, 1);
    paste_figure(&G);
    int result = (h_test_field(&G, &file) &&
                  h_figures_eq(G.figure, (figure_t){1, 0, 3, 0x0F00}));
    fclose(file);
    file = NULL;
    remove_field(&G);
    ck_assert_int_eq(result, SUCCESS);
  }
}
END_TEST

START_TEST(paste_figure_1) {
  // empty field
  FILE *file = fopen(FIELDS_FILE, "r");
  if (file) {
    TetrisInfo_t G = {0};
    init_field(&G);
    h_get_field(&G, &file, "paste_figure_1");
    h_set_next(&G, 1);
    paste_figure(&G);
    int result = (h_test_field(&G, &file) &&
                  h_figures_eq(G.figure, (figure_t){1, 0, 3, 0x0F00}));
    remove_field(&G);
    fclose(file);
    file = NULL;
    ck_assert_int_eq(result, SUCCESS);
  }
}
END_TEST

START_TEST(paste_figure_2) {
  FILE *file = fopen(FIELDS_FILE, "r");
  if (file) {
    TetrisInfo_t G = {0};
    init_field(&G);
    h_get_field(&G, &file, "paste_figure_2");
    h_set_next(&G, 5);
    paste_figure(&G);
    int res_1 = h_test_field(&G, &file);
    int res_2 = h_figures_eq(G.figure, (figure_t){5, 0, 3, 0x0660});
    remove_field(&G);
    fclose(file);
    file = NULL;
    ck_assert_int_eq(res_1, SUCCESS);
    ck_assert_int_eq(res_2, SUCCESS);
  }
}
END_TEST

START_TEST(paste_figure_3) {
  FILE *file = fopen(FIELDS_FILE, "r");
  if (file) {
    TetrisInfo_t G = {0};
    init_field(&G);
    h_get_field(&G, &file, "paste_figure_3");
    h_set_next(&G, 6);
    paste_figure(&G);
    int res_1 = h_test_field(&G, &file);
    int res_2 = h_figures_eq(G.figure, (figure_t){6, 0, 3, 0x0C60});
    remove_field(&G);
    fclose(file);
    file = NULL;
    ck_assert_int_eq(res_1, SUCCESS);
    ck_assert_int_eq(res_2, SUCCESS);
  }
}
END_TEST

START_TEST(rotate_figure_0) {
  FILE *file = fopen(FIELDS_FILE, "r");
  if (file) {
    TetrisInfo_t G = {0};
    init_field(&G);
    h_get_field(&G, &file, "rotate_figure_0");
    G.figure = (figure_t){1, 0, 3, 0x00F0};
    rotate_figure(&G);
    int res_1 = h_test_field(&G, &file);
    int res_2 = G.figure.mask;
    remove_field(&G);
    fclose(file);
    file = NULL;
    ck_assert_int_eq(res_1, SUCCESS);
    ck_assert_int_eq(res_2, 0x4444);
  }
}
END_TEST

START_TEST(rotate_figure_1) {
  FILE *file = fopen(FIELDS_FILE, "r");
  if (file) {
    TetrisInfo_t G = {0};
    init_field(&G);
    h_get_field(&G, &file, "rotate_figure_1");
    G.figure = (figure_t){5, 0, 3, 0x0660};
    rotate_figure(&G);
    int res_1 = h_test_field(&G, &file);
    int res_2 = G.figure.mask;
    remove_field(&G);
    fclose(file);
    file = NULL;
    ck_assert_int_eq(res_1, SUCCESS);
    ck_assert_int_eq(res_2, 0x0660);
  }
}
END_TEST

START_TEST(rotate_figure_2) {
  FILE *file = fopen(FIELDS_FILE, "r");
  if (file) {
    TetrisInfo_t G = {0};
    init_field(&G);
    h_get_field(&G, &file, "rotate_figure_2");
    G.figure = (figure_t){1, 0, 8, 0x4444};
    int res_1 = rotate_figure(&G);
    int res_2 = G.figure.mask;
    remove_field(&G);
    fclose(file);
    file = NULL;
    ck_assert_int_eq(res_1, false);
    ck_assert_int_eq(res_2, 0x4444);
  }
}
END_TEST

START_TEST(rotate_figure_3) {
  FILE *file = fopen(FIELDS_FILE, "r");
  if (file) {
    TetrisInfo_t G = {0};
    init_field(&G);
    h_get_field(&G, &file, "rotate_figure_3");
    G.figure = (figure_t){1, 0, H_TOTAL - 1, 0x00F0};
    int res_1 = rotate_figure(&G);
    int res_2 = G.figure.mask;
    remove_field(&G);
    fclose(file);
    file = NULL;
    ck_assert_int_eq(res_1, false);
    ck_assert_int_eq(res_2, 0x00F0);
  }
}
END_TEST

START_TEST(rotate_figure_4) {
  FILE *file = fopen(FIELDS_FILE, "r");
  if (file) {
    TetrisInfo_t G = {0};
    init_field(&G);
    h_get_field(&G, &file, "rotate_figure_4");
    G.figure = (figure_t){1, 9, 0, 0x2222};
    int res_1 = rotate_figure(&G);
    int res_2 = h_test_field(&G, &file);
    int res_3 = G.figure.mask;
    remove_field(&G);
    fclose(file);
    file = NULL;
    ck_assert_int_eq(res_1, true);
    ck_assert_int_eq(res_2, SUCCESS);
    ck_assert_int_eq(res_3, 0x00F0);
  }
}
END_TEST

START_TEST(rotate_figure_5) {
  FILE *file = fopen(FIELDS_FILE, "r");
  if (file) {
    TetrisInfo_t G = {0};
    TetrisInfo_t check = {0};
    init_field(&G);
    init_field(&check);
    h_get_field(&G, &file, "rotate_figure_5");
    fseek(file, 0, SEEK_SET);
    h_get_field(&check, &file, "rotate_figure_5");
    G.figure = (figure_t){1, 10, 0, 0x2222};
    check.figure = (figure_t){1, 10, 0, 0x2222};
    int res_1 = rotate_figure(&G);
    int res_2 = h_parameters_eq(&G, &check);
    int res_3 = h_fields_eq(&G, &check);
    remove_field(&G);
    remove_field(&check);
    fclose(file);
    file = NULL;
    ck_assert_int_eq(res_1, false);
    ck_assert_int_eq(res_2, SUCCESS);
    ck_assert_int_eq(res_3, SUCCESS);
  }
}
END_TEST

START_TEST(rotate_figure_6) {
  FILE *file = fopen(FIELDS_FILE, "r");
  if (file) {
    TetrisInfo_t G = {0};
    init_field(&G);
    h_get_field(&G, &file, "rotate_figure_6");
    G.figure = (figure_t){1, 9, 0, 0x2222};
    int res_1 = rotate_figure(&G);
    int res_2 = h_test_field(&G, &file);
    int res_3 = G.figure.mask;
    remove_field(&G);
    fclose(file);
    file = NULL;
    ck_assert_int_eq(res_1, true);
    ck_assert_int_eq(res_2, SUCCESS);
    ck_assert_int_eq(res_3, 0x00F0);
  }
}
END_TEST

START_TEST(rotate_figure_7) {
  FILE *file = fopen(FIELDS_FILE, "r");
  if (file) {
    TetrisInfo_t G = {0};
    init_field(&G);
    h_get_field(&G, &file, "rotate_figure_7");
    G.figure = (figure_t){7, 12, 1, 0x4620};
    int res_1 = rotate_figure(&G);
    int res_2 = h_test_field(&G, &file);
    int res_3 = G.figure.mask;
    remove_field(&G);
    fclose(file);
    file = NULL;
    ck_assert_int_eq(res_1, true);
    ck_assert_int_eq(res_2, SUCCESS);
    ck_assert_int_eq(res_3, 0x06C0);
  }
}
END_TEST

START_TEST(check_next_cell_0) {
  // down wall collision
  FILE *file = fopen(FIELDS_FILE, "r");
  if (file) {
    TetrisInfo_t G = {0};
    init_field(&G);
    h_get_field(&G, &file, "movement_0");
    G.figure = (figure_t){7, 20, 0, 0x6C00};
    int i = 0;  // from 0 to 3
    int j = 0;  // from 0 to 3
    bool result = check_next_cell(&G, Down, i, j);
    remove_field(&G);
    fclose(file);
    file = NULL;
    ck_assert_int_eq(result, false);
  }
}
END_TEST

START_TEST(check_next_cell_1) {
  // down wall collision
  FILE *file = fopen(FIELDS_FILE, "r");
  if (file) {
    TetrisInfo_t G = {0};
    init_field(&G);
    h_get_field(&G, &file, "movement_0");
    G.figure = (figure_t){7, 20, 0, 0x6C00};
    int i = 3;  // from 0 to 3
    int j = 3;  // from 0 to 3
    bool result = check_next_cell(&G, Down, i, j);
    remove_field(&G);
    fclose(file);
    file = NULL;
    ck_assert_int_eq(result, true);
  }
}
END_TEST

START_TEST(check_next_cell_2) {
  // down wall collision
  FILE *file = fopen(FIELDS_FILE, "r");
  if (file) {
    TetrisInfo_t G = {0};
    init_field(&G);
    h_get_field(&G, &file, "movement_1");
    G.figure = (figure_t){7, 16, 0, 0x6C00};
    int i = 0;  // from 0 to 3
    int j = 0;  // from 0 to 3
    bool result = check_next_cell(&G, Down, i, j);
    remove_field(&G);
    fclose(file);
    file = NULL;
    ck_assert_int_eq(result, false);
  }
}
END_TEST

START_TEST(check_next_cell_3) {
  FILE *file = fopen(FIELDS_FILE, "r");
  if (file) {
    TetrisInfo_t G = {0};
    init_field(&G);
    h_get_field(&G, &file, "movement_1");
    G.figure = (figure_t){7, 16, 0, 0x6C00};
    int i = 0;  // from 0 to 3
    int j = 1;  // from 0 to 3
    bool result = check_next_cell(&G, Down, i, j);
    remove_field(&G);
    fclose(file);
    file = NULL;
    ck_assert_int_eq(result, false);
  }
}
END_TEST

START_TEST(check_next_cell_4) {
  FILE *file = fopen(FIELDS_FILE, "r");
  if (file) {
    TetrisInfo_t G = {0};
    init_field(&G);
    h_get_field(&G, &file, "movement_2");
    G.figure = (figure_t){7, 16, 0, 0x6C00};
    int i = 1;  // from 0 to 3
    int j = 1;  // from 0 to 3
    bool result = check_next_cell(&G, Down, i, j);
    remove_field(&G);
    fclose(file);
    file = NULL;
    ck_assert_int_eq(result, false);
  }
}
END_TEST

START_TEST(check_next_cell_5) {
  FILE *file = fopen(FIELDS_FILE, "r");
  if (file) {
    TetrisInfo_t G = {0};
    init_field(&G);
    h_get_field(&G, &file, "movement_2");
    G.figure = (figure_t){7, 16, 0, 0x6C00};
    int i = 0;  // from 0 to 3
    int j = 2;  // from 0 to 3
    bool result = check_next_cell(&G, Down, i, j);
    remove_field(&G);
    fclose(file);
    file = NULL;
    ck_assert_int_eq(result, true);
  }
}
END_TEST

START_TEST(check_next_cell_6) {
  FILE *file = fopen(FIELDS_FILE, "r");
  if (file) {
    TetrisInfo_t G = {0};
    init_field(&G);
    h_get_field(&G, &file, "movement_2");
    G.figure = (figure_t){7, 16, 0, 0x6C00};
    int i = 1;  // from 0 to 3
    int j = 1;  // from 0 to 3
    bool result = check_next_cell(&G, Right, i, j);
    remove_field(&G);
    fclose(file);
    file = NULL;
    ck_assert_int_eq(result, true);
  }
}
END_TEST

START_TEST(check_next_cell_7) {
  FILE *file = fopen(FIELDS_FILE, "r");
  if (file) {
    TetrisInfo_t G = {0};
    init_field(&G);
    h_get_field(&G, &file, "movement_2");
    G.figure = (figure_t){7, 16, 0, 0x6C00};
    int i = 0;  // from 0 to 3
    int j = 0;  // from 0 to 3
    bool result = check_next_cell(&G, Left, i, j);
    remove_field(&G);
    fclose(file);
    file = NULL;
    ck_assert_int_eq(result, true);
  }
}
END_TEST

START_TEST(check_next_cell_8) {
  FILE *file = fopen(FIELDS_FILE, "r");
  if (file) {
    TetrisInfo_t G = {0};
    init_field(&G);
    h_get_field(&G, &file, "movement_3");
    G.figure = (figure_t){7, 16, 1, 0x6C00};
    int i = 1;  // from 0 to 3
    int j = 0;  // from 0 to 3
    bool result = check_next_cell(&G, Left, i, j);
    remove_field(&G);
    fclose(file);
    file = NULL;
    ck_assert_int_eq(result, true);
  }
}
END_TEST

START_TEST(check_next_cell_9) {
  FILE *file = fopen(FIELDS_FILE, "r");
  if (file) {
    TetrisInfo_t G = {0};
    init_field(&G);
    h_get_field(&G, &file, "movement_3");
    G.figure = (figure_t){7, 16, 1, 0x6C00};
    int i = 0;  // from 0 to 3
    int j = 2;  // from 0 to 3
    bool result = check_next_cell(&G, Right, i, j);
    remove_field(&G);
    fclose(file);
    file = NULL;
    ck_assert_int_eq(result, true);
  }
}
END_TEST

START_TEST(can_move_0) {
  FILE *file = fopen(FIELDS_FILE, "r");
  if (file) {
    TetrisInfo_t G = {0};
    init_field(&G);
    h_get_field(&G, &file, "movement_0");
    G.figure = (figure_t){7, 20, 0, 0x6C00};
    bool result = can_move(&G, Down);
    remove_field(&G);
    fclose(file);
    file = NULL;
    ck_assert_int_eq(result, false);
  }
}
END_TEST

START_TEST(can_move_1) {
  FILE *file = fopen(FIELDS_FILE, "r");
  if (file) {
    TetrisInfo_t G = {0};
    init_field(&G);
    h_get_field(&G, &file, "movement_0");
    G.figure = (figure_t){7, 20, 0, 0x6C00};
    bool result = can_move(&G, Down);
    remove_field(&G);
    fclose(file);
    file = NULL;
    ck_assert_int_eq(result, false);
  }
}
END_TEST

START_TEST(can_move_2) {
  FILE *file = fopen(FIELDS_FILE, "r");
  if (file) {
    TetrisInfo_t G = {0};
    init_field(&G);
    h_get_field(&G, &file, "movement_0");
    G.figure = (figure_t){7, 20, 0, 0x6C00};
    bool result = can_move(&G, Right);
    remove_field(&G);
    fclose(file);
    file = NULL;
    ck_assert_int_eq(result, true);
  }
}
END_TEST

START_TEST(can_move_3) {
  FILE *file = fopen(FIELDS_FILE, "r");
  if (file) {
    TetrisInfo_t G = {0};
    init_field(&G);
    h_get_field(&G, &file, "movement_2");
    G.figure = (figure_t){7, 16, 0, 0x6C00};
    bool result = can_move(&G, Right);
    remove_field(&G);
    fclose(file);
    file = NULL;
    ck_assert_int_eq(result, false);
  }
}
END_TEST

START_TEST(can_move_4) {
  FILE *file = fopen(FIELDS_FILE, "r");
  if (file) {
    TetrisInfo_t G = {0};
    init_field(&G);
    h_get_field(&G, &file, "movement_2");
    G.figure = (figure_t){7, 16, 0, 0x6C00};
    bool result = can_move(&G, Down);
    remove_field(&G);
    fclose(file);
    file = NULL;
    ck_assert_int_eq(result, false);
  }
}
END_TEST

START_TEST(can_move_5) {
  FILE *file = fopen(FIELDS_FILE, "r");
  if (file) {
    TetrisInfo_t G = {0};
    init_field(&G);
    h_get_field(&G, &file, "movement_3");
    G.figure = (figure_t){7, 16, 1, 0x6C00};
    bool result = can_move(&G, Down);
    remove_field(&G);
    fclose(file);
    file = NULL;
    ck_assert_int_eq(result, true);
  }
}
END_TEST

START_TEST(can_move_6) {
  FILE *file = fopen(FIELDS_FILE, "r");
  if (file) {
    TetrisInfo_t G = {0};
    init_field(&G);
    h_get_field(&G, &file, "movement_3");
    G.figure = (figure_t){7, 16, 1, 0x6C00};
    bool result = can_move(&G, Left);
    remove_field(&G);
    fclose(file);
    file = NULL;
    ck_assert_int_eq(result, false);
  }
}
END_TEST

START_TEST(move_figure_base_0) {
  FILE *file = fopen(FIELDS_FILE, "r");
  if (file) {
    TetrisInfo_t G = {0};
    init_field(&G);
    h_get_field(&G, &file, "base_movement_0");
    G.figure = (figure_t){7, 16, 1, 0x6C00};
    figure_t check = (figure_t){7, 17, 1, 0x6C00};
    move_figure_base(&G, Down);
    int res_1 = h_figures_eq(G.figure, check);
    int res_2 = h_test_field(&G, &file);
    remove_field(&G);
    fclose(file);
    file = NULL;
    ck_assert_int_eq(res_1, SUCCESS);
    ck_assert_int_eq(res_2, SUCCESS);
  }
}
END_TEST

START_TEST(move_figure_base_1) {
  FILE *file = fopen(FIELDS_FILE, "r");
  if (file) {
    TetrisInfo_t G = {0};
    init_field(&G);
    h_get_field(&G, &file, "base_movement_1");
    G.figure = (figure_t){7, 16, 1, 0x6C00};
    figure_t check = (figure_t){7, 16, 0, 0x6C00};
    move_figure_base(&G, Left);
    int res_1 = h_figures_eq(G.figure, check);
    int res_2 = h_test_field(&G, &file);
    remove_field(&G);
    fclose(file);
    file = NULL;
    ck_assert_int_eq(res_1, SUCCESS);
    ck_assert_int_eq(res_2, SUCCESS);
  }
}
END_TEST

START_TEST(move_figure_base_2) {
  FILE *file = fopen(FIELDS_FILE, "r");
  if (file) {
    TetrisInfo_t G = {0};
    init_field(&G);
    h_get_field(&G, &file, "base_movement_2");
    G.figure = (figure_t){7, 16, 1, 0x6C00};
    figure_t check = (figure_t){7, 16, 2, 0x6C00};
    move_figure_base(&G, Right);
    int res_1 = h_figures_eq(G.figure, check);
    int res_2 = h_test_field(&G, &file);
    remove_field(&G);
    fclose(file);
    file = NULL;
    ck_assert_int_eq(res_1, SUCCESS);
    ck_assert_int_eq(res_2, SUCCESS);
  }
}
END_TEST

START_TEST(move_figure_base_3) {
  FILE *file = fopen(FIELDS_FILE, "r");
  if (file) {
    TetrisInfo_t G = {0};
    init_field(&G);
    h_get_field(&G, &file, "base_movement_3");
    G.figure = (figure_t){7, 12, 1, 0x06C0};
    figure_t check = (figure_t){7, 13, 1, 0x06C0};
    move_figure_base(&G, Down);
    int res_1 = h_figures_eq(G.figure, check);
    int res_2 = h_test_field(&G, &file);
    remove_field(&G);
    fclose(file);
    file = NULL;
    ck_assert_int_eq(res_1, SUCCESS);
    ck_assert_int_eq(res_2, SUCCESS);
  }
}
END_TEST

START_TEST(move_figure_base_4) {
  FILE *file = fopen(FIELDS_FILE, "r");
  if (file) {
    TetrisInfo_t G = {0};
    init_field(&G);
    h_get_field(&G, &file, "base_movement_4");
    G.figure = (figure_t){7, 12, 1, 0x06C0};
    figure_t check = (figure_t){7, 12, 2, 0x06C0};
    move_figure_base(&G, Right);
    int res_1 = h_figures_eq(G.figure, check);
    int res_2 = h_test_field(&G, &file);
    remove_field(&G);
    fclose(file);
    file = NULL;
    ck_assert_int_eq(res_1, SUCCESS);
    ck_assert_int_eq(res_2, SUCCESS);
  }
}
END_TEST

START_TEST(move_figure_base_5) {
  FILE *file = fopen(FIELDS_FILE, "r");
  if (file) {
    TetrisInfo_t G = {0};
    init_field(&G);
    h_get_field(&G, &file, "base_movement_5");
    G.figure = (figure_t){7, 12, 1, 0x06C0};
    figure_t check = (figure_t){7, 12, 0, 0x06C0};
    move_figure_base(&G, Left);
    int res_1 = h_figures_eq(G.figure, check);
    int res_2 = h_test_field(&G, &file);
    remove_field(&G);
    fclose(file);
    file = NULL;
    ck_assert_int_eq(res_1, SUCCESS);
    ck_assert_int_eq(res_2, SUCCESS);
  }
}
END_TEST

START_TEST(move_figure_0) {
  // move_figure_0 down hold check
  FILE *file = fopen(FIELDS_FILE, "r");
  if (file) {
    TetrisInfo_t G = {0};
    init_field(&G);
    h_get_field(&G, &file, "move_figure_0");
    G.figure = (figure_t){7, 16, 1, 0x6C00};
    figure_t check = (figure_t){7, 17, 1, 0x6C00};
    int result = move_figure(&G, Down, true);
    int res_1 = h_figures_eq(G.figure, check);
    int res_2 = h_test_field(&G, &file);
    remove_field(&G);
    fclose(file);
    file = NULL;
    ck_assert_int_eq(result, true);
    ck_assert_int_eq(res_1, SUCCESS);
    ck_assert_int_eq(res_2, SUCCESS);
  }
}
END_TEST

START_TEST(move_figure_1) {
  // move_figure_0 down press check
  FILE *file = fopen(FIELDS_FILE, "r");
  if (file) {
    TetrisInfo_t G = {0};
    init_field(&G);
    h_get_field(&G, &file, "move_figure_1");
    G.figure = (figure_t){7, 16, 1, 0x6C00};
    figure_t check = (figure_t){7, 20, 1, 0x6C00};
    int result = move_figure(&G, Down, false);
    int res_1 = h_figures_eq(G.figure, check);
    int res_2 = h_test_field(&G, &file);
    remove_field(&G);
    fclose(file);
    file = NULL;
    ck_assert_int_eq(result, false);
    ck_assert_int_eq(res_1, SUCCESS);
    ck_assert_int_eq(res_2, SUCCESS);
  }
}
END_TEST

START_TEST(move_figure_2) {
  // move_figure_0 down press check
  FILE *file = fopen(FIELDS_FILE, "r");
  if (file) {
    TetrisInfo_t G = {0};
    init_field(&G);
    h_get_field(&G, &file, "move_figure_2");
    G.figure = (figure_t){2, 0, 5, 0x0E80};
    figure_t check = (figure_t){2, 19, 5, 0x0E80};
    int result = move_figure(&G, Down, false);
    int res_1 = h_figures_eq(G.figure, check);
    int res_2 = h_test_field(&G, &file);
    remove_field(&G);
    fclose(file);
    file = NULL;
    ck_assert_int_eq(result, false);
    ck_assert_int_eq(res_1, SUCCESS);
    ck_assert_int_eq(res_2, SUCCESS);
  }
}
END_TEST

Suite *figure_tests(void) {
  Suite *s = suite_create("FIGURE TESTS");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, generate_next_0);  // generate_next
  tcase_add_test(tc_core, generate_next_1);

  tcase_add_test(tc_core, paste_figure_0);  // paste_figure
  tcase_add_test(tc_core, paste_figure_1);
  tcase_add_test(tc_core, paste_figure_2);
  tcase_add_test(tc_core, paste_figure_3);

  tcase_add_test(tc_core, rotate_figure_0);  // rotate_figure_0
  tcase_add_test(tc_core, rotate_figure_1);
  tcase_add_test(tc_core, rotate_figure_2);
  tcase_add_test(tc_core, rotate_figure_3);
  tcase_add_test(tc_core, rotate_figure_4);
  tcase_add_test(tc_core, rotate_figure_5);
  tcase_add_test(tc_core, rotate_figure_6);
  tcase_add_test(tc_core, rotate_figure_7);

  tcase_add_test(tc_core, check_next_cell_0);  // check_next_cell
  tcase_add_test(tc_core, check_next_cell_1);
  tcase_add_test(tc_core, check_next_cell_2);
  tcase_add_test(tc_core, check_next_cell_3);
  tcase_add_test(tc_core, check_next_cell_4);
  tcase_add_test(tc_core, check_next_cell_5);
  tcase_add_test(tc_core, check_next_cell_6);
  tcase_add_test(tc_core, check_next_cell_7);
  tcase_add_test(tc_core, check_next_cell_8);
  tcase_add_test(tc_core, check_next_cell_9);

  tcase_add_test(tc_core, can_move_0);  //   can_move
  tcase_add_test(tc_core, can_move_1);
  tcase_add_test(tc_core, can_move_2);
  tcase_add_test(tc_core, can_move_3);
  tcase_add_test(tc_core, can_move_4);
  tcase_add_test(tc_core, can_move_5);
  tcase_add_test(tc_core, can_move_6);

  tcase_add_test(tc_core, move_figure_base_0);  // move_figure_base
  tcase_add_test(tc_core, move_figure_base_1);
  tcase_add_test(tc_core, move_figure_base_2);
  tcase_add_test(tc_core, move_figure_base_3);
  tcase_add_test(tc_core, move_figure_base_4);
  tcase_add_test(tc_core, move_figure_base_5);

  tcase_add_test(tc_core, move_figure_0);  // move_figure_base
  tcase_add_test(tc_core, move_figure_1);
  tcase_add_test(tc_core, move_figure_2);

  suite_add_tcase(s, tc_core);
  return s;
}