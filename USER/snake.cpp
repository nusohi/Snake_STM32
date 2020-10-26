// snake.cpp: ??????????????
//

#include "sys.h"
#include "delay.h"

#include "snake.h"
//#include <time.h>
//#include <stdio.h>
#include <string.h>
//#include <iostream>

using namespace std;



//???????
int newDirection() {
	
}

//??
void createWall() {
	for (int i = 0; i < WallX; i++)
		Print(i, 0, "?");

	for (int i = 0; i < WallX; i++)
		Print(i, WallY, "?");

	for (int i = 1; i < WallY; i++) {
		Print(0, i, "?");
		Print(WallX - 1, i, "?");
	}
}



//Snake ?
void Snake() {
	length = 3;
	direction = RIGHT;
	speed = 550;
	score = 0;
	grade = 1;
	countFood = 0;
	pos[0].x = 2; pos[1].x = 3; pos[2].x = 4;
	pos[0].y = pos[1].y = pos[2].y = 4;
	/*??? ????*/
	for (int i = 0; i < length; i++) {
		Print(pos[i].x, pos[i].y, "?");
	}
}

//????
void addSnake() {
	for (int i = length - 1; i >= 0; i--) {
		pos[i + 1].x = pos[i].x;
		pos[i + 1].y = pos[i].y;
	}
	pos[0].x = lastTail.x;
	pos[0].y = lastTail.y;
	length++;
}


//????,????
void clearSnake() {
	Print(pos[0].x, pos[0].y, "  ");//????
}

void printSnake() {
	//?????(???????)
	Print(pos[length - 1].x, pos[length - 1].y, "?", 3);	// ????? 3
	Print(pos[length - 2].x, pos[length - 2].y, "?", 7);	// ?????? 7
}

//??
void moveU() {
	int i;
	lastTail = pos[0];	//??????????????????
	for (i = 0; i < length - 1; i++) {
		pos[i] = pos[i + 1];
	}
	pos[i].y--;
	direction = UP;
}
void moveD() {
	int i;
	lastTail = pos[0];
	for (i = 0; i < length - 1; i++) {
		pos[i] = pos[i + 1];
	}
	pos[i].y++;
	direction = DOWN;
}
void moveL() {
	int i;
	lastTail = pos[0];
	for (i = 0; i < length - 1; i++) {
		pos[i] = pos[i + 1];
	}
	pos[i].x --;
	direction = LEFT;
}
void moveR() {
	int i;
	lastTail = pos[0];
	for (i = 0; i < length - 1; i++) {
		pos[i] = pos[i + 1];
	}
	pos[i].x ++;
	direction = RIGHT;
}
void move(int direct) {
	if (direct == 0)
		move(direction);
	if (direct == UP)
		if (direction == DOWN)
			moveD();
		else
			moveU();
	if (direct == DOWN)
		if (direction == UP)
			moveU();
		else
			moveD();
	if (direct == LEFT)
		if (direction == RIGHT)
			moveR();
		else
			moveL();
	if (direct == RIGHT)
		if (direction == LEFT)
			moveL();
		else
			moveR();
	targetDirect = direction;
}

//food knock
bool knockSnake() {
	for (int i = 0; i < length; i++) {
		if (f.x == pos[i].x && f.y == pos[i].y) //???y???x,  Hours wasted
			return 1;
	}
	return 0;
}

//snake knock
bool knockFood() {
	if ((pos[length - 1].x == f.x) && (pos[length - 1].y == f.y)) {
		return 1;
	}
	else if ((pos[length - 2].x == f.x) && (pos[length - 2].y == f.y))
		return 1;
	else
		return 0;
}
bool knockSelf() {
	for (int i = 0; i < length - 1; i++)
		if (pos[i].x == pos[length - 1].x && pos[i].y == pos[length - 1].y)
			return 1;
	return 0;
}
bool knockWall() {
	if (pos[length - 1].x <= 0 || pos[length - 1].y <= 0 ||
		pos[length - 1].x >= WallX - 1 || pos[length - 1].y >= WallY)
		return 1;
	return 0;
}

//food avoid
void avoidSingle() {
	if (f.x % 2 != 0)f.x++;
}
void avoidWall() {
	if (f.x <= 1) f.x += 2;
	if (f.x >= WallX - 1) f.x -= 2;
	if (f.y <= 1) f.y += 4;
	if (f.y >= WallY - 1) f.y -= 2;
}

//food
void createFood() {
//	srand(unsigned(time(NULL)));		//amazing!	//?????????
	do {
//		f.x = rand() % WallX;
//		f.y = rand() % WallY;
		avoidSingle();
		avoidWall();
	} while (knockSnake());

	Print(f.x, f.y, "?");	// setCP(f.x, f.y);
							// cout << "?";
	
	countFood++;                   //???? ?????
}

//????
int Judge() {
	//LOSE
	if (knockSelf() || knockWall()) {
		Print(WallX + 1, WallY - 4, "Sorry! You lose!");
		//cout << "Sorry! You lose!";
		//setCP(2 * WallX + 2, WallY);

		return LOSE;
	}
	//WIN
	if (length == maxlen) {
		Print(WallX + 1, WallY - 4, "Congratulations! You win!");
		//cout << "Congratulations! You win!" << endl;
		//setCP(2 * WallX + 2, WallY);

		return WIN;
	}
	return CONTINUE;

}

//???????  speed grade score
void printInfo() {
	score = 10 * (countFood - 1);	//1000
	if (score >= 1000)	 grade = 10;
	else if (score >= 800)grade = 9;
	else if (score >= 650)grade = 8;
	else if (score >= 500)grade = 7;
	else if (score >= 350)grade = 6;
	else if (score >= 250)grade = 5;
	else if (score >= 150)grade = 4;
	else if (score >= 100)grade = 3;
	else if (score >= 50) grade = 2;
	speed = 600 - 50 * grade;
//	const char* G = "??:" + (grade + '0')+'\0';
	Print(WallX + 1, 1, "??:");
	//Print(WallX + 1, 1, StrCat("??:", (const char*)(grade + '0')));
	//Print(WallX + 1, 3, (const char*)("??:" + (grade + '0') + '\0'));
	//Print(WallX + 1, 5, (const char*)("??:" + (speed + '0') + '\0'));

	Print(WallX + 1, 7, "target:");
	Print(WallX + 8, 7, DirectStr(targetDirect));
}

void Print(int x, int y, const char * str, int color)
{
	if (color == -1);	// set color
	else {
		
	}

	//setCP(x*2, y);
	//cout << str;
}

const char * StrCat(const char * A, const char * B)
{
	//char *res = (char *)malloc(strlen(A) + strlen(B));
	char *res = new char[strlen(A) + strlen(B)];
	//sprintf(res, "%s%s", A, B);
	return res;
}

const char * DirectStr(int direct)
{
	if (direct == UP)
		return "UP    ";
	else if (direct == DOWN)
		return "DOWN  ";
	else if (direct == LEFT)
		return "LEFT  ";
	else if (direct == RIGHT)
		return "RIGHT ";
	else
		return "FK    ";
}



//?????
void snake_main() {
	Snake();			//?? ??????(3?)
	createWall();
	//hideCursor();		//???????????
	createFood();
	while (1) {
		printInfo();
		clearSnake();	//????
		// int tempLen = getLen();	//??(??)

		int D = newDirection();
		move(D);		//??
		if (knockFood()) {
			addSnake();
			createFood();
		}
		printSnake();	//????	//???Sleep()??  //?????????????	//???
		if (Judge() == CONTINUE);
		else break;					//?or? ?break, ??continue????.
		//if (getLen() != tempLen)		//??food->????->?????????? ->>???food
			//createFood();
		delay_ms(getSpeed());
	}
}

