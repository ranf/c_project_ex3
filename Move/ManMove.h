#ifndef MANMOVE_
#define MANMOVE_

#include "Move.h"
#include "../Board.h"
#include "../Position/Position.h"

MoveList* getManMoves(Position position, Board board, int player);
MoveList* createMoveList(Move move);
MoveList* aManEats(Position from, Board board, Move* previousMove, int player);
MoveList* getUpperLeftEatList(Position from, Board board, Move* previousMove, int player);
MoveList* getUpperRightEatList(Position from, Board board, Move* previousMove, int player);
MoveList* getLowerLeftEatList(Position from, Board board, Move* previousMove, int player);
MoveList* getLowerRightEatList(Position from, Board board, Move* previousMove, int player);

#endif