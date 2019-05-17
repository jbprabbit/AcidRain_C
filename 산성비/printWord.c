#include "const.h"
//입력받은 x, y 좌표에 입력받은 word 출력
void printWord(int x, int y, char* word)
{
	gotoxy(x, y);
	printf("%s", word);
	gotoxy(MAX_X, DESCRIPTION_Y);
	wait(2);
}