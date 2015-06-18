#ifndef GAME_
#define GAME_

#include "Settings.h"
#include "Move/Move.h"
#include "Move/Minimax.h"
#include "Board.h"
#include "Utils.h"
#include <string.h>
#include <stdbool.h>

#define ENTER_YOUR_MOVE "Enter your move:\n" 
#define WHITE_PLAYER_WINS "White player wins!\n"
#define BLACK_PLAYER_WINS "Black player wins!\n"

#define MAX_MOVE_LENGTH 150

Settings startGame(Settings settings);
Settings computerTurn(Settings settings);
Settings userTurn(Settings settings);
Settings moveCommand(Settings settings, char* moveString);
Settings executeUserCommand(Settings settings, char* cmd);
void printAllMoves(MoveList* moves);
void printMove(Move* move);
bool playerWon(char** board, int playerColor);

#endif