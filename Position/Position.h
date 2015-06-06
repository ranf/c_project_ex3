#ifndef POSITION_
#define POSITION_

#include <stdlib.h>
#include <stdbool.h>

typedef struct {
	int x;
	int y;
} Position;

typedef struct position_list_struct {
	Position data;
	struct position_list_struct* next;
} PositionList;

Position parsePosition(char* positionString);
PositionList* parseDestination(char* destString);
PositionList* createPositionList(Position position);
void freePositionList(PositionList* list);
bool allPositionsAreValid(PositionList* head);
bool validPosition(Position position);
bool positionEquals(Position p1, Position p2);
bool positionListEquals(PositionList* list1, PositionList* list2);
Position upperLeftDiagonal(Position p);
Position upperRightDiagonal(Position p);
Position lowerLeftDiagonal(Position p);
Position lowerRightDiagonal(Position p);
char* positionToString(Position position);
PositionList* copyPositionList(PositionList* original);

#endif