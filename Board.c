#include "Board.h"

char** setBoard(char** board, Position p, char value) {
	char** result = copyBoard(board);
	result[p.x][p.y] = value;
	return result;
}

char** copyBoard(char** board) {
	char** copy = mallocBoard();
	for (int i = 0; i < BOARD_SIZE; i++)
	for (int j = 0; j < BOARD_SIZE; j++){
		copy[i][j] = board[i][j];
	}
	return copy;
}

char** mallocBoard() {
	char** board = malloc(BOARD_SIZE*sizeof(char*));
	for (int i = 0; i < BOARD_SIZE; ++i) {
		board[i] = malloc(BOARD_SIZE*sizeof(char));
	}
	return board;
}

void freeBoard(char** board) {
	for (int i = 0; i < BOARD_SIZE; ++i) {
		free(board[i]);
	}
	free(board);
}

bool playerInPosition(Position position, char** board, int player) {
	char value = getValueInPosition(position, board);
	if(player == WHITE_COLOR && isWhite(value))
		return true;
	if(player == BLACK_COLOR && isBlack(value))
		return true;
	return false;
}

char getValueInPosition(Position p, char** board) {
	return board[p.x][p.y];
}

bool isKing(char value) {
	return value == WHITE_K || value == BLACK_K;
}

bool isWhite(char value) {
	return value == WHITE_K || value == WHITE_M;
}

bool isBlack(char value) {
	return value == BLACK_M || value == BLACK_K;
}

bool isPlayerPiece(char value, int player) {
	return player == WHITE_COLOR ? isWhite(value) : isBlack(value);
}

int otherPlayer(int player) {
	return player == WHITE_COLOR
			? BLACK_COLOR
			: WHITE_COLOR;
}

bool hasNoPieces(char** board, int player) {
	for (int i = 0; i < BOARD_SIZE; ++i)
	for (int j = 0; j < BOARD_SIZE; ++j) {
		if(isPlayerPiece(board[i][j], player))
			return false;
	}
	return true;
}

void printBoard(char** board) {
	int i,j;
	printBoardLineSeperator();
	for (j = BOARD_SIZE-1; j >= 0 ; j--)
	{
		printf((j < 9 ? " %d" : "%d"), j+1);
		for (i = 0; i < BOARD_SIZE; i++){
			printf("| %c ", board[i][j]);
		}
		printf("|\n");
		printBoardLineSeperator();
	}
	printf("   ");
	for (j = 0; j < BOARD_SIZE; j++){
		printf(" %c  ", (char)('a' + j));
	}
	printf("\n");
}

char** initBoard() {
	char** board = mallocBoard();
	int i,j;
	for (i = 0; i < BOARD_SIZE; i++){
		for (j = 0; j < BOARD_SIZE; j++){
			if ((i + j) % 2 == 0){
				if (j <= 3){
					board[i][j] = WHITE_M;
				}
				else if (j >= 6){
					board[i][j] = BLACK_M;
				}
				else{
					board[i][j] = EMPTY;
				}
			}
			else{
				board[i][j] = EMPTY;
			}
		}
	}
	return board;
}

void printBoardLineSeperator() {
	int i;
	printf("  |");
	for (i = 1; i < BOARD_SIZE*4; i++){
		printf("-");
	}
	printf("|\n");
}

void clearBoard(char** board) {
	int i ,j ;
	for (i = 0; i < BOARD_SIZE; i++){
		for (j = 0; j < BOARD_SIZE; j++){
			if ((i + j) % 2 == 0){
				board[i][j] = EMPTY;
			}
		}
	}
}