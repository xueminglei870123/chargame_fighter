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
	int m_life;
public:
	Enemy(Wall& _wall);
	void initEnemy();
	void createEnemy(pair<int, int> _direct);
	void moveEnemy();
	void delEnemy();
	void showLife();
};

Enemy::Enemy(Wall& _wall):m_wall(_wall)
{

}

void Enemy::createEnemy(pair<int,int> _direct)
{
	for (auto node : this->m_vec)
	{
		this->m_wall.setWall(node, " ");
		goto_xy3(node.second * 2, node.first);
		cout << " ";
	}

	for (auto& node : this->m_vec)
	{
		node.first += _direct.first;
		node.second += _direct.second;
		this->m_wall.setWall(node, CHAR1);
		goto_xy3(node.second * 2, node.first);
		cout << CHAR1;
	}

	//goto_xy3(0, 27);                              //���Եл��Զ��ƶ�����
	//cout << this->m_vec.front().first << endl 
	//	<< this->m_vec.front().second;
}

void Enemy::initEnemy()
{
	this->m_life = LIFE1;
	int row = 3;                    //��ʼλ��
	int col = 10;
	this->m_vec.push_back(make_pair(row, col));
	this->m_vec.push_back(make_pair(row - 1, col - 1));
	this->m_vec.push_back(make_pair(row - 1, col));
	this->m_vec.push_back(make_pair(row - 1, col + 1));
	for (auto node : this->m_vec)
	{
		this->m_wall.setWall(node, CHAR1);
		goto_xy3(node.second * 2, node.first);
		cout << CHAR1;
	}
}

void Enemy::moveEnemy()
{	
	pair<int, int> direct;
	int randint = rand() % 5;    //����0~4�����������ÿ��������Ӧһ��λ������
	switch (randint)
	{
	case 0:
		direct = make_pair(0, 0);
		break;
	case 1:
		direct = make_pair(1, 0);
		break;
	case 2:
		direct = make_pair(-1, 0);
		break;
	case 3:
		direct = make_pair(0, 1);
		break;
	case 4:
		direct = make_pair(0, -1);
		break;
	}

	int row = this->m_vec.front().first + direct.first;       //���µ��׽ڵ��ж��Ƿ�Խ��
	int col = this->m_vec.front().second + direct.second;
	if (col >= 2 && col <= INF - 2 && row >= 2 && row <= 15)  //15����Ϊ�����ķ������򣬴�������Ļ�ϰ�����
	{
		this->createEnemy(direct);
	}
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

void Enemy::showLife()
{
	goto_xy3(44, 5);                  //��ָ��λ��ʵʱ���Ѫ����Ϣ
	cout << this->m_life;
	if (this->m_life == 0)
	{
		this->delEnemy();
		this->initEnemy();
	}
}