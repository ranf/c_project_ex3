#ifndef MINIMAX_
#define MINIMAX_

#include "Move.h"

typedef struct {
	Move* move;
	int score;
} ScoredMove;

Move* findBestMove(char** board, int minimaxDepth, int player);
ScoredMove findMaxScoreMove(MoveList* possibleMoves, char** board, int additionalChecks, int player);
ScoredMove maxScoreMoveInList(MoveList* possibleMoves, char** board, int player);
int scoreBoard(char** board, int player);
int scoreChar(char val);

#endif