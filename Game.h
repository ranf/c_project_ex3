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
} Move;

typedef struct move_list_struct{
	Move data;
	MoveList* next;
	int maxToEat;
} MoveList;

typedef bool (*Predicate)(void*);

void startGame(struct Settings settings);

#endif