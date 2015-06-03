#ifndef POSITION_
#define POSITION_

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
char getValueInPosition(Position p, board_t board);

#endif