#pragma once
#include "head.h"
#include "wall.hpp"
#include "enemy.hpp"
#include "fighter.hpp"
using namespace std;
using NODEIT = vector<pair<int, int>>::iterator;
void goto_xy2(int x, int y)
{
	COORD pos2 = { x,y };
	HANDLE hOut2 = GetStdHandle(STD_OUTPUT_HANDLE);// 获取标准输出设备句柄
	SetConsoleCursorPosition(hOut2, pos2);//两个参数分别是指定哪个窗体，具体位置
}

class Bullet
{
public:
	Wall& m_wall;
	Enemy& m_enemy;
	Fighter& m_fighter;
	list<pair<int, int>> m_list;      //存放己方子弹
	list<pair<int, int>> m_list2;     //存放敌机子弹
public:
	Bullet(Wall& _wall, Enemy& _enemy,Fighter& _fighter);
	void bulletGen();
	void bulletGen2();
	void bulletFly();
	void bulletFly2();
};

Bullet::Bullet(Wall& _wall, Enemy& _enemy,Fighter& _fighter) :m_wall(_wall), m_enemy(_enemy),m_fighter(_fighter)
{
	this->m_list.clear();
	this->m_list2.clear();
}

void Bullet::bulletGen()
{
	pair<int, int> node = this->m_fighter.m_vec.front();
	--node.first;
	this->m_wall.setWall(node, BU1);
	goto_xy2(node.second * 2, node.first);
	cout << BU1;
	this->m_list.push_back(node);
}

void Bullet::bulletGen2()
{
	pair<int, int> node = this->m_enemy.m_vec.front();
	++node.first;
	this->m_wall.setWall(node, BU2);
	goto_xy2(node.second * 2, node.first);
	cout << BU2;
	this->m_list2.push_back(node);
}

/*
子弹碰撞检查的思路：
遍历子弹容器，对每个子弹按以下三种情况处理：
1）恰好重叠在飞机上，直接删除子弹，并判定击中
2）移动一次后重叠，先让原位置子弹消失，然后删除子弹，并判定击中
3）移动一次后未重叠，先让原位置子弹消失，然后在新的位置绘制子弹

删除子弹时，使用STL的erase算法，删除后会自动后移迭代器
*/

void Bullet::bulletFly()
{	
	list<pair<int, int>>::iterator it = this->m_list.begin();
	while (it != this->m_list.end())
	{
		pair<int, int>& node = *it;
		if (node.first != 1)          //子弹不触底
		{
			if (this->m_wall.getWall(node) == CHAR1)   //直接重叠的情况
			{
				it = this->m_list.erase(it);      //erase：返回新的迭代器，指向被删的后一个位置 
				--this->m_enemy.m_life;
				this->m_enemy.showLife();
			}
			
			else       //移动一格后再判断的情况
			{
				this->m_wall.setWall(node, " ");       //先让原位置子弹消失
				goto_xy2(node.second * 2, node.first);
				cout << " ";
				--node.first;                        //新的位置

				if (this->m_wall.getWall(node) == CHAR1)    //新的位置若重叠
				{
					it = this->m_list.erase(it);       
					--this->m_enemy.m_life;
					this->m_enemy.showLife();
				}

				else       //新的位置若不重叠
				{
					this->m_wall.setWall(node, BU1);
					goto_xy2(node.second * 2, node.first);
					cout << BU1;
					++it;                          //这种情况，需要自增迭代器
				}
			}			
		}
		else                                     //触底的子弹删除
		{
			this->m_wall.setWall(node, " ");
			goto_xy2(node.second * 2, node.first);
			cout << " ";
			it = this->m_list.erase(it);
		}
	}



}

void Bullet::bulletFly2()     //逻辑与bulletFly相同
{
	list<pair<int, int>>::iterator it = this->m_list2.begin();
	while (it != this->m_list2.end())
	{
		pair<int, int>& node = *it;
		if (node.first != ROW - 2)         
		{
			if (this->m_wall.getWall(node) == CHAR0)
			{
				it = this->m_list2.erase(it);
				--this->m_fighter.m_life;
				this->m_fighter.showLife();
			}
			
			else
			{
				this->m_wall.setWall(node, " ");
				goto_xy2(node.second * 2, node.first);
				cout << " ";
				++node.first;

				if (this->m_wall.getWall(node) == CHAR0)
				{
					it = this->m_list2.erase(it);
					--this->m_fighter.m_life;
					this->m_fighter.showLife();
				}

				else
				{
					this->m_wall.setWall(node, BU2);
					goto_xy2(node.second * 2, node.first);
					cout << BU2;
					++it;
				}
			}
		}
		else                                       
		{
			this->m_wall.setWall(node, " ");
			goto_xy2(node.second * 2, node.first);
			cout << " ";
			it = this->m_list2.erase(it);
		}
	}
}