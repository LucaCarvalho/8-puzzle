//Luca R. L. de Carvalho, 2018
//Intro. Prog. | Eng. de Comp. | CEFET/RJ
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "scoreboard.h"
#include "board.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

int main (int argc, char* argv[]){
	char image_path [256];
	if (argc > 1)
		strcpy (image_path, argv[1]);
	else
		strcpy (image_path, "image.jpg");
	
	SDL_Window* window;
	SDL_Surface* surface;
	SDL_Renderer* renderer;
	SDL_Texture* texture;
	SDL_Event event;

	SDL_Init (SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_EVENTS);

	window = SDL_CreateWindow("8-Puzzle - Luca Carvalho, 2018", 0, 0, WINDOW_SIZE, WINDOW_SIZE, 0);
	surface = IMG_Load (image_path);
	renderer = SDL_CreateRenderer (window, -1, SDL_RENDERER_ACCELERATED);
	texture = SDL_CreateTextureFromSurface (renderer, surface);
	SDL_FreeSurface (surface);	

	char c_input;
	int moves;
	int zero_x = 0, zero_y = 0;
	int quit = 0;
	time_t initial_time = time (NULL);

	init_scoreboard();
	srand (time(NULL)*clock());

	generate_board();
	moves = 0;
	while (1){
		display_board_SDL (renderer, texture);
		display_board_text();

		if ((!count_inversions() && board[BOARD_SIZE-1][BOARD_SIZE-1].id == 0) || quit){
			if (!quit)
				SDL_Delay (5000);
			break;
		}
		
		while (SDL_PollEvent(&event)){
			if (event.type == SDL_QUIT){
				quit = 1;
				break;
			}
			if (event.type == SDL_KEYDOWN){
				if (event.key.keysym.scancode == SDL_SCANCODE_W){
					if (move_blank(zero_x, zero_y, zero_x, zero_y-1)){
						zero_y--;
						moves++;
						break;
					}
				}
				else if (event.key.keysym.scancode == SDL_SCANCODE_A){
					if (move_blank(zero_x, zero_y, zero_x-1, zero_y)){
						zero_x--;
						moves++;
						break;
					}
				}
				else if (event.key.keysym.scancode == SDL_SCANCODE_S){
					if (move_blank(zero_x, zero_y, zero_x, zero_y+1)){
						zero_y++;
						moves++;
						break;
					}
				}
				if (event.key.keysym.scancode == SDL_SCANCODE_D){
					if (move_blank(zero_x, zero_y, zero_x+1, zero_y)){
						zero_x++;
						moves++;
						break;
					}
				}
			}
		}
		SDL_Delay (1000/60);
	}

	SDL_DestroyRenderer (renderer);
	SDL_DestroyTexture(texture);
	SDL_DestroyWindow (window);
	SDL_Quit();

	system ("clear");
	printf ("=-= STATS =-=\n");
	printf ("Time: %lf minutes\n", difftime (time(NULL), initial_time)/60);
	printf ("Moves: %d\n", moves);
	printf ("=-=-=-=-=-=-=\n\n");
	if (!quit)
		process_score (moves);
	show_scoreboard();

	return 0;
}