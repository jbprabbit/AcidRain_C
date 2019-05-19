#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include "basicFunc.h"
#include "const.h"
#include "printWord.h"
#include "gamePlay.h"

#define RANK_FILE "rank.txt"

char lang_code[3];
char file_name[10];

void printOuterLine(void)
{
	for (int i = 0; i < MAX_Y; i++)	printWord(0, i, "■");
	for (int i = 0; i < MAX_Y; i++)	printWord(MAX_X + 8, i, "■");
	for (int i = 0; i < MAX_X + 10; i++)	printWord(i++, 0, "■");
	for (int i = 0; i < MAX_X + 10; i++)	printWord(i++, MAX_Y, "■");
}

void printName(void)
{

}

void printMenu(void)
{
	char tempstring[MAX_LENGTH_OF_STRING + 1];			//문자열 임시 저장

	sprintf(tempstring, "1. 플레이");
	printWord(MID_X_WOR, MID_Y, tempstring);
	
	sprintf(tempstring, "2. 단어추가");
	printWord(MID_X_WOR, MID_Y + 1, tempstring);

	sprintf(tempstring, "3. 랭킹");
	printWord(MID_X_WOR, MID_Y + 2, tempstring);

	sprintf(tempstring, "4. 언어설정");
	printWord(MID_X_WOR, MID_Y + 3, tempstring);

	sprintf(tempstring, "5. 종료");
	printWord(MID_X_WOR, MID_Y + 4, tempstring);

}

void printMainMenu(void)
{
	system("cls");
	printOuterLine();

	gotoxy(80, 2);
	printf("mode : %s", lang_code);

	printName();
	printMenu();
}

void printWordAddMenu(void)
{
	system("cls");
	printOuterLine();
	char tempstring[MAX_LENGTH_OF_STRING + 1];
	sprintf(tempstring, "추가할 단어를 입력하세요");
	printWord(MID_X_WOR-5, MID_Y, tempstring);
}

void printLangSelMenu(void)
{
	system("cls");
	printOuterLine();
	char tempstring[MAX_LENGTH_OF_STRING + 1];

	sprintf(tempstring, "언어코드를 입력하세요");
	printWord(MID_X_WOR, MID_Y, tempstring);

	sprintf(tempstring, "한글 : kor");
	printWord(MID_X_WOR, MID_Y + 1, tempstring);

	sprintf(tempstring, "영어 : eng");
	printWord(MID_X_WOR, MID_Y + 2, tempstring);

	gotoxy(MID_X_WOR, MID_Y + 3);
	printf("input>");
	scanf("%s", tempstring);
	rewind(stdin);

	gotoxy(MID_X_WOR, MID_Y + 4);

	if (!strcmp(tempstring, "kor"))
	{
		strcpy(file_name, KOR_FILE);
		strcpy(lang_code, "kor");
	}
	else if (!strcmp(tempstring, "eng"))
	{
		strcpy(file_name, ENG_FILE);
		strcpy(lang_code, "eng");
	}
	else
	{
		printf("error!");
		gotoxy(MID_X_WOR, MID_Y + 5);
	}
	
	system("pause");
	return;
}

int main (void)
{
	FILE *add = fopen(FILE_NAME, "a");
	FILE *rank = fopen(RANK_FILE, "a");

	int menu_num = 0;

	system("title 산성비");
	system("color 17");
	system("mode con cols=100 lines=30");

	strcpy(file_name, KOR_FILE);
	strcpy(lang_code, "kor");

	while (1)
	{
		printMainMenu();
		gotoxy(MID_X_WOR, MID_Y + 6);
		printf("input > ");
		scanf("%d", &menu_num);
		rewind(stdin);
		switch (menu_num)
		{
		case 1:
			gameplay();
			break;
		case 2:
			//단어추가
			printWordAddMenu();
			char tempString[MAX_LENGTH_OF_STRING + 1];

			gotoxy(MID_X_WOR-5, MID_Y + 1);
			printf("input > ");
			if (scanf("%s", tempString))
			{
				gotoxy(MID_X_WOR-5, MID_Y + 2);
				printf("input success\n");
				gotoxy(MID_X_WOR-5, MID_Y + 3);
			}
			break;
		case 3:
			//랭킹

			break;
		case 4:
			//언어설정
			printLangSelMenu();
			break;
		case 5:
			//종료
			return;
		default:

			break;
		}
	}

	return 0;
}