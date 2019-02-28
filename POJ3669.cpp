// POJ3669.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include<iostream>
#include<fstream>
#include <cstring>
#include <queue>
using namespace std;
ifstream fin("D:\\test.in");
ofstream fout("D:\\test.out");
//��Ϊ������������ͬ��������ΪN��
int N;
int ans = 0;
//����ά����Ϣ
int dim[300][3];
//���ǵ�ͼ����ʵ˵�ǵ�ͼ��׼ȷ��ֻ��˵�Ǵ��������ֵ����Ϊ�����ǿռ��ͼ��
//��һ��ĵ�ͼ��ò
int nextSecMap[300][300];
//���ĵ�ͼ��ò
int realFutureMap[300][300];


int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };

typedef pair<int, int> P;





void nextSecondFuture(int timer)
{//�����һ��һ����µ�ͼ�ġ�
	for (int j = 0; j < N; j++)
	{//��ʾ����ĳһʱ����£��������������ʱ�������0��������ը����
		if (dim[j][2] - timer == 0)
		{
			//����ը������Ҫ���������������ĸ�������Ϊ1.
			nextSecMap[dim[j][0]][dim[j][1]] = 1;
			for (int k = 0; k < 4; k++)
			{//����ĸ����������
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
{//������δ������ȷ�����յİ�ȫ������������δ���������˴�ҲûΣ�գ��Ϳ��Բ����ˡ�
	for (int i = 0; i <= maxTime;i++)
	{
		for (int j = 0; j < N; j++)
		{//��ʾ����ĳһʱ����£��������������ʱ�������0��������ը����
			if (dim[j][2]-i==0)
			{
				//����ը������Ҫ���������������ĸ�������Ϊ1.
				realFutureMap[dim[j][0]][dim[j][1]] = 1;
				for (int k = 0; k < 4;k++)
				{//����ĸ����������
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
{//�������յ�ͼ���жϴ˴��Ƿ�����Σ�ա�
	if (x>=0 && x<=300 && y>=0 && y<=300 && realFutureMap[x][y]==0)
	{
		return true;
	}
	return false;
	

}

int maxTime()
{//���ڻ�ȡȫ��ը������ʱ��
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
{//��Ӧ����BFS���Ǻ�
	//��������Ҫ��ʱ��
	int rtTime = -1;
	queue<P> que;
	//��Բ������ȥ
	que.push(P(0, 0));
	//�������������ʾĳһ��������սᲢ������һ���ͼ�Ľ�㡣
	que.push(P(-1, -1));
	//�ȳ�ʼ����ͼ
	nextSecondFuture(0);
	int timer = 0;
	while (que.size())
	{
		P p = que.front();
		que.pop();
		int flag = 0;
		if (que.front()==P(-1,-1))
		{//���ʾ��ʱ�Ľ����ĩ�˽ڵ��ǰһ���ڵ�
			flag = 1;

		}
		if (nextSecMap[p.first][p.second]==1)
		{
			//����ж��������ж��ڵ�ǰ��ͼ�£��ɲ����ߵģ��������ߣ���ֻ������ɶҲ������
		}
		else if (isSafety(p.first, p.second))
		{
			rtTime = timer;
			break;
		}
		else
		{
			if (p.first == -1 && p.second == -1)
			{//��ʵ��д���ˣ�������ŵõ���ȷ�𰸣�ʱ���õĳ������Ǹ�����һ���ͼ̫Ƶ����
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
					{//�����ǰѿ��ܵ��ߵĵ�ӽ�ȥ
						que.push(P(nx, ny));
					}
				}
				//�Ѹ��µ�ͼ�Ľ��ӽ�ȥ
				

				if (flag==1)
				{//ֻ�е���ǰ�Ľڵ���ĩ��֮ǰ����һ���ڵ�ʱ���Ÿ��������ĩ�˽ڵ�(-1,-1)
					que.push(P(-1, -1));
				}
				

			}


		}


	}




	return rtTime;
}

int main()
{	//�Ȱ�map����ʼ��Ϊ0.
	memset(nextSecMap, 0, sizeof(nextSecMap));
	memset(realFutureMap, 0, sizeof(realFutureMap));
	fin >> N;
		//�Ȱ���Щ��Ϣ������
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				fin >> dim[i][j];
			}
		}

		//���ȫ����ը����Ҫ��ʱ��
		int maxtime = maxTime();
		theRealFuture(maxtime);
		
		ans = escape();
		cout << ans << endl;
		
		
	

	system("pause");

	return 0;
}

