#ifndef SETTINGS_
#define SETTINGS_

#define SETTINGS_STATE 0
#define GAME_STATE 1
#define TERMINATE_STATE 2

#define ENTER_SETITNGS_MESSAGE "Enter game settings:\n"


typedef struct {
	int state;
} Settings;

Settings getSettings();

#endif