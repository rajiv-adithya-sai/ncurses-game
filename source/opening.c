#include<stdio.h>
#include <ncurses.h>
#include<string.h>
//#include<locale.h>
#define dim 40
#define init_posn 8

char title[dim][dim];
int point_row = init_posn;
void init_title(){
	for(int i=0;i<dim;i++){
		for(int j =0;j<dim;j++){
			title[i][j] = ' ';
		}
	}
	FILE* fin = fopen("../assets/title.txt" , "r");
	char temp[100];
	int row = 0;
	while(fgets(temp , sizeof(temp) , fin)){
		temp[strcspn(temp , "\n")] = '\0';
		for(int j=0;j<strlen(temp);j++){
			title[row][j] = temp[j];
		}
		row++;
	}
	fclose(fin);
}

int option_select(){
	int ch = getch();
	if((ch == KEY_DOWN || ch == 's') && point_row<10){
		point_row ++;
		return 0;
	}
	else if ((ch == KEY_UP || ch == 'w')&& point_row > 8) {
		point_row--;
		return 0;
	}
	else if (ch == '\n'){
		return point_row;
	}
	else return 0;
}


void draw_title(){
	for(int i=0;i<dim;i++){
		for(int j=0;j<dim;j++){
			if(i == point_row && j==0){
				mvaddch(i+4 , 0 , '>');
			}
			
			else mvaddch(i+4 ,j, title[i][j]);
		}	
	}
}
