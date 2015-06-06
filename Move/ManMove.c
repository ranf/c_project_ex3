#include "ManMove.h"

MoveList* getManMoves(Position position, char** board, int player) {
	MoveList* result = NULL;
	Position leftPosition = upperLeftDiagonal(position);
	if(validPosition(leftPosition)) {
		if(getValueInPosition(leftPosition, board) == EMPTY) {
			Move* move = createMove(position, createPositionList(leftPosition), NULL, 0);
			result = createMoveList(move);
		}
		else if (playerInPosition(leftPosition, board, otherPlayer(player)) && getValueInPosition(upperLeftDiagonal(leftPosition), board) == EMPTY) {
			char** boardCopy = setBoard(board, leftPosition, EMPTY);
			Move* move  = createMove(position, createPositionList(upperLeftDiagonal(leftPosition)), createPositionList(leftPosition), 1);
			result = aManEats(upperLeftDiagonal(leftPosition), boardCopy, move, player);
			freeBoard(boardCopy);
		}
	}
	Position rightPosition = upperRightDiagonal(position);
	if(validPosition(rightPosition)){
		if((result==NULL||result->maxToEat==0) && getValueInPosition(rightPosition, board) == EMPTY) {
			Move* move  = createMove(position, createPositionList(rightPosition), NULL, 0);
			if(result == NULL)
				result = createMoveList(move);
			else
				result->next = createMoveList(move);
		}
		else if (playerInPosition(rightPosition, board, otherPlayer(player)) && getValueInPosition(upperRightDiagonal(rightPosition), board) == EMPTY) {
			char** boardCopy = setBoard(board, rightPosition, EMPTY);
			Move* move  = createMove(position, createPositionList(upperRightDiagonal(rightPosition)), createPositionList(rightPosition), 1);
			MoveList* rightMoves = aManEats(upperLeftDiagonal(leftPosition), boardCopy, move, player);
			freeBoard(boardCopy);
			result = bestMoveList(result, rightMoves);
		}
	}
	return result;
}

MoveList* createMoveList(Move* move) {
	MoveList* result = malloc(sizeof(MoveList));
	result->data = move;
	result->maxToEat = move->eatCount;
	return result;
}

MoveList* aManEats(Position from, char** board, Move* previousMove, int player) {
	int maxToEat = previousMove->eatCount;
	MoveList* upperLeftMoves = getUpperLeftEatList(from, board, previousMove);
	MoveList* upperRightMoves = getUpperRightEatList(from, board, previousMove);
	MoveList* lowerLeftMoves = getLowerLeftEatList(from, board, previousMove);
	MoveList* lowerRightMoves = getLowerRightEatList(from, board, previousMove);
	if(upperLeftMoves == NULL&&upperRightMoves==NULL&&lowerLeftMoves==NULL&&lowerRightMoves==NULL)
		return createMoveList(previousMove);
	return bestMoveList(bestMoveList(bestMoveList(upperLeftMoves, upperRightMoves), lowerLeftMoves), lowerRightMoves);
}

MoveList* getUpperLeftEatList(Position from, char** board, Move* previousMove, int player){
	Position leftPosition = upperLeftDiagonal(from);
	if(validPosition(leftPosition) && validPosition(upperLeftDiagonal(leftPosition))
		&& playerInPosition(leftPosition, board, otherPlayer(player))
		&& getValueInPosition(upperLeftDiagonal(leftPosition), board) == EMPTY) {

		Move* newMove = addEatToMove(previousMove, upperLeftDiagonal(leftPosition), leftPosition);
		char** boardCopy = setBoard(board, leftPosition, EMPTY);
		MoveList* list = aManEats(from, boardCopy, newMove, player);
		freeBoard(boardCopy);
		return list;
	}
	return NULL;
}

MoveList* getUpperRightEatList(Position from, char** board, Move* previousMove, int player) {
	Position rightPosition = upperRightDiagonal(from);
	if(validPosition(rightPosition) && validPosition(upperRightDiagonal(rightPosition))
		&& playerInPosition(rightPosition, board, otherPlayer(player))
		&& getValueInPosition(upperRightDiagonal(rightPosition), board) == EMPTY) {
		
		Move* newMove = addEatToMove(previousMove, upperRightDiagonal(rightPosition), rightPosition);
		char** boardCopy = setBoard(board, leftPosition, EMPTY);
		MoveList* list = aManEats(from, boardCopy, newMove, player);
		freeBoard(boardCopy);
		return list;
	}
	return NULL;
}

MoveList* getLowerLeftEatList(Position from, char** board, Move* previousMove, int player) {
	Position leftPosition = lowerLeftDiagonal(from);
	if(validPosition(leftPosition) && validPosition(lowerLeftDiagonal(leftPosition))
		&& playerInPosition(leftPosition, board, otherPlayer(player))
		&& getValueInPosition(lowerLeftDiagonal(leftPosition), board) == EMPTY) {
		
		Move* newMove = addEatToMove(previousMove, lowerLeftDiagonal(leftPosition), leftPosition);
		char** boardCopy = setBoard(board, leftPosition, EMPTY);
		MoveList* list = aManEats(from, boardCopy, newMove, player);
		freeBoard(boardCopy);
		return list;
	}
	return NULL;
}

MoveList* getLowerRightEatList(Position from, char** board, Move* previousMove, int player) {
	Position rightPosition = lowerRightDiagonal(from);
	if(validPosition(rightPosition) && validPosition(lowerRightDiagonal(rightPosition))
		&& playerInPosition(rightPosition, board, otherPlayer(player))
		&& getValueInPosition(lowerRightDiagonal(rightPosition), board) == EMPTY) {
		
		Move* newMove = addEatToMove(previousMove, lowerRightDiagonal(rightPosition), rightPosition);
		char** boardCopy = setBoard(board, leftPosition, EMPTY);
		MoveList* list = aManEats(from, boardCopy, newMove, player);
		freeBoard(boardCopy);
		return list;
	}
	return NULL;
}