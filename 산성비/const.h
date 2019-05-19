#define MAX_LENGTH_OF_STRING 100

#define NAME_PRINT_X 44
#define NAME_PRINT_Y 1

#define DESCRIPTION_Y (NAME_PRINT_Y + 2)
#define STATUS_PRINT_Y	(NAME_PRINT_Y + 4)

#define SCORE_PRINT_X 80
#define SCORE_PRINT_Y (NAME_PRINT_Y + 4)

#define SPEED_PRINT_X 80
#define SPEED_PRINT_Y (SCORE_PRINT_Y + 1)


#define TRUE 1
#define FALSE 0
#define MAX_COUNT_OF_RAINDROPS 20								//����� �ִ� ����
#define GENERATE_PERIOD 2000									//����� ���� �ֱ�
#define DROP_PERIOD_MIN 500										//����� �������� �ֱ� �ּ�
#define DROP_PERIOD_MAX 700										//����� �������� �ֱ� �ִ�

#define KOR_FILE "word.txt"
#define ENG_FILE "english.txt"

#define FILE_NAME "word.txt"									//�ܾ ����Ǿ� �ִ� ���� �̸�(�ѱ� �ܾ�)
//#define FILE_NAME "english.txt"								//�ܾ ����Ǿ� �ִ� ���� �̸�(���� �ܾ�)

#define MAX_X 90												//����� X ��ǥ �ִ� ��
#define MAX_Y (28 + NAME_PRINT_Y)								//����� Y ��ǥ �ִ� ��
#define MIN_Y (8 + NAME_PRINT_Y)								//����� Y ��ǥ �ּ� ��

#define MID_X	(MAX_X / 2)
#define MID_Y	(MAX_Y / 2)
#define MID_X_CON 2
#define MID_X_WOR (MID_X - MID_X_CON)

#define PAUSE 3													//"����"�ܾ� ���� Ƚ�� �ʱ� ��
#define BOMB 3													//"��ź"�ܾ� ���� Ƚ�� �ʱ� ��
#define PAUSE_TIME 3000											//"����"�ܾ� �Է� �� ���� �ð�(ms)
#define LIFE 3													//ü�� �ʱ� ��