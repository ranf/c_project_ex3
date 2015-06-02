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
		playingColor = playingColor == WHITE_COLOR
			? BLACK_COLOR
			: WHITE_COLOR;
	}
}

char computerTurn(Settings settings) {
	Move computerMove = findBestMove(board, minimaxDepth, computerColor);
	applyMove(board, computerMove);
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
		freeMoves(moves);//??
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
	return validateMove(move)
			? applyMove(settings, move)
			: userTurn(settings);
}

Settings parseMove(char* moveString) {
	char initialPosition[6];
	strncpy(initialPosition, moveString, 5);
	initialPosition[5] = '\0';
	Position from = parsePosition(initialPosition);
	PositionList* to = parseDestination(moveString + 9);//<x,y>_to_
	Move move = {.from = from, .to = to};
	return move;
}

bool validateMove(Move move, Settings settings, int player) {
	if(!validPosition(move.from) || !allPositionsAreValid(move.to)) {
		printMessage(INVALID_POSITION);
		return false;
	}
	if(!playerInPosition(move.from, settings.board, player) {
		printMessage(NO_DICS);
		return false;
	}
	if(!isLegalMove(move, settings, player)) {
		printMessage(ILLEGAL_MOVE);
		return false;
	}
	return true;
}

bool isLegalMove(Move move, Settings settings, int player) {
	MoveList* legalMoves = getMoves(settings, player);
	bool legal = movesContains(legalMoves, move);
	//free allocations
	return legal;
}

bool allPositionsAreValid(PositionList* head) {
	while(head) {
		if(!validPosition(head))
			return false;
		head = head->next;
	}
	return true;
}

int otherPlayer(int player) {
	return player == WHITE_COLOR
			? BLACK_COLOR
			: WHITE_COLOR
}

MoveList* getMoves(board_t board, int player) {
	MoveList result = NULL;
	for (int i = 0; i < BOARD_SIZE; ++i)
	for (int j = 0; j < BOARD_SIZE; ++i)
	{
		Position position = {.x = i, .y = j};
		if (playerInPosition(position, board, player)) {
			MoveList* discMoves = isKing(getValueInPosition(position, board))
				? getKingMoves(position, board, player)
				: getManMoves(position, board, player);
			if(discMoves.maxToEat > list.maxToEat){
				//free list
				list = discMoves;
			}else if(discMoves.maxToEat == list.maxToEat) {
				addMoves(list, discMoves);
			}else{
				//free discMoves
			}
		}
	}
	return list;
}

