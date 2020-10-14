#include<iostream>
#include<windows.h>
#include<time.h>
//#include<stdlib.h>
#include<conio.h>
#define N 28
using namespace std;
class Screen
{
public:
	void gotoxy(int x, int y);
	void color(int a);
};
class hungry_snake
{
	int Mode;
	int score;
	int **snake;
	int apple[2];
	int tail[2];
	int len ;
public:
	hungry_snake();
	void init();
	int start();
};
void Screen::gotoxy(int x, int y)//位置函数
{
	COORD pos;
	pos.X = 2 * x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void Screen::color(int a)//颜色函数
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), a);
}
hungry_snake::hungry_snake()
{
	snake = NULL;
	score = 0;
	len = 0;
	apple[0] = 0;
	apple[1] = 0;
	tail[0] = 0;
	tail[1] = 0;
}
void hungry_snake::init()//初始化函数（初始化围墙、显示信息、苹果）
{
	len = 3;
	Screen screen;
	int i, j;//初始化围墙
	int wall[N + 2][N + 2] = { { 0 } };
	for (i = 1; i <= N; i++)
	{
		for (j = 1; j <= N; j++)
			wall[i][j] = 1;
	}
	screen.color(3);//灰，蓝，绿，红
	for (i = 0; i<N + 2; i++)
	{
		for (j = 0; j<N + 2; j++)
		{
			if (wall[i][j])
				cout << "■";
			else cout << "□";
		}
		cout << endl;
	}
	screen.gotoxy(N + 3, 1);//显示信息
	screen.color(9);
	screen.gotoxy(N + 3, 2);//显示信息
	screen.color(9);
	cout << "按  ↑   ↓   ←   →   移动方向" << endl;
	screen.gotoxy(N + 3, 3);
	screen.color(9);
	cout << "按任意其他键暂停" << endl;
	screen.gotoxy(N + 3, 4);
	screen.color(9);
	cout << "得分：" << endl;
	apple[0] = rand() % N + 1;//苹果
	apple[1] = rand() % N + 1;
	screen.gotoxy(apple[0], apple[1]);
	screen.color(12);
	cout << "●" << endl;
}
int hungry_snake::start()
{
	int i;
	Screen screen;
	char ch = 'p';
	snake = (int**)realloc(snake, sizeof(int*)*len);
	for (i = 0; i<len; i++)
		snake[i] = (int*)malloc(sizeof(int) * 2);
	for (i = 0; i<len; i++)//初始化蛇
	{
		snake[i][0] = N / 2;
		snake[i][1] = N / 2 + i;
		screen.gotoxy(snake[i][0], snake[i][1]);
		screen.color(14);
		cout << "★" << endl;
	}
	while (1)//进入消息循环
	{
		tail[0] = snake[len - 1][0];
		tail[1] = snake[len - 1][1];
		screen.gotoxy(tail[0], tail[1]);
		screen.color(3);
		cout << "■" << endl;
		for (i = len - 1; i > 0; i--)
		{
			snake[i][0] = snake[i - 1][0];
			snake[i][1] = snake[i - 1][1];
			screen.gotoxy(snake[i][0], snake[i][1]);
			screen.color(14);
			cout << "★" << endl;
		}
		if (_kbhit())
		{
			screen.gotoxy(0, N + 2);
			ch = _getche();
		}
		switch (ch)
		{
		case 72:snake[0][1]--; break;
		case 80:snake[0][1]++; break;
		case 75:snake[0][0]--; break;
		case 77:snake[0][0]++; break;
		default: break;
		}
		screen.gotoxy(snake[0][0], snake[0][1]);
		screen.color(14);
		cout << "★" << endl;
		Sleep(abs(200 - 0.5*score));//////////////////////////////////////////
		if (snake[0][0] == apple[0] && snake[0][1] == apple[1])//吃掉苹果后蛇分数加1，蛇长加1
		{
			score++;
			len++;
			snake = (int**)realloc(snake, sizeof(int*)*len);
			snake[len - 1] = (int*)malloc(sizeof(int) * 2);
			int q=0;
			while (q != len)
			{
				apple[0] = rand() % N + 1;
				apple[1] = rand() % N + 1;
				for (q = 0; q < len; q++)
				{
					if (snake[q][0] == apple[0] && snake[q][1] == apple[q])
						q = len + 1;
				}
			}
			screen.gotoxy(apple[0], apple[1]);
			screen.color(12);
			cout << "●" << endl;
			screen.gotoxy(N + 5, 4);
			screen.color(20);
			cout << score << endl;
		}
		if (snake[0][1] == 0 || snake[0][1] == N + 1 || snake[0][0] == 0 || snake[0][0] == N + 1)//撞到围墙后失败
		{
			for (i = 0; i < len; i++)
			{
				screen.gotoxy(snake[i][0], snake[i][1]);
				screen.color(3);
				cout << "■" << endl;
				free(snake[i]);
			}
			screen.gotoxy(N / 2, N / 2);
			screen.color(30);
			cout << "Game over! press 'E' to end,press enter any other buttons to continue" << endl;
			ch = _getche();
			if (ch == 'e'||ch=='E')
				return 0;
			else
				return 1;

		}
	}
}
int main()
{
	srand((unsigned)time(NULL));
	system("cls");
	hungry_snake hungrysnake;
	hungrysnake.init();
	while (hungrysnake.start())
	{
		system("cls");
		hungrysnake.init();
	};
	return 0;
}