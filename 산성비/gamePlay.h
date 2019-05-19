#pragma once
typedef struct {
	int life;
	int pause;
	int bomb;
}REMAIN;

typedef struct {
	int score;
	int speed;
}STATUS;

void gameplay(void);