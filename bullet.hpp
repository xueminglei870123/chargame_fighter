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
	HANDLE hOut2 = GetStdHandle(STD_OUTPUT_HANDLE);// ��ȡ��׼����豸���
	SetConsoleCursorPosition(hOut2, pos2);//���������ֱ���ָ���ĸ����壬����λ��
}

class Bullet
{
public:
	int m_ROW;
	int m_COL;
	Wall& m_wall;
	Enemy& m_enemy;
	Fighter& m_fighter;
	list<pair<int, int>> m_list;      //��ż����ӵ�
	list<pair<int, int>> m_list2;     //��ŵط��ӵ�
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
	//			it = this->m_list.erase(it);       //�ж��ӵ����У��ӵ���������ɾ��
	//			--this->m_enemy.m_life;

	//			goto_xy2(44, 5);                  //��ָ��λ��ʵʱ���Ѫ����Ϣ
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
				it = this->m_list.erase(it);       //�ж��ӵ����У��ӵ���������ɾ��
				--this->m_enemy.m_life;

				goto_xy2(44, 5);                  //��ָ��λ��ʵʱ���Ѫ����Ϣ
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
					it = this->m_list.erase(it);       //�ж��ӵ����У��ӵ���������ɾ��
					--this->m_enemy.m_life;

					goto_xy2(44, 5);                  //��ָ��λ��ʵʱ���Ѫ����Ϣ
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
	//	if (node.first != ROW - 2)         //�ӵ�������
	//	{		
	//		this->m_wall.setWall(node, " ");
	//		goto_xy2(node.second * 2, node.first);
	//		cout << " ";

	//		++node.first;
	//		if (this->m_wall.getWall(node) != "+")     //�ж�δ����
	//		{
	//			this->m_wall.setWall(node, BU2);
	//			goto_xy2(node.second * 2, node.first);
	//			cout << BU2;
	//			++it;
	//		}
	//		else
	//		{
	//			it = this->m_list2.erase(it);       //�ж��ӵ����У��ӵ���������ɾ��
	//		}
	//	}
	//	else                                        //�����ӵ�ɾ��
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
		if (node.first != ROW - 2)         //�ӵ�������
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
		else                                        //�����ӵ�ɾ��
		{
			this->m_wall.setWall(node, " ");
			goto_xy2(node.second * 2, node.first);
			cout << " ";
			it = this->m_list2.erase(it);
		}
	}
}