#ifndef DRAUGHTS_
#define DRAUGHTS_

#include "Settings.h"
#include "Game.h"

#define WELCOME_TO_DRAUGHTS "Welcome to Draughts!\n"
#define ENTER_SETTINGS "Enter game settings:\n" 
#define WRONG_MINIMAX_DEPTH "Wrong value for minimax depth. The value should be between 1 to 6\n"
#define ILLEGAL_COMMAND "Illegal command, please try again\n"
#define WROND_BOARD_INITIALIZATION "Wrong board initialization\n"
 

#define perror_message(func_name) (fprintf(stderr, "Error: standard function %s has failed\n", func_name))
#define print_message(message) (printf("%s", message));

#endif  
