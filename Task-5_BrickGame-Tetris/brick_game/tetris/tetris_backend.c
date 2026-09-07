/*!
@file
*/

#include "tetris_backend.h"

/*!
@brief Memory allocation for the game

Allocates memory for the field and the next figure.
Allocates memory for the next figure.
@return Memory allocation status
*/
int init_field(TetrisInfo_t *g) {
  int result = GAME_OK;
  g->field = calloc(H_TOTAL * W * sizeof(int) + H_TOTAL * sizeof(int *), 1);
  if (g->field == NULL) {
    result = GAME_ERR;
  } else {
    int *ptr = (int *)(g->field + H_TOTAL);
    for (int i = 0; i < H_TOTAL; i++) {
      g->field[i] = ptr + W * i;
    }
  }
  if (result == GAME_OK) {
    g->next = calloc(F_SIDE * F_SIDE * sizeof(int) + F_SIDE * sizeof(int *), 1);
    if (g->next == NULL) {
      free(g->field);
      result = GAME_ERR;
    } else {
      int *ptr = (int *)(g->next + F_SIDE);
      for (int i = 0; i < F_SIDE; i++) {
        g->next[i] = ptr + F_SIDE * i;
      }
    }
  }
  return result;
}

/*!
@brief Setting the values

Sets values for the game parameters.
Generates next figure.
Loads the highest score from file if it exists
*/
void set_values(TetrisInfo_t *g) {
  g->figure = (figure_t){NULL_F};
  g->state = tetris_spawn;
  g->line_count = 0;
  g->score = 0;
  g->level = 1;
  g->speed = 10;
  g->pause = PLAY;
  generate_next(g);
  load_score(g);
  return;
}

/*!
@brief Function for cleaning the field

Zeroes the field when restarting the game
Saves the score between games
*/
void clean_field(TetrisInfo_t *g) {
  save_score(g);
  for (int i = 0; i < H_TOTAL; i++) {
    for (int j = 0; j < W; j++) {
      g->field[i][j] = 0;
    }
  }
  return;
}

/*!
@brief Function for removing the game field

Zeroes the game parameters or puts them into an initial state.
Frees up the memory used by the game.
Saves high score into the file.
*/
void remove_field(TetrisInfo_t *g) {
  if (g->field != NULL) {
    free(g->field);
    g->field = NULL;
  }
  if (g->next != NULL) {
    free(g->next);
    g->next = NULL;
  }
  save_score(g);
  g->figure = (figure_t){NULL_F};
  g->state = tetris_start;
  g->line_count = 0;
  g->high_score = 0;
  g->score = 0;
  g->level = 0;
  g->speed = 0;
  g->pause = STAND_BY;
  return;
}

/*!
@brief Function for checking overflow

Checks if the field is overflowing.
@return Overflow status
*/
bool overflow(const TetrisInfo_t *g) {
  bool overflow = false;
  for (int i = 0; i < W; i++) {
    if (g->field[H_SPAWN][i] != 0) {
      overflow = true;
    }
  }
  return overflow;
}

/*!
@brief Function for clearing rows

Collapses filled rows and counts them
@return Amount of collapsed rows
*/
int clear_rows(TetrisInfo_t *g) {
  int removed_count = 0;
  for (int i = 0; i < H_TOTAL; i++) {
    bool remove_row = true;
    for (int j = 0; j < W && remove_row; j++) {
      if (!g->field[i][j]) {
        remove_row = false;
      }
    }
    if (remove_row) {
      removed_count++;
      if (i - g->figure.y >= 0 && i - g->figure.y < F_SIDE &&
          (g->figure.mask & 0xF000u >> ((i - g->figure.y) * F_SIDE))) {
        // && (g->figure.mask & 0xF000u >> ((i - g->figure.y) * F_SIDE))
        cut_mask(i - g->figure.y, &(g->figure));
      }
      for (int j = i; j > 0; j--) {
        for (int k = 0; k < W; k++) {
          g->field[j][k] = g->field[j - 1][k];
        }
      }
      for (int j = 0; j < W; j++) {
        g->field[0][j] = 0;
      }
    }
  }
  return removed_count;
}

/*!
@brief Increasing score

Calculates the score based on the amount of removed lines
Changes level, speed and high score accordingly
*/
void increase_score(TetrisInfo_t *g, int removed_count) {
  g->score += ((1 << removed_count) - 1) * 100;
  g->line_count += removed_count;
  g->level = 1 + g->score / 600;
  g->speed = g->level * 10;
  if (g->score > g->high_score) {
    g->high_score = g->score;
  }
  return;
}

/*!
@brief Loading score

Loads score from a predefined file
*/
void load_score(TetrisInfo_t *g) {
  FILE *file = fopen(TETRIS_SCORES, "a+");
  if (file && !g->high_score) {
    fseek(file, 0, SEEK_SET);
    int c;
    while ((c = fgetc(file)) != EOF && isdigit(c)) {
      g->high_score = g->high_score * 10 + (c - '0');
    }
    if (!isdigit(c) && c != EOF) {
      g->high_score = 0;
    }
    fclose(file);
    file = NULL;
  }
}

/*!
@brief Saving score

Saves score to a predefined file
*/
void save_score(const TetrisInfo_t *g) {
  FILE *file = fopen(TETRIS_SCORES, "w");
  if (file) {
    fprintf(file, "%d", g->high_score);
    fclose(file);
    file = NULL;
  }
  return;
}

/*!
@brief Checking mask at (row, col)

Checks mask at (row, col) position.
0,0 is the first and top left element,
3,3 is the last and lower right
@return Mast status at the point
*/
int get_mask(int row, int col, figure_t f) {
  return (f.mask & (0x8000u >> (row * F_SIDE + col))) ? 1 : 0;
}

/*!
@brief Setting mask to a certain value (row, col)

Sets a certain value to the mask at (row, col)
*/
void set_mask(int row, int col, int value, figure_t *f) {
  if (value) {
    f->mask |= (0x8000u >> (row * F_SIDE + col));
  } else {
    f->mask &= ~(0x8000u >> (row * F_SIDE + col));
  }
  return;
}

/*!
@brief Cutting mask to a certain value (row, col)

Removes row mask at i and shifts the top parting of the mask down.
*/
void cut_mask(int i, figure_t *f) {
  unsigned int tmp = (f->mask & (0xFFFFu << (F_SIDE - i) * F_SIDE)) >> F_SIDE;
  f->mask &= (0xFFFFu >> (i + 1) * F_SIDE);
  f->mask |= tmp;
  return;
}

/*!
@brief Generates next figure

Generates next figure based on the figure structs (index and mask)
@return Next fugure index
*/
int generate_next(TetrisInfo_t *g) {
  static bool seed_flag = false;
  if (!seed_flag) {
    srand(time(NULL));
    seed_flag = true;
  }
  int index = rand() % F_COUNT;
  figure_t all[] = {{I}, {L}, {J}, {T}, {O}, {Z}, {S}};
  for (int i = 0; i < F_SIDE; i++) {
    for (int j = 0; j < F_SIDE; j++) {
      if (get_mask(i, j, all[index])) {
        g->next[i][j] = all[index].id;
      } else {
        g->next[i][j] = 0;
      }
    }
  }
  return index;
}

/*!
@brief Pasting figure

Copies the figure from the next figure and pastes it onto the field
Alse sets up a binary mask for the figure
*/
void paste_figure(TetrisInfo_t *g) {
  g->figure = (figure_t){0, 0, F_SIDE - 1, 0};
  for (int i = 0; i < F_SIDE; i++) {
    for (int j = 0; j < F_SIDE; j++) {
      if (g->next[i][j]) {
        g->field[i][j + g->figure.x] = g->next[i][j];
        if (!g->figure.id) {
          g->figure.id = g->next[i][j];
        }
        set_mask(i, j, 1, &(g->figure));
      }
    }
  }
  return;
}

/*!
@brief Rotating figure

Rotates the mask and checking if it fits (no wall kicks)
around a predefined pivot
@return Whether or not the figure was rotated
*/
bool rotate_figure(TetrisInfo_t *g) {
  bool rotation_bool = (g->figure.id == ID_O) ? false : true;
  figure_t new_position = g->figure;
  new_position.mask = 0;
  float pivot = (g->figure.id == ID_I) ? 1.5f : 1.0f;
  for (int i = 0; i < F_SIDE && rotation_bool; i++) {
    for (int j = 0; j < F_SIDE && rotation_bool; j++) {
      if (get_mask(i, j, g->figure)) {
        int k = (int)roundf(-i + 2 * pivot);
        set_mask(j, k, 1, &new_position);
        if (g->figure.x + k < 0 || g->figure.x + k >= W ||
            g->figure.y + j >= H ||
            (g->field[g->figure.y + j][g->figure.x + k] &&
             !get_mask(j, k, g->figure))) {
          rotation_bool = false;
        }
      }
    }
  }
  if (rotation_bool == true) {
    for (int i = 0; i < F_SIDE; i++) {
      for (int j = 0; j < F_SIDE; j++) {
        if (get_mask(i, j, g->figure)) {
          g->field[g->figure.y + i][g->figure.x + j] = 0;
        }
        if (get_mask(i, j, new_position)) {
          g->field[g->figure.y + i][g->figure.x + j] = g->figure.id;
        }
      }
    }
    g->figure.mask = new_position.mask;
  }
  return rotation_bool;
}

/*!
@brief Universak function for movement

Moves the figure in any direction and can drop it downwards
@return Whether or not the figure was moved
*/
bool move_figure(TetrisInfo_t *g, UserAction_t action, bool hold) {
  bool move_bool = true;
  bool drop = (action == Down && !hold) ? true : false;
  // on hold - slow drop, on press (!hold) - immediate drop
  do {
    if ((move_bool = can_move(g, action)) == true) {
      move_figure_base(g, action);
    }
  } while (move_bool && drop);
  return move_bool;
}

/*!
@brief Collision fucntion

Checks whether the figure can be moved in a needed direction
@return Whether or not the figure can be moved
*/
bool can_move(TetrisInfo_t *g, UserAction_t action) {
  bool move_bool = (g->figure.mask != 0) ? true : false;
  for (int i = 0; i < 4 && move_bool; i++) {
    for (int j = 0; j < 4 && move_bool; j++) {
      if (get_mask(i, j, g->figure) && check_next_cell(g, action, i, j)) {
        move_bool = false;
      }
    }
  }
  return move_bool;
}

/*!
@brief Neighbor detection function

Checks whether the neighboring cell is occupied (based on direction)
@return Whether or not the cell is occupied
*/
bool check_next_cell(const TetrisInfo_t *g, UserAction_t action, int y, int x) {
  int k_y = (action == Down) ? 1 : 0;
  int k_x = 0;
  if (action == Left) {
    k_x = -1;
  } else if (action == Right) {
    k_x = 1;
  }
  bool result = false;
  if (g->figure.x + x + k_x >= W || g->figure.x + x + k_x < 0 ||
      g->figure.y + y + k_y >= H_TOTAL ||
      (g->field[g->figure.y + y + k_y][g->figure.x + x + k_x] &&
       (y == F_SIDE - 1 || (x == 0 && k_x == -1) ||
        (x == F_SIDE - 1 && k_x == 1) ||
        !get_mask(y + k_y, x + k_x, g->figure)))) {
    result = true;
  }
  return result;
}

/*!
@brief Figure movement fucntion (no checks)

Base movement function (no collision check)
*/
void move_figure_base(TetrisInfo_t *g, UserAction_t action) {
  int k_y = (action == Down) ? 1 : 0;
  int k_x = 0;
  if (action == Left) {
    k_x = -1;
  } else if (action == Right) {
    k_x = 1;
  }

  int i = F_SIDE - 1;
  int j = (action == Left) ? 0 : F_SIDE - 1;
  while (i >= 0) {
    while (((action == Right || action == Down) && j >= 0) ||
           (action == Left && j < F_SIDE)) {
      if (get_mask(i, j, g->figure)) {
        g->field[g->figure.y + i][g->figure.x + j] = 0;
        g->field[g->figure.y + i + k_y][g->figure.x + j + k_x] = g->figure.id;
      }
      if (action == Left) {
        j++;
      } else {
        j--;
      }
    }
    j = (action == Left) ? 0 : F_SIDE - 1;
    i--;
  }

  if (action == Down) {
    g->figure.y++;
  } else if (action == Left) {
    g->figure.x--;
  } else if (action == Right) {
    g->figure.x++;
  }
  return;
}
