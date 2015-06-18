#ifndef MOVE_
#define MOVE_

#include "../Board.h"
#include "../Position/Position.h"
#include <string.h>
#include "../Utils.h"

#define ILLEGAL_MOVE "Illegal move\n"
#define NO_DISC "The specified position does not contain your piece\n"

typedef struct {
	Position from;
	PositionList* to;
	PositionList* eatenAt;
	int eatCount;
} Move;

typedef struct move_list_struct {
	Move* data;
	struct move_list_struct* next;
	int maxToEat;
} MoveList;

MoveList* bestMoveList(MoveList* list1, MoveList* list2);
Move* addEatToMove(Move* move, Position targetPosition, Position eatPosition);
Move* parseMove(char* moveString);
bool validateMove(Move* move, char** board, int player);
bool moveInLegalMoves(Move* move, char** board, int player);
bool moveInList(MoveList* list, Move* moveToFind);
MoveList* getMoves(char** board, int player);
void freeMoves(MoveList* list);
void freeMove(Move* move);
Move* createMove(Position from, PositionList* to, PositionList* eatenAt, int eatCount);
char** applyMove(char** board, Move* move);
Move* copyMove(Move* move);
MoveList* createMoveList(Move* move);

#include "ManMove.h"
#include "KingMove.h"

#endif