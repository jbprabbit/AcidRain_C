#pragma once
#include <stdio.h>
#include "basicFunc.h"
#include "const.h"

//�Է¹��� x, y ��ǥ�� �Է¹��� word ���
void printWord(int x, int y, char* word)
{
	gotoxy(x, y);
	printf("%s", word);
	gotoxy(0, 0);
	//gotoxy(MAX_X, DESCRIPTION_Y);
	wait(2);
}