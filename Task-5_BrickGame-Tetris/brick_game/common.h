/*!
@file
*/

#ifndef BRICK_COMMON_H
#define BRICK_COMMON_H

#include <stdbool.h>

#define GAME_OK 0
#define GAME_ERR 1

#define STAND_BY 0
#define PLAY 1
#define PAUSE 2
#define GAME_OVER 3
#define NO_MEMORY 4

#define H 20
#define W 10

#define F_SIDE 4

/*!
@enum UserAction_t
@brief All possible actions in brick game
*/
typedef enum {
  Start,      ///< Starts the game
  Pause,      ///< Turns pause on and off
  Terminate,  ///< Quits game, can be pressed at any point
  Left,       ///< Moves/turns the object left
  Right,      ///< Moves/turns the object right
  Up,         ///< Moves/turns the object up
  Down,       ///< Moves/turns the object down
  Action      ///< Key reserved for any special actions (ex. rotation in tetris)
} UserAction_t;

/*!
@struct GameInfo_t
@brief Game object that is used for every game in brick game
*/
typedef struct {
  int **field;     ///< dynamically allocated HxW field
  int **next;      ///< next spawned figure (relevant for tetris)
  int score;       ///< current score
  int high_score;  ///< highest recorded score (tracked in a file in assets/)
  int level;       ///< current level
  int speed;       ///< current game speed
  int pause;       ///< current state (stand by, play, pause, game over, no mem)
} GameInfo_t;

void userInput(UserAction_t action, bool hold);
GameInfo_t updateCurrentState(void);
#endif
