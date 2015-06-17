#include "KingMove.h"


MoveList* getKingMoves(Position position, char** board, int player) {
	MoveList* result = NULL;
	result = getKingMovesInDirection(result, board, player, position, &upperLeftDiagonal);
	result = getKingMovesInDirection(result, board, player, position, &lowerLeftDiagonal);
	result = getKingMovesInDirection(result, board, player, position, &upperRightDiagonal);
	result = getKingMovesInDirection(result, board, player, position, &lowerRightDiagonal);
	return result;
}

MoveList* getKingMovesInDirection(MoveList* result, char** board, int player,
	Position from, Position (*direction)(Position)) {

	Position dest = direction(from);
	while(validPosition(dest) && getValueInPosition(dest, board) == EMPTY) {
		if (result == NULL || result->maxToEat == 0) { //find zero eats moves
			Move* move  = createMove(from, createPositionList(dest), NULL, 0);
			result = bestMoveList(result, createMoveList(move));
		}
		dest = direction(dest);
	}
	if(validPosition(dest) && playerInPosition(dest, board, otherPlayer(player)) &&
		validPosition(direction(dest)) && getValueInPosition(direction(dest), board) == EMPTY) {
		//after skipping empties reached enemy piece that it can eat
		Move* move  = createMove(from, createPositionList(direction(dest)), createPositionList(dest), 1);
		MoveList* moves = applyEat(from, dest, direction(dest), board, move, player);
		result = bestMoveList(result, moves);
	}
	return result;
}