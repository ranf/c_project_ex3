#ifndef MANMOVE_
#define MANMOVE_

#include "Move.h"
#include "../Board.h"
#include "../Position/Position.h"

MoveList* getManMoves(Position position, char** board, int player);
MoveList* getMovesInDirection(MoveList* result, Position position, Position nextPosition);
MoveList* createMoveList(Move* move);
MoveList* aManEats(Position from, char** board, Move* previousMove, int player);
MoveList* getManEatList(Position from, Position positionToEat, Position to, char** board, Move* previousMove, int player);
MoveList* applyManEat(Position from, Position positionToEat, Position to, char** board, Move* move, int player);

#endif