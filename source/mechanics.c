#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<ncurses.h>
#include<locale.h>

#define Rows 30
#define Cols 45

char bullet = '#';
char frame[Rows+2][Cols+2];

int player_col = (Cols/2);
int near_miss = 0;

void init_frame(){
    init_pair(1, COLOR_RED , COLOR_BLACK);
    init_pair(2,COLOR_YELLOW , COLOR_BLACK);

    for(int i=0;i<Rows+2;i++){ 
        frame[i][0] = '|';
        frame[i][Cols+1]= '|';
    }

    for(int i=0;i<Cols+2;i++){
        frame[0][i] = '-';
        frame[Rows+1][i] = '-';
    }

    for(int i=0;i<Rows;i++){
        for(int j=0;j<Cols;j++){
            frame[i+1][j+1] = ' ';
        }
    }
    setlocale(LC_ALL ,"");
}
/*int random_no(){
    return rand()%(1 << Cols);
}*/

unsigned long long generate_k_bits(int n, int k) {
    if (k == 0) return 0;
    if (k == n) return (1 << n) - 1;

    if (rand() % n < k)
        return (1 << (n - 1)) | generate_k_bits(n - 1, k - 1);
    else
        return generate_k_bits(n - 1, k);
}

unsigned long long random_no() {
	int bullets = rand()%((Cols)/2);
	return generate_k_bits(Cols , bullets+(Cols/4));
}

void generate_bullet(){
    unsigned long long barrage = random_no();

    for(int i=0;i<Cols;i+=1){
        if(barrage & 1){
		frame[1][i+1] = bullet ;
	}
        barrage >>= 1;
    }
}

void generate_blank(){
	for(int i=0;i<Cols;i++){
		frame[1][i+1] = ' ';
	}
}

void push_down(){
    for(int i=Rows-1;i>0;i--){
        for(int j=1;j<=Cols;j++){
            frame[i+1][j] = frame[i][j];
        }
    }

    for(int j=1;j<=Cols;j++){
        frame[1][j] = ' ';
    }
}

void player_posn(char c){
	if(c=='d') player_col = (player_col+1)%Cols;
	else if (c== 'a') player_col = (player_col-1+Cols)%Cols;
	else return;
}

int get_player_col(){
	return player_col;
}

int check_collision(){
    return (frame[Rows][player_col-1] == bullet /*|| frame[Rows][player_col+1] == '_'*/);
}

void check_near_miss(){
	if(player_col  <Cols && frame[Rows-2][player_col] == bullet) near_miss++;
       	if(player_col - 1 > 0 && frame[Rows-2][player_col-2] == bullet) near_miss++;
}

int get_near(){
	return near_miss;
}

int get_Rows(){
	return Rows;
}

void draw() {
    static int time = 0;

    for (int i = 0; i < Rows + 2; i++) {
        for (int j = 0; j < Cols + 2; j++) {
            if (i == Rows && j == player_col - 1) {
                if (time % 4 == 0)
                    attron(COLOR_PAIR(2)); 
                else
                    attron(COLOR_PAIR(1)); 

                mvaddch(i + 4, j, ACS_CKBOARD);

                attroff(COLOR_PAIR(1));
                attroff(COLOR_PAIR(2));
            }
	    else {
	    	mvaddch(i+4 , j , frame[i][j]);
	    }
        }
    }
    time++; 
}

/*void draw(){
    for(int i=0;i<Rows+2;i++){
        for(int j=0;j<Cols+2;j++){
            if(i==Rows && j==player_col+1)
                printf("P");
            else
                printf("%c", frame[i][j]);
        }
        printf("\n");
    }
}*/
