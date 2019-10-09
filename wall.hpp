#pragma once
#include "head.h"
using namespace std;
class Wall
{
private:
	string m_Screen[ROW][COL];
public:
	void initWall();
	void printWall();
	void setWall(pair<int,int> _node,string _str);
	string getWall(pair<int,int> _node);
};
void Wall::initWall()
{
	for (int i = 0; i < ROW; ++i)
	{
		for (int j = 0; j < COL; ++j)
		{
			if (i == 0 || i == ROW - 1)
			{
				this->m_Screen[i][j] = "=";
				continue;
			}

			if (j == 0 || j == COL - 1 || j == INF)
			{
				this->m_Screen[i][j] = "=";
				continue;
			}

			if (i == 5 && j == 21)
			{
				this->m_Screen[i][j] = "%";
				continue;
			}
                                         
			this->m_Screen[i][j] = " ";
		}
	}
}

void Wall::printWall()
{
	for (int i = 0; i < ROW; ++i)
	{
		for (int j = 0; j < COL; ++j)
		{
			cout << this->m_Screen[i][j] << " ";
		}
		cout << endl;
	}
}

void Wall::setWall(pair<int, int> _node, string _str)
{
	this->m_Screen[_node.first][_node.second] = _str;
}

string Wall::getWall(pair<int, int> _node)
{
	return this->m_Screen[_node.first][_node.second];
}