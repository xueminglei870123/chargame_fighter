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
	int m_ROW;
	int m_COL;
	Wall& m_wall;
	Enemy& m_enemy;
	Fighter& m_fighter;
	list<pair<int, int>> m_list;      //存放己方子弹
	list<pair<int, int>> m_list2;     //存放地方子弹
public:
	Bullet(Wall& _wall, Enemy& _enemy,Fighter& _fighter);
	void bulletGen();
	void bulletGen2(pair<int,int> _node);
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
	node.first--;
	this->m_wall.setWall(node, "*");
	goto_xy2(node.second * 2, node.first);
	cout << "*";
	this->m_list.push_back(node);
}

void Bullet::bulletGen2(pair<int,int> _node)
{
	++_node.first;
	this->m_wall.setWall(_node, BU2);
	goto_xy2(_node.second * 2, _node.first);
	cout << BU2;
	this->m_list2.push_back(_node);
}

void Bullet::bulletFly()
{	
	//list<pair<int, int>>::iterator it = this->m_list.begin();
	//while (it != this->m_list.end())
	//{
	//	pair<int, int>& node = *it;
	//	if (node.first != 1)
	//	{
	//		this->m_wall.setWall(node, " ");
	//		goto_xy2(node.second * 2, node.first);
	//		cout << " ";

	//		--node.first;
	//		if (this->m_wall.getWall(node) != CHAR1)
	//		{
	//			this->m_wall.setWall(node, BU2);
	//			goto_xy2(node.second * 2, node.first);
	//			cout << BU2;
	//			++it;
	//		}
	//		else
	//		{				
	//			it = this->m_list.erase(it);       //判定子弹击中，子弹从容器中删除
	//			--this->m_enemy.m_life;

	//			goto_xy2(44, 5);                  //在指定位置实时输出血量信息
	//			cout << this->m_enemy.m_life;
	//			if (this->m_enemy.m_life == 0)
	//			{
	//				this->m_enemy.delEnemy();
	//				this->m_enemy.initEnemy();
	//			}
	//		}
	//	}
	//	else
	//	{
	//		this->m_wall.setWall(node, " ");
	//		goto_xy2(node.second * 2, node.first);
	//		cout << " ";
	//		it = this->m_list.erase(it);
	//	}
	//}



	list<pair<int, int>>::iterator it = this->m_list.begin();
	while (it != this->m_list.end())
	{
		pair<int, int>& node = *it;
		if (node.first != 1)
		{
			if (this->m_wall.getWall(node) == CHAR1)
			{
				it = this->m_list.erase(it);       //判定子弹击中，子弹从容器中删除
				--this->m_enemy.m_life;

				goto_xy2(44, 5);                  //在指定位置实时输出血量信息
				cout << this->m_enemy.m_life;
				if (this->m_enemy.m_life == 0)
				{
					this->m_enemy.delEnemy();
					this->m_enemy.initEnemy();
				}
			}
			
			else
			{
				this->m_wall.setWall(node, " ");
				goto_xy2(node.second * 2, node.first);
				cout << " ";
				--node.first;

				if (this->m_wall.getWall(node) == CHAR1)
				{
					it = this->m_list.erase(it);       //判定子弹击中，子弹从容器中删除
					--this->m_enemy.m_life;

					goto_xy2(44, 5);                  //在指定位置实时输出血量信息
					cout << this->m_enemy.m_life;
					if (this->m_enemy.m_life == 0)
					{
						this->m_enemy.delEnemy();
						this->m_enemy.initEnemy();
					}
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
			it = this->m_list.erase(it);
		}
	}



}

void Bullet::bulletFly2()
{
	//list<pair<int, int>>::iterator it = this->m_list2.begin();
	//while (it != this->m_list2.end())
	//{
	//	pair<int, int>& node = *it;
	//	if (node.first != ROW - 2)         //子弹不触底
	//	{		
	//		this->m_wall.setWall(node, " ");
	//		goto_xy2(node.second * 2, node.first);
	//		cout << " ";

	//		++node.first;
	//		if (this->m_wall.getWall(node) != "+")     //判定未击中
	//		{
	//			this->m_wall.setWall(node, BU2);
	//			goto_xy2(node.second * 2, node.first);
	//			cout << BU2;
	//			++it;
	//		}
	//		else
	//		{
	//			it = this->m_list2.erase(it);       //判定子弹击中，子弹从容器中删除
	//		}
	//	}
	//	else                                        //触底子弹删除
	//	{
	//		this->m_wall.setWall(node, " ");
	//		goto_xy2(node.second * 2, node.first);
	//		cout << " ";
	//		it = this->m_list2.erase(it);
	//	}
	//}




	list<pair<int, int>>::iterator it = this->m_list2.begin();
	while (it != this->m_list2.end())
	{
		pair<int, int>& node = *it;
		if (node.first != ROW - 2)         //子弹不触底
		{
			if (this->m_wall.getWall(node) == "+")
			{
				it = this->m_list2.erase(it);
			}
			
			else
			{
				this->m_wall.setWall(node, " ");
				goto_xy2(node.second * 2, node.first);
				cout << " ";
				++node.first;

				if (this->m_wall.getWall(node) == "+")
				{
					it = this->m_list2.erase(it);
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
		else                                        //触底子弹删除
		{
			this->m_wall.setWall(node, " ");
			goto_xy2(node.second * 2, node.first);
			cout << " ";
			it = this->m_list2.erase(it);
		}
	}
}