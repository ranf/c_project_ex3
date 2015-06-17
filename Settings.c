#include "Settings.h"

Settings getSettings() {
	Settings settings = {.state = SETTINGS_STATE, .userColor = WHITE_COLOR, .minimaxDepth = 1, .playingColor = WHITE_COLOR};
	settings.board = initBoard();
	printMessage(ENTER_SETTINGS_MESSAGE);
	while (settings.state == SETTINGS_STATE) {
		char* cmd = readString();
		switch (getCmdType(cmd)) {
			case MINIMAX_DEPTH:
				settings = setMinimaxDepth(settings, cmd);
				break;
			case USER_COLOR:
				settings = setUserColor(settings,cmd);
				break;
			case CLEAR:
				clearBoard(settings.board);
				break;
			case RM:
				removeDisc(settings.board, cmd);
				break;
			case SET:
				setDisc(settings.board, cmd);
				break;
			case PRINT:
				printBoard(settings.board);
				break;
			case QUIT:
				settings.state = TERMINATE_STATE;
				break;
			case START:
				startBoard(settings);
				break;
			default:
				printMessage(ILLEGAL_COMMAND);
				break;
		}
		free(cmd);
	}
	return settings;
}

Settings setMinimaxDepth(Settings settings, char* cmd) {
	char* cmdValue = strchr(cmd, ' ');
	int minimaxDepth = atoi(cmdValue + 1);
	if (minimaxDepth <= 6 && minimaxDepth >= 1){
		settings.minimaxDepth = minimaxDepth;
	} else {
		printf(WRONG_MINIMAX_DEPTH);
	}
	return settings;
}

Settings setUserColor(Settings settings, char* cmd) {
	char* cmdValue = strchr(cmd, ' ');
	settings.userColor = strcmp(cmdValue, "white") ? WHITE_COLOR : BLACK_COLOR;
	return settings;
}

void removeDisc(char** board, char* cmd) {
	char* cmdValue = strchr(cmd, ' ');
	Position p = parsePosition(cmdValue + 1);
	if (validPosition(p))
		board[p.x][p.y] = EMPTY;
	else
		printf("Invalid on the board\n");
}

void startBoard (Settings settings) {
	if (emptyBoard(settings.board) || oneColorBoard(settings.board) ||
		moreThen20Discs(settings.board))
		printMessage(WROND_BOARD_INITIALIZATION);
	else
		settings.state = GAME_STATE;
}

void setDisc(char** board, char* cmd) {
	char* cmdValue = strchr(cmd, ' ');
	Position p = parsePosition(cmdValue + 1);
	if (validPosition(p)) {
		char v = EMPTY;
		cmdValue  = strchr(cmdValue,' ') + 1;
		char pieceType = strchr(cmdValue, ' ') + 1;
	 	if(startsWith(cmdValue, "white "))
	 		v = isKing(pieceType) ? WHITE_K : WHITE_M;
	 	else
	 		v = isKing(pieceType) ? BLACK_K : BLACK_M;
	 	board[p.x][p.y] = v;
	 } else {
	 	printf("Invalid on the board\n");
	 }
}

int getCmdType(char* cmdString) {
	// for all commands command+anything will be consider valid (rmdsfnson for example)
	// need to check there is space for commands with argumets and string equals for other commands
	if(startsWith(cmdString, "minimax_depth "))
		return MINIMAX_DEPTH;
	if(startsWith(cmdString, "user_color "))
		return USER_COLOR;
	if(strcmp(cmdString, "clear") == 0)
		return CLEAR;
	if(startsWith(cmdString, "rm "))
		return RM;
	if(startsWith(cmdString, "set "))
		return SET;
	if(strcmp(cmdString, "print") == 0)
		return PRINT;
	if(strcmp(cmdString, "quit") == 0)
		return QUIT;
	if(strcmp(cmdString, "start") == 0)
		return START;
	return UNKNOWN_CMD;
}