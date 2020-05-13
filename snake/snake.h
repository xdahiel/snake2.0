#ifndef SNAKE_H
#define SNAKE_H

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <string.h>
#include <time.h>
#include <Shlwapi.h>


#define LENTH_WALL 25   //墙的长度
#define WIDTH_WALL 50   //墙的宽度

//设置蛇的链节点结构体
struct Snake{
	int x, y;			//链节点的横纵坐标
	struct Snake* next;	//链节点的下一个节点
};
typedef struct Snake* snake;	//结构体指针
typedef struct Snake SNAKE;


//设置食物的结构体
typedef struct Food{
    int x, y;
}food;

//定义用户结构体
typedef struct User{
	char name[10], email[20], passwd[10];
	int highest_score, longest_time, id;
}user;

/***********************
	功能：记录游戏分数
	取值范围：[0，1104]
	函数调用关系：snake_forward_move, game_over, print_map, print_end, update_user_info
	注意事项：游戏开始时要归零
***********************/
int game_score;

/***********************
	功能：记录用户游戏时长
	取值范围：[0，+∞）
	函数调用关系：game_processing, update_user_info
	注意事项：无
***********************/
int game_time;

/***********************
	功能：设定难度系数
	取值范围：{100,75,50,25}
	函数调用关系：snake_move, print_menu
	注意事项：无
***********************/
int Difficulty_Level;

/***********************
	功能：充当食物
	取值范围：x∈[2, 49], y∈[2, 24]
	函数调用关系：place_ok, food_generate, main, snake_move_forward
	注意事项：无
***********************/
food fd;

/***********************
	功能：炫彩模式开关
	取值范围：{0，1}
	函数调用关系：colorful_select, print_snake
	注意事项：无
***********************/
int COLORFUL_OPTION;

/***********************
	功能：控制游戏运行
	取值范围：{0,1}
	函数调用关系：main, game_over
	注意事项：初始化为1
***********************/
int CONTINUE_GAME;

/***********************
	功能：记录用户数量
	取值范围：[0，+∞）
	函数调用关系：get_user_info, update_user_info
	注意事项：用get_pre_user_info初始化
***********************/
int USER_NUM;

/***********************
	功能：记录用户ID
	取值范围：[0，+∞）
	函数调用关系：sign_in, update_user_info
	注意事项：无
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
