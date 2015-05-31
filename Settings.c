#include "Settings.h"

Settings getSettings() {
	Settings settings = {.state = SETTINGS_STATE};
	char board[BOARD_SIZE][BOARD_SIZE];
	init_board(board);
	print_message(ENTER_SETTINGS_MESSAGE);
	while (settings.state == SETTINGS_STATE) {
		char* cmd = readString();
		char* cmdType = getStringUntilFirstSpace(cmd);
		if (strcmp(cmdType, "minimax_depth")) {

		} else if (strcmp(cmdType, "user_color")) {

		} else if (strcmp(cmdType, "clear")) {

		} else if (strcmp(cmdType, "rm")) {

		} else if (strcmp(cmdType, "set")) {

		} else if (strcmp(cmdType, "print")) {

		} else if (strcmp(cmdType, "quit")) {

		} else if (strcmp(cmdType, "start")) {

		} else {
			invalidCommand();
		} 
	}
	
	return settings;
}