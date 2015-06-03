#include "Position.h"

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

PositionList* createPositionList(Position position) {
	PositionList* result = malloc(sizeof(Position));
	result->data = position;
	return result;
}

void freePositionList(PositionList* list) {
	PositionList* head = list;
	while(head){
		PositionList* next = head->next;
		free(head);
		head = next;
	}
}

bool playerInPosition(Position position, board_t board, int player){
	char value = getValueInPosition(position, board);
	if(player == WHITE_COLOR && (value == WHITE_M || value == WHITE_K)
		return true;
	if(player == BLACK_COLOR && (value == BLACK_M || value == BLACK_K)
		return true;
	return false;
}

bool allPositionsAreValid(PositionList* head) {
	while(head) {
		if(!validPosition(head->data))
			return false;
		head = head->next;
	}
	return true;
}

bool validPosition(Position position) {
	return position.x > 0 && position.x <= BOARD_SIZE &&
		position.y > 0 && position.y <= BOARD_SIZE &&
		mod(position.x, 2) == mod(position.y, 2);
}

bool positionEquals(Position p1, Position p2) {
	return p1.x == p2.x && p1.y == p2.y;
}

bool positionListEquals(PositionList* list1, PositionList* list2) {
	if (list1 == NULL || list2 == NULL)
		return false;
	PositionList* head1 = list1;
	PositionList* head2 = list2;
	while(head1 &&  head2){
		if(!positionEquals(head1->data, head2->data))
			return false;
		head1 = head1->next;
		head2 = head2->next;
	}
	return head1 == NULL && head2 == NULL;
}

char getValueInPosition(Position p, board_t board) {
	return board[position.x][position.y];
}