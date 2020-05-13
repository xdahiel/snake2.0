#include "snake.h"

/****************************************************
	函数参数：无
	函数功能：程序入口
	返回值  ：0
	调用函数：HiddenConsoleCursor，game_start
****************************************************/
int main()
{
	HiddenConsoleCursor();  //隐藏光标
	CONTINUE_GAME = 1;      //设置初始游戏运行参数
	PlaySound("gaming.wav", NULL, SND_FILENAME | SND_ASYNC|SND_LOOP);	//播放音乐

	system("color 0E");

    while (CONTINUE_GAME)	//根据游戏运行参数判断是否继续游戏
    {
		game_start();
    }
    return 0;
}
