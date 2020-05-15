#include "snake.h"

/*
    *Filename��gameStart.c
    *Author: @2018856302@qq.com
    *Date: 2020.5.14
    *Discription: Deal with all things before playing
*/

/****************************************************
	������������
	�������ܣ�������Ϸǰ������
	����ֵ  ����
	���ú�����get_pre_user_num, menu_select, sign_in,
              sigh_up, difficulty_level_select, colorful_select
              ,game_processing
****************************************************/
void game_start()
{
	int op;
	char* option[] = {"ע��", "��¼"};

	//��ȡ�����û���Ŀ
	get_pre_user_num();

	//�����¼/ע������
	while (1)
	{
		system("cls");
		gotoxy(35, 10);
		printf("*******̰����*******");

		gotoxy(30, 11);
		printf("��Ϸʱ�뿪����дģʽ����WASD���Ʒ���");

		op = menu_select(option, 2, 14);

		if (op) //ѡ���¼
		{
			sign_in();
			//��¼�������Ϸ
			break;
		}
		else    //ѡ��ע��
		{
			sign_up();
		}
	}

	//��Ϸ����ѡ��
	difficulty_level_select();

	//�Ų�ģʽѡ��
	colorful_select();

	//���ڿ����Ų�ģʽ������ͣ��ʱ�����������Ѷ�ϵ����ƽ��
	if(COLORFUL_OPTION)
	{
		Difficulty_Level -= 25;
	}

	//��Ϸ��ʽ��ʼ
	game_processing();
}

/****************************************************
	������������
	�������ܣ�ѡ����Ϸ�Ѷ�
	����ֵ  ����
	���ú�����menu_select
****************************************************/
void difficulty_level_select()
{
	int op;
	char *option[] = {"�ֲ�ģʽ","��ͨģʽ","���ģʽ","����ģʽ"};

    system("cls");  //����

    gotoxy(32, 10);
    printf("��ѡ���Ѷȣ�ʹ�á�����ͷѡ��,��Esc���˳���Ϸ");
    op = menu_select(option, 4, 14); //��ȡѡ����

    //����ѡ���������Ѷ�ϵ��
    switch(op)
    {
        case 0: //�ֲ�ģʽ
            Difficulty_Level = 100;
            break;
        case 1: //��ͨģʽ
            Difficulty_Level = 75;
            break;
        case 2: //���ģʽ
            Difficulty_Level = 50;
            break;
        case 3: //����ģʽ
            Difficulty_Level = 25;
            break;
    }
}

/****************************************************
	�������ܣ����û�ѡ���Ƿ����Ų�ģʽ
	����˵������
	����ֵ  ����
	���ú�����menu_select
****************************************************/
void colorful_select()
{
	char *option[] = {"��", "��"};

    system("cls");
    system("COLOR 0E");

    //����ѡ��
    gotoxy(20, 10);
    printf("�Ƿ����Ų�ģʽ(�������Ų�ģʽ���Ѷ�Ҳ��֮��С)��");
	COLORFUL_OPTION = menu_select(option, 2, 14);
}
