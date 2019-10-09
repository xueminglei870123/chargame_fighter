#pragma once
#include "head.h"
#include "wall.hpp"
using namespace std;
void goto_xy1(int x, int y)
{
	COORD pos1 = { x,y };
	HANDLE hOut1 = GetStdHandle(STD_OUTPUT_HANDLE);// 获取标准输出设备句柄
	SetConsoleCursorPosition(hOut1, pos1);//两个参数分别是指定哪个窗体，具体位置
}

class Fighter
{
public:
	Wall& m_wall;
	vector<pair<int, int>> m_vec;
	int m_life;

public:
	Fighter(Wall& _wall);
	void createFighter(pair<int,int> _direct);
	void initFighter();
	void moveFighter(char _direction);
	void showLife();
};

Fighter::Fighter(Wall& _wall):m_wall(_wall)
{
	this->m_vec.clear();
}

void Fighter::createFighter(pair<int,int> _direct)
{
	for (auto node : this->m_vec)
	{
		this->m_wall.setWall(node, " ");
		goto_xy1(node.second * 2, node.first);
		cout << " ";
	}

	for (auto& node : this->m_vec)     //这一步遍历时必须引用，要改变原坐标
	{
		node.first += _direct.first;
		node.second += _direct.second;
		this->m_wall.setWall(node, "+");
		goto_xy1(node.second * 2, node.first);
		cout << "+";
	}
}

void Fighter::initFighter()
{
	this->m_life = LIFE2;
	int row = ROW - 4;
	int col = COL / 2;
	this->m_vec.push_back(make_pair(row, col));
	this->m_vec.push_back(make_pair(row + 1, col - 1));
	this->m_vec.push_back(make_pair(row + 1, col));
	this->m_vec.push_back(make_pair(row + 1, col + 1));
	this->m_vec.push_back(make_pair(row + 2, col - 1));
	this->m_vec.push_back(make_pair(row + 2, col + 1));

	for (auto node : this->m_vec)
	{
		this->m_wall.setWall(node, CHAR0);
		goto_xy1(node.second * 2, node.first);
		cout << CHAR0;
	}
}

void Fighter::moveFighter(char _direction)
{
	pair<int, int> direct;
	switch (_direction)
	{
	case 'w':
		direct = make_pair(-1, 0);
		break;
	case 's':
		direct = make_pair(1, 0);
		break;
	case 'a':
		direct = make_pair(0, -1);
		break;
	case 'd':
		direct = make_pair(0, 1);
		break;
	default:
		break;
	}

	int row = this->m_vec.front().first + direct.first;
	int col = this->m_vec.front().second + direct.second;
	if (col >= 2 && col <= INF - 2 && row >= 1 && row <= ROW - 4)
	{
		this->createFighter(direct);
	}
}

void Fighter::showLife()
{
	goto_xy1(44, 10);                  //在指定位置实时输出血量信息
	cout << this->m_life;
	if (this->m_life == 0)
	{
		//this->delEnemy();
		//this->initEnemy();
	}
}