#include "snake.h"

/*
    *Filename��main.c
    *Author: @2018856302@qq.com
    *Date: 2020.5.14
    *Discription: As the entrance of the program
*/

/****************************************************
	������������
	�������ܣ��������
	����ֵ  ��0
	���ú�����HiddenConsoleCursor��game_start
****************************************************/
int main()
{
	HiddenConsoleCursor();  //���ع��
	CONTINUE_GAME = 1;      //���ó�ʼ��Ϸ���в���
	PlaySound("gaming.wav", NULL, SND_FILENAME | SND_ASYNC|SND_LOOP);	//��������

	system("color 0E");

    while (CONTINUE_GAME)	//������Ϸ���в����ж��Ƿ������Ϸ
    {
		game_start();
    }
    return 0;
}
