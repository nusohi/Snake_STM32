#include "sys.h"
#include "delay.h"
#include "lcd.h"
#include "led.h"
#include "beep.h"
#include <stdlib.h>
#include "stdbool.h"

#define maxlen 104
#define LOSE 1
#define WIN 2
#define CONTINUE 3

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

#define WallX 20
#define WallY 30



typedef struct{
	int x;
	int y;
}Position;


static Position SnakePos[maxlen];	//?? public
static Position lastTail;
static Position f;
static int speed = 0;
static int score = 0;
static int grade = 0;
static int countFood = 0;
static int length = 0;
static int direction = 0;
static int targetDirect;

void clearSnake(void);
void printSnake(void);
bool knockSnake(void);	//food
bool knockFood(void);	//snake
bool knockSelf(void);	//snake
bool knockWall(void);	//snake
bool closeToWall(void);

void avoidSingle(void);	//food avoid
void avoidWall(void);	//food avoid
void createFood(void);
void updateScore(void);	// update Score Grade

int Judge(void);
void printInfo(void);

void moveU(void);
void moveD(void);
void moveL(void);
void moveR(void);
void move(int direct);
/******************************/
void Snake(void);
int getLen(void);
int getSpeed(void);
void addSnake(void);


void Print(int x, int y, const char* str, int color);
void PrintNum(int x, int y, int num, int len, int color);
const char* DirectStr(int direct); 


int newDirection(void);
void UpdateDirection(int direct);

//??
void createWall(void);
//???
void snake_main(void);
