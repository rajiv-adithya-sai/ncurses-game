#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
#include<ncurses.h>

#include "score_panel.h"
#include "mechanics.h"
#include "display.h"
#include "savedata.h"
#include "opening.h"

int main(){
	int stop = 0;
	char name[MAX_NAME];
	srand(time(0));
	printf("Your Tag(:");
	scanf("%s" , name);
	
	init_display();
	get_data();
	//init_title();
	/*while(1){
		int x = option_select();
		draw_title();
		if(x == 8){
			break;
		}
		else if(x == 9){
			system("clear");
			leaderboard();
			break;
		}
		else if(x == 10){
			stop = 1;
			break;	
		}
		napms(300);
	}*/
	//show_title();
	init_score(name);
	init_frame();
	int speed = 500;
	while(stop == 0){
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
		int time = 0;
		while(time<speed){
			ch = get_input();
			if(ch == KEY_LEFT || ch == 'a') player_posn('a');
			else if (ch == KEY_RIGHT || ch == 'd') player_posn('d');
			if(ch == 'e') stop = 1;
			napms(10);
			time+=10;
		}

		check_near_miss();

		refresh_screen();
		if(wave <50) speed = 500;
		else if(wave >=50 && wave< 100) speed = 400;
		else if(wave>100 && wave <120) speed = 350;
		else speed = 300;
	}
	
	end_display();
	
	output_score();

	system("make clean");
}
