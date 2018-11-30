#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define SNAKE_MAX_LENGTH 20
#define SNAKE_HEAD 'H'
#define SNAKE_BODY 'X'
#define BLANK_CELL ' '
#define SNAKE_FOOD '$'
#define WALL_CELL '*'

void put_money();
void output();
void left();
void right();
void up();
void down();

char map[12][13] = { //老师给的似乎错了
	"************",
	"*XXXXH     *",
	"*          *",
	"*          *",
	"*          *",
	"*          *",
	"*          *",
	"*          *",
	"*          *",
	"*          *",
	"*          *",
	"************"
};

int snakeX[SNAKE_MAX_LENGTH] = {5, 4, 3, 2, 1}; //为了避免蛇长度增加时无谓的元素移动，将老师代码里的顺序反向了。0号元素是头。
int snakeY[SNAKE_MAX_LENGTH] = {1, 1, 1, 1, 1};
int snakeLength = 5;
bool play = 1; //b标识是否Game over

void output(){
	printf("\n");
	for(int i = 0; i < 12; i++){
		printf("\t%s\n", map[i]);
	}
}

void put_money(){
	int row, column;
	do{
		srand(time(NULL));
		row = 1 + rand() % 11;
		srand(time(NULL));
		column = 1 + rand() % 11;
	} while(map[row][column] != BLANK_CELL);
	map[row][column] = SNAKE_FOOD;
}

int main(){
	char ch;
	put_money();
	output();
	while(play){ //play用于判定是否Game Over，可能被left、right、up、down四个函数所改变
		ch = getchar(); //不使用回车就读取字符依赖于操作系统，既然不给用微软提供的头文件，那就每次都回车呗。搞不懂为什么限制这种鬼东西。
		//The C library itself deals with files, and doesn't concern itself with how data gets into the input file.
		//Therefore, there's no way in the language itself to get keys as they are pressed; instead, this is platform-specific.
		//Since you haven't specified OS or compiler, we can't look it up for you.
		switch(ch){
			case 'A':
			case 'a':{
				left();
				break;
			}
			case 'D':
			case 'd':{
				right();
				break;
			}
			case 'W':
			case 'w':{
				up();
				break;
			}
			case 'S':
			case 's':{
				down();
				break;
			}
			default: //匹配到其他所有字符，都要求重新输入
				break;
		}
	}
	printf("\nGame over!\n");
}

void left(){
	int i;
	if(map[snakeY[0]][snakeX[0] - 1] == SNAKE_BODY ||
	   map[snakeY[0]][snakeX[0] - 1] == WALL_CELL){
		play = 0; //蛇头碰到蛇身或墙壁时，结束游戏
		return;
	} else{
		int put_money_flag = 0; //由于put_money函数应该在蛇身移动之后执行，但吃食物的判定在蛇身移动之前，所以设置了一个flag
		if(map[snakeY[0]][snakeX[0] - 1] == SNAKE_FOOD){
			put_money_flag = 1;
			if(snakeLength != SNAKE_MAX_LENGTH)
				snakeLength++;
		} else
			map[snakeY[snakeLength - 1]][snakeX[snakeLength - 1]] = BLANK_CELL;
			//这里的区别在于，如果吃到了食物，在原来蛇身最后一节处增加新的一节，图像上看起来就是最后一节没有变化。
			//假如没有吃到食物，则图像上的蛇尾需要移动，因此将原蛇尾所在位置设为空格

		for(i = snakeLength - 1; i > 0; i--){
			snakeX[i] = snakeX[i - 1]; //每一节的位置变为前一节的原位置
			snakeY[i] = snakeY[i - 1];
		}
		map[snakeY[0]][snakeX[0]] = SNAKE_BODY; //原蛇头位置变为蛇身
		snakeX[0]--;
		map[snakeY[0]][snakeX[0]] = SNAKE_HEAD; //蛇头的新位置用H来代表
		if(put_money_flag)
			put_money(); //蛇身移动完全加载后，才生成食物
	}
	output();
}
//其实也可以分为两个函数，但这会增加生成食物与否的判断语句

void right(){
	int i;
	if(map[snakeY[0]][snakeX[0] + 1] == SNAKE_BODY ||
	   map[snakeY[0]][snakeX[0] + 1] == WALL_CELL){
		play = 0;
		return;
	} else{
		int put_money_flag = 0;
		if(map[snakeY[0]][snakeX[0] + 1] == SNAKE_FOOD){
			put_money_flag = 1;
			if(snakeLength != SNAKE_MAX_LENGTH)
				snakeLength++;
		} else
			map[snakeY[snakeLength - 1]][snakeX[snakeLength - 1]] = BLANK_CELL;

		for(i = snakeLength - 1; i > 0; i--){
			snakeX[i] = snakeX[i - 1];
			snakeY[i] = snakeY[i - 1];
		}
		map[snakeY[0]][snakeX[0]] = SNAKE_BODY;
		snakeX[0]++;
		map[snakeY[0]][snakeX[0]] = SNAKE_HEAD;
		if(put_money_flag)
			put_money();
	}
	output();
}

void up(){
	int i;
	if(map[snakeY[0] - 1][snakeX[0]] == SNAKE_BODY ||
	   map[snakeY[0] - 1][snakeX[0]] == WALL_CELL){
		play = 0;
		return;
	} else{
		int put_money_flag = 0;
		if(map[snakeY[0] - 1][snakeX[0]] == SNAKE_FOOD){
			put_money_flag = 1;
			if(snakeLength != SNAKE_MAX_LENGTH)
				snakeLength++;
		} else
			map[snakeY[snakeLength - 1]][snakeX[snakeLength - 1]] = BLANK_CELL;

		for(i = snakeLength - 1; i > 0; i--){
			snakeX[i] = snakeX[i - 1];
			snakeY[i] = snakeY[i - 1];
		}
		map[snakeY[0]][snakeX[0]] = SNAKE_BODY;
		snakeY[0]--;
		map[snakeY[0]][snakeX[0]] = SNAKE_HEAD;
		if(put_money_flag)
			put_money();
	}
	output();
}

void down(){
	int i;
	if(map[snakeY[0] + 1][snakeX[0]] == SNAKE_BODY ||
	   map[snakeY[0] + 1][snakeX[0]] == WALL_CELL){
		play = 0;
		return;
	} else{
		int put_money_flag = 0;
		if(map[snakeY[0] + 1][snakeX[0]] == SNAKE_FOOD){
			put_money_flag = 1;
			if(snakeLength != SNAKE_MAX_LENGTH)
				snakeLength++;
		} else
			map[snakeY[snakeLength - 1]][snakeX[snakeLength - 1]] = BLANK_CELL;
			
		for(i = snakeLength - 1; i > 0; i--){
			snakeX[i] = snakeX[i - 1];
			snakeY[i] = snakeY[i - 1];
		}
		map[snakeY[0]][snakeX[0]] = SNAKE_BODY;
		snakeY[0]++;
		map[snakeY[0]][snakeX[0]] = SNAKE_HEAD;
		if(put_money_flag)
			put_money();
	}
	output();
}