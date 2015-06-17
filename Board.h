#ifndef BOARD_
#define BOARD_

#include "Position/Position.h"
#include "Utils.h"
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
char** setBoardAndFree(char** board, Position p, char value);
char** copyBoard(char** board);
bool playerInPosition(Position position, char** board, int player);
char getValueInPosition(Position p, char** board);
bool isKing(char value);
bool isWhite(char value);
bool isBlack(char value);
bool isPlayerPiece(char value, int player);
int otherPlayer(int player);
bool hasNoPieces(char** board, int player);
void printBoard(char** board);
char** initBoard();
void printBoardLineSeperator();
char** mallocBoard();
void freeBoard(char** board);
void clearBoard(char** board);
bool endOfBoard(Position p, int player);
bool emptyBoard(char** board);
bool oneColorBoard(char** board);
bool moreThen20Discs(char** board);
char crownPiece(char value);
int piecePlayer(char value);
	
#endif