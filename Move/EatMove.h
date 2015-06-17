#ifndef EATMOVE_
#define EATMOVE_

#include "Move.h"
#include "../Board.h"
#include "../Position/Position.h"

MoveList* aPieceEats(Position from, char** board, Move* previousMove, int player);
MoveList* getEatList(Position from, Position positionToEat, Position to, char** board, Move* previousMove, int player);
MoveList* applyEat(Position from, Position positionToEat, Position to, char** board, Move* move, int player);

#endif