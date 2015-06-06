#ifndef GAME_
#define GAME_

#include "Settings.h"
#include "Move/Move.h"
#include "Board.h"

#define MAX_COMMAND_LENGTH 150
#define ENTER_YOUR_MOVE "Enter your move:\n" 

void startGame(Settings settings);
Settings computerTurn(Settings settings);
Settings userTurn(Settings settings);
Settings moveCommand(Settings settings, char* moveString);
Board applyMove(Settings settings, Move move);
char* getIndexOfFirstSpaceOrEnd(char* str);

#endif