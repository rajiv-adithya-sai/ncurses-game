#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
#include<ncurses.h>

#include "score_panel.h"
#include "mechanics.h"
#include "display.h"
#include "savedata.h"

int main(){
	char name[MAX_NAME];
	srand(time(0));
	printf("Your Tag(:");
	scanf("%s" , name);
	
	init_display();

	//show_title();
	get_data();
	init_score(name);
	init_frame();
	int speed = 500;
	while(1){
		clear_screen();
		int wave = get_wave();
		push_down();

		if((wave%3) ==0) generate_bullet();
		else generate_blank();
		update_wave();

		draw();
		display_score();

		if(check_collision()){
			int score = get_score();
			update_data(name,score,wave/3);
			put_data();
			break;
		}
		int ch;
		int stop;
		int time = 0;
		while(time<speed){
			ch = get_input();
			if(ch == KEY_LEFT || ch == 'a') player_posn('a');
			else if (ch == KEY_RIGHT || ch == 'd') player_posn('d');
			if(ch == 'e') stop = 1;
			delay(10);
			time+=10;
		}

		check_near_miss();

		refresh_screen();
		if(stop == 1) break;
		if(wave <50) speed = 500;
		else if(wave >=50 && wave< 100) speed = 400;
		else if(wave>100 && wave <120) speed = 350;
		else speed = 300;
	}
	
	end_display();
	
	output_score();
	leaderboard();

	system("make clean");
}
