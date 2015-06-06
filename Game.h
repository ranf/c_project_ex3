#ifndef GAME_
#define GAME_

#include "Settings.h"
#include "Move/Move.h"

#define ENTER_YOUR_MOVE "Enter your move:\n" 

void startGame(Settings settings);
char computerTurn(Settings settings);
Settings userTurn(Settings settings);
Settings moveCommand(Settings settings, char* moveString);
Settings applyMove(Settings settings, Move move);

#include "Board.h"

#endif