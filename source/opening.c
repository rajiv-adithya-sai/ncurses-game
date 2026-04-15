#include<stdio.h>
#include<ncurses.h>

char index[50][50] = {" "};
void show_title(){
	FILE* fin = fopen(title.txt , "r");
	char temp[100];
	int count = 4;
	while(fscanf(fin , "%[\n]\n" ,temp)){
		temp[strcspn(str , "\n")] = '\0';
		sprintf(temp , "%s" , index[count]);
		count++;
	}
}

void option_select(){
	char point = '►';
}
