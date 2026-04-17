#include<ncurses.h>
#include<unistd.h>

void init_display(){
	initscr();
	noecho();
	cbreak();
	keypad(stdscr , TRUE);
	nodelay(stdscr , TRUE);
	curs_set(0);	
	start_color();
}

void end_display(){
	endwin();
}

int get_input(){
	return getch();
}

void refresh_screen(){
	refresh();
}

void clear_screen(){
	erase();
}

void delay(int ms){
	usleep(ms*1000);
}
