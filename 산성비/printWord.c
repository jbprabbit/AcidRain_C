#include "const.h"
//�Է¹��� x, y ��ǥ�� �Է¹��� word ���
void printWord(int x, int y, char* word)
{
	gotoxy(x, y);
	printf("%s", word);
	gotoxy(MAX_X, DESCRIPTION_Y);
	wait(2);
}