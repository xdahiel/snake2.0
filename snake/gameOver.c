#include "snake.h"

/*
    *Filename：gameOver.c
    *Author: @2018856302@qq.com
    *Date: 2020.5.14
    *Discription: Deal with all things after playing
*/

/****************************************************
	函数参数：无
	函数功能：显示游戏结束画面
	返回值  ：无
	调用函数：gotoxy
****************************************************/
void game_over(snake s)
{
    char ch;

    free_snake(s);
    update_user_info();
    print_end();

    do
    {
        ch = getch();
    }while (ch != 0xd);

	print_rank();
}

/****************************************************
	函数参数：蛇的头指针
	函数功能：释放蛇占用的所有空间
	返回值  ：无
	调用函数：无
****************************************************/
void free_snake(snake s)
{
    snake q, p;

    //释放内存
	q = p = s;
	while (q)	//当前驱节点为空时，结束循环。
	{
		p = q->next;
		free(q);
		q = p;
	}
}

/****************************************************
	函数参数：无
	函数功能：更新用户数据
	返回值  ：无
	调用函数：get_user_info, open_file_error
****************************************************/
void update_user_info()
{
    int i;
    FILE* fp;
    //获取用户信息
    user* users = get_user_info();

    for (i = 0; i < USER_NUM; ++i)
    {
        //识别当前用户
        if (users[i].id == USER_ID)
        {
            //如果分数超过了该用户历史最高分，则更新
            if (game_score > users[i].highest_score)
            {
                users[i].highest_score = game_score;
            }

            //如果最长游戏时间超过了历史最高，则更新
            if (game_time > users[i].longest_time)
            {
                users[i].longest_time = game_time;
            }

            //修改完则退出
            break;
        }
    }

    //以写方式打开文件
    if ((fp = fopen("users.txt", "w")) == NULL)
    {
        open_file_error();
    }

    //输入更新后的用户数据
    for (i = 0; i < USER_NUM; ++i)
    {
        fprintf(fp, "%d %s %s %s %d %d\n", users[i].id,
        users[i].name, users[i].email, users[i].passwd,
        users[i].highest_score, users[i].longest_time);
    }

    //释放空间，关闭文件
	free(users);
	fclose(fp);
}

/****************************************************
	函数参数：无
	函数功能：打印当前用户当局游戏数据
	返回值  ：无
	调用函数：无
****************************************************/
void print_end()
{
	system("cls");

    gotoxy(40, 8);
    printf("游戏结束！");
    gotoxy(40, 9);
    printf("您的分数为%d, 游戏时长为%ds, 再接再厉！", game_score, game_time);
    gotoxy(40, 12);
    printf("按回车键继续...");
}
