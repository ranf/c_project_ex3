#ifndef BOARD_
#define BOARD_

#include "Position/Position.h"
#include <stdbool.h>

#define BOARD_SIZE 10

#define BLACK_COLOR 1;
#define WHITE_COLOR 2;

#define WHITE_M 'm'
#define WHITE_K 'k'
#define BLACK_M 'M'
#define BLACK_K 'K'
#define EMPTY ' '

typedef char** Board;

Board setBoard(Board board, Position p, char value);
Board copyBoard(Board board);
bool playerInPosition(Position position, Board board, int player);
char getValueInPosition(Position p, Board board);
bool isKing(char value);
bool isWhite(char value);
bool isBlack(char value);
int otherPlayer(int player);
void print_board(char board[BOARD_SIZE][BOARD_SIZE]);
void init_board(char board[BOARD_SIZE][BOARD_SIZE]);
void printBoardLineSeperator();

#endif