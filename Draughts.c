#include "Draughts.h"

int main()
{
	Settings settings = getSettings();
	if(settings.state == GAME_STATE) {
		startGame(settings);
	}
	return 0;
}