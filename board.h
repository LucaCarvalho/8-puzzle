//Luca R. L. de Carvalho, 2018
//Intro. Prog. | Eng. de Comp. | CEFET/RJ
#ifndef BOARD_H
#define BOARD_H

#define BOARD_SIZE 3 //utilizar APENAS numeros impares
#define WINDOW_SIZE 600
#define TILE_SIZE WINDOW_SIZE/BOARD_SIZE

#include <SDL2/SDL.h>

typedef struct Tile{
	int id;
	SDL_Rect src_rect;
} Tile;

extern Tile board[BOARD_SIZE][BOARD_SIZE]; //[y][x]

extern void generate_board ();
extern void display_board_SDL (SDL_Renderer* renderer, SDL_Texture* texture);
extern void display_board_text();
extern int count_inversions ();
extern void swap_tiles (Tile* t1, Tile* t2);
extern int move_blank (int original_x, int original_y, int target_x, int target_y);

#endif