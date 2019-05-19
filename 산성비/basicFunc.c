#include <time.h>
#ifdef _WIN32
//define something for Windows (32-bit and 64-bit, this part is common)
#include <Windows.h>
void gotoxy(int x, int y) {
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void wait(int msec) {
	Sleep(msec);
}
void clear(void) {
	system("cls");
}
clock_t getClock(void) {
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