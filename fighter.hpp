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
	vector<pair<int, int>> m_vec;
	Wall& m_wall;

public:
	Fighter(Wall& _wall);
	void createFighter(pair<int,int> _node);
	void showFighter();
	void moveFighter(char _direction);
	void shootFighter();
	int getSpeed();
};

Fighter::Fighter(Wall& _wall):m_wall(_wall)
{
	this->m_vec.clear();
}

void Fighter::createFighter(pair<int,int> _node)
{
	//for (auto node : this->m_vec)
	//{
	//	this->m_wall.setWall(node, " ");
	//	goto_xy1(node.second * 2, node.first);
	//	cout << " ";
	//}
	//this->m_vec.clear();

	//int y = _node.first;
	//int x = _node.second;
	//this->m_vec.push_back(make_pair(y,x));
	//this->m_vec.push_back(make_pair(y + 1, x - 1));
	//this->m_vec.push_back(make_pair(y + 1, x));
	//this->m_vec.push_back(make_pair(y + 1, x + 1));
	//this->m_vec.push_back(make_pair(y + 2, x - 1));
	//this->m_vec.push_back(make_pair(y + 2, x + 1));

	//for (auto node : this->m_vec)
	//{
	//	this->m_wall.setWall(node, "+");
	//}

	//for (auto node : this->m_vec)
	//{
	//	goto_xy1(node.second * 2, node.first);
	//	cout << "+";
	//}

	int y = _node.first;
	int x = _node.second;
	for (auto node : this->m_vec)
	{
		this->m_wall.setWall(node, " ");
		goto_xy1(node.second * 2, node.first);
		cout << " ";
	}

	for (auto& node : this->m_vec)
	{
		node.first += y;
		node.second += x;
		this->m_wall.setWall(node, "+");
		goto_xy1(node.second * 2, node.first);
		cout << "+";
	}

}

void Fighter::showFighter()
{
	int y = ROW - 4;
	int x = COL / 2;
	this->m_vec.push_back(make_pair(y, x));
	this->m_vec.push_back(make_pair(y + 1, x - 1));
	this->m_vec.push_back(make_pair(y + 1, x));
	this->m_vec.push_back(make_pair(y + 1, x + 1));
	this->m_vec.push_back(make_pair(y + 2, x - 1));
	this->m_vec.push_back(make_pair(y + 2, x + 1));

	for (auto node : this->m_vec)
	{
		this->m_wall.setWall(node, "+");
	}

	for (auto node : this->m_vec)
	{
		goto_xy1(node.second * 2, node.first);
		cout << "+";
	}
}

void Fighter::moveFighter(char _direction)
{
	//int y = this->m_vec.front().first;
	//int x = this->m_vec.front().second;
	//switch (_direction)
	//{
	//case 'w':
	//	--y;
	//	break;
	//case 's':
	//	++y;
	//	break;
	//case 'a':
	//	--x;
	//	break;
	//case 'd':
	//	++x;
	//	break;
	//default:
	//	break;
	//}
	//if (x >= 2 && x <= INF - 2 && y >= 1 && y <= ROW - 4)
	//{
	//	this->createFighter(make_pair(y,x));
	//}

	//pair<int, int> direct;
	int y = 0;
	int x = 0;
	switch (_direction)
	{
	case 'w':
		//direct = make_pair(-1, 0);
		--y;
		break;
	case 's':
		++y;
		break;
	case 'a':
		--x;
		break;
	case 'd':
		++x;
		break;
	default:
		break;
	}
	//if (x >= 2 && x <= INF - 2 && y >= 1 && y <= ROW - 4)
	//{
		this->createFighter(make_pair(y, x));
	//}

}
