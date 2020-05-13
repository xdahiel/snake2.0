#ifndef SNAKE_H
#define SNAKE_H

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <string.h>
#include <time.h>
#include <Shlwapi.h>


#define LENTH_WALL 25   //ǽ�ĳ���
#define WIDTH_WALL 50   //ǽ�Ŀ��

//�����ߵ����ڵ�ṹ��
struct Snake{
	int x, y;			//���ڵ�ĺ�������
	struct Snake* next;	//���ڵ����һ���ڵ�
};
typedef struct Snake* snake;	//�ṹ��ָ��
typedef struct Snake SNAKE;


//����ʳ��Ľṹ��
typedef struct Food{
    int x, y;
}food;

//�����û��ṹ��
typedef struct User{
	char name[10], email[20], passwd[10];
	int highest_score, longest_time, id;
}user;

/***********************
	���ܣ���¼��Ϸ����
	ȡֵ��Χ��[0��1104]
	�������ù�ϵ��snake_forward_move, game_over, print_map, print_end, update_user_info
	ע�������Ϸ��ʼʱҪ����
***********************/
int game_score;

/***********************
	���ܣ���¼�û���Ϸʱ��
	ȡֵ��Χ��[0��+�ޣ�
	�������ù�ϵ��game_processing, update_user_info
	ע�������
***********************/
int game_time;

/***********************
	���ܣ��趨�Ѷ�ϵ��
	ȡֵ��Χ��{100,75,50,25}
	�������ù�ϵ��snake_move, print_menu
	ע�������
***********************/
int Difficulty_Level;

/***********************
	���ܣ��䵱ʳ��
	ȡֵ��Χ��x��[2, 49], y��[2, 24]
	�������ù�ϵ��place_ok, food_generate, main, snake_move_forward
	ע�������
***********************/
food fd;

/***********************
	���ܣ��Ų�ģʽ����
	ȡֵ��Χ��{0��1}
	�������ù�ϵ��colorful_select, print_snake
	ע�������
***********************/
int COLORFUL_OPTION;

/***********************
	���ܣ�������Ϸ����
	ȡֵ��Χ��{0,1}
	�������ù�ϵ��main, game_over
	ע�������ʼ��Ϊ1
***********************/
int CONTINUE_GAME;

/***********************
	���ܣ���¼�û�����
	ȡֵ��Χ��[0��+�ޣ�
	�������ù�ϵ��get_user_info, update_user_info
	ע�������get_pre_user_info��ʼ��
***********************/
int USER_NUM;

/***********************
	���ܣ���¼�û�ID
	ȡֵ��Χ��[0��+�ޣ�
	�������ù�ϵ��sign_in, update_user_info
	ע�������
***********************/
int USER_ID;

extern void HiddenConsoleCursor();
extern int menu_select(char *option[], int n, int st);
extern void gotoxy(int x, int y);
extern void open_file_error();

extern void game_over(snake s);
extern void free_snake(snake s);
extern void update_user_info();
extern void print_end();

extern void game_processing();
extern void print_map();
extern void food_generate(snake s);
extern void print_snake(snake s, int dir);
extern void snake_move(snake s);
extern void snake_forward_move(snake s, int dir);
extern int is_eat_food(snake s);
extern int is_alive(snake s);
extern int place_ok(int x, int y, snake s);

extern void game_start();
extern void difficulty_level_select();
extern void colorful_select();

extern int cmp(const void *a,const void *b);
extern user* get_user_info();
extern void print_rank();
extern void sign_in();
extern void sign_up();
extern void get_pre_user_num();
extern void users_sort(user* users);


#endif // SNAKE_H_INCLUDED
