#ifndef MANMOVE_
#define MANMOVE_

#include "Move.h"
#include "../Board.h"
#include "../Position/Position.h"

MoveList* getManMoves(Position position, char** board, int player);
MoveList* createMoveList(Move* move);
MoveList* aManEats(Position from, char** board, Move* previousMove, int player);
MoveList* getUpperLeftEatList(Position from, char** board, Move* previousMove, int player);
MoveList* getUpperRightEatList(Position from, char** board, Move* previousMove, int player);
MoveList* getLowerLeftEatList(Position from, char** board, Move* previousMove, int player);
MoveList* getLowerRightEatList(Position from, char** board, Move* previousMove, int player);

#endif