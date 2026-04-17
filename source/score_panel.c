#include <stdio.h>
#include <string.h>
#include "mechanics.h"
#include<ncurses.h>

#define MAX_NAME 20   

static char player_name[MAX_NAME];
static int wave = 0;

int get_wave_crossed(int wave, int Rows) {
    return (wave < Rows) ? 0 : (wave - Rows);
}

void init_score(char name[]) {
	strncpy(player_name, name, 6);
	player_name[MAX_NAME-1] = '\0';
}

void update_wave() {
    wave++;
}

int get_wave(){return wave;}

int get_score(int space) {
	int rows = get_Rows();
	int wave_crossed = get_wave_crossed(wave , rows);
	int near_miss = get_near();
    	return (wave_crossed-1)/space +1 * 100 + near_miss * 75;
}

void display_score(int space) {
    int rows = get_Rows();
    int near_miss = get_near();
    int wave_crossed = get_wave_crossed(get_wave(), rows);

    int start_col = 2;   // left margin
    int width = 50;

    // Top border
    for (int i = 0; i < width; i++) {
        mvaddch(0, start_col + i, '-');
    }

    // Score text
    mvprintw(1, start_col,
        "Player: %s | Wave: %d | Score: %d",
        player_name, wave_crossed/space, get_score(space));

    mvprintw(2, start_col, "Near Miss: %d", near_miss);

    // Bottom border
    for (int i = 0; i < width; i++) {
        mvaddch(3, start_col + i, '-');
    }

 }
void output_score(int space){
	int rows = get_Rows();
	int near_miss = get_near();
	int final_wave = get_wave_crossed(get_wave() , rows);

	for(int i=0;i<50;i++){printf("-");}
	printf("\n");
	printf("Player : %s | Wave : %d | Final Score %d\n" , player_name , final_wave/space , get_score(space));
	for(int i=0;i<50;i++){printf("-");}
	printf("\n");
}
