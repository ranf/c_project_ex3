#include "Settings.h"

Settings getSettings() {
	Settings settings = {.state = SETTINGS_STATE};
	print_message(ENTER_SETTINGS_MESSAGE);
	while (settings.state == SETTINGS_STATE) {

	}
	
	return settings;
}