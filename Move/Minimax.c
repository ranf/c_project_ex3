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
	Move* bestMove = findMaxScore(possibleMoves, board, minimaxDepth - 1, player);
	freeMoves(possibleMoves);
	return bestMove;
}

ScoredMove findMaxScoreMove(MoveList* possibleMoves, char** board, int additionalChecks, int player) {
	if(additionalChecks == 0) {
		return maxScoreMoveInList(possibleMoves, board, player);
	}
	ScoredMove result = {.score = -101};
	MoveList* head = possibleMoves;
	while (head) {
		tempBoard = copyBoard(board);
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
		int tempScore = scoreBoard(board, player);
		if(tempScore > maxScore) {
			maxScore = tempScore;
			maxMove = head->data;
		}
		freeBoard(tempBoard);
	}
	ScoredMove result = {.move = maxMove, .score = maxScore};
	return result;
}

int scoreBoard(char** board, int player) {
	if(playerWon(player))
		return 100;
	if(playerWon(otherPlayer(player)))
		return -100;

	int score = 0;
	for (int i = 0; i < BOARD_SIZE; ++i)
	for (int j = 0; j < BOARD_SIZE; ++j) {
		score += scoreChar(board[i][j]);
	}
	return player == WHITE_COLOR
		? score
		: -score;
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