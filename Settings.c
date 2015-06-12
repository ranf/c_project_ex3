#include "Settings.h"

Settings getSettings() {
	Settings settings = {.state = SETTINGS_STATE, .userColor = WHITE_COLOR};
	settings.board = initBoard();
	printMessage(ENTER_SETTINGS_MESSAGE);
	while (settings.state == SETTINGS_STATE) {
		char* cmd = readString();
		switch (getCmdType(cmdString)) {
			case MINIMAX_DEPTH:
				settings = setMinimaxdepth(settings,cmd);
				break;
			case USER_COLOR:
				settings = setUserColor(settings,cmd);
				break;
			case CLEAR:
				clearBoard(settings.board);
				break;
			case RM:
				removeDisc(settings.board);
				break;
			case SET:
				setDisc(settings.board);
				break;
			case PRINT:
				printBoard(settings.board);
				break;
			case QUIT:
				settings.state = TERMINATE_STATE;
				break;
			case START:
				settings.state = GAME_STATE;
				break;
			default:
				printMessage(ILLEGAL_COMMAND);
				break;
		}
		free(cmdString);
	}
	return settings;
}

Settings setMinimaxdepth (Settings settings, char* cmd){
	char* cmdValue = strchr(cmd, ' ');
	int minimaxDepth = charToInt(*cmdValue);
	if (minimaxDepth <= 6 && minimaxDepth >= 1){
		settings.minimaxDepth = minimaxDepth;
	} else {
		printf(WRONG_MINIMAX_DEPTH);
	}
	return settings;
}

Settings setUserColor (Settings settings,char* cmd) {
	char* cmdValue = strchr(cmd, ' ');
	settings.userColor = strcmp(cmdValue, "white") ? WHITE_COLOR : BLACK_COLOR;
	return settings;
}

void removeDisc (char** board) {
	char* cmdValue = strchr(cmd, ' ');
	Position p = parsePosition(cmdValue);
	if (validPosition(p))
		setting.board[x][y] = EMPTY;
	else
		printf("Invalid on the board\n");
}

void setDisc (char** board, char* cmd) {
	char* cmdValue = strchr(cmd, ' ');
	char*[]  splitted =  split(cmdValue, " ");
	Position p = parsePosition(splitted[0]);
	if (validPosition(p)) {
		char v = EMPTY;
		if(isWhite(splitted[1]))
			v = isKing(splitted[2]) ? WHITE_K : WHITE_M;
		else
			v = isKing(splitted[2]) ? BLACK_K : BLACK_M;
		setting.board[x][y] = v;
	} else {
		printf("Invalid on the board\n");
	}
}

int getCmdType(char* cmdString) {
	if(startsWith(cmdString, "minimax_depth"))
		return MINIMAX_DEPTH;
	if(startsWith(cmdString, "user_color"))
		return USER_COLOR;
	if(startsWith(cmdString, "clear"))
		return CLEAR;
	if(startsWith(cmdString, "rm"))
		return RM;
	if(startsWith(cmdString, "set"))
		return SET;
	if(startsWith(cmdString, "print"))
		return PRINT;
	if(startsWith(cmdString, "quit"))
		return QUIT;
	if(startsWith(cmdString, "start"))
		return START;
	return PRINT_CMD;
}

bool startsWith(const char *str, const char *pre) {
	size_t lenpre = strlen(pre);
	size_t lenstr = strlen(str);
	return lenstr < lenpre ? false : strncmp(pre, str, lenpre) == 0;
}

int charToInt (char* cmd) {
	int val = (int)*cmd;
}

char[] split(char* str, char delim) {
	char*[3] splitted;
	char *token;
	token = strtok(str, delim);
	int i=0;
	while(token != NULL) {
		splitted[i] = token;
		i++;   
		token = strtok(NULL, s);
	}

	return splitted;
}
