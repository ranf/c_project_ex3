#ifndef SETTINGS_
#define SETTINGS_

#define SETTINGS_STATE 0
#define GAME_STATE 1
#define TERMINATE_STATE 2

#define ENTER_SETTINGS_MESSAGE "Enter game settings:\n"

typedef struct {
	int state;
	int minimaxDepth;
	int userColor;
	Board board;
} Settings;

Settings getSettings();

#endif