#include "Game.h"

void startGame(Settings settings) {
	int playingColor = WHITE_COLOR;
	while(settings.state == GAME_STATE) {
		settings = settings.userColor == playingColor
			? userTurn(settings)
			: computerTurn(settings);
		if(settings.state == TERMINATING_STATE)
				return;
		printBoard(settings.board);
		if(gameEnded()) {
			xWon();
			settings.state = TERMINATING_STATE;
		}
		playingColor = otherPlayer(playingColor);
	}
}

char computerTurn(Settings settings) {
	//Move computerMove = findBestMove(board, minimaxDepth, computerColor);
	//applyMove(board, computerMove);
}

Settings userTurn(Settings settings) {
	printMessage(ENTER_YOUR_MOVE);
	char cmd[MAX_COMMAND_LENGTH];
	scanf("%s",cmd);
	char* cmdType = getStringUntilFirstSpace(cmd);
	if (strcmp(cmdType, "move")) {
		settings = moveCommand(settings, cmd + 5);
	} else if (strcmp(cmdType, "get_moves")) {
		MoveList moves = getMoves();
		printAllMoves(moves);
		freeMoves(moves);
		settings = userTurn(settings);
	} else if (strcmp(cmdType, "quit")) {
		settings.state = TERMINATING_STATE;
	} else {
		invalidCommand();
		settings = userTurn(settings);
	}
	return settings;
}

Settings moveCommand(Settings settings, char* moveString) {
	Move move = parseMove(moveString);
	if(validateMove(&move)){
		Settings s = applyMove(settings, move);
		freeMove(move);
		return s;
	}
	freeMove(move);
	return userTurn(settings);
}

Settings applyMove(Settings settings, Move move) {
	Board board = settings.board;
	char movingDisc = getValueInPosition(board, move.from);
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
	settings.board = setBoard(board, head->data, movingDisc);
	return board;
}

