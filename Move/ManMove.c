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
		result = bestMoveList(result, createMoveList(move));		
	}
	else if (playerInPosition(firstPosition, board, otherPlayer(player)) && validPosition(nextPosition)
		&& getValueInPosition(nextPosition, board) == EMPTY) {
		
		Move* move  = createMove(from, createPositionList(nextPosition), createPositionList(firstPosition), 1);
		MoveList* moves = applyEat(from, firstPosition, nextPosition, board, move, player);
		result = bestMoveList(result, moves);
	}
	return result;
}