#ifndef MANMOVE_
#define MANMOVE_

#include "Move.h"
#include "EatMove.h"
#include "../Board.h"
#include "../Position/Position.h"

MoveList* getManMoves(Position position, char** board, int player);
MoveList* getMovesInDirection(MoveList* result, char** board, int player, Position from, Position firstPosition, Position nextPosition);

#endif