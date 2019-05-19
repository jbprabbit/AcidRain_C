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
	char tempstring[MAX_LENGTH_OF_STRING + 1];			//���ڿ� �ӽ� ����
	//stat ���
	sprintf(tempstring, "���� ü��: %2d", remain.life);
	printWord(2, STATUS_PRINT_Y, tempstring);

	sprintf(tempstring, "���� ����: %2d", remain.pause);
	printWord(2, STATUS_PRINT_Y + 1, tempstring);

	sprintf(tempstring, "���� ��ź: %2d", remain.bomb);
	printWord(2, STATUS_PRINT_Y + 2, tempstring);
}
void scorePrint(STATUS stat)
{
	char tempstring[MAX_LENGTH_OF_STRING + 1];			//���ڿ� �ӽ� ����
	//score ���
	sprintf(tempstring, "SCORE: %8d", stat.score);
	printWord(SCORE_PRINT_X, SCORE_PRINT_Y, tempstring);
}
void speedPrint(STATUS stat)
{
	char tempstring[MAX_LENGTH_OF_STRING + 1];			//���ڿ� �ӽ� ����
	//speed ���
	sprintf(tempstring, "SPEED: %7d%%", stat.speed);
	printWord(SPEED_PRINT_X, SPEED_PRINT_Y, tempstring);
}
void printAll(REMAIN remain, STATUS stat)
{
	clear();

	printWord(NAME_PRINT_X, NAME_PRINT_Y, "�꼺��");

	statPrint(remain);
	scorePrint(stat);
	speedPrint(stat);

	//endCommand ���
	printWord(0, DESCRIPTION_Y, "     ����: 3�ʰ� �����մϴ�\t  ��ź: ��� �ܾ �����մϴ�\t  ����: ��������� �����մϴ�");

	//������ ������ �κ� ǥ��
	for (int i = 0; i < MAX_X + 10; i++)	printWord(i++, MAX_Y, "��");
}