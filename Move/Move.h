#ifndef MOVE_
#define MOVE_

MoveList* bestMoveList(MoveList* list1, MoveList* list2);
Move* addEatToMove(Move* move, Position targetPosition, Position eatPosition);
void freeMoves(MoveList* list);
void freeMove(Move move);

#endif