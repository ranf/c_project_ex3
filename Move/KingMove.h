#ifndef KINGMOVE_
#define KINGMOVE_

#include "Move.h"
#include "EatMove.h"
#include "../Board.h"
#include "../Position/Position.h"

MoveList* getKingMoves(Position position, char** board, int player);
MoveList* getKingMovesInDirection(MoveList* result, char** board, int player,
	Position from, Position (*direction)(Position));

#endif