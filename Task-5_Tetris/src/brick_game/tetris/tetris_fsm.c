/*!
@file
*/

#include "tetris_backend.h"

/*!
@brief Game pointer helper

Static object with the game info
@return Game object pointer
*/
TetrisInfo_t *get_game(void) {
  static TetrisInfo_t game = {DEFAULT_INFO};
  return &game;
}

/*!
@brief User input interpreter

Function for communicating with the frontend.
Interprets user input
*/
void userInput(UserAction_t action, bool hold) {
  TetrisInfo_t *g = get_game();
  if (action == Terminate) {
    remove_field(g);
  } else if (action == Pause) {
    pause_unpause(g);
  } else if (g->pause != PAUSE && g->pause != NO_MEMORY) {
    tetris_fsm(g, action, hold);
  }
  return;
}

/*!
@brief Updating game state

Function for communicating with the frontend.
Passes the updated filds back to the frontend
@return Game object info
*/
GameInfo_t updateCurrentState(void) {
  TetrisInfo_t *g = get_game();
  GameInfo_t output = {0};
  if (g->field != NULL) {
    output.field = &g->field[H_SPAWN];
  }
  if (g->next != NULL) {
    output.next = g->next;
  }
  output.score = g->score;
  output.high_score = g->high_score;
  output.level = g->level;
  output.speed = g->speed;
  output.pause = g->pause;
  return output;
}

/*!
@brief Game pausing

Pausing and unpausing the game
*/
void pause_unpause(TetrisInfo_t *g) {
  if (g->pause == PLAY) {
    g->pause = PAUSE;
  } else if (g->pause == PAUSE) {
    g->pause = PLAY;
  }
  return;
}

/*!
@brief Tetris finite state machine

Main FSM function
Has 5 states (start, spawn, fall, collision, game over)
Takes user actions as a parameter
*/
void tetris_fsm(TetrisInfo_t *g, UserAction_t action, bool hold) {
  switch (g->state) {
    case tetris_start:
      on_start(g, action);
      break;
    case tetris_spawn:
      on_spawn(g);
      break;
    case tetris_fall:
      on_fall(g, action, hold);
      break;
    case tetris_collision:
      on_collision(g);
      break;
    case tetris_gameover:
      g->pause = GAME_OVER;
      if (action == Start) {
        g->state = tetris_start;
      }
      break;
  }
  return;
}

/*!
@brief Start state function

If the game is started, it allocates the memory if neered and assigns the values
If the game is restartedm it cleans the field and resets values
*/
void on_start(TetrisInfo_t *g, UserAction_t action) {
  if (action == Start && g->pause == STAND_BY) {
    if (init_field(g) == GAME_OK) {
      set_values(g);
    } else {
      g->pause = NO_MEMORY;
    }
  } else if (g->pause == GAME_OVER) {
    clean_field(g);
    set_values(g);
  }
  return;
}

/*!
@brief Spawn state function

Pastes next onto the field, generates another next figure and changes states
*/
void on_spawn(TetrisInfo_t *g) {
  paste_figure(g);
  generate_next(g);
  g->state = tetris_fall;
  return;
}

/*!
@brief Fall state function

Deals with figure movement, gravity (action = down, hold = true) and rotation
Changes state to collision when the figure bumps into something below
*/
void on_fall(TetrisInfo_t *g, UserAction_t action, bool hold) {
  bool move_bool = false;
  if (action == Action) {
    rotate_figure(g);
  } else {
    move_bool = move_figure(g, action, hold);
  }
  if (!move_bool && action == Down) {
    g->state = tetris_collision;
  }
  return;
}

/*!
@brief Collision state function

Deals with clearing rows, calculating the score and checking overflow
If after clearing rows the figure is suspended in the air, its dropped down
*/
void on_collision(TetrisInfo_t *g) {
  int row_count = 0;
  while ((row_count = clear_rows(g)) != 0) {
    increase_score(g, row_count);
    move_figure(g, Down, false);
  }
  if (overflow(g) || g->level == 11) {
    g->state = tetris_gameover;
  } else {
    g->state = tetris_spawn;
  }
  return;
}
