#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ncurses.h>

#define MAX_NAME 20
struct save{
    	char name[MAX_NAME];
    	int score;
    	int max_wave;
    	struct save* next;
};

struct save* head = NULL;

void get_data(){
    FILE* fin = fopen("data/data.csv", "r");
    if(!fin) return;

    char temp[100];
	
    	while(fgets(temp , 100 , fin) != NULL){
		struct save* newsafe = malloc(sizeof(struct save));
        	char *tok = strtok(temp , ",");
		if(!tok) continue;
        	strcpy(newsafe->name , tok);
        	tok = strtok(NULL , ",");
		if(!tok) continue ;
        	newsafe->score = atoi(tok);
        	tok = strtok(NULL , ",");
		if(!tok) continue ;
        	newsafe->max_wave = atoi(tok);

        	newsafe->next = NULL;

         	if(head == NULL){
            		head = newsafe;
        	}
	        else {
            		struct save* curr = head;
            		while(curr->next){
                		curr = curr->next;
            		}
            		curr->next = newsafe;
        	}
    	}
    	fclose(fin);
}


void update_data(char name[] , int score , int max_wave){
	if(head == NULL){
		struct save* newsafe = (struct save*)malloc(sizeof(struct save));
		newsafe->score = score;
		strcpy(newsafe->name , name);
		newsafe->max_wave = max_wave;
		head = newsafe;
		newsafe->next = NULL;
		return;
	}
	struct save* curr = head;
	
	while(curr->next && strcmp(curr->name , name)){
		curr = curr->next;
	}
	if(curr->next == NULL && strcmp(curr->name , name)!=0){
		struct save* newsafe = (struct save*)malloc(sizeof(struct save));
		newsafe->score = score;
		newsafe->max_wave = max_wave;
		strcpy(newsafe->name , name);
		curr->next = newsafe;
		newsafe->next = NULL;
		return ;
	}

	if(curr->score <= score){
		curr->score = score;
		curr->max_wave = max_wave;
	}
}
         

void put_data(){
    	FILE *fput = fopen("data/data.csv" , "w");
    	if(!fput) return;

    	struct save* curr = head;

    	while(curr){
        	fprintf(fput , "%s,%d,%d\n", curr->name , curr->score , curr->max_wave);
        	curr = curr->next;
    	}

    	fclose(fput);
}

void sort_data(){
	if(head == NULL) return;

	struct save* curr = head;
	while(curr){
		int swap = 0;
		struct save* temp = curr->next;
		while(temp && !swap){
			if(temp->score > curr->score){
				char name[MAX_NAME];
				int score;
				int wave;

				strcpy(name , temp->name);
				strcpy(temp->name , curr->name);
				strcpy(curr->name , name);

				score = temp->score;
				temp->score = curr->score;
				curr->score = score;

				wave = temp->max_wave;
				temp->max_wave = curr->max_wave;
				curr->max_wave = wave;
				swap = 1;
			}
			else temp = temp->next;
		}
		if(swap) curr = head;
		else curr = curr->next;
	}
}

void leaderboard(){
	char name[MAX_NAME];
        sort_data();
        struct save* temp = head;
        int rank = 1;

        while(temp){
		strcpy(name, temp->name);
		for(int i = strlen(name);i<MAX_NAME;i++){
			name[i] = ' ';
		}
		name[MAX_NAME - 1] = '\0';
                mvprintw(rank , 1 ,"%d. %s%d %d\n",rank , name , temp->score , temp->max_wave);
                rank++;
                temp = temp->next;
        }
}
