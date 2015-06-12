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
#define PRINT_CMD 11

#define ENTER_SETTINGS_MESSAGE "Enter game settings:\n"
#define ILLEGAL_COMMAND "Illegal command, please try again\n"

typedef struct {
	int state;
	int minimaxDepth;
	int userColor;
	char** board;
} Settings;

Settings getSettings();
Settings setMinimaxDepth(Settings settings, char* cmd);
Settings setUserColor (Settings settings, char* cmd);
void removeDisc(char** board, char* cmd);
void setDisc(char** board, char* cmd);

int getCmdType(char* cmdString);
bool startsWith(const char *str, const char *pre);
int charToInt(char* cmd);

#endif