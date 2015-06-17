#include "Game.h"

Settings startGame(Settings settings) {
	while (settings.state == GAME_STATE) {
		settings = settings.userColor == settings.playingColor
			? userTurn(settings)
			: computerTurn(settings);
		if(settings.state == TERMINATE_STATE)
				return settings;
		printBoard(settings.board);
		if(playerWon(settings.board, otherPlayer(settings.playingColor))) {
			char* winningMessage = otherPlayer(settings.playingColor) == WHITE_COLOR
				? WHITE_PLAYER_WINS
				: BLACK_PLAYER_WINS;
			printMessage(winningMessage);
			settings.state = TERMINATE_STATE;
		}
	}
	return settings;
}

Settings computerTurn(Settings settings) {
	Move* computerMove = findBestMove(settings.board, settings.minimaxDepth, otherPlayer(settings.userColor));
	settings.board = applyMove(settings.board, computerMove);
	printf("Computer: move ");
	printMove(computerMove);
	freeMove(computerMove);
	settings.playingColor = settings.userColor;
	return settings;
}

Settings userTurn(Settings settings) {
	printMessage(ENTER_YOUR_MOVE);
	while (settings.state == GAME_STATE && settings.playingColor == settings.userColor) {
		char* cmd = readString();
		settings = executeUserCommand(settings, cmd);
		free(cmd);
	}
	return settings;
}

Settings executeUserCommand(Settings settings, char* cmd) {
	if (startsWith(cmd, "move ")) {
		settings = moveCommand(settings, cmd + 5);
		settings.playingColor = otherPlayer(settings.userColor);
	} else if (strcmp(cmd, "get_moves") == 0) {
		MoveList* moves = getMoves(settings.board, settings.userColor);
		printAllMoves(moves);
		freeMoves(moves);
	} else if (strcmp(cmd, "quit") == 0) {
		settings.state = TERMINATE_STATE;
	} else {
		printMessage(ILLEGAL_COMMAND);
	}
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
	char tempPositionString[7];
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