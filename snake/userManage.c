#include "snake.h"

/*
    *Filename��userManage.c
    *Author: @2018856302@qq.com
    *Date: 2020.5.14
    *Discription: Manage users' infomation
*/


/****************************************************
	������������
	�������ܣ���ȡ�ļ��е��û���Ϣ
	����ֵ  �������û���Ϣ������
	���ú�����open_file_error
****************************************************/
user* get_user_info()
{
	int i = 0, n;
	FILE* fp;

	//�����¿ռ�
	user *users = (user*)malloc(USER_NUM*sizeof(user));

	//��ֻ����ʽ���ļ�
	if ((fp = fopen("users.txt", "r+")) == NULL)
	{
		open_file_error();
	}

	//�����û�����
	while (!feof(fp))
	{
		n = fscanf(fp, "%d%s%s%s%d%d",&users[i].id, users[i].name, users[i].email,
		users[i].passwd, &users[i].highest_score, &users[i].longest_time);

		if (n == 6)
		{
			++i;
		}
	}

	//�ر��ļ�
	fclose(fp);

	//����ָ��
	return users;
}

/****************************************************
	������������
	�������ܣ���ӡ�û����а��ж��Ƿ������Ϸ
	����ֵ  ����
	���ú�����user_sort, get_user_info
****************************************************/
void print_rank()
{
	int i;
    char *option[] = {"��", "��"};

    //��ȡ�����û���Ϣ
	user* users = get_user_info();

	system("cls");

	//����ʷ��߷֡���ʷ���Ϸʱ������
	users_sort(users);

	//��ӡ���а�
	gotoxy(35, 4);
	printf("*********���а�*********");
	gotoxy(20, 6);
	printf("����     �˻�\t  ����       ��Ϸ��߷�  ���Ϸʱ��");
	for (i = 0; i < USER_NUM; ++i)
	{
		gotoxy(20, 8+2*i);
		printf("%d: %10s%19s%8d%10ds", i+1, users[i].name,
			users[i].email, users[i].highest_score, users[i].longest_time);
	}

	//�ж��Ƿ������Ϸ
	gotoxy(20, 8+2*i);
	printf("������Ϸ?");
	CONTINUE_GAME = menu_select(option, 2, 10+2*i);

	//�ͷſռ�
	free(users);
}

/****************************************************
	������������
	�������ܣ��û���¼
	����ֵ  ����
	���ú�����get_user_info
****************************************************/
void sign_in()
{
	int f = 0, i;   //f����Ƿ���Ե�¼
	char passwd[10], email[20];

	//��ȡ�����û���Ϣ
	user* users = get_user_info();

	//��¼
	while (1)
	{
		system("cls");

		gotoxy(40, 8);
		printf("���������䣺");
		scanf("%s", email);
		gotoxy(40, 9);
		printf("���������룺");
		scanf("%s", passwd);

		for (i = 0; i < USER_NUM; ++i)
		{
		    //����û��������붼�Ե��ϣ���ô��¼
			if (strcmp(users[i].email, email) == 0
				&& strcmp(users[i].passwd, passwd) == 0)
			{
			    //���±��
				f = 1;

				//��¼���û�ID
				USER_ID = users[i].id;
				break;
			}
		}

		//���Ϊ1�����Ե�¼
		if (f)
		{
			break;
		}
		else    //��ʾ�û�
		{
			gotoxy(40, 10);
			printf("�˻������������");
			Sleep(1000);
		}
	}

	gotoxy(40, 10);
	printf("��¼�ɹ���");

	//�ͷſռ�
	free(users);
}

/****************************************************
	������������
	�������ܣ��û�ע��
	����ֵ  ����
	���ú�����get_user_info, open_file_error
****************************************************/
void sign_up()
{
    int i;
    FILE* fp;

    //��¼ע���õ���Ϣ
	char email[20], passwd1[10], passwd2[10], name[10];

	//��ȡ�����û���Ϣ
	user* users = get_user_info();

	while (1)
	{
		system("cls");

		gotoxy(40, 8);
		printf("������������䣨����19���ַ�����");
		scanf("%s", email);

		gotoxy(40, 9);
		printf("�������˻���������10���ַ�����");
		scanf("%s", name);

		gotoxy(40, 10);
		printf("�������루����10���ַ�����");
		scanf("%s", passwd1);

		gotoxy(40, 11);
		printf("���ٴ��������루����10���ַ�����");
		scanf("%s", passwd2);


		//�������벻��ȣ�����
		if (strcmp(passwd1, passwd2) != 0)
		{
			gotoxy(40, 12);
			printf("���벻һ�£����������룡");
			Sleep(1000);
			continue;
		}

		for (i = 0; i < USER_NUM; ++i)
		{
		    //�������˻���ͻ������
			if (strcmp(users[i].email, email) == 0 ||
				strcmp(users[i].name, name) == 0)
			{
				gotoxy(40, 12);
				printf("������û�����ע�ᣡ");
				Sleep(1000);
				break;
			}
		}

		//ע��ɹ�
		if (i == USER_NUM)
		{
			break;
		}
	}

	//��׷�ӷ�ʽ���ļ�
	if ((fp = fopen("users.txt", "a")) == NULL)
	{
		open_file_error();
	}

	//�������û�
	fprintf(fp, "%d %s %s %s %d %d\n", USER_NUM+1, name, email, passwd1, 0, 0);
	USER_NUM++;

	//�ͷſռ䣬�ر��ļ�
	free(users);
	fclose(fp);
}

/****************************************************
	�����������û���Ϣ����
	�������ܣ����ݷ�������Ϸʱ�����û�����
	����ֵ  ����
	���ú�������
****************************************************/
void users_sort(user* users)
{
    int i, j;
    user temp;

    //ð������
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
            //��Ϸ������ͬ������ʱ������ͬ
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
	������������
	�������ܣ���ȡ��ʷ�û�����
	����ֵ  ����
	���ú�����open_file_error
****************************************************/
void get_pre_user_num()
{
	int n;
	FILE* fp;
	user users;

	USER_NUM = 0;

	//��ֻ����ʽ�����ļ�
	if ((fp = fopen("users.txt", "r+")) == NULL)
	{
		open_file_error();
	}

	//�����ļ�
	while (!feof(fp))
	{
		n = fscanf(fp, "%d%s%s%s%d%d",&users.id, users.name, users.email,
		users.passwd, &users.highest_score, &users.longest_time);
		if (n == 6)
		{
			USER_NUM++;
		}
	}

	//�ر��ļ�
	fclose(fp);
}
