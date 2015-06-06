#include "Game.h"

void startGame(Settings settings) {
	int playingColor = WHITE_COLOR;
	while(settings.state == GAME_STATE) {
		settings = settings.userColor == playingColor
			? userTurn(settings)
			: computerTurn(settings);
		if(settings.state == TERMINATE_STATE)
				return;
		printBoard(settings.board);
		// if(gameEnded()) {
		// 	xWon();
		// 	settings.state = TERMINATING_STATE;
		// }
		playingColor = otherPlayer(playingColor);
	}
}

Settings computerTurn(Settings settings) {
	//Move computerMove = findBestMove(board, minimaxDepth, computerColor);
	//applyMove(board, computerMove);
}

Settings userTurn(Settings settings) {
	printMessage(ENTER_YOUR_MOVE);
	char cmd[MAX_COMMAND_LENGTH];
	scanf("%s", cmd);
	int endOfFirstWord = getIndexOfFirstSpaceOrEnd(cmd);
	if (strncmp(cmd, "move", endOfFirstWord)) {
		settings = moveCommand(settings, cmd + 5);
	} else if (strcmp(cmd, "get_moves")) {
		MoveList* moves = getMoves(settings.board, settings.userColor);
		printAllMoves(moves);
		freeMoves(moves);
		settings = userTurn(settings);
	} else if (strcmp(cmd, "quit")) {
		settings.state = TERMINATE_STATE;
	} else {
		printMessage(ILLEGAL_COMMAND);
		settings = userTurn(settings);
	}
	return settings;
}

Settings moveCommand(Settings settings, char* moveString) {
	Move* move = parseMove(moveString);
	if(validateMove(move, settings.board, settings.userColor)){
		settings.board = applyMove(settings.board, move);
		freeMove(move);
		return settings;
	}
	freeMove(move);
	return userTurn(settings);
}

char** applyMove(char** board, Move* move) {
	char movingDisc = getValueInPosition(move->from, board);
	char** tempBoard = setBoard(board, move->from, EMPTY);
	freeBoard(board);
	board = tempBoard;
	PositionList* head = move->eatenAt;
	while(head){
		tempBoard = setBoard(board, head->data, EMPTY);
		freeBoard(board);
		board = tempBoard;
		head = head->next;
	}
	head = move->to;
	while(head->next){
		head = head->next;
	}
	tempBoard = setBoard(board, head->data, movingDisc);
	freeBoard(board);
	board = tempBoard;
	return board;
}

void printAllMoves(MoveList* moves) {
	MoveList* head = moves;
	while(head) {
		printMove(head->data);
		head = head->next;
	}
}

void printMove(Move* move) {
	char result[MAX_COMMAND_LENGTH];
	result[0] = '\0';
	char tempPositionString[6];
	positionToString(move->from, tempPositionString);
	strcat(result, tempPositionString);
	strcat(result, " to ");
	PositionList* dest = move->to;
	while(dest){
		positionToString(dest->data, tempPositionString);
		strcat(result, tempPositionString);
		dest= dest->next;
	}
	printf("%s\n", result);
}

int getIndexOfFirstSpaceOrEnd(char* str) {
	int i = 0;
	while (str[i] != '\0' && str[i] != ' ') {
		i++;
	}
	return i;
}