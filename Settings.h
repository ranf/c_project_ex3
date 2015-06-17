#ifndef SETTINGS_
#define SETTINGS_

#include "Board.h"
#include "Position/Position.h"
#include "Utils.h"
#include <stdbool.h>
#include <string.h>

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
#define UNKNOWN_CMD 11

#define ENTER_SETTINGS_MESSAGE "Enter game settings:\n"
#define WRONG_MINIMAX_DEPTH "Wrong value for minimax depth. The value should be between 1 to 6\n"
#define WROND_BOARD_INITIALIZATION "Wrong board initialization\n"
#define ILLEGAL_COMMAND "Illegal command, please try again\n"

typedef struct {
	int state;
	int minimaxDepth;
	int userColor;
	int playingColor;
	char** board;
} Settings;

Settings getSettings();
Settings setMinimaxDepth(Settings settings, char* cmd);
Settings setUserColor (Settings settings, char* cmd);
void removeDisc(char** board, char* cmd);
void setDisc(char** board, char* cmd);
void startBoard (Settings settings);
int getCmdType(char* cmdString);
int charToInt(char cmd);

#endif