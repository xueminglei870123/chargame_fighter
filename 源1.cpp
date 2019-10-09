#pragma once
#include "head.h" 
#include "wall.hpp"
#include "fighter.hpp"
#include "bullet.hpp"
#include "enemy.hpp"
using namespace std;
#define UNTIME 5       //��׼ʱ��,����Sleep,ֵԽСԽ��
#define KBTIME 100      //������Ӧʱ�䣬��ʱ�������ް���������ָ��

#define BUTIME 10       //�ӵ����м������׼ʱ��
#define FLTIME 30       //�ɻ����м��

void goto_xy(int x, int y)
{
	COORD pos = { x,y };
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);// ��ȡ��׼����豸���
	SetConsoleCursorPosition(hOut, pos);//���������ֱ���ָ���ĸ����壬����λ��
}

void hide_cursor()//���ع��
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


