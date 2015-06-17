#include "Minimax.h"

Move* findBestMove(char** board, int minimaxDepth, int player) {
	MoveList* possibleMoves = getMoves(board, player);
	if (possibleMoves == NULL)
		return NULL;
	if (possibleMoves->next == NULL) {
		Move* result = copyMove(possibleMoves->data);
		freeMoves(possibleMoves);
		return result;
	}
	Move* bestMove = copyMove(findMaxScoreMove(possibleMoves, board, minimaxDepth - 1, player).move);
	freeMoves(possibleMoves);
	return bestMove;
}

ScoredMove findMaxScoreMove(MoveList* possibleMoves, char** board, int additionalChecks, int player) {
	if(additionalChecks == 0) {
		return maxScoreMoveInList(possibleMoves, board, player);
	}
	ScoredMove result = {.score = -101, .move = NULL};
	MoveList* head = possibleMoves;
	while (head) {
		char** tempBoard = copyBoard(board);
		tempBoard = applyMove(tempBoard, head->data);
		MoveList* otherPlayerMoves = getMoves(tempBoard, otherPlayer(player));
		ScoredMove otherPlayerBestMove = findMaxScoreMove(otherPlayerMoves,
			tempBoard, additionalChecks - 1, otherPlayer(player));
		if(result.score < -otherPlayerBestMove.score) {
			result.score = -otherPlayerBestMove.score;
			result.move = head->data;
		}
		freeBoard(tempBoard);
		freeMoves(otherPlayerMoves);
		head = head->next;
	}
	return result;
}

ScoredMove maxScoreMoveInList(MoveList* possibleMoves, char** board, int player) {
	int maxScore = -101;
	Move* maxMove = NULL;
	char** tempBoard;
	MoveList* head = possibleMoves;
	while (head) {
		tempBoard = copyBoard(board);
		tempBoard = applyMove(tempBoard, head->data);
		int tempScore = scoreBoard(tempBoard, player);
		if(tempScore > maxScore) {
			maxScore = tempScore;
			maxMove = head->data;
		}
		freeBoard(tempBoard);
		head = head->next;
	}
	ScoredMove result = {.move = maxMove, .score = maxScore};
	return result;
}

int scoreBoard(char** board, int player) {
	if (cannotPlay(board, otherPlayer(player)))
		return WINNING_SCORE;
	if (hasNoPieces(board, player))
		return LOSING_SCORE;

	int score = 0;
	for (int i = 0; i < BOARD_SIZE; ++i)
	for (int j = 0; j < BOARD_SIZE; ++j) {
		score += scoreChar(board[i][j]);
	}
	return player == WHITE_COLOR
		? score
		: -score;
}

bool cannotPlay(char** board, int player) {
	if(hasNoPieces(board, player))
		return true;
	for (int i = 0; i < BOARD_SIZE; ++i)
	for (int j = 0; j < BOARD_SIZE; ++j) {
		if(!isPlayerPiece(board[i][j], player))
			continue;
		Position p = {.x = i, .y = j};
		if ((isKing(board[i][j]) && (
			canGoInDirection(board, p, &upperLeftDiagonal, player) ||
			canGoInDirection(board, p, &upperRightDiagonal, player) ||
			canGoInDirection(board, p, &lowerLeftDiagonal, player) ||
			canGoInDirection(board, p, &lowerRightDiagonal, player))) ||
			(player == WHITE_COLOR && (
			canGoInDirection(board, p, &upperLeftDiagonal, player) ||
			canGoInDirection(board, p, &upperRightDiagonal, player))) ||
			(player == BLACK_COLOR && (
			canGoInDirection(board, p, &lowerLeftDiagonal, player) ||
			canGoInDirection(board, p, &lowerRightDiagonal, player))))
			return false;
	}
	return true;
}

bool canGoInDirection(char** board, Position from, Position (*direction)(Position), int player) {
	return (validPosition(direction(from)) && getValueInPosition(direction(from), board) == EMPTY) ||
			(validPosition(direction(from)) && validPosition(direction(direction(from))) &&
				playerInPosition(direction(from), board, otherPlayer(player)) &&
				getValueInPosition(direction(direction(from)), board) == EMPTY);
}

int scoreChar(char val) {
	if(val == WHITE_M)
		return 1;
	if(val == WHITE_K)
		return 3;
	if(val == BLACK_M)
		return -1;
	if(val == BLACK_K)
		return -3;
	return 0;
}