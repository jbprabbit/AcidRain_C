#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define HAVE_STRUCT_TIMESPEC
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <pthread.h>

#ifdef _WIN32
//define something for Windows (32-bit and 64-bit, this part is common)
#include <Windows.h>
#include <conio.h>
#define getch() _getch()

void gotoxy(int x, int y) {
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void wait(int msec) {
	Sleep(msec);
}
void clear() {
	system("cls");
}
clock_t getClock() {
	return clock();
}
#elif __linux__
// linux
#include <unistd.h>
#include <termio.h>
int getch(void)
{
	int c;
	struct termios oldattr, newattr;
	tcgetattr(STDIN_FILENO, &oldattr);           // ���� �͹̳� ���� ����
	newattr = oldattr;
	newattr.c_lflag &= ~(ICANON | ECHO);         // CANONICAL�� ECHO ��
	newattr.c_cc[VMIN] = 1;                      // �ּ� �Է� ���� ���� 1�� ����
	newattr.c_cc[VTIME] = 0;                     // �ּ� �б� ��� �ð��� 0���� ����
	tcsetattr(STDIN_FILENO, TCSANOW, &newattr);  // �͹̳ο� ���� �Է�
	c = getchar();                               // Ű���� �Է� ����
	tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);  // ������ �������� ����
	return c;
}
void gotoxy(int x, int y) {
	printf("\033[%d;%df", y, x);
	fflush(stdout);
}
void wait(int msec) {
	usleep(msec * 1000);
}
void clear() {
	printf("\033[H\033[J");
}
clock_t getClock() {
	return clock() / 10;
}
#elif __unix__ // all unices not caught above
// Unix
#include <unistd.h>
#include <termio.h>
int getch(void)
{
	int c;
	struct termios oldattr, newattr;
	tcgetattr(STDIN_FILENO, &oldattr);           // ���� �͹̳� ���� ����
	newattr = oldattr;
	newattr.c_lflag &= ~(ICANON | ECHO);         // CANONICAL�� ECHO ��
	newattr.c_cc[VMIN] = 1;                      // �ּ� �Է� ���� ���� 1�� ����
	newattr.c_cc[VTIME] = 0;                     // �ּ� �б� ��� �ð��� 0���� ����
	tcsetattr(STDIN_FILENO, TCSANOW, &newattr);  // �͹̳ο� ���� �Է�
	c = getchar();                               // Ű���� �Է� ����
	tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);  // ������ �������� ����
	return c;
}
void gotoxy(int x, int y) {
	printf("\033[%d;%df", y, x);
	fflush(stdout);
}
void wait(int msec) {
	usleep(msec * 1000);
}
void clear() {
	printf("\033[H\033[J");
}
clock_t getClock() {
	return clock() / 10;
}
#endif

#define MAX_LENGTH_OF_STRING 100
#define SCORE_X 30
#define SPEED_X 50
#define DESCRIPTION_Y 1
#define REMAIN_SPECIAL_Y 2

#define TRUE 1
#define FALSE 0
#define MAX_COUNT_OF_RAINDROPS 20								//����� �ִ� ����
#define GENERATE_PERIOD 2000									//����� ���� �ֱ�
#define DROP_PERIOD_MIN 500										//����� �������� �ֱ� �ּ�
#define DROP_PERIOD_MAX 700										//����� �������� �ֱ� �ִ�
#define FILE_NAME "word.txt"									//�ܾ ����Ǿ� �ִ� ���� �̸�(�ѱ� �ܾ�)
//#define FILE_NAME "english.txt"								//�ܾ ����Ǿ� �ִ� ���� �̸�(���� �ܾ�)
#define MAX_X 70												//����� X ��ǥ �ִ� ��
#define MAX_Y 25												//����� Y ��ǥ �ִ� ��
#define MIN_Y 5													//����� Y ��ǥ �ּ� ��

#define PAUSE 3													//"����"�ܾ� ���� Ƚ�� �ʱ� ��
#define BOMB 3													//"��ź"�ܾ� ���� Ƚ�� �ʱ� ��
#define PAUSE_TIME 3000											//"����"�ܾ� �Է� �� ���� �ð�(ms)
#define LIFE 3													//ü�� �ʱ� ��

//�Է¹��� x, y ��ǥ�� �Է¹��� word ���
void printWord(int x, int y, char* word)
{
	gotoxy(x, y);
	printf("%s", word);
	gotoxy(MAX_X, DESCRIPTION_Y);
	wait(2);
}

#ifdef _WIN32
///////////////////////////////////////////////////////////////////////// ���� Ȯ��
//define something for Windows (32-bit and 64-bit, this part is common)

// Version 1
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
// Version 2
/*
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
				if(temp > 0) {
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
*/
// Version 3
/*
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
*/

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
/////////////////////////////////

///////////////////////////////// �ؼ��� �ʿ��� �ڵ�
typedef struct {
	char* word;												//�ܾ� ����
	int x, y;												//�ܾ��� ù ������ ��ǥ
	int length;												//�ܾ��� ����
	int period;												//������Ʈ �ֱ�(ms����, 100~300���� ������ ��, main�� speed�� ����)
	clock_t lastUpdatedTime;								//�ֱ� ������Ʈ �ð�
}RAINDROP;													//ȭ�鿡�� �������� �ܾ ������ ����ü
typedef struct {
	RAINDROP raindrops[MAX_COUNT_OF_RAINDROPS];				//���� ȭ�鿡 ǥ�õ� �ܾ��
	int cntRaindrop;										//�������� �ܾ��� ����
}RAINDROP_LIST;												//�������� �ܾ��� ����� ������ ����ü
typedef struct {
	char** words;											//���Ͽ� �ִ� �ܾ ������ ���� ����
	int cntWord;											//�ܾ ����Ǿ� �ִ� ����
}WORD_LIST;													//�ܾ��� ����� ������ ����ü

void setWordList(WORD_LIST * wordList);													//�ܾ ����� ������ �ҷ��ͼ� WORD_LIST�� �ܾ��� ����� �����ϴ� �Լ�

void addRaindrop(RAINDROP_LIST *raindropList, WORD_LIST wordList, clock_t time);		//WORD_LIST�� ����� �ܾ��� ������ �ܾ�� ���ο� ������� ����� �Լ�
int findRaindropIdx(RAINDROP_LIST raindropList, char *word);							//�Ű������� word�� ��ġ�ϴ� �ܾ ���� ������� ã�� �ε����� ��ȯ�ϴ� �Լ� (���� ��� -1 ��ȯ)

void removeRaindrop(RAINDROP_LIST *raindropList, int idx);
void removeRaindropFromConsole(RAINDROP_LIST *raindropList, int idx);					//�־��� �ε����� ������� �ܼ�â���� ����
void removeRaindropFromList(RAINDROP_LIST *raindropList, int idx);						//�־��� �ε����� ������� ����Ʈ���� �����ϰ� �� �ڿ� �����ϴ� �������� ��ĭ�� ������ �ű�� �Լ�

int calculateScore(RAINDROP raindrop, int speed);										//�߰��� ���� ���

void scoreUpdate(RAINDROP_LIST raindropList, int idx);
void speedUpdate(void);
void statPrint(void);
void scorePrint(void);
void speedPrint(void);
void printAll(void);

int remainPause = PAUSE;							//���� ���� Ƚ��
int remainBomb = BOMB;								//���� ��ź Ƚ��
int remainLife = LIFE;								//���� ü��

int score = 0;										//����
int speed = 100;									//%����, 100���� �����Ͽ� �ð��� �������� speed ���

int main(void)
{
	//���� ����
	RAINDROP_LIST raindropList;							//����� ���
	//int idx;											//�ε��� ���忡 ���

	INPUT_WORD input;									//Ű���� �Է� ����
	char tempstring[MAX_LENGTH_OF_STRING + 1];			//���ڿ� �ӽ� ����
	WORD_LIST wordList;									//���Ͽ� �ִ� �ܾ� ��� ����

	pthread_t thread;									//Ű���� �Է��� ���� ������
	int joinStatus;										//������ ����
	
	clock_t lastRaindropTime = 0;						//���� �ֱٿ� ������� ������ �ð�
	clock_t currentTime;								//�ð� ����
	char run = TRUE;									//���� �ݺ� ����(����Ǹ� FALSE)

	char stopFlag = FALSE;
	clock_t stopTime = 0;

	//�ʱ�ȭ
	srand((unsigned int)time(NULL));
	setWordList(&wordList);								//���Ͽ��� �ܾ� ��� �о��
	raindropList.cntRaindrop = 0;
	input.flag = FALSE;

	/*****�ʱ� ȭ�� ���*****/
	printAll();

	/*****����� �Է� ���� ������ ����*****/
	pthread_create(&thread, NULL, wordScan, (void*)&input);		//�����带 �����ϰ� �۵���Ų�� (����� �Է� ���� ������)
	pthread_detach(thread);										//������ ����

	while (run)
	{
		//�Է¹��� �ܾ�ó��
		if (input.flag)
		{
			//�����Է½�
			if (!strcmp(input.word, "����"))
			{
				pthread_cancel(thread);
				break;
			}
			//���� �Է½�
			else if (!strcmp(input.word, "����") && remainPause > 0)
			{
				remainPause--;
				statPrint();
				stopFlag = TRUE;
				stopTime = getClock();
			}
			//��ź �Է½�
			else if (!strcmp(input.word, "��ź") && remainBomb > 0)
			{
				while(raindropList.cntRaindrop != 0)	removeRaindrop(&raindropList, 0);
				remainBomb--;
				statPrint();
			}
			//������� �Էµ� �ܾ� ã���� ó��
			int index;
			do {
				index = findRaindropIdx(raindropList, input.word);
				if (index != -1)
				{
					scoreUpdate(raindropList,index);	//���� ���
					speedUpdate();					//�ӵ� ���
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
				if (raindropList.raindrops[i].lastUpdatedTime + (double)raindropList.raindrops[i].period / speed * 100 <= currentTime)
				{
					//������� �� �� �Ʒ��� ������
					raindropList.raindrops[i].lastUpdatedTime = currentTime;
					removeRaindropFromConsole(&raindropList, i);						//��ġ�� �ܾ� ȭ�鿡�� ����
					raindropList.raindrops[i].y++;
					if (raindropList.raindrops[i].y >= MAX_Y)
					{
						/////////////////////////////////
						//���� ������� �ڵ�
						pthread_cancel(thread);
						/////////////////////////////////

						//////////
						//�߰��� �ڵ� : ����3��
						removeRaindropFromList(&raindropList, i);
						remainLife--;
						if (remainLife < 0)	run = FALSE;
						statPrint();
						//////////
					}
					else
					{
						printWord(raindropList.raindrops[i].x, raindropList.raindrops[i].y, raindropList.raindrops[i].word);
					}
				}
			}

			if (lastRaindropTime + (double)GENERATE_PERIOD / speed * 100 <= currentTime && raindropList.cntRaindrop < MAX_COUNT_OF_RAINDROPS)
			{
				//���ο� ����� �߰�
				lastRaindropTime = currentTime;
				addRaindrop(&raindropList, wordList, currentTime);
			}
		}
		statPrint();
	}

	//EXIT
	pthread_join(thread, (void**)&joinStatus); //�����尡 ���������� ��ٸ���
	for (int i = 0; i < wordList.cntWord; i++)	free(wordList.words[i]);
	free(wordList.words);
	for (int i = 0; i < raindropList.cntRaindrop; i++)	free(raindropList.raindrops[i].word);

	printWord(0, MAX_Y + 1, "�����մϴ�.");
	gotoxy(0, MAX_Y + 2);

	return 0;
}

void setWordList(WORD_LIST *wordList)
{
	FILE *fp;
	int tempInt;
	char tempString[MAX_LENGTH_OF_STRING + 1];

	fp = fopen(FILE_NAME, "r");
	fscanf(fp, "%d", &wordList->cntWord);
	wordList->words = (char**)malloc(sizeof(char*) * wordList->cntWord);
	for (int i = 0; i < wordList->cntWord; i++)
	{
		fscanf(fp, "%s", tempString);
		tempInt = strlen(tempString);
		wordList->words[i] = (char*)malloc(sizeof(char) * tempInt + 1);
		strcpy(wordList->words[i], tempString);
	}
	fclose(fp);
	return;
}
void addRaindrop(RAINDROP_LIST *raindropList, WORD_LIST wordList, clock_t time)
{
	int idx, tempInt;
	idx = rand() % wordList.cntWord;
	raindropList->raindrops[raindropList->cntRaindrop].lastUpdatedTime = time;
	raindropList->raindrops[raindropList->cntRaindrop].period = rand() % (DROP_PERIOD_MAX - DROP_PERIOD_MIN + 1) + DROP_PERIOD_MIN;
	raindropList->raindrops[raindropList->cntRaindrop].x = rand() % MAX_X + 1;
	raindropList->raindrops[raindropList->cntRaindrop].y = MIN_Y;

	tempInt = strlen(wordList.words[idx]);
	raindropList->raindrops[raindropList->cntRaindrop].word = (char*)malloc(sizeof(char) * tempInt + 1);
	strcpy(raindropList->raindrops[raindropList->cntRaindrop].word, wordList.words[idx]);
	raindropList->raindrops[raindropList->cntRaindrop].length = tempInt;
	raindropList->cntRaindrop++;
}
int findRaindropIdx(RAINDROP_LIST raindropList, char *word)
{
	for (int i = 0; i < raindropList.cntRaindrop; i++)
	{
		if (strcmp(raindropList.raindrops[i].word, word) == 0) 	return i;
	}
	return -1;
}

void removeRaindrop(RAINDROP_LIST *raindropList, int idx)
{
	removeRaindropFromConsole(raindropList, idx);
	removeRaindropFromList(raindropList, idx);
}
void removeRaindropFromConsole(RAINDROP_LIST *raindropList, int idx)
{
	char tempstring[MAX_LENGTH_OF_STRING + 1];

	/////////////////////////////////
	//���� ������� �ڵ�
	//�ֿܼ��� �ܾ� ����
	for (int i = 0; i < raindropList->raindrops[idx].length; i++)	tempstring[i] = ' ';
	tempstring[raindropList->raindrops[idx].length] = '\0';
	printWord(raindropList->raindrops[idx].x, raindropList->raindrops[idx].y, tempstring);
	/////////////////////////////////
}
void removeRaindropFromList(RAINDROP_LIST *raindropList, int idx)
{
	free(raindropList->raindrops[idx].word);
	for (int i = idx; i < raindropList->cntRaindrop - 1; i++)
	{
		raindropList->raindrops[i].lastUpdatedTime = raindropList->raindrops[i + 1].lastUpdatedTime;
		raindropList->raindrops[i].length = raindropList->raindrops[i + 1].length;
		raindropList->raindrops[i].period = raindropList->raindrops[i + 1].period;
		raindropList->raindrops[i].x = raindropList->raindrops[i + 1].x;
		raindropList->raindrops[i].y = raindropList->raindrops[i + 1].y;
		raindropList->raindrops[i].word = raindropList->raindrops[i + 1].word;
	}
	raindropList->cntRaindrop--;
}


int calculateScore(RAINDROP raindrop, int speed)
{
	return (speed * (DROP_PERIOD_MAX - raindrop.period + 100)) / 100;
}

void scoreUpdate(RAINDROP_LIST raindropList, int idx)
{
	score += calculateScore(raindropList.raindrops[idx], speed);
	scorePrint();
}
void speedUpdate(void)
{
	speed = 100 + score / 100;
	speedPrint();
}
void statPrint(void)
{
	char tempstring[MAX_LENGTH_OF_STRING + 1];			//���ڿ� �ӽ� ����
	//stat ���
	sprintf(tempstring, "���� ü��: %2d ���� ���� Ƚ��: %2d ���� ��ź Ƚ��: %2d", remainLife, remainPause, remainBomb);
	printWord(0, REMAIN_SPECIAL_Y, tempstring);
}
void scorePrint(void)
{
	char tempstring[MAX_LENGTH_OF_STRING + 1];			//���ڿ� �ӽ� ����
	//score ���
	sprintf(tempstring, "SCORE: %8d", score);
	printWord(SCORE_X, DESCRIPTION_Y, tempstring);
}
void speedPrint(void)
{
	char tempstring[MAX_LENGTH_OF_STRING + 1];			//���ڿ� �ӽ� ����
	//speed ���
	sprintf(tempstring, "SPEED: %5d%%", speed);
	printWord(SPEED_X, DESCRIPTION_Y, tempstring);
}
void printAll(void)
{
	clear();

	statPrint();
	scorePrint();
	speedPrint();

	//endCommand ���
	printWord(0, DESCRIPTION_Y, "�������� '����'�� �Է��ϼ���.");

	//������ ������ �κ� ǥ��
	for (int i = 0; i < MAX_X + 10; i++)	printWord(i++, MAX_Y, "��");
}