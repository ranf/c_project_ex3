#ifndef MINIMAX_
#define MINIMAX_

#include "Move.h"
#include "../Board.h"

#define WINNING_SCORE 100
#define LOSING_SCORE -100

typedef struct {
	Move* move;
	int score;
} ScoredMove;

Move* findBestMove(char** board, int minimaxDepth, int player);
ScoredMove findMaxScoreMove(MoveList* possibleMoves, char** board, int additionalChecks, int player);
ScoredMove maxScoreMoveInList(MoveList* possibleMoves, char** board, int player);
int scoreBoard(char** board, int player);
int scoreChar(char val);
bool canGoInDirection(char** board, Position from, Position (*direction)(Position), int player);
bool cannotPlay(char** board, int player);

#endif