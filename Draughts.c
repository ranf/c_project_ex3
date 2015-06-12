#include "Draughts.h"

int main()
{
	Settings settings = getSettings();
	if(settings.state == GAME_STATE) {
		settings = startGame(settings);
	}
	freeBoard(settings.board);
	return 0;
}