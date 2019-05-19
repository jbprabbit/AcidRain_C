#pragma once
#include <time.h>
#include "const.h"
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