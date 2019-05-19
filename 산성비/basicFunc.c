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
	tcgetattr(STDIN_FILENO, &oldattr);           // 현재 터미널 설정 읽음
	newattr = oldattr;
	newattr.c_lflag &= ~(ICANON | ECHO);         // CANONICAL과 ECHO 끔
	newattr.c_cc[VMIN] = 1;                      // 최소 입력 문자 수를 1로 설정
	newattr.c_cc[VTIME] = 0;                     // 최소 읽기 대기 시간을 0으로 설정
	tcsetattr(STDIN_FILENO, TCSANOW, &newattr);  // 터미널에 설정 입력
	c = getchar();                               // 키보드 입력 읽음
	tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);  // 원래의 설정으로 복구
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
	tcgetattr(STDIN_FILENO, &oldattr);           // 현재 터미널 설정 읽음
	newattr = oldattr;
	newattr.c_lflag &= ~(ICANON | ECHO);         // CANONICAL과 ECHO 끔
	newattr.c_cc[VMIN] = 1;                      // 최소 입력 문자 수를 1로 설정
	newattr.c_cc[VTIME] = 0;                     // 최소 읽기 대기 시간을 0으로 설정
	tcsetattr(STDIN_FILENO, TCSANOW, &newattr);  // 터미널에 설정 입력
	c = getchar();                               // 키보드 입력 읽음
	tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);  // 원래의 설정으로 복구
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