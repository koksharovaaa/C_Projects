/*!
@file
*/

#ifndef TETRIS_BACKEND_H
#define TETRIS_BACKEND_H
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "common.h"

#define TETRIS_SCORES "assets/tetris_scores.txt"

#define H_TOTAL 22
#define H_SPAWN H_TOTAL - H
#define DEFAULT_INFO {NULL_F}, 0, 0, 0, 0, 0, 0, 1, 10, 0

#define F_COUNT 7

/*!
Tetris figures
*/
#define I 1, 0, 0, 0x0F00  // 0x2222 0x0F00 0x4444
#define L 2, 0, 0, 0x02E0  // 0x4460 0x0E80 0xС440
#define J 3, 0, 0, 0x08E0  // 0x6440 0x0E20 0x44C0
#define T 4, 0, 0, 0x04E0  // 0x0464 0x0E40 0x4C40
#define O 5, 0, 0, 0x0660  // no change
#define Z 6, 0, 0, 0x0C60  // 0x2640 0x0C60 0x4C80
#define S 7, 0, 0, 0x06C0  // 0x4620 0x06C0 0x8C40

#define ID_I 1
#define ID_O 5

#define NULL_F 0, 0, 0, 0

/*!
@enum game_state_t
@brief Tetris FSM states
*/
typedef enum {
  tetris_start,
  tetris_spawn,
  tetris_fall,
  tetris_collision,
  tetris_gameover
} game_state_t;

/*!
@struct figure_t
@brief Falling figure struct

Struct for the moving figure, 30 bits total
*/
typedef struct {
  unsigned int id : 3;     ///< number that corresponds to figure color
  int y : 6;               ///< top coordinate
  int x : 5;               ///< left coordinate
  unsigned int mask : 16;  // F_SIDE x F_SIDE mask of the figure
} figure_t;

/*!
@struct TetrisInfo_t
@brief Tetris game info struct.

Expanded GameInfo_t struct.
Added fields:
- figure_t figure
- game_state_t state;
- int line_count;
*/
typedef struct {
  figure_t figure;     ///< Current falling figure
  game_state_t state;  ///< Tetris FSM state
  int line_count;      ///< Cleared line count
  int **field;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} TetrisInfo_t;

TetrisInfo_t *get_game(void);

void pause_unpause(TetrisInfo_t *g);

void tetris_fsm(TetrisInfo_t *g, UserAction_t action, bool hold);
void on_start(TetrisInfo_t *g, UserAction_t action);
void on_spawn(TetrisInfo_t *g);
void on_fall(TetrisInfo_t *g, UserAction_t action, bool hold);
void on_collision(TetrisInfo_t *g);

int init_field(TetrisInfo_t *g);
void set_values(TetrisInfo_t *g);
void clean_field(TetrisInfo_t *g);
void remove_field(TetrisInfo_t *g);

bool overflow(const TetrisInfo_t *g);
int clear_rows(TetrisInfo_t *g);
void increase_score(TetrisInfo_t *g, int removed_count);

void load_score(TetrisInfo_t *g);
void save_score(const TetrisInfo_t *g);

int get_mask(int row, int col, figure_t f);
void set_mask(int row, int col, int value, figure_t *f);
void cut_mask(int i, figure_t *f);

int generate_next(TetrisInfo_t *g);
void paste_figure(TetrisInfo_t *g);
bool rotate_figure(TetrisInfo_t *g);

bool move_figure(TetrisInfo_t *g, UserAction_t action, bool hold);
bool can_move(TetrisInfo_t *g, UserAction_t action);
bool check_next_cell(const TetrisInfo_t *g, UserAction_t action, int y, int x);
void move_figure_base(TetrisInfo_t *g, UserAction_t action);

#endif