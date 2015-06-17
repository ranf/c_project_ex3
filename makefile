CFLAGS=-std=c99 -pedantic-errors -c -Wall -g -lm
OBJ=Draughts.o Settings.o Game.o Board.o Utils.o Move/Move.o Move/ManMove.o Move/KingMove.o Move/EatMove.o Move/Minimax.o Position/Position.o

all: Draughts 

clean:
	-rm Draughts $(OBJ)

Draughts: $(OBJ)
	gcc -o Draughts $(OBJ) -lm -std=c99 -pedantic-errors -g

Draughts.o: Draughts.h Draughts.c
	gcc $(CFLAGS) Draughts.c

Settings.o: Settings.h Settings.c
	gcc $(CFLAGS) Settings.c

Game.o: Game.h Game.c
	gcc $(CFLAGS) Game.c

Board.o: Board.h Board.c
	gcc $(CFLAGS) Board.c

Utils.o: Utils.h Utils.c
	gcc $(CFLAGS) Utils.c

Move/Move.o: Move/Move.h Move/Move.c
	gcc $(CFLAGS) Move/Move.c -o Move/Move.o

Move/ManMove.o: Move/ManMove.h Move/ManMove.c
	gcc $(CFLAGS) Move/ManMove.c -o Move/ManMove.o

Move/KingMove.o: Move/KingMove.h Move/KingMove.c
	gcc $(CFLAGS) Move/KingMove.c -o Move/KingMove.o

Move/EatMove.o: Move/EatMove.h Move/EatMove.c
	gcc $(CFLAGS) Move/EatMove.c -o Move/EatMove.o

Position/Position.o: Position/Position.h Position/Position.c
	gcc $(CFLAGS) Position/Position.c -o Position/Position.o

Move/Minimax.o: Move/Minimax.h Move/Minimax.c
	gcc $(CFLAGS) Move/Minimax.c -o Move/Minimax.o