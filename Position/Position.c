#include "Position.h"

Position parsePosition(char* positionString) {
	Position p = {.x = -1, .y = -1};
	if(positionString == NULL || strlen(positionString) < 5 ||
		positionString[0] != '<' || positionString[2] != ','||
		(positionString[4] != '>'  && positionString[5] != '>')) {
		return p;
	}
	char xLetter = positionString[1];
	p.y = atoi(positionString + 3) - 1;
	p.x = xLetter - 'a';
	return p;
}

PositionList* parseDestination(char* destString){
	Position p = parsePosition(destString);
	PositionList* list = createPositionList(p);
	PositionList* head = list;
	int i = 5;
	while (destString[i] == '<' || (destString[i] == '>' && destString[i+1] == '<')) {
		if(destString[i] == '>')
			i++;
		Position p = parsePosition(destString+i);
		head->next = createPositionList(p);
		head = head->next;
		i += 5;
	}
	return list;
}

void positionToString(Position position, char* str) {
	str[0] = '<';
	str[1] = position.x + 'a';
	str[2] = ',';
	if(position.y >= 9) {
		str[3] = ((position.y + 1) / 10)  + '0';
		str[4] = ((position.y + 1) % 10)  + '0';
		str[5] = '>';
		str[6] = '\0';
	} else {
		str[3] = position.y + '1';
		str[4] = '>';
		str[5] = '\0';
	}
}

PositionList* createPositionList(Position position) {
	PositionList* result = safeMalloc(sizeof(PositionList));
	result->data = position;
	result->next = NULL;
	return result;
}

PositionList* copyPositionList(PositionList* original) {
	if(original == NULL)
		return NULL;
	PositionList* result = createPositionList(original->data);
	PositionList* resultHead = result;
	PositionList* head = original->next;
	while(head){
		resultHead->next = createPositionList(head->data);
		resultHead = resultHead->next;
		head = head->next;
	}
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

bool allPositionsAreValid(PositionList* head) {
	if(head == NULL)
		return false;
	while(head) {
		if(!validPosition(head->data))
			return false;
		head = head->next;
	}
	return true;
}

bool validPosition(Position position) {
	return position.x > -1 && position.x < BOARD_SIZE &&
		position.y > -1 && position.y < BOARD_SIZE &&
		(position.x % 2) == (position.y % 2);
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

Position upperLeftDiagonal(Position p) {
	Position p2 = {.x = p.x - 1, .y = p.y + 1};
	return p2;
}

Position upperRightDiagonal(Position p) {
	Position p2 = {.x = p.x + 1, .y = p.y + 1};
	return p2;
}

Position lowerLeftDiagonal(Position p) {
	Position p2 = {.x = p.x - 1, .y = p.y - 1};
	return p2;
}

Position lowerRightDiagonal(Position p) {
	Position p2 = {.x = p.x + 1, .y = p.y - 1};
	return p2;
}