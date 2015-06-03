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

Settings applyMove(Settings settings, Move move){
	board_t board = settings.board;
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

Settings parseMove(char* moveString) {
	char initialPosition[6];
	strncpy(initialPosition, moveString, 5);
	initialPosition[5] = '\0';
	Position from = parsePosition(initialPosition);
	PositionList* to = parseDestination(moveString + 9);//<x,y>_to_
	Move move = {.from = from, .to = to};
	return move;
}

bool validateMove(Move* move, Settings settings, int player) {
	if(!validPosition(move->from) || !allPositionsAreValid(move->to)) {
		printMessage(INVALID_POSITION);
		return false;
	}
	if(!playerInPosition(move->from, settings.board, player) {
		printMessage(NO_DICS);
		return false;
	}
	if(!moveInLegalMoves(move, settings, player)) {
		printMessage(ILLEGAL_MOVE);
		return false;
	}
	return true;
}


bool moveInLegalMoves(Move* move, Settings settings, int player) {
	MoveList* legalMoves = getMoves(settings, player);
	bool legal = moveInList(legalMoves, move);
	freeMoves(legalMoves);
	return legal;
}

bool moveInList(MoveList* list, Move* moveToFind){
	if(list==NULL)
		return false;
	MoveList* head = list;
	while(head){
		if(positionEquals(head->from, moveToFind->from) &&
			positionListEquals(next->to, moveToFind->to)){
			moveToFind->from = head->from;
			moveToFind->to = head->to;
			moveToFind->eatenAt = head->eatenAt;
			moveToFind->eatCount = head->eatCount;
			return true;
		}
		head = head->next;
	}
	return false;
}

int otherPlayer(int player) {
	return player == WHITE_COLOR
			? BLACK_COLOR
			: WHITE_COLOR;
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
			result = bestMoveList(result, discMoves);
		}
	}
	return result;
}

board_t setBoard(board_t board, Position p, char value){
	board_t result = copyBoard(board);
	result[p.x][p.y] = value;
	return result;
}

board_t copyBoard(board_t board){
	char copy[BOARD_SIZE][BOARD_SIZE];
	for (int i = 0; i < BOARD_SIZE; i++)
	for (int j = 0; j < BOARD_SIZE; j++){
		copy[i][j] = board[i][j];
	}
	return copy;
}