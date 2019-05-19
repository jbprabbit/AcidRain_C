#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "const.h"
#include <time.h>
#include "rainDropMng.h"
#include "printWord.h"

extern char file_name[10];

//추가구현: 단어 추가위해 txt파일 첫줄 숫자 지움
void setWordList(WORD_LIST *wordList)
{
	FILE *fp = fopen(file_name, "r");

	int tempLen;
	char tempString[MAX_LENGTH_OF_STRING + 1];

	//init
	wordList->cntWord = 0;
	wordList->words = NULL;

	while (fscanf(fp, "%s", tempString) != EOF)
	{
		tempLen = strlen(tempString);
		wordList->words = (char **)realloc(wordList->words, sizeof(char *) * (wordList->cntWord + 1));
		wordList->words[wordList->cntWord] = NULL;
		wordList->words[wordList->cntWord] = (char *)realloc(wordList->words[wordList->cntWord], sizeof(char) * tempLen + 1);
		strcpy(wordList->words[wordList->cntWord], tempString);
		wordList->cntWord++;
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

	for (int i = 0; i < raindropList->raindrops[idx].length; i++)	tempstring[i] = ' ';
	tempstring[raindropList->raindrops[idx].length] = '\0';
	printWord(raindropList->raindrops[idx].x, raindropList->raindrops[idx].y, tempstring);
}
void removeRaindropFromList(RAINDROP_LIST *raindropList, int idx)
{
	free(raindropList->raindrops[idx].word);
	for (int i = idx; i < raindropList->cntRaindrop - 1; i++)
		raindropList->raindrops[i] = raindropList->raindrops[i + 1];
	raindropList->cntRaindrop--;
}