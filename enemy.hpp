#pragma once
#include "head.h"
#include "wall.hpp"
using namespace std;
void goto_xy3(int x, int y)
{
	COORD pos3 = { x,y };
	HANDLE hOut3 = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOut3, pos3);
}

class Enemy
{
public:
	Wall& m_wall;
	vector<pair<int, int>> m_vec;
	pair<int, int> m_node;
	int m_life;
public:
	Enemy(Wall& _wall);
	void initEnemy();
	void createEnemy(pair<int, int> _node);
	void moveEnemy();
	void delEnemy();
};

Enemy::Enemy(Wall& _wall):m_wall(_wall)
{

}

void Enemy::createEnemy(pair<int,int> _node)
{
	for (auto node : this->m_vec)
	{
		this->m_wall.setWall(node, " ");
		goto_xy3(node.second * 2, node.first);
		cout << " ";
	}
	this->m_vec.clear();

	int y = _node.first;
	int x = _node.second;
	this->m_vec.push_back(make_pair(y, x));
	this->m_vec.push_back(make_pair(y - 1, x - 1));
	this->m_vec.push_back(make_pair(y - 1, x));
	this->m_vec.push_back(make_pair(y - 1, x + 1));

	for (auto node : this->m_vec)
	{
		this->m_wall.setWall(node, CHAR1);
		goto_xy3(node.second * 2, node.first);
		cout << CHAR1;
	}
}

void Enemy::initEnemy()
{
	this->m_life = LIFE1;
	pair<int, int> node = make_pair(3, 10);
	this->createEnemy(node);
}

void Enemy::moveEnemy()
{	
	int row = this->m_vec.front().first;
	int col = this->m_vec.front().second;

	while(true)
	{
		int step = rand() % 3 - 1;
		int temp = col + step;
		if (temp >= 2 && temp <= INF - 2)   
		{
			col = temp;
			break;
		}
	}

	while (true)
	{
		int step = rand() % 3 - 1;
		int temp = row + step;
		if (temp >= 2 && temp <= 15)  //15是人为划定的飞行区域，大致在屏幕上半区域
		{
			row = temp;
			break;
		}
	}
	this->createEnemy(make_pair(row, col));
}

void Enemy::delEnemy()
{
	for (auto node : this->m_vec)
	{
		this->m_wall.setWall(node, "X");
		goto_xy3(node.second * 2, node.first);
		cout << "X";
	}
	this->m_vec.clear();
}