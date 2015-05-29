CFLAGS=-std=c99 -pedantic-errors -c -Wall -g -lm

all: Draughts 

clean:
	-rm Draughts.o Draughts Settings.o

Draughts: Draughts.o Settings.o Game.o
	gcc -o Draughts Draughts.o Settings.o Game.o -lm -std=c99 -pedantic-errors -g

Draughts.o: Draughts.h Draughts.c
	gcc $(CFLAGS) Draughts.c

Settings.o: Settings.h Settings.c
	gcc $(CFLAGS) Settings.c

Game.o: Game.h Game.c
	gcc $(CFLAGS) Game.c