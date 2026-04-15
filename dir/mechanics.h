#ifndef GAME_H
#define GAME_H

void init_frame();
int random_no();
void generate_bullet();
void generate_blank();
void push_down();
void player_posn(char c);
int check_collision();
void draw();
int get_player_col();
void check_near_miss();
int get_near();
int get_Rows();

#endif
