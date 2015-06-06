#include "Board.h"

char** setBoard(char** board, Position p, char value) {
	char** result = copyBoard(board);
	result[p.x][p.y] = value;
	return result;
}

char** copyBoard(char** board){
	char** copy[BOARD_SIZE][BOARD_SIZE];
	for (int i = 0; i < BOARD_SIZE; i++)
	for (int j = 0; j < BOARD_SIZE; j++){
		copy[i][j] = board[i][j];
	}
	return result;
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

int otherPlayer(int player) {
	return player == WHITE_COLOR
			? BLACK_COLOR
			: WHITE_COLOR;
}

void printBoard(char** board)
{
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
	char board[BOARD_SIZE][BOARD_SIZE];
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