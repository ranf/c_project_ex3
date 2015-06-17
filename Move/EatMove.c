#include "EatMove.h"

MoveList* aPieceEats(Position from, char** board, Move* previousMove, int player) {
	MoveList* upperLeftMoves = getEatList(from, upperLeftDiagonal(from), upperLeftDiagonal(upperLeftDiagonal(from)),
		board, previousMove, player);
	MoveList* upperRightMoves = getEatList(from, upperRightDiagonal(from), upperRightDiagonal(upperRightDiagonal(from)),
		board, previousMove, player);
	MoveList* lowerLeftMoves = getEatList(from, lowerLeftDiagonal(from), lowerLeftDiagonal(lowerLeftDiagonal(from)),
		board, previousMove, player);
	MoveList* lowerRightMoves = getEatList(from, lowerRightDiagonal(from), lowerRightDiagonal(lowerRightDiagonal(from)),
		board, previousMove, player);
	if(upperLeftMoves == NULL && upperRightMoves == NULL && lowerLeftMoves == NULL && lowerRightMoves == NULL)
		return createMoveList(previousMove);
	freeMove(previousMove);
	return bestMoveList(bestMoveList(bestMoveList(upperLeftMoves, upperRightMoves), lowerLeftMoves), lowerRightMoves);
}

MoveList* getEatList(Position from, Position positionToEat, Position to, char** board, Move* previousMove, int player) {
	if(!validPosition(positionToEat) || !validPosition(to) ||
		!playerInPosition(positionToEat, board, otherPlayer(player)) ||
		getValueInPosition(to, board) != EMPTY)
		return NULL;

	Move* newMove = addEatToMove(previousMove, to, positionToEat);
	return applyEat(from, positionToEat, to, board, newMove, player);
}

MoveList* applyEat(Position from, Position positionToEat, Position to, char** board, Move* move, int player) {
	char piece = getValueInPosition(from, board);
	bool isKingMove = isKing(piece);
	if (endOfBoard(to, player)) {
		piece = crownPiece(piece);
	}
	char** boardCopy = setBoard(board, from, EMPTY);
	boardCopy = setBoardAndFree(boardCopy, positionToEat, EMPTY);
	boardCopy = setBoardAndFree(boardCopy, to, piece);
	MoveList* list = endOfBoard(to, player) && !isKingMove
		? createMoveList(move)
		: aPieceEats(to, boardCopy, move, player);
	freeBoard(boardCopy);
	return list;
}