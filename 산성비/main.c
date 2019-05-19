#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include "basicFunc.h"
#include "const.h"
#include "printWord.h"
#include "gamePlay.h"

char lang_code[3];
char file_name[10];

void printOuterLine(void);
void printName(void);
void printMenu(void);
void printLangSet(void);
void printMainMenu(void);
void printWordAddMenu(void);
void printLangSelMenu(void);

int main (void)
{
	strcpy(file_name, KOR_FILE);
	strcpy(lang_code, "kor");

	FILE *chk = fopen(file_name, "r");
	FILE *add = fopen(file_name, "a+");
	FILE *rank = fopen(RANK_FILE, "a+");

	typedef struct rank_view
	{
		int cnt;
		char name[MAX_LENGTH_OF_STRING + 1];
		int score;
		int speed;
	}RANK;

	RANK rankviewer;
	int rankCounter = 0;

	int menu_num = 0;

	system("title �꼺��");
	system("color 17");
	system("mode con cols=100 lines=30");

	strcpy(file_name, KOR_FILE);
	strcpy(lang_code, "kor");

	while (1)
	{
		printMainMenu();
		scanf("%d", &menu_num);
		rewind(stdin);
		switch (menu_num)
		{
		case 1:
			gameplay();
			break;
		case 2:
			//�ܾ��߰�
			printWordAddMenu();
			char inputString[MAX_LENGTH_OF_STRING + 1];
			char tempString[MAX_LENGTH_OF_STRING + 1];
			char newString[MAX_LENGTH_OF_STRING + 1] = "\n";

			add = fopen(file_name, "a");
			chk = fopen(file_name, "r");

			gotoxy(MID_X_WOR - 15, MID_Y - 3);
			printf("(���׷� ���� ���α׷� ����۽� ����˴ϴ٤�) ");

			gotoxy(MID_X_WOR - 10, MID_Y - 2);
			printf("(�׳� Enter �Է½� �ڷΰ�) ");

			gotoxy(MID_X_WOR-5, MID_Y + 1);
			printf("input > ");
			if (gets_s(tempString, MAX_LENGTH_OF_STRING))
			{
				int cnt = 0;
				if(strcmp(tempString, ""))
				{
					while (fscanf(chk, "%s", inputString) != EOF)
					{
						if (!strcmp(inputString, tempString))	cnt++;
						if (cnt != 0)
						{
							gotoxy(MID_X_WOR - 5, MID_Y + 2);
							printf("�̹� �����ϴ� �ܾ��Դϴ�!\n");

							gotoxy(MID_X_WOR - 11, MAX_Y - 2);
							system("pause");
							break;
						}
					}
					if (cnt == 0)
					{
						strcat(newString, tempString);
						fputs(newString, add);
						//add = fopen(file_name, "a");
						gotoxy(MID_X_WOR - 5, MID_Y + 2);
						printf("input success\n");
						gotoxy(MID_X_WOR - 11, MAX_Y - 2);
						system("pause");
					}
				}
			}
			break;
		case 3:
			//��ŷ
			system("cls");
			printOuterLine();

			gotoxy(MID_X_WOR - 15, 1);
			printf("(���׷� ���� ���α׷� ����۽� ������Ʈ�˴ϴ٤�) ");

			printWord(MID_X, 3, "RANK");

			while (fscanf(rank, "%d %s %d %d", &rankviewer.cnt, rankviewer.name, &rankviewer.score, &rankviewer.speed) != EOF)
			{
				gotoxy(30, 7 + rankCounter);
				rankCounter++;
				if(rankviewer.cnt != 0)
				printf("%3d %10s %6d�� %5d%%\n", rankviewer.cnt, rankviewer.name, rankviewer.score, rankviewer.speed);
			}
			gotoxy(MID_X_WOR - 11, MAX_Y - 2);
			system("pause");
			break;
		case 4:
			//����
			printLangSelMenu();
			break;
		case 5:
			//����
			return;
		default:
			gotoxy(MID_X_WOR, MID_Y + 10);
			printf("type again!");
			gotoxy(MID_X_WOR - 11, MAX_Y - 2);
			system("pause");
			break;
		}
	}

	return 0;
}

void printOuterLine(void)
{
	for (int i = 0; i < MAX_Y; i++)	printWord(0, i, "��");
	for (int i = 0; i < MAX_Y; i++)	printWord(MAX_X + 8, i, "��");
	for (int i = 0; i < MAX_X + 10; i++)	printWord(i++, 0, "��");
	for (int i = 0; i < MAX_X + 10; i++)	printWord(i++, MAX_Y, "��");
}

void printName(void)
{
	printWord(MID_X, MID_Y - 4, "�� �� ��");
}

void printMenu(void)
{
	char tempstring[MAX_LENGTH_OF_STRING + 1];			//���ڿ� �ӽ� ����
	const int plusy = 3;

	sprintf(tempstring, "1. �÷���");
	printWord(MID_X_WOR, MID_Y + plusy, tempstring);

	sprintf(tempstring, "2. �ܾ��߰�");
	printWord(MID_X_WOR, MID_Y + plusy + 1, tempstring);

	sprintf(tempstring, "3. ��ŷ");
	printWord(MID_X_WOR, MID_Y + plusy + 2, tempstring);

	sprintf(tempstring, "4. ����");
	printWord(MID_X_WOR, MID_Y + plusy + 3, tempstring);

	sprintf(tempstring, "5. ����");
	printWord(MID_X_WOR, MID_Y + plusy + 4, tempstring);

	gotoxy(MID_X_WOR, MID_Y + plusy + 6);
	printf("input > ");

}

void printLangSet(void)
{
	gotoxy(80, 2);
	printf("mode : %s", lang_code);
}

void printMainMenu(void)
{
	system("cls");
	printOuterLine();
	printLangSet();
	printName();
	printMenu();
}

void printWordAddMenu(void)
{
	system("cls");
	printOuterLine();
	printLangSet();
	char tempstring[MAX_LENGTH_OF_STRING + 1];
	sprintf(tempstring, "�߰��� �ܾ �Է��ϼ���");
	printWord(MID_X_WOR - 5, MID_Y, tempstring);
}

void printLangSelMenu(void)
{
	system("cls");
	printOuterLine();
	printLangSet();
	char tempstring[MAX_LENGTH_OF_STRING + 1];

	sprintf(tempstring, "����ڵ带 �Է��ϼ���");
	printWord(MID_X_WOR, MID_Y, tempstring);

	sprintf(tempstring, "�ѱ� : kor");
	printWord(MID_X_WOR, MID_Y + 1, tempstring);

	sprintf(tempstring, "���� : eng");
	printWord(MID_X_WOR, MID_Y + 2, tempstring);

	gotoxy(MID_X_WOR - 10, MAX_Y - 3);
	printf("(�׳� Enter �Է½� �ڷΰ�) ");

	gotoxy(MID_X_WOR, MID_Y + 3);
	printf("input>");
	gets_s(tempstring, MAX_LENGTH_OF_STRING);
	rewind(stdin);


	if (!strcmp(tempstring, "kor"))
	{
		strcpy(file_name, KOR_FILE);
		strcpy(lang_code, "kor");
		printLangSet();
		gotoxy(MID_X_WOR, MID_Y + 4);
	}
	else if (!strcmp(tempstring, "eng"))
	{
		strcpy(file_name, ENG_FILE);
		strcpy(lang_code, "eng");
		printLangSet();
		gotoxy(MID_X_WOR, MID_Y + 4);
	}
	else if (!strcmp(tempstring, ""))	return;
	else
	{
		gotoxy(MID_X_WOR, MID_Y + 4);
		printf("error!");
		gotoxy(MID_X_WOR, MID_Y + 5);
	}
	gotoxy(MID_X_WOR - 11, MAX_Y - 2);
	system("pause");
	return;
}