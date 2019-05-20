#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define HAVE_STRUCT_TIMESPEC
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <pthread.h>
#include <Windows.h>

#include "const.h"
#include "basicFunc.h"
#include "printWord.h"
#include "rainDropMng.h"
#include "printer.h"
#include "gamePlay.h"

char run = TRUE;									//���� �ݺ� ����(����Ǹ� FALSE)

#define VERSION 0
#ifdef _WIN32

#if VERSION == 1
typedef struct
{
	char temp[MAX_LENGTH_OF_STRING + 1][2];
	char word[MAX_LENGTH_OF_STRING + 1];
	int length;
	char flag;
}INPUT_WORD;
void* wordScan(void* data)
{
	INPUT_WORD *input = (INPUT_WORD*)data;
	char temp;
	int cnt;

	input->length = 0;
	while (TRUE)
	{
		if (!input->flag)
		{
			temp = getch();
			if (temp == 13)	//Enter �Է�
			{
				cnt = 0;
				for (int i = 0; i < input->length; i++)
				{
					input->word[cnt++] = input->temp[i][0];
					if (input->temp[i][1] != 0)	input->word[cnt++] = input->temp[i][1];
				}
				input->word[cnt] = '\0';
				input->length = 0;
				input->flag = TRUE;
			}
			else if (temp == 8)	//backspace �Է�
			{
				if (input->length > 0)	input->length--;
			}
			else
			{
				if (temp > 0)
				{
					input->temp[input->length][0] = temp;
					input->temp[input->length][1] = 0;
					input->length++;
				}
				else
				{
					input->temp[input->length][0] = temp;
					temp = getch();
					input->temp[input->length][1] = temp;
					input->length++;
				}
			}
		}
	}
	gotoxy(0, MAX_Y + 2);
	return NULL;
}
#elif VERSION == 2
// Version 2

typedef struct {
	char temp[MAX_LENGTH_OF_STRING + 1][2];
	char word[MAX_LENGTH_OF_STRING + 1];
	int length;
	char flag;
}INPUT_WORD;
void*wordScan(void* data) {
	INPUT_WORD *input = (INPUT_WORD*)data;
	char temp;
	int i, cnt;
	input->length = 0;
	while (TRUE) {
		if (!input->flag) {
			temp = getch();
			if (temp == 13) {		//Enter �Է�
				temp = getch();
				cnt = 0;
				for (i = 0; i < input->length; i++) {
					input->word[cnt++] = input->temp[i][0];
					if (input->temp[i][1] != 0)
						input->word[cnt++] = input->temp[i][1];
				}
				input->word[cnt] = '\0';
				input->length = 0;
				input->flag = TRUE;
			}
			else if (temp == 8) {	//backspace
				temp = getch();
				if (input->length > 0)
					input->length--;
			}
			else {
				if (temp > 0) {
					input->temp[input->length][0] = temp;
					input->temp[input->length][1] = 0;
					if (temp != 0)
						temp = getch();
					input->length++;
				}
				else {
					input->temp[input->length][0] = temp;
					temp = getch();
					input->temp[input->length][1] = temp;
					if (temp != 0)
						temp = getch();
					input->length++;
				}
			}
		}
	}
	gotoxy(0, MAX_Y + 2);
	return NULL;
}
#elif VERSION == 3
// Version 3
typedef struct {
	char word[MAX_LENGTH_OF_STRING + 1];
	char flag;
}INPUT_WORD;
void*wordScan(void* data) {
	INPUT_WORD *input = (INPUT_WORD*)data;
	while (TRUE) {
		if (!input->flag) {
			scanf("%s", input->word);
			input->flag = TRUE;
		}
	}
	gotoxy(0, MAX_Y + 2);
	return NULL;
}
#elif VERSION == 0
#include <process.h>
typedef struct
{
	char temp[MAX_LENGTH_OF_STRING + 1][2];
	char word[MAX_LENGTH_OF_STRING + 1];
	int length;
	char flag;
}INPUT_WORD;
unsigned __stdcall wordScan(void* data)
{
	INPUT_WORD *input = (INPUT_WORD*)data;
	char temp;
	int cnt;

	input->length = 0;
	while (TRUE)
	{
		if (!input->flag && run != FALSE)
		{
			temp = getch();
			if (temp == 13)	//Enter �Է�
			{
				cnt = 0;
				for (int i = 0; i < input->length; i++)
				{
					input->word[cnt++] = input->temp[i][0];
					if (input->temp[i][1] != 0)	input->word[cnt++] = input->temp[i][1];
				}
				input->word[cnt] = '\0';
				input->length = 0;
				input->flag = TRUE;
}
			else if (temp == 8)	//backspace �Է�
			{
				if (input->length > 0)	input->length--;
			}
			else
			{
				if (temp > 0)
				{
					input->temp[input->length][0] = temp;
					input->temp[input->length][1] = 0;
					input->length++;
				}
				else
				{
					input->temp[input->length][0] = temp;
					temp = getch();
					input->temp[input->length][1] = temp;
					input->length++;
				}
			}
		}
	}
	gotoxy(0, MAX_Y + 2);
	return NULL;
}
void wordScanEnd(INPUT_WORD *data)
{
	data = NULL;
}
#endif

#elif __linux__
// linux
typedef struct {
	char word[MAX_LENGTH_OF_STRING + 1];
	char flag;
}INPUT_WORD;
void*wordScan(void* data) {
	INPUT_WORD *input = (INPUT_WORD*)data;
	while (TRUE) {
		if (!input->flag) {
			scanf("%s", input->word);
			input->flag = TRUE;
		}
	}
	gotoxy(0, MAX_Y + 2);
	return NULL;
}
#elif __unix__ // all unices not caught above
// Unix
typedef struct {
	char word[MAX_LENGTH_OF_STRING + 1];
	char flag;
}INPUT_WORD;
void*wordScan(void* data) {
	INPUT_WORD *input = (INPUT_WORD*)data;
	while (TRUE) {
		if (!input->flag) {
			scanf("%s", input->word);
			input->flag = TRUE;
		}
	}
	gotoxy(0, MAX_Y + 2);
	return NULL;
}
#endif

extern void printOuterLine(void);


void gameend(STATUS stat)
{
	system("cls");
	printOuterLine();
	char tempString[MAX_LENGTH_OF_STRING + 1];
	printWord(MID_X_WOR, MID_Y, "GAME OVER!");

	sprintf(tempString, "SCORE : %d", stat.score);
	printWord(MID_X_WOR, MID_Y + 1, tempString);

	sprintf(tempString, "SPEED : %d%%", stat.speed);
	printWord(MID_X_WOR, MID_Y + 2, tempString);

	FILE *rank = fopen(RANK_FILE, "a");
	FILE *read = fopen(RANK_FILE, "r");
	char nameStr[MAX_LENGTH_OF_STRING + 1];

	gotoxy(MID_X_WOR, MID_Y + 4);
	printf("input name> ");
	scanf("%s", nameStr);

	int cnt;
	char name[MAX_LENGTH_OF_STRING + 1];
	int score, speed;
	
	cnt = 0;
	while (fscanf(read, "%d %s %d %d", &cnt, name, &score, &speed) != EOF);
	
	//sprintf(tempString, "\n%d %s %d %d", cnt + 1, nameStr, stat.score, stat.speed);
	fprintf(rank, "\n%d %s %d %d", cnt + 1, nameStr, stat.score, stat.speed);
	//fputs(tempString, rank);

	fclose(rank);
	fclose(read);

	gotoxy(MID_X_WOR-11, MAX_Y - 2);
	system("pause");
}

void gameplay(void)
{
	//���� ����
	RAINDROP_LIST raindropList;							//����� ���
	WORD_LIST wordList;									//���Ͽ� �ִ� �ܾ� ��� ����

	INPUT_WORD input;									//Ű���� �Է� ����
	pthread_t thread;									//Ű���� �Է��� ���� ������
	int joinStatus;										//������ ����

	clock_t lastRaindropTime = 0;						//���� �ֱٿ� ������� ������ �ð�
	clock_t currentTime;								//�ð� ����

	
	char stopFlag = FALSE;
	clock_t stopTime = 0;

	//�ʱ�ȭ
	srand((unsigned int)time(NULL));
	STATUS stat = { 0, 100 };
	REMAIN remain = { LIFE, PAUSE, BOMB };
	setWordList(&wordList);								//���Ͽ��� �ܾ� ��� �о��
	raindropList.cntRaindrop = 0;
	input.flag = FALSE;

	/*****�ʱ� ȭ�� ���*****/
	printAll(remain, stat);

	/*****����� �Է� ���� ������ ����*****/
#if VERSION != 0
	pthread_create(&thread, NULL, wordScan, (void*)&input);		//�����带 �����ϰ� �۵���Ų�� (����� �Է� ���� ������)
	pthread_detach(thread);										//������ ����
#else	//threadPrgm
	_beginthreadex(NULL, 0, wordScan, (void *)&input, 0, NULL);
#endif

	run = TRUE;

	while (run)
	{
		//�Է¹��� �ܾ�ó��
		if (input.flag)
		{
			//�����Է½�
			if (!strcmp(input.word, "����"))
			{
#if VERSION != 0
				pthread_cancel(thread);
				//pthread_exit(NULL);
#else	//threadPrgm
				//_endthreadex(0);
#endif
				run = FALSE;
				break;
			}
			//���� �Է½�
			else if (!strcmp(input.word, "����") && remain.pause > 0)
			{
				remain.pause--;
				statPrint(remain);
				stopFlag = TRUE;
				stopTime = getClock();
			}
			//��ź �Է½�
			else if (!strcmp(input.word, "��ź") && remain.bomb > 0)
			{
				while (raindropList.cntRaindrop != 0)	removeRaindrop(&raindropList, 0);
				remain.bomb--;
				statPrint(remain);
			}

			//������� �Էµ� �ܾ� ã���� ó��
			int index;
			do {
				index = findRaindropIdx(raindropList, input.word);
				if (index != -1)
				{
					scoreUpdate(raindropList, index, &stat);	//���� ���
					speedUpdate(&stat);					//�ӵ� ���
					removeRaindrop(&raindropList, index);
				}
			} while (index != -1);

			input.flag = FALSE;
		}

		currentTime = getClock();
		if (currentTime - stopTime >= PAUSE_TIME)	stopFlag = FALSE;	//�߰��� �ڵ�: ���� ��

		if (stopFlag == FALSE)	//�߰��� �ڵ�: �����ð� �ƴҶ��� �������� �� ������
		{
			//����� ����
			for (int i = 0; i < raindropList.cntRaindrop; i++)
			{
				if (raindropList.raindrops[i].lastUpdatedTime + (double)raindropList.raindrops[i].period / stat.speed * 100 <= currentTime)
				{
					//������� �� �� �Ʒ��� ������
					raindropList.raindrops[i].lastUpdatedTime = currentTime;
					removeRaindropFromConsole(&raindropList, i);						//��ġ�� �ܾ� ȭ�鿡�� ����
					raindropList.raindrops[i].y++;
					if (raindropList.raindrops[i].y >= MAX_Y)
					{
#if VERSION != 0
						pthread_cancel(thread);
#else	//threadPrgm
						//_endthreadex(0);
#endif
						//////////
						//�߰��� �ڵ� : ����3��
						removeRaindropFromList(&raindropList, i);
						remain.life--;
						if (remain.life == 0)	run = FALSE;
						statPrint(remain);

						//////////
					}
					else
					{
						printWord(raindropList.raindrops[i].x, raindropList.raindrops[i].y, raindropList.raindrops[i].word);
					}
				}
			}

			if ((double)GENERATE_PERIOD / stat.speed * 100 <= (currentTime - lastRaindropTime) && raindropList.cntRaindrop < MAX_COUNT_OF_RAINDROPS)
			{
				//���ο� ����� �߰�
				lastRaindropTime = currentTime;
				addRaindrop(&raindropList, wordList, currentTime);
			}
		}
		statPrint(remain);
	}

	//EXIT
#if VERSION != 0
	pthread_join(thread, (void**)&joinStatus); //�����尡 ���������� ��ٸ���
	pthread_cancel(thread);
	//pthread_exit(NULL);
#else	//threadPrgm
	//_endthreadex(0);
#endif

	gameend(stat);

	for (int i = 0; i < wordList.cntWord; i++)	free(wordList.words[i]);
	free(wordList.words);
	for (int i = 0; i < raindropList.cntRaindrop; i++)	free(raindropList.raindrops[i].word);
	
	gotoxy(0, MAX_Y + 2);

	return;
}