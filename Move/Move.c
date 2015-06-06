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
	return head;
}

Move* addEatToMove(Move* move, Position targetPosition, Position eatPosition) {
	Move* newMove = copyMove(move);
	PositionList* newPositionNode = createPositionList(position);
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

Move parseMove(char* moveString) {
	char initialPosition[6];
	strncpy(initialPosition, moveString, 5);
	initialPosition[5] = '\0';
	Position from = parsePosition(initialPosition);
	PositionList* to = parseDestination(moveString + 9);//<x,y>_to_
	Move move = {.from = from, .to = to};
	return move;
}

bool validateMove(Move* move, char** board, int player) {
	if(!validPosition(move->from) || !allPositionsAreValid(move->to)) {
		printMessage(INVALID_POSITION);
		return false;
	}
	if(!playerInPosition(move->from, board, player) {
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

MoveList* getMoves(char** board, int player) {
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

void freeMoves(MoveList* list) {
	MoveList* head = list;
	while(head){
		MoveList* next = head->next;
		freeMove(head->data);
		free(head);
		head = next;
	}
}

void freeMove(Move move) {
	freePositionList(move.to);
	freePositionList(move.eatenAt);
}