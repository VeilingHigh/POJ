// POJ3669.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<fstream>
#include <cstring>
#include <queue>
using namespace std;
ifstream fin("D:\\test.in");
ofstream fout("D:\\test.out");
//因为列数和行数相同，所以设为N。
int N;
int ans = 0;
//这是维度信息
int dim[300][3];
//这是地图，其实说是地图不准确，只能说是存入坐标的值。因为它不是空间地图。
//下一秒的地图样貌
int nextSecMap[300][300];
//最后的地图样貌
int realFutureMap[300][300];


int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };

typedef pair<int, int> P;





void nextSecondFuture(int timer)
{//这个是一点一点更新地图的。
	for (int j = 0; j < N; j++)
	{//表示，在某一时间点下，若是它与这个计时器相减得0，则引爆炸弹。
		if (dim[j][2] - timer == 0)
		{
			//引爆炸弹，需要把相关坐标和它的四个方向置为1.
			nextSecMap[dim[j][0]][dim[j][1]] = 1;
			for (int k = 0; k < 4; k++)
			{//获得四个方向的坐标
				int nx = dim[j][0] + dx[k];
				int ny = dim[j][1] + dy[k];
				if (nx >= 0 && nx <= 300 && ny >= 0 && ny <= 300)
				{
					nextSecMap[nx][ny] = 1;
				}
			}

		}
	}
}

void theRealFuture(int maxTime)
{//真正的未来用于确保最终的安全区，若是最终未来到来，此处也没危险，就可以不走了。
	for (int i = 0; i <= maxTime;i++)
	{
		for (int j = 0; j < N; j++)
		{//表示，在某一时间点下，若是它与这个计时器相减得0，则引爆炸弹。
			if (dim[j][2]-i==0)
			{
				//引爆炸弹，需要把相关坐标和它的四个方向置为1.
				realFutureMap[dim[j][0]][dim[j][1]] = 1;
				for (int k = 0; k < 4;k++)
				{//获得四个方向的坐标
					int nx = dim[j][0] + dx[k];
					int ny = dim[j][1] + dy[k];
					if (nx>=0 && nx<=300 && ny>=0 && ny<=300)
					{
						realFutureMap[nx][ny] = 1;
					}
				}

			}
		}
	}
}

bool isSafety(int x,int y)
{//根据最终地图，判断此处是否再无危险。
	if (x>=0 && x<=300 && y>=0 && y<=300 && realFutureMap[x][y]==0)
	{
		return true;
	}
	return false;
	

}

int maxTime()
{//用于获取全爆炸完的最大时间
	int maxT = 0;
	for (int i = 0; i < N; i++)
	{
		if (dim[i][2]>maxT)
		{
			maxT = dim[i][2];
		}
	}
	return maxT;
}

int escape()
{//我应该用BFS，呵呵
	//返回所需要的时间
	int rtTime = -1;
	queue<P> que;
	//把圆点塞进去
	que.push(P(0, 0));
	//我这个是用来表示某一层次搜索终结并更新下一秒地图的结点。
	que.push(P(-1, -1));
	//先初始化地图
	nextSecondFuture(0);
	int timer = 0;
	while (que.size())
	{
		P p = que.front();
		que.pop();
		int flag = 0;
		if (que.front()==P(-1,-1))
		{//这表示此时的结点是末端节点的前一个节点
			flag = 1;

		}
		if (nextSecMap[p.first][p.second]==1)
		{
			//这个判断条件是判断在当前地图下，可不可走的，若不可走，就只弹出，啥也不做。
		}
		else if (isSafety(p.first, p.second))
		{
			rtTime = timer;
			break;
		}
		else
		{
			if (p.first == -1 && p.second == -1)
			{//其实我写错了，歪打正着得到正确答案，时间用的长可能是更新下一秒地图太频繁了
				timer++;
				nextSecondFuture(timer);
			}
			else
			{
				for (int i = 0; i < 4; i++)
				{
					int nx = p.first + dx[i];
					int ny = p.second + dy[i];
					if (nx >= 0 && nx <= 300 && ny >= 0 && ny <= 300 )
					{//以上是把可能的走的点加进去
						que.push(P(nx, ny));
					}
				}
				//把更新地图的结点加进去
				

				if (flag==1)
				{//只有当当前的节点是末端之前的那一个节点时，才给它后面加末端节点(-1,-1)
					que.push(P(-1, -1));
				}
				

			}


		}


	}




	return rtTime;
}

int main()
{	//先把map都初始化为0.
	memset(nextSecMap, 0, sizeof(nextSecMap));
	memset(realFutureMap, 0, sizeof(realFutureMap));
	fin >> N;
		//先把这些信息读进来
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				fin >> dim[i][j];
			}
		}

		//求出全部爆炸所需要的时间
		int maxtime = maxTime();
		theRealFuture(maxtime);
		
		ans = escape();
		cout << ans << endl;
		
		
	

	system("pause");

	return 0;
}

