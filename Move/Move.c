#include "Move.h"

MoveList* bestMoveList(MoveList* list1, MoveList* list2) {
	if(list1 == NULL)
		return list2;
	if(list2 == NULL)
		return list1;
	if(list1->maxToEat > list2->maxToEat){
		freeMoves(list2);
		return list1;
	}
	if(list1->maxToEat < list2->maxToEat){
		freeMoves(list1);
		return list2;
	}

	MoveList* head = list1;
	while(head->next){
		head = head->next;
	}
	head->next = list2;
	return list1;
}

Move* addEatToMove(Move* move, Position targetPosition, Position eatPosition) {
	Move* newMove = copyMove(move);
	PositionList* newPositionNode = createPositionList(targetPosition);
	PositionList* head = newMove->to;
	if(head==NULL){
		newMove->to = newPositionNode;
	}else{
		while(head->next){
			head = head->next;
		}
		head->next = newPositionNode;
	}
	
	PositionList* newEatNode = createPositionList(eatPosition);
	head = newMove->eatenAt;
	if(head==NULL){
		newMove->eatenAt = newEatNode;
	}else{
		while(head->next){
			head = head->next;
		}
		head->next = newEatNode;
	}
	newMove->eatCount++; 

	return newMove;
}

Move* copyMove(Move* move) {
	return createMove(move->from, copyPositionList(move->to),
		copyPositionList(move->eatenAt), move->eatCount);
}

MoveList* createMoveList(Move* move) {
	MoveList* result = safeMalloc(sizeof(MoveList));
	result->data = move;
	result->next = NULL;
	result->maxToEat = move->eatCount;
	return result;
}

Move* parseMove(char* moveString) {
	char initialPosition[7];
	bool isDoubleDigits = moveString[4] != '>';
	if (isDoubleDigits) {
		strncpy(initialPosition, moveString, 6);
		initialPosition[6] = '\0';
	} else {
		strncpy(initialPosition, moveString, 5);
		initialPosition[5] = '\0';
	}	
	Position from = parsePosition(initialPosition);
	int lengthToSkip = isDoubleDigits ? 10 : 9;//<x,y>_to_
	PositionList* to = parseDestination(moveString + lengthToSkip);
	return createMove(from, to, NULL, 0);
}

bool validateMove(Move* move, char** board, int player) {
	if(!validPosition(move->from) || !allPositionsAreValid(move->to)) {
		printMessage(INVALID_POSITION);
		return false;
	}
	if(!playerInPosition(move->from, board, player)) {
		printMessage(NO_DISC);
		return false;
	}
	if(!moveInLegalMoves(move, board, player)) {
		printMessage(ILLEGAL_MOVE);
		return false;
	}
	return true;
}


bool moveInLegalMoves(Move* move, char** board, int player) {
	MoveList* legalMoves = getMoves(board, player);
	bool legal = moveInList(legalMoves, move);
	freeMoves(legalMoves);
	return legal;
}

bool moveInList(MoveList* list, Move* moveToFind) {
	if(list == NULL)
		return false;
	MoveList* head = list;
	while(head){
		if(positionEquals(head->data->from, moveToFind->from) &&
			positionListEquals(head->data->to, moveToFind->to)){
			moveToFind->eatenAt = copyPositionList(head->data->eatenAt);
			moveToFind->eatCount = head->data->eatCount;
			return true;
		}
		head = head->next;
	}
	return false;
}

MoveList* getMoves(char** board, int player) {
	MoveList* result = NULL;
	for (int i = 0; i < BOARD_SIZE; ++i)
	for (int j = 0; j < BOARD_SIZE; ++j)
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

Move* createMove(Position from, PositionList* to, PositionList* eatenAt, int eatCount) {
	Move* move = safeMalloc(sizeof(Move));
	move->from = from;
	move->to = to;
	move->eatenAt = eatenAt;
	move->eatCount = eatCount;
	return move;
}

void freeMoves(MoveList* list) {
	MoveList* head = list;
	while(head){
		MoveList* next = head->next;
		freeMove(head->data);
		free(head);
		head = next;
	}
}

void freeMove(Move* move) {
	freePositionList(move->to);
	freePositionList(move->eatenAt);
	free(move);
}

char** applyMove(char** board, Move* move) {
	char movingDisc = getValueInPosition(move->from, board);
	board = setBoardAndFree(board, move->from, EMPTY);
	PositionList* head = move->eatenAt;
	while(head){
		board = setBoardAndFree(board, head->data, EMPTY);
		head = head->next;
	}
	head = move->to;
	while(head->next){
		head = head->next;
	}
	if(!isKing(movingDisc) && endOfBoard(head->data, piecePlayer(movingDisc))) {
		movingDisc = crownPiece(movingDisc);
	}
	return setBoardAndFree(board, head->data, movingDisc);
}