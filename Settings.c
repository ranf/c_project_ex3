#include "Settings.h"

Settings getSettings() {
	Settings settings = {.state = SETTINGS_STATE, .userColor = WHITE_COLOR};
	settings.board = initBoard();
	printMessage(ENTER_SETTINGS_MESSAGE);
	while (settings.state == SETTINGS_STATE) {
		char* cmd = readString();
		char* cmdType = getStringUntilFirstSpace(cmd);
		char* cmdValue = getStringAfterFirstSpace(cmd);
		if (strcmp(cmdType, "minimax_depth")) {
			int minimaxDepth = charToInt(*cmdValue);
			if (minimaxDepth <= 6 && minimaxDepth >= 1){
				settings.minimaxDepth = minimaxDepth;
			} else {
				printf(WRONG_MINIMAX_DEPTH);
			}
		} else if (strcmp(cmdType, "user_color")) {
			settings.userColor = strcmp(cmdValue, "white") ? WHITE_COLOR : BLACK_COLOR;
		} else if (strcmp(cmdType, "clear")) {
			clearBoard(settings.board);
		} else if (strcmp(cmdType, "rm")) {
			Position p = parsePosition(cmdValue);
			if (validPosition(p))
				setting.board[x][y] = EMPTY;
			else
				printf("Invalid on the board\n");
		} else if (strcmp(cmdType, "set")) {
			char* x = getStringUntilComma(cmdValue);
			char* y = getStringUntilFirstSpace(getStringAfterComma(cmdValue));
			char* a_b = getStringAfterFirstSpace(cmdValue);
			char* a = getStringUntilFirstSpace(a_b);
			char* b = getStringAfterFirstSpace(a_b);
			if (isPositionOnTheBoard(x,y)){
				char v = EMPTY;
				if(isWhite(a)) {
					v = isKing(b)? WHITE_K : WHITE_M;
				}else{
					v= isKing(b)? BLACK_K : BLACK_M;
				}
				setting.board[x][y] = v;
			}else{
				printf("Invalid on the board\n");
			}
		} else if (strcmp(cmdType, "print")) {
			printBoard(settings.board);
		} else if (strcmp(cmdType, "quit")) {
			settings.state = TERMINATE_STATE;
		} else if (strcmp(cmdType, "start")) {
			settings.state = GAME_STATE;
		} else {
			printMessage(ILLEGAL_COMMAND);
		} 
	}
	
	return settings;
}

bool isPositionOnTheBoard (char* x, char* y) {
	return ((x is not in the range a to j)
		or (y is not in the range 1 to 10)
		or (x,w=y is white))
}

