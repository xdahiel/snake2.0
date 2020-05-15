#include "snake.h"

/*
    *Filename：gameProcessing.c
    *Author: @2018856302@qq.com
    *Date: 2020.5.14
    *Discription: Deal with all things while playing
*/

/****************************************************
	函数参数：无
	函数功能：处理游戏中的事务
	返回值  ：无
	调用函数：print_map, food_generate, snake_move, game_over
****************************************************/
void game_processing()
{
    snake s, p;
    clock_t st, end;

    //黄黑在终端中的对比度高于白黑
    system("color 0E");

    //构造初始蛇身与出生点
    s = (snake)malloc(sizeof(SNAKE));
    p = (snake)malloc(sizeof(SNAKE));
    s->x = 25, s->y = 23, s->next = p;
    p->x = 25, p->y = 24, p->next = NULL;

    //打印地图
    print_map();

    //生成第一个食物
    food_generate(s);

    //开始时刻
    st = clock();

    //蛇开始移动
    snake_move(s);

    //结束时可
    end = clock();

    //计算游戏时间
    game_time = (end - st) / CLK_TCK;

    //游戏结束
    game_over(s);
}

/****************************************************
	函数参数：无
	函数功能：打印地图
	返回值  ：无
	调用函数：gotoxy
****************************************************/
void print_map()
{
	int i, j;
	char Map[LENTH_WALL+1][WIDTH_WALL+1];   //储存地图

    system("cls");

	//二重循环输入地图
    for (i = 0; i < LENTH_WALL+1; ++i)	//依长度遍历
    {
        for (j = 0; j < WIDTH_WALL+1; ++j)	//依宽度遍历
        {
            if (i == 0 || i == LENTH_WALL)	//边界
            {
                Map[i][j] = '=';
            }
            else if (j == 0 || j == WIDTH_WALL)	//边界
            {
                Map[i][j] = '#';
            }
            else	//边界内打空格
            {
                Map[i][j] = ' ';
            }
        }
    }

    //二重循环输出地图
    for (i = 0; i <= LENTH_WALL; ++i)
    {
        for (j = 0; j <= WIDTH_WALL; ++j)
        {
            printf("%c", Map[i][j]);
        }
        printf("\n");
    }

    //显示初始分数
    gotoxy(70, 10);
    printf("score: %d", game_score);
}

/****************************************************
	函数参数：无
	函数功能：生成食物
	返回值  ：无
	调用函数：gotoxy
****************************************************/
void food_generate(snake s)
{
	int x, y;

    //随机生成横纵坐标
    srand(time(NULL));
    x = rand()%(WIDTH_WALL-2) + 1;
    y = rand()%(LENTH_WALL-2) + 1;

    //判断食物是否放置合理
    if (place_ok(x, y, s))
    {
        x = rand()%(WIDTH_WALL-2) + 1;
        y = rand()%(LENTH_WALL-2) + 1;
    }

    //显示食物
    gotoxy(x, y);
    printf("$");

    fd.x = x, fd.y = y;
}

/****************************************************
	函数参数：无
	函数功能：打印蛇
	返回值  ：无
	调用函数：gotoxy
****************************************************/
void print_snake(snake s, int dir)
{
    snake p = s;
	int t;
	char head;

    gotoxy(p->x, p->y);

	//根据蛇头朝向打印蛇头
    switch(dir)
    {
        case 'W':
            head = 'A';
            break;
        case 'S':
            head = 'V';
            break;
        case 'A':
            head = '<';
            break;
        case 'D':
            head = '>';
            break;
    }
    printf("%c", head);

    //打印蛇身
    while (p->next)	//若该节点不是最后一个节点，则继续
    {
        p = p->next;
        gotoxy(p->x, p->y);
        printf("o");
    }

    //如果玩家开启了炫彩模式，每次打印蛇的时候，顺便随机给界面换颜色
    if (COLORFUL_OPTION)
    {
        char cl[9];

        //获取随机数
        srand(time(NULL));
        t = rand()%10;

        //更换颜色
        sprintf(cl, "color 0%d", t);
        system(cl);
    }
}

/****************************************************
	函数参数：蛇头指针
	函数功能：控制蛇的移动
	返回值  ：无
	调用函数：is_alive, snake_forward_move, game_over
****************************************************/
void snake_move(snake s)
{
    //设定初始方向
    int dir = 'W';
    int dr = 'S', db = dir; //dr为蛇头朝向的反方向，db记录旧方向

    //死循环，保持游戏运行
    while (1)
    {
        if (kbhit()) //键盘输入
        {
            dir = getch();  //从键盘传入新方向
        }

        //若传入的方向不合理，则不改变
        if (dir == dr)
        {
            dir = db;
        }
        else
        {
            //更新反方向
            switch(dir)
            {
                case 'W':
                    dr = 'S';
                    break;
                case 'A':
                    dr = 'D';
                    break;
                case 'D':
                    dr = 'A';
                    break;
                case 'S':
                    dr = 'W';
                    break;
				default:
					dir = db;	//不接受除了WASD外的参数
					break;
            }
        }

        //更新db
        db = dir;

        //如果蛇还存活，则继续游戏
        if (is_alive(s))
        {
            snake_forward_move(s, dir);
        }
        else    //蛇若死了，游戏结束
        {
            break;
        }

        //根据难度系数来休眠终端
        Sleep(Difficulty_Level);
    }
}

/****************************************************
	函数参数：蛇头指针，蛇头朝向
	函数功能：使蛇向指定的方向移动一个单位，顺便处理蛇吃食物
	返回值  ：无
	调用函数：food_generate，print_snake
****************************************************/
void snake_forward_move(snake s, int dir)
{
    int x1, y1, x2, y2;
    snake p = s, q;

    //记录旧蛇头节点坐标
    x1 = p->x, y1 = p->y;

    //根据朝向改变坐标
    switch(dir)
    {
        case 'W':
            --y1;
            break;
        case 'S':
            ++y1;
            break;
        case 'A':
            --x1;
            break;
        case 'D':
            ++x1;
            break;
    }

    while (p)	//依次改变蛇的节点坐标
    {
        //记录前驱
        q = p;

		//后一个节点和新坐标为前一个节点的旧坐标
        x2 = p->x, y2 = p->y;
        p->x = x1, p->y = y1;
        x1 = x2, y1 = y2;
        p = p->next;
    }

    if (is_eat_food(s)) //蛇吃到食物
    {
		snake k;

        ++game_score;   //游戏分数+1
		printf("\007"); //发出声音
        gotoxy(77, 10);
        printf("%d", game_score);   //刷新游戏分数

        //尾部插入新节点
		k = (snake)malloc(sizeof(SNAKE));   //新增一个节点
        q->next = k;
        k->x = x1, k->y = y1, k->next = NULL;

        //再生成下一个食物
        food_generate(s);
    }
    else	//蛇没有吃到食物
    {
        //除去最后一个节点的痕迹
        gotoxy(x1, y1);
        printf(" ");
    }

    //打印新蛇
    print_snake(s, dir);
}


/****************************************************
	函数功能：判断蛇是否吃到食物
	参数说明：蛇的头指针
	返回值  ：1代表吃到，0代表没吃到
	调用函数：无
****************************************************/
int is_eat_food(snake s)
{
    //即头指针的横纵坐标与食物的横纵坐标相等
    if (s->x == fd.x && s->y == fd.y)
	{
		return 1;
	}
    return 0;
}

/****************************************************
	函数功能：判断蛇是否存活
	参数说明：蛇的头指针
	返回值  ：1代表活着，0代表死了
	调用函数：无
****************************************************/
int is_alive(snake s)
{
    if (s->x == 0 || s->x == WIDTH_WALL)	//撞左右两边墙
	{
		return 0;
	}
    else if (s->y == 0 || s->y == LENTH_WALL)	//撞上下两边墙
	{
		return 0;
	}
    else	//自己吃自己判定，即头指针与蛇身的某个节点重合
	{
        snake p = s->next;

        while (p)	//指针为空代表遍历结束
		{
            if (p->x == s->x && p->y == s->y)	//蛇头与蛇身有重合
			{
				return 0;
			}
            p = p->next;
        }
    }
    return 1;
}

/****************************************************
	函数功能：判断食物是否放在空着的地方
	参数说明：食物的横纵坐标，蛇的头指针
	返回值  ：1代表不可以放在这，0代表可以
	调用函数：无
****************************************************/
int place_ok(int x, int y, snake s)
{
    snake p;
    p = s;

    while (p)	//遍历蛇身
	{
        if (x == p->x && y == p->y)	//食物和蛇身某个节点重合
		{
			return 1;
		}
        p = p->next;
    }
    return 0;
}
