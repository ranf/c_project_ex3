#ifndef GAME_
#define GAME_

#include "Settings.h"

typedef struct {
	int x;
	int y;
} Position;

typedef struct position_list_struct {
	Position data;
	position_list_struct* next;
} PositionList;

typedef struct {
	Position from;
	PositionList* to;
	int eatCount;
} Move;

typedef struct move_list_struct {
	Move data;
	move_list_struct* next;
	int maxToEat;
} MoveList;

void startGame(struct Settings settings);

#endif