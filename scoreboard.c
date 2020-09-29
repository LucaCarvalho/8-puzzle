//Luca R. L. de Carvalho, 2018
//Intro. Prog. | Eng. de Comp. | CEFET/RJ
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "scoreboard.h"
#include "board.h"

#define SCOREBOARD_SIZE 10
#define SCORE_FILENAME "score.sco"

void process_score (int moves){
	/* Essa funcao processa o score dado o numero de movimentos
	 * realizados pelo jogador na rodada. 
	 * Se for adequado, requisita o nome do jogador e adiciona
	 * a pontuacao no lugar adequado. 
	 */
	Player scores [SCOREBOARD_SIZE+1];
	char s_input[128];

	read_scoreboard (scores);

	if (moves < scores[SCOREBOARD_SIZE-1].score){
		printf ("Enter your name: ");
		scanf ("%[^\n]%*c", s_input);

		strcpy (scores[SCOREBOARD_SIZE].name, s_input);
		scores[SCOREBOARD_SIZE].score = moves;

		qsort (scores, SCOREBOARD_SIZE+1, sizeof (scores[0]), cmp_scores);

		write_scoreboard (scores);
	}
}

int read_scoreboard (Player* output_array){
	/* Le o scoreboard do arquivo e salva no
	 * array fornecido.
	 * 
	 * Retorna: 0, se o arquivo nao existir; 1, se tudo funcionar.
	 */ 
	FILE* file = fopen (SCORE_FILENAME, "r");

	if (file == NULL)
		return 0;
	
	for (int i=0; 
		fscanf (file, "%d%*c%[^\n]%*c", &output_array[i].score, output_array[i].name)!=EOF &&
		i<SCOREBOARD_SIZE; i++);

	fclose (file);
	return 1;
}

void write_scoreboard (Player* score_array){
	/* Escreve o scoreboard contido no array fornecido
	 * no arquivo.
	 */
	FILE* file = fopen (SCORE_FILENAME, "w");

	for (int i=0; i<SCOREBOARD_SIZE; i++){
		fprintf (file, "%d %s\n", score_array[i].score, score_array[i].name);
	}

	fclose (file);
}

void init_scoreboard (){
	/* Inicializa o scoreboard caso nao exista um.
	 * Por padrao, os nomes sao ' ' e as pontucoes
	 * o maior valor que cabe em um inteiro (signed).
	 * 
	 * Essa funcao deve ser chamada sempre que o programa
	 * inicia.
	 */ 
	Player empty[SCOREBOARD_SIZE];
	if (!read_scoreboard(empty)){
		for (int i=0; i<SCOREBOARD_SIZE; i++){
			empty[i].score = INT_MAX;
			strcpy (empty[i].name, " ");
		}
		write_scoreboard(empty);
	}
}

int cmp_scores (const void* a, const void* b){
	/* Funcao acessoria para uso com o qsort */
	Player s1 = *(Player*)a;
	Player s2 = *(Player*)b;

	if (s1.score < s2.score)
		return -1;
	if (s1.score > s2.score)
		return 1;
	return 0;
}

void show_scoreboard (){
	/* Imprime o scoreboard no stdout*/
	Player scoreboard[SCOREBOARD_SIZE];

	read_scoreboard (scoreboard);
	printf ("###############################################\n");
	printf ("##                HIGH SCORES                ##\n");
	printf ("###############################################\n\n");
	for (int i=0; i<SCOREBOARD_SIZE; i++){
		printf ("#%2d | %32s | %6d\n", i+1, scoreboard[i].name, scoreboard[i].score);
	}
}