#pragma once
#include "head.h" 
#include "wall.hpp"
#include "fighter.hpp"
#include "bullet.hpp"
#include "enemy.hpp"
using namespace std;
#define UNTIME 5       //基准时间,传入Sleep,值越小越快
#define KBTIME 100      //按键反应时间，该时间内若无按键，按无指令

#define BUTIME 10       //子弹飞行间隔：基准时间
#define FLTIME 30       //飞机飞行间隔

void goto_xy(int x, int y)
{
	COORD pos = { x,y };
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);// 获取标准输出设备句柄
	SetConsoleCursorPosition(hOut, pos);//两个参数分别是指定哪个窗体，具体位置
}

void hide_cursor()//隐藏光标
{
	HANDLE h_GAME = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor_info;
	GetConsoleCursorInfo(h_GAME, &cursor_info);
	cursor_info.bVisible = false;
	SetConsoleCursorInfo(h_GAME, &cursor_info);
}

void checkCollide(Bullet& _bullet,Enemy& _enemy)
{
		
}

int main()
{
	srand((unsigned int)time(NULL));
	hide_cursor();
	Wall wall;
	wall.initWall();
	wall.printWall();

	Fighter fighter(wall);
	fighter.initFighter();

	Enemy enemy(wall);
	enemy.initEnemy();

	Bullet bullet(wall,enemy,fighter);
	Sleep(3000);

	char key;
	int a = 1;
	int b = 1;
	int c = 1;
	int d = 1;
	while(true)
	{
		if (a++ % 10 == 0)
		{
			if (c++ % 5 == 0)
			{
				enemy.moveEnemy();
			}
			if (d++ % 5 == 0)
			{
				bullet.bulletGen2();
			}
			if (b++ % 2 == 0)
			{
				if (_kbhit())
				{
					key = _getch();
					if (key == 'w' || key == 's' || key == 'a' || key == 'd')
					{
						fighter.moveFighter(key);
					}

					if (key == 'j')
					{
						bullet.bulletGen();
					}
				}
			}
			bullet.bulletFly();
			bullet.bulletFly2();
		}
		Sleep(UNTIME);
	}
	system("pause");
	return 0;
}


