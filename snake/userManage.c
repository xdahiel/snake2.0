#include "snake.h"

/*
    *Filename：userManage.c
    *Author: @2018856302@qq.com
    *Date: 2020.5.14
    *Discription: Manage users' infomation
*/


/****************************************************
	函数参数：无
	函数功能：获取文件中的用户信息
	返回值  ：含有用户信息的数组
	调用函数：open_file_error
****************************************************/
user* get_user_info()
{
	int i = 0, n;
	FILE* fp;

	//开辟新空间
	user *users = (user*)malloc(USER_NUM*sizeof(user));

	//以只读方式打开文件
	if ((fp = fopen("users.txt", "r+")) == NULL)
	{
		open_file_error();
	}

	//输入用户数据
	while (!feof(fp))
	{
		n = fscanf(fp, "%d%s%s%s%d%d",&users[i].id, users[i].name, users[i].email,
		users[i].passwd, &users[i].highest_score, &users[i].longest_time);

		if (n == 6)
		{
			++i;
		}
	}

	//关闭文件
	fclose(fp);

	//返回指针
	return users;
}

/****************************************************
	函数参数：无
	函数功能：打印用户排行榜，判定是否继续游戏
	返回值  ：无
	调用函数：user_sort, get_user_info
****************************************************/
void print_rank()
{
	int i;
    char *option[] = {"否", "是"};

    //获取所有用户信息
	user* users = get_user_info();

	system("cls");

	//以历史最高分、历史最长游戏时间排序
	users_sort(users);

	//打印排行榜
	gotoxy(35, 4);
	printf("*********排行榜*********");
	gotoxy(20, 6);
	printf("排名     账户\t  邮箱       游戏最高分  最长游戏时间");
	for (i = 0; i < USER_NUM; ++i)
	{
		gotoxy(20, 8+2*i);
		printf("%d: %10s%19s%8d%10ds", i+1, users[i].name,
			users[i].email, users[i].highest_score, users[i].longest_time);
	}

	//判定是否继续游戏
	gotoxy(20, 8+2*i);
	printf("继续游戏?");
	CONTINUE_GAME = menu_select(option, 2, 10+2*i);

	//释放空间
	free(users);
}

/****************************************************
	函数参数：无
	函数功能：用户登录
	返回值  ：无
	调用函数：get_user_info
****************************************************/
void sign_in()
{
	int f = 0, i;   //f标记是否可以登录
	char passwd[10], email[20];

	//获取所有用户信息
	user* users = get_user_info();

	//登录
	while (1)
	{
		system("cls");

		gotoxy(40, 8);
		printf("请输入邮箱：");
		scanf("%s", email);
		gotoxy(40, 9);
		printf("请输入密码：");
		scanf("%s", passwd);

		for (i = 0; i < USER_NUM; ++i)
		{
		    //如果用户名和密码都对的上，那么登录
			if (strcmp(users[i].email, email) == 0
				&& strcmp(users[i].passwd, passwd) == 0)
			{
			    //更新标记
				f = 1;

				//记录该用户ID
				USER_ID = users[i].id;
				break;
			}
		}

		//标记为1，可以登录
		if (f)
		{
			break;
		}
		else    //提示用户
		{
			gotoxy(40, 10);
			printf("账户名或密码错误！");
			Sleep(1000);
		}
	}

	gotoxy(40, 10);
	printf("登录成功！");

	//释放空间
	free(users);
}

/****************************************************
	函数参数：无
	函数功能：用户注册
	返回值  ：无
	调用函数：get_user_info, open_file_error
****************************************************/
void sign_up()
{
    int i;
    FILE* fp;

    //记录注册用的信息
	char email[20], passwd1[10], passwd2[10], name[10];

	//获取所有用户信息
	user* users = get_user_info();

	while (1)
	{
		system("cls");

		gotoxy(40, 8);
		printf("请输入电子邮箱（至多19个字符）：");
		scanf("%s", email);

		gotoxy(40, 9);
		printf("请输入账户名（至多10个字符）：");
		scanf("%s", name);

		gotoxy(40, 10);
		printf("输入密码（至多10个字符）：");
		scanf("%s", passwd1);

		gotoxy(40, 11);
		printf("请再次输入密码（至多10个字符）：");
		scanf("%s", passwd2);


		//两次密码不相等，重输
		if (strcmp(passwd1, passwd2) != 0)
		{
			gotoxy(40, 12);
			printf("密码不一致！请重新输入！");
			Sleep(1000);
			continue;
		}

		for (i = 0; i < USER_NUM; ++i)
		{
		    //与已有账户冲突，重输
			if (strcmp(users[i].email, email) == 0 ||
				strcmp(users[i].name, name) == 0)
			{
				gotoxy(40, 12);
				printf("邮箱或用户名已注册！");
				Sleep(1000);
				break;
			}
		}

		//注册成功
		if (i == USER_NUM)
		{
			break;
		}
	}

	//以追加方式打开文件
	if ((fp = fopen("users.txt", "a")) == NULL)
	{
		open_file_error();
	}

	//加入新用户
	fprintf(fp, "%d %s %s %s %d %d\n", USER_NUM+1, name, email, passwd1, 0, 0);
	USER_NUM++;

	//释放空间，关闭文件
	free(users);
	fclose(fp);
}

/****************************************************
	函数参数：用户信息数组
	函数功能：根据分数和游戏时长对用户排序
	返回值  ：无
	调用函数：无
****************************************************/
void users_sort(user* users)
{
    int i, j;
    user temp;

    //冒泡排序
    for (i = 1; i < USER_NUM; ++i)
    {
        for (j = 0; j < USER_NUM - i; ++j)
        {
            if (users[j].highest_score < users[j+1].highest_score)
            {
                temp = users[j];
                users[j] = users[j+1];
                users[j+1] = temp;
            }
            //游戏分数相同，但是时长不相同
            else if (users[j].highest_score == users[j+1].highest_score
                     && users[j].longest_time > users[j+1].longest_time)
            {
                temp = users[j];
                users[j] = users[j+1];
                users[j+1] = temp;
            }
        }
    }
}

/****************************************************
	函数参数：无
	函数功能：获取历史用户个数
	返回值  ：无
	调用函数：open_file_error
****************************************************/
void get_pre_user_num()
{
	int n;
	FILE* fp;
	user users;

	USER_NUM = 0;

	//以只读方式代开文件
	if ((fp = fopen("users.txt", "r+")) == NULL)
	{
		open_file_error();
	}

	//遍历文件
	while (!feof(fp))
	{
		n = fscanf(fp, "%d%s%s%s%d%d",&users.id, users.name, users.email,
		users.passwd, &users.highest_score, &users.longest_time);
		if (n == 6)
		{
			USER_NUM++;
		}
	}

	//关闭文件
	fclose(fp);
}
