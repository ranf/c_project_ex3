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

Move* findMaxScore(MoveList* possibleMoves, char** board, int additionalChecks, int player) {
	if(additionalChecks == 0) {
		// possibleMoves find with max score
		//		apply
		//		scoreBoard
		//		return the move with bet score
	}
	//foreach move
	//	apply move
	//	get other player moves
	//	recursive call to find the best out of them
}

int scoreBoard(char** board, int player) {
	if(playerWon(player))
		return 100;
	if(playerWon(otherPlayer(player)))
		return -100;

	int score = 0;
	for (int i = 0; i < BOARD_SIZE; ++i)
	for (int j = 0; j < BOARD_SIZE; ++j)
	{
		score = player == WHITE_COLOR
			? score + scoreChar(board[i][j])
			: score - scoreChar(board[i][j]);
	}
	return score;
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