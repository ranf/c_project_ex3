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
	if(validMove(move)){
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

Position parsePosition(char* positionString) {
	//assuming valid string
	char xLetter = positionString[1];
	char yDigit = positionString[3];
	int x = xLetter - 'a' + 1;
	int y = yDigit - '0';
	Position p = {.x = x, .y = y};
	return p;
}

PositionList* parseDestination(char* destString){
	PositionList* list = malloc(sizeof(PositionList));
	Position p = parsePosition(destString);
	list->data = p;
	PositionList* head = list;
	int i = 5;
	while (destString[i] == '<') {
		Position p = parsePosition(destString+i);
		head->next = malloc(sizeof(PositionList));
		head = head->next;
		head->data = p;
		i += 5;
	}
	return list;
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

bool playerInPosition(Position position, board_t board, int player){
	char value = getValueInPosition(position, board);
	if(player == WHITE_COLOR && (value == WHITE_M || value == WHITE_K)
		return true;
	if(player == BLACK_COLOR && (value == BLACK_M || value == BLACK_K)
		return true;
	return false;
}

bool allPositionsAreValid(PositionList* list){
	PositionList* head = list;
	while(head){
		if(!validPosition(head->data))
			false;
		head = head->next;
	}
	return true;
}

bool validPosition(Position position) {
	return position.x > 0 && position.x <= BOARD_SIZE &&
		position.y > 0 && position.y <= BOARD_SIZE &&
		mod(position.x, 2) == mod(position.y, 2);
}

bool isLegalMove(Move move, Settings settings, int player) {
	MoveList* legalMoves = getMoves(settings, player);
	bool legal = movesContains(legalMoves, move);
	freeMoves(legalMoves);
	return legal;
}

bool movesContains(MoveList* list, Move moveToFind){
	if(list==NULL)
		return false;
	MoveList* head = list;
	while(head->next && result == false){
		MoveList* next = head->next;
		if(positiosEquals(next->from, moveToFind.from) &&
			positionListEquals(next->to, moveToFind.to)){
			return true;
		}
		head = head->next;
	}
	return false;
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
			result = bestMoveList(result, discMoves);
		}
	}
	return result;
}

char getValueInPosition(Position p, board_t board){
	return board[position.x][position.y];
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