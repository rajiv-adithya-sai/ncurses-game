#include <stdio.h>
#include <string.h>
#include "mechanics.h"
#include<ncurses.h>

#define MAX_NAME 7   // 6 chars + '\0'

static char player_name[MAX_NAME];
static int wave = 0;

int get_wave_crossed(int wave, int Rows) {
    return (wave < Rows) ? 0 : (wave - Rows);
}

void init_score(char name[]) {
	strncpy(player_name, name, 6);
	player_name[6] = '\0';
}

void update_wave() {
    wave++;
}

int get_wave(){return wave;}

/*void check_near_miss(char frame_row[], int cols) {
    int player_col = get_player_col();
    if (player_col - 1 >= 0 && frame_row[player_col] == '#')
        near_miss++;

    if (player_col + 1 < cols && frame_row[player_col + 2] == '#')
        near_miss++;
}*/


int get_score() {
	int rows = get_Rows();
	int wave_crossed = get_wave_crossed(wave , rows);
	int near_miss = get_near();
    	return (wave_crossed+2)/3 * 100 + near_miss * 75;
}

void display_score() {
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
        player_name, wave_crossed, get_score()
    );

    mvprintw(2, start_col, "Near Miss: %d", near_miss);

    // Bottom border
    for (int i = 0; i < width; i++) {
        mvaddch(3, start_col + i, '-');
    }

 }
void output_score(){
	int rows = get_Rows();
	int near_miss = get_near();
	int final_wave = get_wave_crossed(get_wave() , rows);

	for(int i=0;i<50;i++){printf("-");}
	printf("\n");
	printf("Player : %s | Wave : %d | Final Score %d\n" , player_name , final_wave/3 , get_score());
	for(int i=0;i<50;i++){printf("-");}
	printf("\n");
}
