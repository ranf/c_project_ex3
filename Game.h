#ifndef GAME_
#define GAME_

#include "Settings.h"

typedef struct {
	Position from;
	PositionList* to;
	PositionList* eatenAt;
	int eatCount;
} Move;

typedef struct move_list_struct {
	Move data;
	struct move_list_struct* next;
	int maxToEat;
} MoveList;

void startGame(struct Settings settings);

#endif