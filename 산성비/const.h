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
#define MAX_COUNT_OF_RAINDROPS 20								//빗방울 최대 개수
#define GENERATE_PERIOD 2000									//빗방울 생성 주기
#define DROP_PERIOD_MIN 500										//빗방울 떨어지는 주기 최소
#define DROP_PERIOD_MAX 700										//빗방울 떨어지는 주기 최대

#define KOR_FILE "word.txt"
#define ENG_FILE "english.txt"

#define FILE_NAME "word.txt"									//단어가 저장되어 있는 파일 이름(한글 단어)
//#define FILE_NAME "english.txt"								//단어가 저장되어 있는 파일 이름(영어 단어)

#define MAX_X 90												//빗방울 X 좌표 최대 값
#define MAX_Y (28 + NAME_PRINT_Y)								//빗방울 Y 좌표 최대 값
#define MIN_Y (8 + NAME_PRINT_Y)								//빗방울 Y 좌표 최소 값

#define MID_X	(MAX_X / 2)
#define MID_Y	(MAX_Y / 2)
#define MID_X_CON 2
#define MID_X_WOR (MID_X - MID_X_CON)

#define PAUSE 3													//"정지"단어 가능 횟수 초기 값
#define BOMB 3													//"폭탄"단어 가능 횟수 초기 값
#define PAUSE_TIME 3000											//"정지"단어 입력 시 정지 시간(ms)
#define LIFE 3													//체력 초기 값