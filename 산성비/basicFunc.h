#pragma once
#include <time.h>

#ifdef _WIN32
#include <conio.h>
#define getch() _getch()
void gotoxy(int x, int y);
void wait(int msec);
void clear(void);
clock_t getClock(void);

#elif __linux__
int getch(void);
void gotoxy(int x, int y);
void wait(int msec);
void clear(void);
clock_t getClock(void);

#elif __unix__ // all unices not caught above
int getch(void);
void gotoxy(int x, int y);
void wait(int msec);
void clear(void);
clock_t getClock(void);

#endif