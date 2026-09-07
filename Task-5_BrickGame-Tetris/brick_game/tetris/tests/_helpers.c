#include "tests.h"

void h_set_parameters(TetrisInfo_t *G) {
  G->figure = (figure_t){5, 0, 3, 0x0660};
  G->state = tetris_fall;
  G->line_count = 5;
  G->high_score = 100;
  G->score = 750;
  G->level = 1;
  G->speed = 20;
  G->pause = PLAY;
  return;
}

// Set next
void h_set_next(TetrisInfo_t *G, int index) {
  figure_t all[] = {{I}, {L}, {J}, {T}, {O}, {Z}, {S}};
  for (int i = 0; i < F_SIDE; i++) {
    for (int j = 0; j < F_SIDE; j++) {
      if (get_mask(i, j, all[index - 1])) {
        G->next[i][j] = all[index - 1].id;
      } else {
        G->next[i][j] = 0;
      }
    }
  }
  return;
}

// Fill field
void h_fill_field(TetrisInfo_t *G, int value) {
  for (int i = 0; i < H_TOTAL; i++) {
    for (int j = 0; j < W; j++) {
      G->field[i][j] = value;
    }
  }
  return;
}

// Are figures equal
int h_figures_eq(figure_t a, figure_t b) {
  return (a.id == b.id && a.y == b.y && a.x == b.x && a.mask == b.mask);
}

// Are field parameters equal
int h_parameters_eq(TetrisInfo_t *A, TetrisInfo_t *B) {
  return (h_figures_eq(A->figure, B->figure) && A->state == B->state &&
          A->line_count == B->line_count && A->score == B->score &&
          A->high_score == B->high_score && A->level == B->level &&
          A->speed == B->speed && A->pause == B->pause);
}

// Are fields equal
int h_fields_eq(TetrisInfo_t *A, TetrisInfo_t *B) {
  int result = SUCCESS;
  for (int i = 0; i < H_TOTAL && result; i++) {
    for (int j = 0; j < W && result; j++) {
      if (A->field[i][j] != B->field[i][j]) {
        result = FAILURE;
      }
    }
  }
  return result;
}

// Checks if next is a valid figure
int h_check_next(TetrisInfo_t *G) {
  int result = FAILURE;
  figure_t all[] = {{I}, {L}, {J}, {T}, {O}, {Z}, {S}};
  for (int index = 0; index < F_COUNT && !result; index++) {
    result = SUCCESS;
    for (int i = 0; i < F_SIDE && result; i++) {
      for (int j = 0; j < F_SIDE && result; j++) {
        if ((!!G->next[i][j]) ^ get_mask(i, j, all[index])) {
          result = FAILURE;
        }
      }
    }
  }
  return result;
}

// Is the field empty
int h_is_field_empty(TetrisInfo_t *G) {
  int result = SUCCESS;
  for (int i = 0; i < H_TOTAL && result; i++) {
    for (int j = 0; j < W && result; j++) {
      if (G->field[i][j] != 0) {
        result = FAILURE;
      }
    }
  }
  return result;
}

// Scans a field from file
void h_get_field(TetrisInfo_t *G, FILE **file, const char *test) {
  char buffer[128] = {0};
  bool test_flag = false;

  while (!test_flag && fgets(buffer, sizeof(buffer), *file) != NULL) {
    if (strstr(buffer, test)) {
      test_flag = true;
    }
  }

  for (int i = 0; i < H_TOTAL; i++) {
    if (fgets(buffer, sizeof(buffer), *file) != NULL) {
      int j = 0;
      for (char *ptr = buffer; *ptr; ptr++) {
        if (isdigit(*ptr)) {
          G->field[i][j++] = *ptr - '0';
        } else if (*ptr == '-') {
          G->field[i][j++] = 0;
        }
      }
    }
  }

  return;
}

// Compares the field to the field from file
int h_test_field(TetrisInfo_t *G, FILE **file) {
  int result = SUCCESS;
  char buffer[128] = {0};
  bool test_flag = false;

  while (!test_flag && fgets(buffer, sizeof(buffer), *file) != NULL) {
    if (strstr(buffer, "check")) {
      test_flag = true;
    }
  }
  if (!test_flag) {
    result = NO_TEST;  //
  }
  for (int i = 0; i < H_TOTAL && result; i++) {
    if (fgets(buffer, sizeof(buffer), *file) != NULL) {
      int j = 0;
      for (char *ptr = buffer; *ptr; ptr++) {
        if (((*ptr == '-' || *ptr == '0') && G->field[i][j] != 0) ||
            (isdigit((unsigned char)*ptr) && G->field[i][j] != *ptr - '0')) {
          result = FAILURE;
        }
        if (isdigit((unsigned char)*ptr) || *ptr == '-') {
          j++;
        }
      }
    }
  }
  return result;
}

// int h_next_eq(TetrisInfo_t *A, TetrisInfo_t *B) {
//   int result = SUCCESS;
//   for (int i = 0; i < H_TOTAL && result; i++) {
//     for (int j = 0; j < W && result; j++) {
//       if (A->field[i][j] != B->field[i][j]) {
//         result = FAILURE;
//       }
//     }
//   }
//   return result;
// }