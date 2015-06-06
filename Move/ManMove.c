#include "ManMove.h"

MoveList* getManMoves(Position position, char** board, int player) {
	MoveList* result = NULL;
	Position leftPosition = upperLeftDiagonal(position);
	if(isValidPosition(leftPosition)) {
		if(getValueInPosition(leftPosition) == EMPTY) {
			Move* move = createMove(position, createPositionList(leftPosition), NULL, 0);
			result = createMoveList(move);
		}
		else if (playerInPosition(leftPosition, board, otherPlayer(player)) && getValueInPosition(upperLeftDiagonal(leftPosition)) == EMPTY) {
			char** boardCopy = setBoard(board, leftPosition, EMPTY);
			Move* move  = createMove(position, createPositionList(upperLeftDiagonal(leftPosition)), createPositionList(leftPosition), 1);
			result = aManEats(upperLeftDiagonal(leftPosition), boardCopy, move, player);
			freeBoard(boardCopy);
		}
	}
	Position rightPosition = upperRightDiagonal(position);
	if(isValidPosition(rightPosition)){
		if((result==NULL||result.maxToEat==0) && getValueInPosition(rightPosition) == EMPTY) {
			Move* move  = createMove(position, createPositionList(rightPosition), NULL, 0);
			if(result == NULL)
				result = createMoveList(move);
			else
				result->next = createMoveList(move);
		}
		else if (playerInPosition(rightPosition, board, otherPlayer(player)) && getValueInPosition(upperRightDiagonal(RightPosition)) == EMPTY) {
			char** boardCopy = setBoard(board, rightPosition, EMPTY);
			Move* move  = createMove(position, createPositionList(upperRightDiagonal(rightPosition)), createPositionList(rightPosition), .eatCount = 1};
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
	result->maxToEat = move.eatCount;
	return result;
}

MoveList* aManEats(Position from, char** board, Move* previousMove, int player) {
	MoveList* upperLeftMoves = NULL,upperRightMoves=NULL,lowerLeftMoves=NULL,lowerRightMoves=NULL;
	int maxToEat = previousMove->eatCount;
	upperLeftMoves = getUpperLeftMoveList(from, board, previousMove);
	upperRightMoves = getUpperRightMoveList(from, board, previousMove);
	lowerLeftMoves = getLowerLeftMoveList(from, board, previousMove);
	lowerRightMoves = getLowerRightMoveList(from, board, previousMove);
	if(upperLeftMoves == NULL&&upperRightMoves==NULL&&lowerLeftMoves==NULL&&lowerRightMoves==NULL)
		return createMoveList(previousMove);
	return bestMoveList(bestMoveList(bestMoveList(upperLeftMoves, upperRightMoves), lowerLeftMoves), lowerRightMoves);
}

MoveList* getUpperLeftEatList(Position from, char** board, Move* previousMove, int player){
	Position leftPosition = upperLeftDiagonal(position);
	if(isValidPosition(leftPosition) && isValidPosition(upperLeftDiagonal(leftPosition))
		&& playerInPosition(leftPosition, board, otherPlayer(player))
		&& getValueInPosition(upperLeftDiagonal(leftPosition)) == EMPTY) {

		Move* newMove = addEatToMove(previousMove, upperLeftDiagonal(leftPosition));
		char** boardCopy = setBoard(leftPosition, EMPTY);
		MoveList* list = aManEats(from, boardCopy, newMove, player);
		freeBoard(boardCopy);
		return list;
	}
	return NULL;
}

MoveList* getUpperRightEatList(Position from, char** board, Move* previousMove, int player) {
	Position leftPosition = upperRightDiagonal(position);
	if(isValidPosition(rightPosition) && isValidPosition(upperRightDiagonal(rightPosition))
		&& playerInPosition(rightPosition, board, otherPlayer(player))
		&& getValueInPosition(upperRightDiagonal(rightPosition)) == EMPTY) {
		
		Move* newMove = addEatToMove(previousMove, upperRightDiagonal(rightPosition));
		char** boardCopy = setBoard(leftPosition, EMPTY);
		MoveList* list = aManEats(from, boardCopy, newMove, player);
		freeBoard(boardCopy);
		return list;
	}
	return NULL;
}

MoveList* getLowerLeftEatList(Position from, char** board, Move* previousMove, int player) {
	Position leftPosition = lowerLeftDiagonal(position);
	if(isValidPosition(leftPosition) && isValidPosition(lowerLeftDiagonal(leftPosition))
		&& playerInPosition(leftPosition, board, otherPlayer(player))
		&& getValueInPosition(lowerLeftDiagonal(leftPosition)) == EMPTY) {
		
		Move* newMove = addEatToMove(previousMove, lowerLeftDiagonal(leftPosition));
		char** boardCopy = setBoard(leftPosition, EMPTY);
		MoveList* list = aManEats(from, boardCopy, newMove, player);
		freeBoard(boardCopy);
		return list;
	}
	return NULL;
}

MoveList* getLowerRightEatList(Position from, char** board, Move* previousMove, int player) {
	Position rightPosition = lowerRightDiagonal(position);
	if(isValidPosition(rightPosition) && isValidPosition(lowerRightDiagonal(rightPosition))
		&& playerInPosition(rightPosition, board, otherPlayer(player))
		&& getValueInPosition(lowerRightDiagonal(rightPosition)) == EMPTY) {
		
		Move* newMove = addEatToMove(previousMove, lowerRightDiagonal(rightPosition));
		char** boardCopy = setBoard(leftPosition, EMPTY);
		MoveList* list = aManEats(from, boardCopy, newMove, player);
		freeBoard(boardCopy);
		return list;
	}
	return NULL;
}