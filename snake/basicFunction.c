#include "snake.h"

/****************************************************
	������������
	�������ܣ����ع��
	����ֵ  ����
****************************************************/
void HiddenConsoleCursor()
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;
    GetConsoleCursorInfo(h, &cci);  //��ȡ���λ��
    cci.bVisible = 0;               //�������Ӳ���Ϊ0
    SetConsoleCursorInfo(h, &cci);  //���ù��
}


/****************************************************
	�������ܣ�ѡ��ѡ��
	����˵����ѡ�����飬ѡ�����
	����ֵ  ��ѡ��
	���ú�������
****************************************************/
int menu_select(char *option[], int n, int st)
{
	char key = 0;
	int i, select = 0;
	HANDLE ohandle = GetStdHandle(STD_OUTPUT_HANDLE);

	while(1)
	{
		for(i = 0; i < n; i++) //���ﹲ4��ѡ��
		{
			if(i == select) //���ý������
			{
				SetConsoleTextAttribute(ohandle, BACKGROUND_INTENSITY);
			}
			else if(i == select + 1) //�ָ�����
			{
				SetConsoleTextAttribute(ohandle, FOREGROUND_INTENSITY);
			}
            gotoxy(43, st + 2*i);
			puts(option[i]);
		}
		SetConsoleTextAttribute(ohandle, FOREGROUND_INTENSITY); //�ָ�����

		key = getch();
		if (key == 0xd)  //�س���
		{
			break;	//ѡ�����
		}

		if (key == 0x1b)	//Esc��
		{
			exit(0);	//ֱ���˳�����
		}

		if(key < 0)
		{  //��ASCII���2���ֽ�
			key = getch();

			switch(MapVirtualKey(key, 1))	//���ݴ���������иı�
			{
				case VK_UP:
					select = (select + 3) % n;//�������ƣ���һ��������ģ��
					break;
				case VK_DOWN:
					select = (select + 1) % n;//�������ƣ���һ������һģ��
					break;
			}
		}
	}
	return select;	//����ѡ��
}

/****************************************************
	������������������
	�������ܣ�ʹ����ƶ���ָ����λ��
	����ֵ  ����
	���ú�������
****************************************************/
void gotoxy(int x, int y)
{
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

/****************************************************
	������������
	�������ܣ������д�ļ���������
	����ֵ  ����
	���ú�������
****************************************************/
void open_file_error()
{
    system("cls");
    gotoxy(40, 10);
    printf("��ȡ�ļ����󣬳��򼴽��˳���");
    Sleep(1000);

    //�˳�����
    exit(0);
}
