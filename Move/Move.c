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