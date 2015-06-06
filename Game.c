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
		MoveList moves = getMoves();
		printAllMoves(moves);
		freeMoves(moves);
		settings = userTurn(settings);
	} else if (strcmp(cmdType, "quit")) {
		settings.state = TERMINATE_STATE;
	} else {
		printMessage(ILLEGAL_COMMAND);
		settings = userTurn(settings);
	}
	return settings;
}

Settings moveCommand(Settings settings, char* moveString) {
	Move move = parseMove(moveString);
	if(validateMove(&move, settings.board, settings.userColor)){
		settings.board = applyMove(settings.board, move);
		freeMove(move);
		return settings;
	}
	freeMove(move);
	return userTurn(settings);
}

Board applyMove(Board board, Move move) {
	char movingDisc = getValueInPosition(move.from, board);
	board = setBoard(board, move.from, EMPTY);
	PositionList* head = move.eatenAt;
	while(head){
		board = setBoard(board, head->data, EMPTY);
		head = head->next;
	}
	head = move.to;
	while(head->next){
		head = head->next;
	}
	board = setBoard(board, head->data, movingDisc);
	return board;
}

char* getIndexOfFirstSpaceOrEnd(char* str) {
	int i = 0;
	while (str[i] != '\0' && str[i] != ' ') {
		i++;
	}
	return i;
}