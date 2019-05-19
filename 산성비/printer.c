#define _CRT_SECURE_NO_WARNINGS
#include "gamePlay.h"
#include "const.h"
#include <stdio.h>
#include "printWord.h"
#include "basicFunc.h"
#include "rainDropMng.h"
#include "printer.h"

void scoreUpdate(RAINDROP_LIST raindropList, int idx, STATUS *stat)
{
	stat->score += (stat->speed * (DROP_PERIOD_MAX - raindropList.raindrops[idx].period + 100) / 100);
	scorePrint(*stat);
}
void speedUpdate(STATUS *stat)
{
	stat->speed = 100 + stat->score / 100;
	speedPrint(*stat);
}
void statPrint(REMAIN remain)
{
	char tempstring[MAX_LENGTH_OF_STRING + 1];			//문자열 임시 저장
	//stat 출력
	sprintf(tempstring, "남은 체력: %2d", remain.life);
	printWord(2, STATUS_PRINT_Y, tempstring);

	sprintf(tempstring, "남은 정지: %2d", remain.pause);
	printWord(2, STATUS_PRINT_Y + 1, tempstring);

	sprintf(tempstring, "남은 폭탄: %2d", remain.bomb);
	printWord(2, STATUS_PRINT_Y + 2, tempstring);
}
void scorePrint(STATUS stat)
{
	char tempstring[MAX_LENGTH_OF_STRING + 1];			//문자열 임시 저장
	//score 출력
	sprintf(tempstring, "SCORE: %8d", stat.score);
	printWord(SCORE_PRINT_X, SCORE_PRINT_Y, tempstring);
}
void speedPrint(STATUS stat)
{
	char tempstring[MAX_LENGTH_OF_STRING + 1];			//문자열 임시 저장
	//speed 출력
	sprintf(tempstring, "SPEED: %7d%%", stat.speed);
	printWord(SPEED_PRINT_X, SPEED_PRINT_Y, tempstring);
}
void printAll(REMAIN remain, STATUS stat)
{
	clear();

	printWord(NAME_PRINT_X, NAME_PRINT_Y, "산성비");

	statPrint(remain);
	scorePrint(stat);
	speedPrint(stat);

	//endCommand 출력
	printWord(0, DESCRIPTION_Y, "     정지: 3초간 정지합니다\t  폭탄: 모든 단어를 삭제합니다\t  종료: 현재게임을 종료합니다");

	//닿으면 끝나는 부분 표시
	for (int i = 0; i < MAX_X + 10; i++)	printWord(i++, MAX_Y, "■");
}