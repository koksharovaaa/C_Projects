#include "cli.h"

void game_loop(int game_id);

int main(void) {
  WIN_INIT(60);
  setlocale(LC_ALL, "");
  if (valid_terminal()) {
    assign_colors();
    game_loop(TETRIS);
  }
  endwin();
  return 0;
}

void game_loop(int game_id) {
  UserAction_t action = Start;
  struct timespec last_drop = {0};
  timespec_get(&last_drop, TIME_UTC);
  while (action != Terminate) {
    GameInfo_t game = updateCurrentState();
    if (game.pause != NO_MEMORY) {
      print_game(&game, game_id);
    } else {
      print_error(no_memory_err);
      break;
    }
    bool hold = false;
    if (get_user_input(&action, &hold)) {
      userInput(action, hold);
    }
    struct timespec now = {0};
    timespec_get(&now, TIME_UTC);
    long passed_ns = (now.tv_sec - last_drop.tv_sec) * 1000000000L +
                     (now.tv_nsec - last_drop.tv_nsec);
    if (game.pause != STAND_BY && passed_ns >= DROPTIME_NS(game.level)) {
      userInput(Down, true);
      timespec_get(&last_drop, TIME_UTC);
    }
    napms(20);
  }
  return;
}
