#include "snake.h"

/****************************************************
	函数参数：无
	函数功能：隐藏光标
	返回值  ：无
****************************************************/
void HiddenConsoleCursor()
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;
    GetConsoleCursorInfo(h, &cci);  //获取光标位置
    cci.bVisible = 0;               //调整可视参数为0
    SetConsoleCursorInfo(h, &cci);  //重置光标
}


/****************************************************
	函数功能：选项选择
	参数说明：选项数组，选项个数
	返回值  ：选项
	调用函数：无
****************************************************/
int menu_select(char *option[], int n, int st)
{
	char key = 0;
	int i, select = 0;
	HANDLE ohandle = GetStdHandle(STD_OUTPUT_HANDLE);

	while(1)
	{
		for(i = 0; i < n; i++) //这里共4个选项
		{
			if(i == select) //设置焦点高亮
			{
				SetConsoleTextAttribute(ohandle, BACKGROUND_INTENSITY);
			}
			else if(i == select + 1) //恢复设置
			{
				SetConsoleTextAttribute(ohandle, FOREGROUND_INTENSITY);
			}
            gotoxy(43, st + 2*i);
			puts(option[i]);
		}
		SetConsoleTextAttribute(ohandle, FOREGROUND_INTENSITY); //恢复设置

		key = getch();
		if (key == 0xd)  //回车键
		{
			break;	//选择完毕
		}

		if (key == 0x1b)	//Esc键
		{
			exit(0);	//直接退出程序
		}

		if(key < 0)
		{  //非ASCII码键2个字节
			key = getch();

			switch(MapVirtualKey(key, 1))	//根据传入参数进行改变
			{
				case VK_UP:
					select = (select + 3) % n;//焦点上移，减一，即加三模四
					break;
				case VK_DOWN:
					select = (select + 1) % n;//焦点下移，加一，即加一模四
					break;
			}
		}
	}
	return select;	//返回选项
}

/****************************************************
	函数参数：横纵坐标
	函数功能：使光标移动到指定的位置
	返回值  ：无
	调用函数：无
****************************************************/
void gotoxy(int x, int y)
{
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

/****************************************************
	函数参数：无
	函数功能：处理读写文件错误事务
	返回值  ：无
	调用函数：无
****************************************************/
void open_file_error()
{
    system("cls");
    gotoxy(40, 10);
    printf("读取文件错误，程序即将退出！");
    Sleep(1000);

    //退出程序
    exit(0);
}
