#ifndef GAME_
#define GAME_

#include "Settings.h"
#include "Move/Move.h"
#include "Move/Minimax.h"
#include "Board.h"
#include "Utils.h"
#include <string.h>
#include <stdbool.h>

#define MAX_COMMAND_LENGTH 150
#define ENTER_YOUR_MOVE "Enter your move:\n" 
#define ILLEGAL_COMMAND "Illegal command, please try again\n"

void startGame(Settings settings);
Settings computerTurn(Settings settings);
Settings userTurn(Settings settings);
Settings moveCommand(Settings settings, char* moveString);
int getIndexOfFirstSpaceOrEnd(char* str);
void printAllMoves(MoveList* moves);
void printMove(Move* move);
bool playerWon(char** board, int playerColor);

#endif