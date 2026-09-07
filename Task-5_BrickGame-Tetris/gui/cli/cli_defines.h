/*!
@file
*/

#define WIN_INIT(time)      \
  {                         \
    initscr();              \
    noecho();               \
    curs_set(0);            \
    keypad(stdscr, TRUE);   \
    timeout(time);          \
    scrollok(stdscr, TRUE); \
  }

#define DROPTIME_NS(a) (500 - (a - 1) * 60) * 1000000L

#define CONTROLS_FILE "assets/controls.txt"
#define GAME_LIST "generic", "tetris", "snake", "race",
#define GENERIC 0
#define TETRIS 1
#define SNAKE 2
#define RACE 3

#define K 2
#define RIM 1
#define PAD 1
#define GAP 1

#define DATA_Y1 0
#define DATA_X1 0
#define DATA_Y2 8 + RIM + (PAD) * 2
#define DATA_X2 12 + (RIM + PAD * 2) * K

#define PRINT_DATA(a, ...) \
  mvprintw(DATA_Y1 + RIM + PAD + a, DATA_X1 + (RIM + PAD) * K, __VA_ARGS__)

#define NEXT_Y2 DATA_Y2 + F_SIDE + RIM

#define FIELD_Y1 0
#define FIELD_X1 DATA_X2 + (GAP) * K + 1
#define FIELD_Y2 FIELD_Y1 + H + RIM
#define FIELD_X2 FIELD_X1 + (2 * RIM + W) * K - 1

#define CTRL_Y1 0
#define CTRL_X1 FIELD_X2 + (GAP) * K + 1
#define CTRL_X2 CTRL_X1 + 16 + (RIM + PAD) * K - 1

#define SMALL_WINDOW 1
#define NO_COLORS 2

#define PRINT_CENTER(arr, msg, a) \
  mvprintw(H / 2 + RIM + a, (CTRL_X2 - strlen(arr[msg])) / 2, "%s", arr[msg])

#define BLACK_SOLID 0
#define CYAN_SOLID 1
#define WHITE_SOLID 2
#define BLUE_SOLID 3
#define MAGENTA_SOLID 4
#define YELLOW_SOLID 5
#define RED_SOLID 6
#define GREEN_SOLID 7

#define YELLOW_CLEAR 8