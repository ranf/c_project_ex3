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
	int minimaxDepth = charToInt(*(cmdValue+1));
	if (minimaxDepth <= 6 && minimaxDepth >= 1){
		settings.minimaxDepth = minimaxDepth;
	} else {
		printf(WRONG_MINIMAX_DEPTH);
	}
	return settings;
}
int charToInt(char cmd) {
	return cmd - '0';
}

Settings setUserColor(Settings settings, char* cmd) {
	char* cmdValue = strchr(cmd, ' ');
	settings.userColor = strcmp(cmdValue, "white") ? WHITE_COLOR : BLACK_COLOR;
	return settings;
}

void removeDisc(char** board, char* cmd) {
	char* cmdValue = strchr(cmd, ' ');
	Position p = parsePosition(cmdValue);
	if (validPosition(p))
		board[p.x][p.y] = EMPTY;
	else
		printf("Invalid on the board\n");
}
void startBoard (Settings settings){
	if (emptyBoard(settings.board))||(OneColorDisc(settings.board))||(moreThen20Disc(settings.board)))
		printMessage(WROND_BOARD_INITIALIZATION);
	else
		settings.state = GAME_STATE;
}
void setDisc(char** board, char* cmd) {
	char* cmdValue = strchr(cmd, ' ');
	char[]  splitted = split(cmdValue, " ");
	Position p = parsePosition(splitted[0]);
	if (validPosition(p)) {
		char v = EMPTY;
	 	if(isWhite(splitted[1]))
	 		v = isKing(splitted[2]) ? WHITE_K : WHITE_M;
	 	else
	 		v = isKing(splitted[2]) ? BLACK_K : BLACK_M;
	 	board[p.x][p.y] = v;
	 } else {
	 	printf("Invalid on the board\n");
	 }
}

int getCmdType(char* cmdString) {
	// for all commands command+anything will be consider valid (rmdsfnson for example)
	// need to check there is space for commands with argumets and string equals for other commands
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



 char[] split(char* str, char delim) {
 	char[3] splitted;
 	char token;
 	token = strtok(str, delim);
 	int i=0;
 	while(token != NULL) {
 		splitted[i] = token;
 		i++;   
 		token = strtok(NULL, s);
 	}

 	return splitted;
 }