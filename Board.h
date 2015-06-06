#ifndef BOARD_
#define BOARD_

#include "Position/Position.h"
#include <stdbool.h>
#include <stdio.h>

#define BOARD_SIZE 10

#define BLACK_COLOR 1
#define WHITE_COLOR 2

#define WHITE_M 'm'
#define WHITE_K 'k'
#define BLACK_M 'M'
#define BLACK_K 'K'
#define EMPTY ' '

char** setBoard(char** board, Position p, char value);
char** copyBoard(char** board);
bool playerInPosition(Position position, char** board, int player);
char getValueInPosition(Position p, char** board);
bool isKing(char value);
bool isWhite(char value);
bool isBlack(char value);
int otherPlayer(int player);
void printBoard(char** board);
char** initBoard();
void printBoardLineSeperator();

#endif