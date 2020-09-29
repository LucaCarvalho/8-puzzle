# Luca R. L. de Carvalho, 2018
# Intro. Prog. | Eng. de Comp. | CEFET/RJ
# Requer SDL2 e SDL2_image
# Testado com GCC 8.2.1 20180831, sdl2 2.0.9-1 e sdl2_image 2.0.4-1
game: main.o scoreboard.o board.o
	gcc main.o scoreboard.o board.o -o game -lSDL2 -lSDL2_image -lm
main.o: main.c board.h scoreboard.h
	gcc -c main.c
scoreboard.o: scoreboard.c scoreboard.h board.h
	gcc -c scoreboard.c
board.o: board.c board.h
	gcc -c board.c
clean:
	rm *.o