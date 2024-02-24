prog: main.o functions.o game.o menu.o
	gcc main.o functions.o game.o menu.o -o prog -g -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf -lm
6main.o: main.c
	gcc -c main.c -g
functions.o: functions.c
	gcc -c functions.c -g -lm
game.o: game.c
	gcc -c game.c -g
menu.o: menu.c
	gcc -c menu.c -g
