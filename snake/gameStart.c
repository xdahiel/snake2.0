#include "snake.h"

/*
    *Filename：gameStart.c
    *Author: @2018856302@qq.com
    *Date: 2020.5.14
    *Discription: Deal with all things before playing
*/

/****************************************************
	函数参数：无
	函数功能：处理游戏前的事务
	返回值  ：无
	调用函数：get_pre_user_num, menu_select, sign_in,
              sigh_up, difficulty_level_select, colorful_select
              ,game_processing
****************************************************/
void game_start()
{
	int op;
	char* option[] = {"注册", "登录"};

	//获取已有用户数目
	get_pre_user_num();

	//处理登录/注册事务
	while (1)
	{
		system("cls");
		gotoxy(35, 10);
		printf("*******贪吃蛇*******");

		gotoxy(30, 11);
		printf("游戏时请开启大写模式，按WASD控制方向。");

		op = menu_select(option, 2, 14);

		if (op) //选择登录
		{
			sign_in();
			//登录后进入游戏
			break;
		}
		else    //选择注册
		{
			sign_up();
		}
	}

	//游戏单独选择
	difficulty_level_select();

	//炫彩模式选择
	colorful_select();

	//由于开启炫彩模式会增加停顿时长，故增加难度系数以平衡
	if(COLORFUL_OPTION)
	{
		Difficulty_Level -= 25;
	}

	//游戏正式开始
	game_processing();
}

/****************************************************
	函数参数：无
	函数功能：选择游戏难度
	返回值  ：无
	调用函数：menu_select
****************************************************/
void difficulty_level_select()
{
	int op;
	char *option[] = {"手残模式","普通模式","灵活模式","死亡模式"};

    system("cls");  //清屏

    gotoxy(32, 10);
    printf("请选择难度（使用↑↓箭头选择）,按Esc键退出游戏");
    op = menu_select(option, 4, 14); //获取选择结果

    //根据选择结果调节难度系数
    switch(op)
    {
        case 0: //手残模式
            Difficulty_Level = 100;
            break;
        case 1: //普通模式
            Difficulty_Level = 75;
            break;
        case 2: //灵活模式
            Difficulty_Level = 50;
            break;
        case 3: //死亡模式
            Difficulty_Level = 25;
            break;
    }
}

/****************************************************
	函数功能：让用户选择是否开启炫彩模式
	参数说明：无
	返回值  ：无
	调用函数：menu_select
****************************************************/
void colorful_select()
{
	char *option[] = {"否", "是"};

    system("cls");
    system("COLOR 0E");

    //进行选择
    gotoxy(20, 10);
    printf("是否开启炫彩模式(若开启炫彩模式，难度也随之减小)？");
	COLORFUL_OPTION = menu_select(option, 2, 14);
}
