#include "Game.h"

void startGame(struct Settings settings) {
	int playingColor = WHITE_COLOR;
	while(settings.state == GAME_STATE) {
		if(settings.userColor== playingColor){
			settings.board = userTurn(settings);
			if(settings.state==GAME_STATE)
				printBoard();
		} else {
			settings.board = computerTurn(settings);
			printBoard();
		}
		if(gameEnded()){
			xWon();
			settings.state = TERMINATING_STATE;
		}
		playingColor = playingColor==WHITE_COLOR ? BLACK_COLOR:WHITE_COLOR;
	}
}

char computerTurn(Settings settings) {
	Move computerMove = findBestMove(board, minimaxDepth, computerColor);
	applyMove(board, computerMove);
}