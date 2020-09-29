//Luca R. L. de Carvalho, 2018
//Intro. Prog. | Eng. de Comp. | CEFET/RJ
#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include <SDL2/SDL.h>

Tile board[BOARD_SIZE][BOARD_SIZE]; //[y][x]

void generate_board (){
	/* Quando chamada, um tabuleiro eh gerado e
	 * armazenado na variavel global "board".
	 * Para isso, gera-se um tabuleiro e verifica-se
	 * se ele eh valido. Caso nao seja, outro eh
	 * gerado.
	 * (aparentemente, exatamente metade dos tabuleiros
	 * possiveis de gerar sao impossiveis de resolver)
	 */
	int used [BOARD_SIZE*BOARD_SIZE];
	SDL_Rect rectangles [BOARD_SIZE*BOARD_SIZE];

	//Gera um array de retangulos (proporcoes e posicoes adequados) cujos indices correpondem aos ids dos tiles
	rectangles [0].x = WINDOW_SIZE-TILE_SIZE;
	rectangles [0].y = WINDOW_SIZE-TILE_SIZE;
	rectangles [0].h = rectangles[0].w = TILE_SIZE;
	for (int i=1, y=0, x=0; i<BOARD_SIZE*BOARD_SIZE; i++){
		if (x >= WINDOW_SIZE){
			x = 0;
			y += TILE_SIZE;
		}
		//printf ("%d x %d y %d\n", i, x, y);
		rectangles[i].x = x;
		rectangles[i].y = y;
		rectangles [i].h = rectangles[i].w = TILE_SIZE;
		x += TILE_SIZE;
	}

	//O primeiro sempre eh o vazio
	board[0][0].id = 0;
	board[0][0].src_rect = rectangles[0];

	//Gera o tabuleiro em si
	while (1){
		used[0] = 1;
		for (int i=1; i<BOARD_SIZE*BOARD_SIZE; i++)
			used[i] = 0;
		for (int i=0; i<BOARD_SIZE; i++){
			for (int j=(!i?1:i*BOARD_SIZE); j<i*BOARD_SIZE+BOARD_SIZE; j++){
				while (1){
					int n = rand()%(BOARD_SIZE*BOARD_SIZE);
					if (!used[n]){
						board[i][j%BOARD_SIZE].id = n;
						board[i][j%BOARD_SIZE].src_rect = rectangles [n];
						used [n] = 1;
						break;
					}
				}
			}
		}

		if (count_inversions()%2 == 0)
			break;
	}
	
}

void display_board_SDL (SDL_Renderer* renderer, SDL_Texture* texture){
	/* Copia para o renderer fornecido o tabuleiro no estado atual
	 * (dada a textura que contem a imagem a ser utilizada)*/
	SDL_Rect destination_rect;
	destination_rect.h = destination_rect.w = TILE_SIZE;

	SDL_RenderClear (renderer);
	for (int i=0; i<BOARD_SIZE; i++){
		for (int j=0; j<BOARD_SIZE; j++){
			//printf ("board[%d][%d]: x %d y %d\n", i, j, board[j][i].src_rect.x, board[j][i].src_rect.y);
			if (board[i][j].id){//se nao eh o tile vazio
				//printf ("board[%d][%d]: x %d y %d\n", i, j, board[i][j].src_rect.x, board[i][j].src_rect.y);
				destination_rect.x = j*TILE_SIZE;
				destination_rect.y = i*TILE_SIZE;
				SDL_RenderCopy (renderer, texture, &board[i][j].src_rect, &destination_rect);
			}
		}
	}
	SDL_RenderPresent (renderer);
}

void display_board_text (){
	/* Simplesmente imprime o tabuleiro no estado atual
	 * em stdout.
	 */
	for (int i=0; i<BOARD_SIZE; i++){
		for (int j=0; j<BOARD_SIZE; j++){
			printf("%d ", board[i][j].id);
		}
		printf ("\n");
	}
	printf ("---\n");
}

int count_inversions (){
	/* Essa funcao conta o numero de inversoes encontradas
	 * no tabuleiro.
	 * Isso eh feito contando-se a quantidade de tiles com
	 * id menor na frente de cada tile (nao inclui 0).
	 * 
	 * Retorno: numero de inversoes encontradas
	*/
	int inversions = 0;

	//O tabuleiro eh copiado em um array unidimensional
	Tile board_1d[BOARD_SIZE*BOARD_SIZE];
	for (int i=0; i<BOARD_SIZE; i++){
		for (int j=i*BOARD_SIZE; j<i*BOARD_SIZE+BOARD_SIZE; j++){
			board_1d[j] = board[i][j%BOARD_SIZE];
		}
	}

	for (int i=0; i<BOARD_SIZE*BOARD_SIZE; i++){
		int current = board_1d[i].id;
		if (current){ //0 nao eh incluido
			for (int j=i; j<BOARD_SIZE*BOARD_SIZE; j++){
				if (board_1d[j].id < current && board_1d[j].id){
					inversions++;
				}
			}
		}
	}

	return inversions;
}

void swap_tiles (Tile* t1, Tile* t2){
	Tile tmp = *t1;
	*t1 = *t2;
	*t2 = tmp;
}

int move_blank (int original_x, int original_y, int target_x, int target_y){
	/* Essa funcao verifica se o movimento requisitado eh valido
	 * e entao permuta os dois tiles, dadas as suas coordenadas.
	 * (usualmente, um deles eh o tile vazio)
	 * 
	 * original_x e original_y sao as posicoes originais
	 * target_x e target_y sao as posicoes desejadas
	 * 
	 * Retorno: 0, se estiver fora dos limites; 1 , se funcionar
	 */

	//Verifica se o alvo esta fora dos limites
	if (target_x < 0 || target_x > BOARD_SIZE-1 || target_y < 0 || target_y > BOARD_SIZE-1)
		return 0;
	swap_tiles (&board[original_y][original_x], &board[target_y][target_x]);
	return 1;
}