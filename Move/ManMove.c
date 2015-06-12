#include "ManMove.h"

MoveList* getManMoves(Position position, char** board, int player) {
	MoveList* result = NULL;
	Position leftPosition = player == WHITE_COLOR
		? upperLeftDiagonal(position)
		: lowerLeftDiagonal(position);
	Position nextLeftPosition = player == WHITE_COLOR
		? upperLeftDiagonal(leftPosition)
		: lowerLeftDiagonal(leftPosition);
	Position rightPosition = player == WHITE_COLOR
		? upperRightDiagonal(position)
		: lowerRightDiagonal(position);
	Position nextRightPosition = player == WHITE_COLOR
		? upperRightDiagonal(rightPosition)
		: lowerRightDiagonal(rightPosition);
	result = getMovesInDirection(result, board, player, position, leftPosition, nextLeftPosition);
	result = getMovesInDirection(result, board, player, position, rightPosition, nextRightPosition);
	return result;
}

MoveList* getMovesInDirection(MoveList* result, char** board, int player,
	Position from, Position firstPosition, Position nextPosition) {
	
	if(!validPosition(firstPosition))
		return result;

	if((result == NULL || result->maxToEat == 0) && getValueInPosition(firstPosition, board) == EMPTY) {
		Move* move  = createMove(from, createPositionList(firstPosition), NULL, 0);
		if(result == NULL)
			result = createMoveList(move);
		else
			result->next = createMoveList(move);
	}
	else if (playerInPosition(firstPosition, board, otherPlayer(player)) && validPosition(nextPosition)
		&& getValueInPosition(nextPosition, board) == EMPTY) {
		
		Move* move  = createMove(from, createPositionList(nextPosition), createPositionList(firstPosition), 1);
		MoveList* moves = applyManEat(from, firstPosition, nextPosition, board, move, player);
		result = bestMoveList(result, moves);
	}
	return result;
}

MoveList* createMoveList(Move* move) {
	MoveList* result = malloc(sizeof(MoveList));
	result->data = move;
	result->next = NULL;
	result->maxToEat = move->eatCount;
	return result;
}

MoveList* aManEats(Position from, char** board, Move* previousMove, int player) {
	MoveList* upperLeftMoves = getManEatList(from, upperLeftDiagonal(from), upperLeftDiagonal(upperLeftDiagonal(from)),
		board, previousMove, player);
	MoveList* upperRightMoves = getManEatList(from, upperRightDiagonal(from), upperRightDiagonal(upperRightDiagonal(from)),
		board, previousMove, player);
	MoveList* lowerLeftMoves = getManEatList(from, lowerLeftDiagonal(from), lowerLeftDiagonal(lowerLeftDiagonal(from)),
		board, previousMove, player);
	MoveList* lowerRightMoves = getManEatList(from, lowerRightDiagonal(from), lowerRightDiagonal(lowerRightDiagonal(from)),
		board, previousMove, player);
	if(upperLeftMoves == NULL && upperRightMoves == NULL && lowerLeftMoves == NULL && lowerRightMoves == NULL)
		return createMoveList(previousMove);
	return bestMoveList(bestMoveList(bestMoveList(upperLeftMoves, upperRightMoves), lowerLeftMoves), lowerRightMoves);
}

MoveList* getManEatList(Position from, Position positionToEat, Position to, char** board, Move* previousMove, int player) {
	if(!validPosition(positionToEat) || !validPosition(to) ||
		!playerInPosition(positionToEat, board, otherPlayer(player)) ||
		!getValueInPosition(to, board) == EMPTY)
		return NULL;

	Move* newMove = addEatToMove(previousMove, to, positionToEat);
	return applyManEat(from, positionToEat, to, board, newMove, player);
}

MoveList* applyManEat(Position from, Position positionToEat, Position to, char** board, Move* move, int player) {
	char piece = getValueInPosition(from, board);
	if (endOfBoard(to, player)) {
		piece = player == WHITE_COLOR ? WHITE_K : BLACK_K;
	}
	char** boardCopy = setBoard(board, from, EMPTY);
	boardCopy = setBoardAndFree(boardCopy, positionToEat, EMPTY);
	boardCopy = setBoardAndFree(boardCopy, to, piece);
	MoveList* list = endOfBoard(to, player)
		? createMoveList(move)
		: aManEats(to, boardCopy, move, player);
	freeBoard(boardCopy);
	return list;
}