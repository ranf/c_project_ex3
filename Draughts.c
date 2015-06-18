#include "Draughts.h"

int main()
{
	printMessage(WELCOME_TO_DRAUGHTS);
	Settings settings = getSettings();
	if(settings.state == GAME_STATE) {
		settings = startGame(settings);
	}
	freeBoard(settings.board);
	return 0;
}