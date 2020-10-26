// snake.cpp: 
//
#include "snake.h"


//???????
int newDirection() {
	return targetDirect;
}
void UpdateDirection(int direct){
	targetDirect = direct;
}

//??
void createWall() {
	int i;
	for (i = 0; i < WallX; i++)
		Print(i, 0, "Q\0", BLACK);

	for (i = 0; i < WallX; i++)
		Print(i, WallY, "Q\0", BLACK);

	for (i = 1; i < WallY; i++) {
		Print(0, i, "Q\0", BLACK);
		Print(WallX - 1, i, "Q\0", BLACK);
	}
}




//Snake ?
void Snake() {
	int i;
	
	length = 3;
	direction = RIGHT;
	targetDirect = RIGHT;
	speed = 550;
	score = 0;
	grade = 1;
	countFood = 0;
	SnakePos[0].x = 2; SnakePos[1].x = 3; SnakePos[2].x = 4;
	SnakePos[0].y = SnakePos[1].y = SnakePos[2].y = 4;
	
	/*??? ????*/
	for (i = 0; i < length; i++) {
		Print(SnakePos[i].x, SnakePos[i].y, "S\0", BLACK);
	}
}

// 添加一节
void addSnake() {
	int i;
	for (i = length - 1; i >= 0; i--) {
		SnakePos[i + 1].x = SnakePos[i].x;
		SnakePos[i + 1].y = SnakePos[i].y;
	}
	SnakePos[0].x = lastTail.x;
	SnakePos[0].y = lastTail.y;
	length++;
}


// 清除蛇尾
void clearSnake() {
	Print(SnakePos[0].x, SnakePos[0].y, "  ", -1);//????
}
// 打印新蛇头
void printSnake() {
	//?????(???????)
	Print(SnakePos[length - 1].x, SnakePos[length - 1].y, "H\0", BLUE);	// ????? 3
	Print(SnakePos[length - 2].x, SnakePos[length - 2].y, "S\0", BLACK);	// ?????? 7
}

// 移动
void moveU() {
	int i;
	lastTail = SnakePos[0];	//??????????????????
	for (i = 0; i < length - 1; i++) {
		SnakePos[i] = SnakePos[i + 1];
	}
	SnakePos[i].y--;
	direction = UP;
}
void moveD() {
	int i;
	lastTail = SnakePos[0];
	for (i = 0; i < length - 1; i++) {
		SnakePos[i] = SnakePos[i + 1];
	}
	SnakePos[i].y++;
	direction = DOWN;
}
void moveL() {
	int i;
	lastTail = SnakePos[0];
	for (i = 0; i < length - 1; i++) {
		SnakePos[i] = SnakePos[i + 1];
	}
	SnakePos[i].x --;
	direction = LEFT;
}
void moveR() {
	int i;
	lastTail = SnakePos[0];
	for (i = 0; i < length - 1; i++) {
		SnakePos[i] = SnakePos[i + 1];
	}
	SnakePos[i].x ++;
	direction = RIGHT;
}
void move(int direct) {
	if (direct == UP){
		if (direction == DOWN)
			moveD();
		else
			moveU();
	}
	else if (direct == DOWN){
		if (direction == UP)
			moveU();
		else
			moveD();
	}
	else if (direct == LEFT){
		if (direction == RIGHT)
			moveR();
		else
			moveL();
	}
	else if (direct == RIGHT){
		if (direction == LEFT)
			moveL();
		else
			moveR();
	}
	else{
		move(direction);
	}
}

//food knock
bool knockSnake() {
	int i;
	for (i = 0; i < length; i++) {
		if (f.x == SnakePos[i].x && f.y == SnakePos[i].y) //???y???x,  Hours wasted
			return 1;
	}
	return 0;
}

//snake knock
bool knockFood() {
	if ((SnakePos[length - 1].x == f.x) && (SnakePos[length - 1].y == f.y)) {
		return 1;
	}
	else if ((SnakePos[length - 2].x == f.x) && (SnakePos[length - 2].y == f.y))
		return 1;
	else
		return 0;
}
bool knockSelf() {
	int i;
	for (i = 0; i < length - 1; i++)
		if (SnakePos[i].x == SnakePos[length - 1].x && SnakePos[i].y == SnakePos[length - 1].y)
			return 1;
	return 0;
}
bool knockWall() {
	if (SnakePos[length - 1].x <= 0 || SnakePos[length - 1].y <= 0 ||
		SnakePos[length - 1].x >= WallX - 1 || SnakePos[length - 1].y >= WallY)
		return 1;
	return 0;
}

bool closeToWall(void){
	int x = SnakePos[length-1].x,
		y = SnakePos[length-1].y;
	if(direction==RIGHT && x>=WallX-3)
		return 1;
	else if(direction==LEFT && x<=2)
		return 1;
	else if(direction==UP && y<=2)
		return 1;
	else if(direction==DOWN && y>=WallY-3)
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
	do {
		f.x = rand() % WallX;
		f.y = rand() % WallY;
		avoidSingle();
		avoidWall();
	} while (knockSnake());

	Print(f.x, f.y, "F\0", RED);
	countFood++;
}

void updateScore(void){
	score = 20 * (countFood - 1);	//1000
	if (score >= 600)	 grade = 10;
	else if (score >= 460)grade = 9;
	else if (score >= 340)grade = 8;
	else if (score >= 280)grade = 7;
	else if (score >= 200)grade = 6;
	else if (score >= 160)grade = 5;
	else if (score >= 120)grade = 4;
	else if (score >= 80)grade = 3;
	else if (score >= 40) grade = 2;
	else grade = 1;
	speed = 600 - 50 * grade;
}

//????
int Judge() {
	//LOSE
	if (knockSelf() || knockWall()) {
		Print(WallX + 1, WallY - 4, "Sorry! You lose!", RED);
		Print(WallX + 1, WallY - 2, "Hit UP to restart!", RED);
		return LOSE;
	}
	//WIN
	if (length == maxlen) {
		Print(WallX + 1, WallY - 4, "Congratulations! You win!", RED);
		return WIN;
	}
	return CONTINUE;
}

// speed grade score
void printInfo() {
	Print(WallX + 1, 	1, "SCORE:", RED);
	PrintNum(WallX + 4, 1, score, 5, RED);
	
	Print(WallX + 1, 	3, "Grade:", BLUE);
	PrintNum(WallX + 4, 3, grade, 5, BLUE);
	
	Print(WallX + 1, 	5, "Speed:", BROWN);
	PrintNum(WallX + 4, 5, speed, 5, BROWN);
 
	Print(WallX + 1, 9, "target:", GREEN);
	Print(WallX + 5, 9, DirectStr(targetDirect), GREEN);
	
	Print(WallX + 1, 11, "current:",GBLUE);
	Print(WallX + 5, 11, DirectStr(direction), GBLUE);
}

int getLen(void) { return length; }
int getSpeed(void) { return speed; }

// 打印到 LCD
void Print(int x, int y, const char * str, int color)
{
	int raw = POINT_COLOR;
	POINT_COLOR = color == -1 ? BLACK : color;
	LCD_ShowString(x*16, y*16, 200, 16, 16, (u8*)str);
	POINT_COLOR = raw;
}
void PrintNum(int x, int y, int num, int len, int color)
{
	int raw = POINT_COLOR;
	POINT_COLOR = color == -1 ? BLACK : color;
	LCD_ShowxNum(x*16, y*16, num, len, 16, 0);
	POINT_COLOR = raw;
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

// 撞墙警告
void alarm(int delay){
	LED1 = 0;
	BEEP = 1;
	delay_ms(delay);
	LED1 = 1;
	BEEP = 0;
}

// 游戏主程序
void snake_main() {
	Snake();
	createWall();
	createFood();
	while (1) {
		clearSnake();
		move(newDirection());
		
		// Bingo
		if (knockFood()) {
			addSnake();
			createFood();
			updateScore();
		}
		
		printSnake();
		printInfo();
		if (Judge() != CONTINUE){
			alarm(100);
			break;
		}
		
		if(closeToWall()) alarm(30);
		
		delay_ms(getSpeed());
	}
}

