#include "Game.h"

void startGame(Settings settings) {
	int playingColor = WHITE_COLOR;
	while(settings.state == GAME_STATE) {
		settings = settings.userColor == playingColor
			? userTurn(settings)
			: computerTurn(settings);
		if(settings.state == TERMINATE_STATE)
				return;
		printBoard(settings.board);
		if(playerWon(settings.board, playingColor)) {
			char* winningMessage = playingColor == WHITE_COLOR
				? WHITE_PLAYER_WINS
				: BLACK_PLAYER_WINS;
			printMessage(winningMessage);
			settings.state = TERMINATE_STATE;
		}
		playingColor = otherPlayer(playingColor);
	}
	freeBoard(settings.board);
}

Settings computerTurn(Settings settings) {
	Move* computerMove = findBestMove(settings.board, settings.minimaxDepth, otherPlayer(settings.userColor));
	settings.board = applyMove(settings.board, computerMove);
	freeMove(computerMove);
	return settings;
}

Settings userTurn(Settings settings) {
	printMessage(ENTER_YOUR_MOVE);
	char* cmd = readString();
	if (startsWith(cmd, "move ")) {
		settings = moveCommand(settings, cmd + 5);
	} else if (strcmp(cmd, "get_moves") == 0) {
		MoveList* moves = getMoves(settings.board, settings.userColor);
		printAllMoves(moves);
		freeMoves(moves);
		settings = userTurn(settings);
	} else if (strcmp(cmd, "quit") == 0) {
		settings.state = TERMINATE_STATE;
	} else {
		printMessage(ILLEGAL_COMMAND);
		settings = userTurn(settings);
	}
	free(cmd);
	return settings;
}

Settings moveCommand(Settings settings, char* moveString) {
	Move* move = parseMove(moveString);
	if(move && validateMove(move, settings.board, settings.userColor)){
		settings.board = applyMove(settings.board, move);
		freeMove(move);
		return settings;
	}
	freeMove(move);
	return userTurn(settings);
}

void printAllMoves(MoveList* moves) {
	MoveList* head = moves;
	while(head) {
		printMove(head->data);
		head = head->next;
	}
}

void printMove(Move* move) {
	char result[MAX_MOVE_LENGTH];
	result[0] = '\0';
	char tempPositionString[6];
	positionToString(move->from, tempPositionString);
	strcat(result, tempPositionString);
	strcat(result, " to ");
	PositionList* dest = move->to;
	while(dest){
		positionToString(dest->data, tempPositionString);
		strcat(result, tempPositionString);
		dest = dest->next;
	}
	printf("%s\n", result);
}

bool playerWon(char** board, int playerColor) {
	MoveList* otherPlayerMoves = getMoves(board, otherPlayer(playerColor));
	if (otherPlayerMoves) {
		freeMoves(otherPlayerMoves);
		return false;
	}
	return true;
}