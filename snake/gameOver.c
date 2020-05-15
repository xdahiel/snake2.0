#include "snake.h"

/*
    *Filename��gameOver.c
    *Author: @2018856302@qq.com
    *Date: 2020.5.14
    *Discription: Deal with all things after playing
*/

/****************************************************
	������������
	�������ܣ���ʾ��Ϸ��������
	����ֵ  ����
	���ú�����gotoxy
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
	�����������ߵ�ͷָ��
	�������ܣ��ͷ���ռ�õ����пռ�
	����ֵ  ����
	���ú�������
****************************************************/
void free_snake(snake s)
{
    snake q, p;

    //�ͷ��ڴ�
	q = p = s;
	while (q)	//��ǰ���ڵ�Ϊ��ʱ������ѭ����
	{
		p = q->next;
		free(q);
		q = p;
	}
}

/****************************************************
	������������
	�������ܣ������û�����
	����ֵ  ����
	���ú�����get_user_info, open_file_error
****************************************************/
void update_user_info()
{
    int i;
    FILE* fp;
    //��ȡ�û���Ϣ
    user* users = get_user_info();

    for (i = 0; i < USER_NUM; ++i)
    {
        //ʶ��ǰ�û�
        if (users[i].id == USER_ID)
        {
            //������������˸��û���ʷ��߷֣������
            if (game_score > users[i].highest_score)
            {
                users[i].highest_score = game_score;
            }

            //������Ϸʱ�䳬������ʷ��ߣ������
            if (game_time > users[i].longest_time)
            {
                users[i].longest_time = game_time;
            }

            //�޸������˳�
            break;
        }
    }

    //��д��ʽ���ļ�
    if ((fp = fopen("users.txt", "w")) == NULL)
    {
        open_file_error();
    }

    //������º���û�����
    for (i = 0; i < USER_NUM; ++i)
    {
        fprintf(fp, "%d %s %s %s %d %d\n", users[i].id,
        users[i].name, users[i].email, users[i].passwd,
        users[i].highest_score, users[i].longest_time);
    }

    //�ͷſռ䣬�ر��ļ�
	free(users);
	fclose(fp);
}

/****************************************************
	������������
	�������ܣ���ӡ��ǰ�û�������Ϸ����
	����ֵ  ����
	���ú�������
****************************************************/
void print_end()
{
	system("cls");

    gotoxy(40, 8);
    printf("��Ϸ������");
    gotoxy(40, 9);
    printf("���ķ���Ϊ%d, ��Ϸʱ��Ϊ%ds, �ٽ�������", game_score, game_time);
    gotoxy(40, 12);
    printf("���س�������...");
}
