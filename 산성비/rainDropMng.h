#pragma once
#include <time.h>
#include "const.h"
typedef struct {
	char* word;												//단어 저장
	int x, y;												//단어의 첫 글자의 좌표
	int length;												//단어의 길이
	int period;												//업데이트 주기(ms단위, 100~300사이 임의의 값, main의 speed와 연동)
	clock_t lastUpdatedTime;								//최근 업데이트 시간
}RAINDROP;													//화면에서 떨어지는 단어를 저장할 구조체
typedef struct {
	RAINDROP raindrops[MAX_COUNT_OF_RAINDROPS];				//현재 화면에 표시된 단어들
	int cntRaindrop;										//떨어지는 단어의 개수
}RAINDROP_LIST;												//떨어지는 단어의 목록을 저장할 구조체
typedef struct {
	char** words;											//파일에 있는 단어를 저장해 놓을 변수
	int cntWord;											//단어가 저장되어 있는 개수
}WORD_LIST;													//단어의 목록을 저장할 구조체

void setWordList(WORD_LIST * wordList);													//단어가 저장된 파일을 불러와서 WORD_LIST에 단어의 목록을 저장하는 함수

void addRaindrop(RAINDROP_LIST *raindropList, WORD_LIST wordList, clock_t time);		//WORD_LIST에 저장된 단어중 임의의 단어로 새로운 빗방울을 만드는 함수
int findRaindropIdx(RAINDROP_LIST raindropList, char *word);							//매개변수의 word와 일치하는 단어를 가진 빗방울을 찾아 인덱스를 반환하는 함수 (없을 경우 -1 반환)

void removeRaindrop(RAINDROP_LIST *raindropList, int idx);
void removeRaindropFromConsole(RAINDROP_LIST *raindropList, int idx);					//주어진 인덱스의 빗방울을 콘솔창에서 삭제
void removeRaindropFromList(RAINDROP_LIST *raindropList, int idx);						//주어진 인덱스의 빗방울을 리스트에서 삭제하고 그 뒤에 존재하는 빗방울들을 한칸씩 앞으로 옮기는 함수