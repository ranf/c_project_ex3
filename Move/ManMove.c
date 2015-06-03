#include "ManMove.h"

MoveList* getManMoves(Position position, board_t board, player) {
	MoveList* result = NULL;
	Position leftPosition = upperLeftDiagonal(position);
	if(isValidPosition(leftPosition)) {
		if(getValueInPosition(leftPosition) == EMPTY) {
			Move move  = {.from position, .to = createPositionList(leftPosition), .eatCount = 0};
			result = createMoveList(move);
		}
		else if (playerInPosition(leftPosition, board, otherPlayer(player)) && getValueInPosition(upperLeftDiagonal(leftPosition)) == EMPTY) {
			board_t boardCopy = setBoard(board, leftPosition, EMPTY);
			Move move  = {.from position, .to = createPositionList(upperLeftDiagonal(leftPosition)),
				.eatenAt = createPositionList(leftPosition), .eatCount = 1};
			result = aManEats(upperLeftDiagonal(leftPosition)),boardCopy, previousMove, player);
		}
	}
	Position rightPosition = upperRightDiagonal(position);
	if(isValidPosition(rightPosition)){
		if((result==NULL||result.maxToEat==0)&&getValueInPosition(leftPosition) == EMPTY) {
			Move move  = {.from position, .to = createPositionList(leftPosition), .eatCount = 0};
			if(result == NULL)
				result = createMoveList(move);
			else
				result.next = createMoveList(move);
		}
		else if (playerInPosition(leftPosition, board, otherPlayer(player)) && getValueInPosition(upperLeftDiagonal(leftPosition)) == EMPTY) {
			board_t boardCopy = setBoard(board, leftPosition, EMPTY);
			Move move  = {.from position, .to = createPositionList(upperLeftDiagonal(leftPosition)), .eatCount = 1};
			MoveList* rightMoves = aManEats(upperLeftDiagonal(leftPosition)),boardCopy, &previousMove, player);
			result = bestMoveList(result, rightMoves);
		}
	}
	return result;
}

MoveList* createMoveList(Move move){
	MoveList* result = malloc(sizeof(MoveList));
	result->data = move;
	result->maxToEat = move.eatCount;
	return result;
}

MoveList* aManEats(Position from, board_t board, Move* previousMove, int player){
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

MoveList* getUpperLeftEatList(Position from, board_t board, Move* previousMove. int player){
	Position leftPosition = upperLeftDiagonal(position);
	if(isValidPosition(leftPosition)&&isValidPosition(upperLeftDiagonal(leftPosition))
		&& playerInPosition(leftPosition, board, otherPlayer(player))
		&& getValueInPosition(upperLeftDiagonal(leftPosition)) == EMPTY) {

		Move* newMove = addEatToMove(previousMove, upperLeftDiagonal(leftPosition));
		return aManEats(from, setBoard(leftPosition, EMPTY), newMove, player);
	}
	return NULL;
}

MoveList* getUpperRightEatList(Position from, board_t board, Move* previousMove. int player){
	Position leftPosition = upperRightDiagonal(position);
	if(isValidPosition(rightPosition)&&isValidPosition(upperRightDiagonal(rightPosition))
		&&playerInPosition(rightPosition, board, otherPlayer(player))
		&& getValueInPosition(upperRightDiagonal(rightPosition)) == EMPTY) {
		
		Move* newMove = addEatToMove(previousMove, upperRightDiagonal(rightPosition));
		return aManEats(from, setBoard(rightPosition, EMPTY), newMove, player);
	}
	return NULL;
}

MoveList* getLowerLeftEatList(Position from, board_t board, Move* previousMove. int player){
	Position leftPosition = lowerLeftDiagonal(position);
	if(isValidPosition(leftPosition)&&isValidPosition(lowerLeftDiagonal(leftPosition))
		&&playerInPosition(leftPosition, board, otherPlayer(player))
		&& getValueInPosition(lowerLeftDiagonal(leftPosition)) == EMPTY) {
		
		Move* newMove = addEatToMove(previousMove, lowerLeftDiagonal(leftPosition));
		return aManEats(from, setBoard(leftPosition, EMPTY), newMove, player);
	}
	return NULL;
}

MoveList* getLowerRightEatList(Position from, board_t board, Move* previousMove. int player){
	Position rightPosition = lowerRightDiagonal(position);
	if(isValidPosition(rightPosition)&&isValidPosition(lowerRightDiagonal(rightPosition))
		&&playerInPosition(rightPosition, board, otherPlayer(player))
		&& getValueInPosition(lowerRightDiagonal(rightPosition)) == EMPTY) {
		
		Move* newMove = addEatToMove(previousMove, lowerRightDiagonal(rightPosition));
		return aManEats(from, setBoard(rightPosition, EMPTY), newMove, player);
	}
	return NULL;
}