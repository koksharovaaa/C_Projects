/*!
@file
*/

#include "cli.h"

/*!
@brief Action interpreter for user input
Takes a char and finds a corresponding action
@return Action
*/
UserAction_t action_interpreter(int ch) {
  UserAction_t action = -1;
  switch (ch) {
    case KEY_LEFT:
      action = Left;
      break;
    case KEY_RIGHT:
      action = Right;
      break;
    case KEY_DOWN:
      action = Down;
      break;
    case KEY_UP:
      action = Up;
      break;
    case ' ':
      action = Action;
      break;
    case 'p':
      action = Pause;
      break;
    case 'q':
      action = Terminate;
      break;
    case '\n':
      action = Start;
      break;
  }
  return action;
}

/*!
@brief Function for parsing user input
@param action - user input for the tetris backend
@param hold - relevant for movement actions
@return input status (valid or not)
*/
bool get_user_input(UserAction_t *action, bool *hold) {
  bool valid_input = false;
  static int last = ERR;
  int ch = getch();
  ch = tolower(ch);
  if (ch == '\n' || ch == 'p' || ch == 'q' || ch == ' ') {
    *action = action_interpreter(ch);
    *hold = false;
    valid_input = true;
  } else if (last == KEY_DOWN || last == KEY_UP || last == KEY_LEFT ||
             last == KEY_RIGHT) {
    *action = action_interpreter(last);
    if (ch == last) {
      *hold = true;
    } else {
      *hold = false;
    }
    valid_input = true;
  }
  last = ch;
  return valid_input;
}

/*!
@brief Clears ncurses field
Prints a rectangle of spaces, clearing the field
*/
void print_overlay(void) {
  for (int i = 0; i <= FIELD_Y2; i++) {
    for (int j = 0; j <= CTRL_X2; j++) {
      mvaddch(i, j, ' ');
    }
  }
  return;
}

/*!
@brief Prints a square cell on the screen
Prints a proportionally square cell (2x chars) in the terminal
Used for tetris figures and borders mainly
*/
void print_cell(int row, int col, int colour_id) {
  attron(COLOR_PAIR(colour_id));
  mvaddch(row, col, ' ');
  attroff(COLOR_PAIR(colour_id));
  return;
}

/*!
@brief Prints a frame for the menus and field
Prints a white rectangle using aquare cells
@param y1 top coordinate
@param x1 left coordinate
@param y2 bottom coordinate
@param x2 right coordinate
*/
void print_frame(int y1, int x1, int y2, int x2) {
  for (int i = x1; i <= x2; i++) {
    print_cell(y1, i, WHITE_SOLID);
    print_cell(y2, i, WHITE_SOLID);
  }
  for (int i = y1 + 1; i < y2; i++) {
    for (int j = 0; j < K; j++) {
      print_cell(i, x1 + j, WHITE_SOLID);
      print_cell(i, x2 - j, WHITE_SOLID);
    }
  }
  return;
}

/*!
@brief Prints an error message
The message is printed in the rop left corner of the screen
@param err_code internal code for the error
*/
void print_error(int err_code) {
  static const char *errors[err_count] = {
      [quit_err] = "Press Q to quit",
      [small_window_err] = "TERMINAL IS TOO SMALL",
      [no_colors_err] = "COLOURS ARE NOT SUPPORTED",
      [no_memory_err] = "NOT ENOUGH MEMORY"};
  mvprintw(0, 0, "ERROR %d", err_code);
  mvprintw(1, 0, "%s", errors[err_code]);
  mvprintw(2, 0, "%s", errors[quit_err]);
  refresh();
  UserAction_t action = Start;
  while (action != Terminate) {
    bool hold = false;
    get_user_input(&action, &hold);
  }
  return;
}

/*!
@brief Checks if the terminal can play games
To play tetris terminal should be able to fit all menus
And terminal must support colors
@return terminal validity status
*/
bool valid_terminal(void) {
  int result = true;
  if (LINES < FIELD_Y2 || COLS < CTRL_X2) {
    print_error(small_window_err);
    result = false;
  } else if (has_colors() == false) {
    print_error(no_colors_err);
    result = false;
  }
  return result;
}

/*!
@brief Prints an non-error message
The message is printed in the middle of the game screen
Cases in which the message is printed: startup, pause, gameover
*/
void print_message(const GameInfo_t *game) {
  print_frame(0, 0, FIELD_Y2, CTRL_X2);
  static const char *msgs[msg_count] = {
      [tetris_msg] = "TETRIS",
      [standby_msg] = "Press ENTER to start",
      [pause_msg] = "GAME PAUSED",
      [resume_msg] = "Press 'P' to resume",
      [gameover_msg] = "GAMEOVER",
      [level_msg] = "You completed all 10 levels!",
      [overflow_msg] = "You lost...",
      [quit_msg] = "Press Q to quit",
      [restart_msg] = "Press Enter to restart!"};
  attron(A_BOLD);
  switch (game->pause) {
    case STAND_BY:
      PRINT_CENTER(msgs, tetris_msg, -1);
      PRINT_CENTER(msgs, standby_msg, 0);
      PRINT_CENTER(msgs, quit_msg, 1);
      break;
    case PAUSE:
      PRINT_CENTER(msgs, pause_msg, -1);
      PRINT_CENTER(msgs, resume_msg, 0);
      PRINT_CENTER(msgs, quit_msg, 1);
      break;
    case GAME_OVER:
      PRINT_CENTER(msgs, gameover_msg, -2);
      if (game->level > 10) {
        PRINT_CENTER(msgs, level_msg, -1);
      } else {
        PRINT_CENTER(msgs, overflow_msg, -1);
      }
      PRINT_CENTER(msgs, quit_msg, 0);
      PRINT_CENTER(msgs, restart_msg, 1);
      break;
  }
  attroff(A_BOLD);
  return;
}

/*!
@brief Prints all the game parameters which are not the field
The parameters are printed in the right part of the screen
Parameters are shown inside a white frame
For tetris the next figure is also shown
*/
void print_game_data(const GameInfo_t *game, int game_id) {
  if (game_id == TETRIS) {
    print_frame(DATA_Y1, DATA_X1, NEXT_Y2, DATA_X2);
  } else {
    print_frame(DATA_Y1, DATA_X1, DATA_Y2, DATA_X2);
  }
  attron(A_BOLD);
  PRINT_DATA(0, "SCORE:");
  PRINT_DATA(2, "HIGH SCORE:");
  PRINT_DATA(4, "LEVEL:");
  PRINT_DATA(6, "SPEED:");
  if (game_id == TETRIS) {
    PRINT_DATA(9, "NEXT:");
  }
  attroff(A_BOLD);
  attron(COLOR_PAIR(YELLOW_CLEAR));
  PRINT_DATA(1, "%d", game->score);
  PRINT_DATA(3, "%d", game->high_score);
  PRINT_DATA(5, "%d", game->level);
  PRINT_DATA(7, "%d", game->speed);
  attroff(COLOR_PAIR(YELLOW_CLEAR));

  if (game_id == TETRIS) {
    int offset = 0;
    for (int i = 0; i < F_SIDE; i++) {
      if (!!game->next[i][0]) {
        offset = 1;
      }
    }
    for (int i = 0; i < F_SIDE; i++) {
      for (int j = 0; j < F_SIDE * K; j++) {
        print_cell(11 + RIM + i, DATA_X1 + (RIM + offset) * K + j,
                   game->next[i][j / K]);
      }
    }
  }
  return;
}

/*!
@brief Prints game field
The field is printed inside a white frame
*/
void print_game_field(const GameInfo_t *game) {
  print_frame(FIELD_Y1, FIELD_X1, FIELD_Y2, FIELD_X2);
  for (int i = 0; i < H; i++) {
    for (int j = 0; j < W * K; j++) {
      print_cell(FIELD_Y1 + RIM + i, FIELD_X1 + RIM * K + j,
                 game->field[i][j / K]);
    }
  }
  return;
}

/*!
@brief Scanning game controls from file
Function scans the controls from a file in the /assets
The controls are put into a small static array and passed to the print function
@return Parsing status
*/
bool load_game_controls(char arr[H][16], int game_id) {
  FILE *file = fopen(CONTROLS_FILE, "r");
  bool ctrls_found = false;
  if (file) {
    const char games[][16] = {GAME_LIST};
    char buffer[16] = {0};
    while (!ctrls_found && fgets(buffer, sizeof(buffer), file) != NULL) {
      if (strstr(buffer, games[game_id])) {
        ctrls_found = true;
      }
    }
    if (ctrls_found) {
      int i = 0;
      while (i < H && fgets(arr[i], sizeof(arr[0]), file) != NULL) {
        if (arr[i][0] == '\n') {
          arr[i][0] = '\0';
          break;
        }
        size_t l = strlen(arr[i]);
        if (l > 0 && arr[i][l - 1] == '\n') {
          arr[i][l - 1] = '\0';
        }
        i++;
      }
      ctrls_found = (i > 0);
    }
    fclose(file);
    file = NULL;
  }
  return ctrls_found;
}

/*!
@brief Prints game controls
Function calls load_game_controls function to parse controls once
Prints them repeatedly on the screen
*/
void print_game_controls(int game_id) {
  static char controls[H][16] = {'\0'};
  static bool print_ctrl = true;
  if (controls[0][0] == '\0' && print_ctrl) {
    print_ctrl = load_game_controls(controls, game_id);
  }
  if (print_ctrl) {
    int i = 0;
    while (i < H && controls[i][0] != '\0') {
      if (i < 2) {
        attron(A_BOLD);
      }
      mvprintw(CTRL_Y1 + RIM + PAD + i, CTRL_X1 + (RIM + PAD) * K, "%s",
               controls[i]);
      if (i < 2) {
        attroff(A_BOLD);
      }
      i++;
    }
    print_frame(CTRL_Y1, CTRL_X1, CTRL_Y1 + RIM * 2 + PAD + i, CTRL_X2);
  }
  return;
}

/*!
@brief Prints game screen
Generic function for all possible game pause states
Either prints a relevant message or the game field with controls and parameters
*/
void print_game(const GameInfo_t *game, int game_id) {
  static int last_pause_state = -1;
  if (game->pause == PLAY || last_pause_state != game->pause) {
    print_overlay();
    if (game->pause == PLAY) {
      print_game_data(game, game_id);
      print_game_field(game);
      print_game_controls(game_id);
    } else {
      print_message(game);
    }
    refresh();
  }
  last_pause_state = game->pause;
  return;
}

/*!
@brief Function for assigning ncurses colors
Assigns colors using predefined macros
*/
void assign_colors(void) {
  start_color();
  init_pair(BLACK_SOLID, COLOR_BLACK, COLOR_BLACK);
  init_pair(CYAN_SOLID, COLOR_CYAN, COLOR_CYAN);
  init_pair(WHITE_SOLID, COLOR_WHITE, COLOR_WHITE);
  init_pair(BLUE_SOLID, COLOR_BLUE, COLOR_BLUE);
  init_pair(MAGENTA_SOLID, COLOR_MAGENTA, COLOR_MAGENTA);
  init_pair(YELLOW_SOLID, COLOR_YELLOW, COLOR_YELLOW);
  init_pair(RED_SOLID, COLOR_RED, COLOR_RED);
  init_pair(GREEN_SOLID, COLOR_GREEN, COLOR_GREEN);

  init_pair(YELLOW_CLEAR, COLOR_YELLOW, COLOR_BLACK);
  return;
}

// bool get_user_input(UserAction_t *action, bool *hold) {
//   bool valid_input = false;
//   static int last_ch = ERR;
//   int ch = getch();
// if (ch != ERR) {
// ch = tolower(ch);
//   *action = action_interpreter(ch);
//   if (*action == Start || *action == Terminate || *action == Pause) {
//     *hold = false;
//   } else {
//     timeout(10);
//     int ch_2 = getch();
//     timeout(50);
//     if (ch == ch_2) {
//       *hold = true;
//     } else {
//       *hold = false;
//     }
//   }
//   valid_input = true;
// }
//   return valid_input;
// }