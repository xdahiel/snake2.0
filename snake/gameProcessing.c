#include "snake.h"

/*
    *Filename��gameProcessing.c
    *Author: @2018856302@qq.com
    *Date: 2020.5.14
    *Discription: Deal with all things while playing
*/

/****************************************************
	������������
	�������ܣ�������Ϸ�е�����
	����ֵ  ����
	���ú�����print_map, food_generate, snake_move, game_over
****************************************************/
void game_processing()
{
    snake s, p;
    clock_t st, end;

    //�ƺ����ն��еĶԱȶȸ��ڰ׺�
    system("color 0E");

    //�����ʼ�����������
    s = (snake)malloc(sizeof(SNAKE));
    p = (snake)malloc(sizeof(SNAKE));
    s->x = 25, s->y = 23, s->next = p;
    p->x = 25, p->y = 24, p->next = NULL;

    //��ӡ��ͼ
    print_map();

    //���ɵ�һ��ʳ��
    food_generate(s);

    //��ʼʱ��
    st = clock();

    //�߿�ʼ�ƶ�
    snake_move(s);

    //����ʱ��
    end = clock();

    //������Ϸʱ��
    game_time = (end - st) / CLK_TCK;

    //��Ϸ����
    game_over(s);
}

/****************************************************
	������������
	�������ܣ���ӡ��ͼ
	����ֵ  ����
	���ú�����gotoxy
****************************************************/
void print_map()
{
	int i, j;
	char Map[LENTH_WALL+1][WIDTH_WALL+1];   //�����ͼ

    system("cls");

	//����ѭ�������ͼ
    for (i = 0; i < LENTH_WALL+1; ++i)	//�����ȱ���
    {
        for (j = 0; j < WIDTH_WALL+1; ++j)	//����ȱ���
        {
            if (i == 0 || i == LENTH_WALL)	//�߽�
            {
                Map[i][j] = '=';
            }
            else if (j == 0 || j == WIDTH_WALL)	//�߽�
            {
                Map[i][j] = '#';
            }
            else	//�߽��ڴ�ո�
            {
                Map[i][j] = ' ';
            }
        }
    }

    //����ѭ�������ͼ
    for (i = 0; i <= LENTH_WALL; ++i)
    {
        for (j = 0; j <= WIDTH_WALL; ++j)
        {
            printf("%c", Map[i][j]);
        }
        printf("\n");
    }

    //��ʾ��ʼ����
    gotoxy(70, 10);
    printf("score: %d", game_score);
}

/****************************************************
	������������
	�������ܣ�����ʳ��
	����ֵ  ����
	���ú�����gotoxy
****************************************************/
void food_generate(snake s)
{
	int x, y;

    //������ɺ�������
    srand(time(NULL));
    x = rand()%(WIDTH_WALL-2) + 1;
    y = rand()%(LENTH_WALL-2) + 1;

    //�ж�ʳ���Ƿ���ú���
    if (place_ok(x, y, s))
    {
        x = rand()%(WIDTH_WALL-2) + 1;
        y = rand()%(LENTH_WALL-2) + 1;
    }

    //��ʾʳ��
    gotoxy(x, y);
    printf("$");

    fd.x = x, fd.y = y;
}

/****************************************************
	������������
	�������ܣ���ӡ��
	����ֵ  ����
	���ú�����gotoxy
****************************************************/
void print_snake(snake s, int dir)
{
    snake p = s;
	int t;
	char head;

    gotoxy(p->x, p->y);

	//������ͷ�����ӡ��ͷ
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

    //��ӡ����
    while (p->next)	//���ýڵ㲻�����һ���ڵ㣬�����
    {
        p = p->next;
        gotoxy(p->x, p->y);
        printf("o");
    }

    //�����ҿ������Ų�ģʽ��ÿ�δ�ӡ�ߵ�ʱ��˳����������滻��ɫ
    if (COLORFUL_OPTION)
    {
        char cl[9];

        //��ȡ�����
        srand(time(NULL));
        t = rand()%10;

        //������ɫ
        sprintf(cl, "color 0%d", t);
        system(cl);
    }
}

/****************************************************
	������������ͷָ��
	�������ܣ������ߵ��ƶ�
	����ֵ  ����
	���ú�����is_alive, snake_forward_move, game_over
****************************************************/
void snake_move(snake s)
{
    //�趨��ʼ����
    int dir = 'W';
    int dr = 'S', db = dir; //drΪ��ͷ����ķ�����db��¼�ɷ���

    //��ѭ����������Ϸ����
    while (1)
    {
        if (kbhit()) //��������
        {
            dir = getch();  //�Ӽ��̴����·���
        }

        //������ķ��򲻺����򲻸ı�
        if (dir == dr)
        {
            dir = db;
        }
        else
        {
            //���·�����
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
					dir = db;	//�����ܳ���WASD��Ĳ���
					break;
            }
        }

        //����db
        db = dir;

        //����߻����������Ϸ
        if (is_alive(s))
        {
            snake_forward_move(s, dir);
        }
        else    //�������ˣ���Ϸ����
        {
            break;
        }

        //�����Ѷ�ϵ���������ն�
        Sleep(Difficulty_Level);
    }
}

/****************************************************
	������������ͷָ�룬��ͷ����
	�������ܣ�ʹ����ָ���ķ����ƶ�һ����λ��˳�㴦���߳�ʳ��
	����ֵ  ����
	���ú�����food_generate��print_snake
****************************************************/
void snake_forward_move(snake s, int dir)
{
    int x1, y1, x2, y2;
    snake p = s, q;

    //��¼����ͷ�ڵ�����
    x1 = p->x, y1 = p->y;

    //���ݳ���ı�����
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

    while (p)	//���θı��ߵĽڵ�����
    {
        //��¼ǰ��
        q = p;

		//��һ���ڵ��������Ϊǰһ���ڵ�ľ�����
        x2 = p->x, y2 = p->y;
        p->x = x1, p->y = y1;
        x1 = x2, y1 = y2;
        p = p->next;
    }

    if (is_eat_food(s)) //�߳Ե�ʳ��
    {
		snake k;

        ++game_score;   //��Ϸ����+1
		printf("\007"); //��������
        gotoxy(77, 10);
        printf("%d", game_score);   //ˢ����Ϸ����

        //β�������½ڵ�
		k = (snake)malloc(sizeof(SNAKE));   //����һ���ڵ�
        q->next = k;
        k->x = x1, k->y = y1, k->next = NULL;

        //��������һ��ʳ��
        food_generate(s);
    }
    else	//��û�гԵ�ʳ��
    {
        //��ȥ���һ���ڵ�ĺۼ�
        gotoxy(x1, y1);
        printf(" ");
    }

    //��ӡ����
    print_snake(s, dir);
}


/****************************************************
	�������ܣ��ж����Ƿ�Ե�ʳ��
	����˵�����ߵ�ͷָ��
	����ֵ  ��1����Ե���0����û�Ե�
	���ú�������
****************************************************/
int is_eat_food(snake s)
{
    //��ͷָ��ĺ���������ʳ��ĺ����������
    if (s->x == fd.x && s->y == fd.y)
	{
		return 1;
	}
    return 0;
}

/****************************************************
	�������ܣ��ж����Ƿ���
	����˵�����ߵ�ͷָ��
	����ֵ  ��1������ţ�0��������
	���ú�������
****************************************************/
int is_alive(snake s)
{
    if (s->x == 0 || s->x == WIDTH_WALL)	//ײ��������ǽ
	{
		return 0;
	}
    else if (s->y == 0 || s->y == LENTH_WALL)	//ײ��������ǽ
	{
		return 0;
	}
    else	//�Լ����Լ��ж�����ͷָ���������ĳ���ڵ��غ�
	{
        snake p = s->next;

        while (p)	//ָ��Ϊ�մ����������
		{
            if (p->x == s->x && p->y == s->y)	//��ͷ���������غ�
			{
				return 0;
			}
            p = p->next;
        }
    }
    return 1;
}

/****************************************************
	�������ܣ��ж�ʳ���Ƿ���ڿ��ŵĵط�
	����˵����ʳ��ĺ������꣬�ߵ�ͷָ��
	����ֵ  ��1�������Է����⣬0�������
	���ú�������
****************************************************/
int place_ok(int x, int y, snake s)
{
    snake p;
    p = s;

    while (p)	//��������
	{
        if (x == p->x && y == p->y)	//ʳ�������ĳ���ڵ��غ�
		{
			return 1;
		}
        p = p->next;
    }
    return 0;
}
