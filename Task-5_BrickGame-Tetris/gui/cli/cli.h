/*!
@file
*/

#ifndef BRICK_CLI_H
#define BRICK_CLI_H

#include <ctype.h>
#include <locale.h>
#include <ncurses.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "cli_defines.h"
#include "common.h"

typedef enum {
  tetris_msg,
  standby_msg,
  pause_msg,
  resume_msg,
  gameover_msg,
  level_msg,
  overflow_msg,
  quit_msg,
  restart_msg,
  msg_count
} msg_id;

typedef enum {
  quit_err,
  small_window_err,
  no_colors_err,
  no_memory_err,
  err_count
} err_id;

void assign_colors(void);
bool valid_terminal(void);
void print_error(int err_code);

bool get_user_input(UserAction_t *action, bool *hold);
void print_game(const GameInfo_t *game, int game_id);

#endif
