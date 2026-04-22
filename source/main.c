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

#define space 5

int main(){
	srand(time(0));
	int stop = 0;
	int lb = 0;
	int next = 0;

	char name[MAX_NAME];
	srand(time(0));
	printf("Your Tag :");
	scanf("%s" , name);
	get_data();

	init_display();
	init_title();
	while(!next){
		refresh();
		erase();
		while(1){
			int x = option_select();
			draw_title();
			if(x == 7){
				next = 1;
				break;
			}
			else if(x == 8){
				lb = 1;
				break;
			}
			else if(x == 9){
				stop = 1;
				next = 1;
				break;	
			}
			napms(100);
		}
		if(lb == 1){
			while(1){
				refresh();
				erase();
				leaderboard();
				mvprintw(10,20,"Press Q to quit");
				mvprintw(11,20,"Press R to return to main");
				int ch = getch();
				if (ch == 'q' || ch == 'Q') {next = 1;stop = 1;break;}
				if (ch == 'r' || ch == 'R') break;
				napms(100);
			}
		}
	}

	init_score(name);
	init_frame();

	int speed = 250;
	while(stop == 0){
		refresh();
		erase();
		int wave = get_wave();
		push_down();

		if((wave%(space)) ==0) generate_bullet();
		else generate_blank();
		update_wave();

		draw();
		display_score(space);

		if(check_collision()){
			int score = get_score(space);
			update_data(name,score,wave/space);
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
			draw();
			refresh();
			napms(10);
			time+=10;
		}

		check_near_miss();

		if(wave <50) speed = 250;
		else if(wave >=50 && wave< 100) speed = 200;
		else if(wave>100 && wave <120) speed = 170;
		else speed = 150;
	}

	end_display();
	
	if(stop == 0) output_score(space);
}
