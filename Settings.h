#ifndef SETTINGS_
#define SETTINGS_

#include "Board.h"
#include "Position/Position.h"
#include "Utils.h"
#include <stdbool.h>

#define SETTINGS_STATE 0
#define GAME_STATE 1
#define TERMINATE_STATE 2

#define MINIMAX_DEPTH 3
#define USER_COLOR 4
#define CLEAR 5
#define RM 6
#define SET 7
#define PRINT 8
#define QUIT 9
#define START 10
#define PRINT_CMD 11

#define ENTER_SETTINGS_MESSAGE "Enter game settings:\n"

typedef struct {
	int state;
	int minimaxDepth;
	int userColor;
	char** board;
} Settings;

Settings getSettings();
void setMinimaxdepth (Settings settings);
void setUserColor (Settings settings);
void removeDisc (char** board);
void setDisc (char** board);


#endif