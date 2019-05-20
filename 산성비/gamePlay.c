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

char run = TRUE;									//게임 반복 여부(종료되면 FALSE)

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
			if (temp == 13)	//Enter 입력
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
			else if (temp == 8)	//backspace 입력
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
			if (temp == 13) {		//Enter 입력
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
			if (temp == 13)	//Enter 입력
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
			else if (temp == 8)	//backspace 입력
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
	//변수 선언
	RAINDROP_LIST raindropList;							//빗방울 목록
	WORD_LIST wordList;									//파일에 있는 단어 목록 저장

	INPUT_WORD input;									//키보드 입력 저장
	pthread_t thread;									//키보드 입력을 위한 쓰레드
	int joinStatus;										//쓰레드 상태

	clock_t lastRaindropTime = 0;						//가장 최근에 빗방울이 생성된 시간
	clock_t currentTime;								//시간 저장

	
	char stopFlag = FALSE;
	clock_t stopTime = 0;

	//초기화
	srand((unsigned int)time(NULL));
	STATUS stat = { 0, 100 };
	REMAIN remain = { LIFE, PAUSE, BOMB };
	setWordList(&wordList);								//파일에서 단어 목록 읽어옴
	raindropList.cntRaindrop = 0;
	input.flag = FALSE;

	/*****초기 화면 출력*****/
	printAll(remain, stat);

	/*****사용자 입력 관리 쓰레드 시작*****/
#if VERSION != 0
	pthread_create(&thread, NULL, wordScan, (void*)&input);		//스레드를 생성하고 작동시킨다 (사용자 입력 관리 쓰레드)
	pthread_detach(thread);										//쓰레드 실행
#else	//threadPrgm
	_beginthreadex(NULL, 0, wordScan, (void *)&input, 0, NULL);
#endif

	run = TRUE;

	while (run)
	{
		//입력받은 단어처리
		if (input.flag)
		{
			//종료입력시
			if (!strcmp(input.word, "종료"))
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
			//정지 입력시
			else if (!strcmp(input.word, "정지") && remain.pause > 0)
			{
				remain.pause--;
				statPrint(remain);
				stopFlag = TRUE;
				stopTime = getClock();
			}
			//폭탄 입력시
			else if (!strcmp(input.word, "폭탄") && remain.bomb > 0)
			{
				while (raindropList.cntRaindrop != 0)	removeRaindrop(&raindropList, 0);
				remain.bomb--;
				statPrint(remain);
			}

			//빗방울중 입력된 단어 찾은후 처리
			int index;
			do {
				index = findRaindropIdx(raindropList, input.word);
				if (index != -1)
				{
					scoreUpdate(raindropList, index, &stat);	//점수 계산
					speedUpdate(&stat);					//속도 계산
					removeRaindrop(&raindropList, index);
				}
			} while (index != -1);

			input.flag = FALSE;
		}

		currentTime = getClock();
		if (currentTime - stopTime >= PAUSE_TIME)	stopFlag = FALSE;	//추가한 코드: 정지 끝

		if (stopFlag == FALSE)	//추가한 코드: 정지시가 아닐때만 빗방울생성 및 떨어짐
		{
			//빗방울 관리
			for (int i = 0; i < raindropList.cntRaindrop; i++)
			{
				if (raindropList.raindrops[i].lastUpdatedTime + (double)raindropList.raindrops[i].period / stat.speed * 100 <= currentTime)
				{
					//빗방울이 한 줄 아래로 내려감
					raindropList.raindrops[i].lastUpdatedTime = currentTime;
					removeRaindropFromConsole(&raindropList, i);						//일치한 단어 화면에서 삭제
					raindropList.raindrops[i].y++;
					if (raindropList.raindrops[i].y >= MAX_Y)
					{
#if VERSION != 0
						pthread_cancel(thread);
#else	//threadPrgm
						//_endthreadex(0);
#endif
						//////////
						//추가한 코드 : 생명3개
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
				//새로운 빗방울 추가
				lastRaindropTime = currentTime;
				addRaindrop(&raindropList, wordList, currentTime);
			}
		}
		statPrint(remain);
	}

	//EXIT
#if VERSION != 0
	pthread_join(thread, (void**)&joinStatus); //스레드가 끝날때까지 기다린다
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