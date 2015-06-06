#ifndef SETTINGS_
#define SETTINGS_

#include "Board.h"

#define SETTINGS_STATE 0
#define GAME_STATE 1
#define TERMINATE_STATE 2

#define ENTER_SETTINGS_MESSAGE "Enter game settings:\n"

typedef struct {
	int state;
	int minimaxDepth;
	int userColor;
	char** board;
} Settings;

Settings getSettings();

#endif