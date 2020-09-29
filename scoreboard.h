//Luca R. L. de Carvalho, 2018
//Intro. Prog. | Eng. de Comp. | CEFET/RJ
#ifndef SCOREBOARD_H
#define SCOREBOARD_H

typedef struct Player{
	char name [128];
	int score;
} Player;

extern void process_score (int moves);
extern int read_scoreboard (Player* output_array);
extern void write_scoreboard (Player* score_array);
extern int cmp_scores (const void* a, const void* b);
extern void init_scoreboard ();
extern void show_scoreboard ();

#endif