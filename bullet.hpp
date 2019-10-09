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
	Wall& m_wall;
	Enemy& m_enemy;
	Fighter& m_fighter;
	list<pair<int, int>> m_list;      //��ż����ӵ�
	list<pair<int, int>> m_list2;     //��ŵл��ӵ�
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
�ӵ���ײ����˼·��
�����ӵ���������ÿ���ӵ������������������
1��ǡ���ص��ڷɻ��ϣ�ֱ��ɾ���ӵ������ж�����
2���ƶ�һ�κ��ص�������ԭλ���ӵ���ʧ��Ȼ��ɾ���ӵ������ж�����
3���ƶ�һ�κ�δ�ص�������ԭλ���ӵ���ʧ��Ȼ�����µ�λ�û����ӵ�

ɾ���ӵ�ʱ��ʹ��STL��erase�㷨��ɾ������Զ����Ƶ�����
*/

void Bullet::bulletFly()
{	
	list<pair<int, int>>::iterator it = this->m_list.begin();
	while (it != this->m_list.end())
	{
		pair<int, int>& node = *it;
		if (node.first != 1)          //�ӵ�������
		{
			if (this->m_wall.getWall(node) == CHAR1)   //ֱ���ص������
			{
				it = this->m_list.erase(it);      //erase�������µĵ�������ָ��ɾ�ĺ�һ��λ�� 
				--this->m_enemy.m_life;
				this->m_enemy.showLife();
			}
			
			else       //�ƶ�һ������жϵ����
			{
				this->m_wall.setWall(node, " ");       //����ԭλ���ӵ���ʧ
				goto_xy2(node.second * 2, node.first);
				cout << " ";
				--node.first;                        //�µ�λ��

				if (this->m_wall.getWall(node) == CHAR1)    //�µ�λ�����ص�
				{
					it = this->m_list.erase(it);       
					--this->m_enemy.m_life;
					this->m_enemy.showLife();
				}

				else       //�µ�λ�������ص�
				{
					this->m_wall.setWall(node, BU1);
					goto_xy2(node.second * 2, node.first);
					cout << BU1;
					++it;                          //�����������Ҫ����������
				}
			}			
		}
		else                                     //���׵��ӵ�ɾ��
		{
			this->m_wall.setWall(node, " ");
			goto_xy2(node.second * 2, node.first);
			cout << " ";
			it = this->m_list.erase(it);
		}
	}



}

void Bullet::bulletFly2()     //�߼���bulletFly��ͬ
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