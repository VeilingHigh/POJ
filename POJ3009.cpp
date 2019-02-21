// POJ3009.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<fstream>
#include <cstring>
using namespace std;
ifstream fin("D:\\test.in");
ofstream fout("D:\\test.out");
//读入的数据列数和行数
int W, H;
int ans = 0;
char map[21][21];
int result = 100;

int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };






void Curling(int x, int y)
{	//先搜索起点临近的方向，看能不能滑
	if (map[x][y]=='3')
	{//一直取最小的那个ans
		if (ans<result)
		{
			result = ans;
		}
		return;
	}
	else if (x < 0 || x==W || y<0 || y==H || ans>10)
	{//这是边界情况
		
		return;
	}
	
	

	for (int i = 0; i < 4; i++)
	{
		int nx = x + dx[i];
		int ny = y + dy[i];
		if (0 <= nx && nx<W && 0 <= ny && ny<H && map[nx][ny] != '1')
		{	//无论如何，肯定得移一次,以上这句，先判断可不可走
			//走之前先把上次累计的给记录下来
			char maptemp[21][21];
			for (int a = 0; a < H; a++)
			{
				for (int b = 0; b < W; b++)
				{
					maptemp[b][a] = map[b][a];

				}
				
			}
			
		
			int anstemp = ans;
			//开始走
			ans++;		
			//以下是4个方向开始找
			if (dx[i]==1)
			{//向右移动
				int flag = 0;
				for (int k = x + 1; k<W; k++)
				{
					nx = k;
					if (map[nx][y] == '3')
					{
						
						break;


					}
					else if (map[nx][y] == '1')
					{

						map[nx][y] = '0';
						flag = 1;
						break;
						

					}

				}
				if (flag==1)
				{
					//针对被挡住的，向左返回一格
					Curling(nx - 1, y);
				}
				else
				{//针对到达终点的3和出界的情况和ans>10的情况
					Curling(nx, y);
				}
				
				
			}

			if (dx[i]==-1)
			{//向左移动
				int flag = 0;
				for (int k = x - 1; k >= 0; k--)
				{
					nx = k;
					if (map[nx][y] == '3')
					{

						break ;


					}
					else if (map[nx][y] == '1')
					{

						map[nx][y] = '0';
						flag = 1;
						break;
						

					}

				}
				if (flag==1)
				{
					Curling(nx + 1, y);
				}
				else
				{
					Curling(nx, y);
				}
			}

			if (dy[i]==1)
			{//向下移动
				int flag = 0;
				for (int k = y + 1; k<H; k++)
				{
					ny = k;
					if (map[x][ny] == '3')
					{

						break;


					}
					else if (map[x][ny] == '1')
					{

						map[x][ny] = '0';
						flag = 1;
						break;
						

					}

				}

				if (flag==1)
				{
					Curling(x, ny - 1);
				}
				else
				{
					Curling(x, ny );
				}

			}

			if (dy[i]==-1)
			{//向上移动
				int flag = 0;
				for (int k = y - 1; k >= 0; k--)
				{
					ny = k;
					if (map[x][ny] == '3')
					{

						break;


					}
					else if (map[x][ny] == '1')
					{

						map[x][ny] = '0';
						flag = 1;
						break;
						

					}

				}
				if (flag==1)
				{
					Curling(x, ny + 1);
				}
				else
				{
					Curling(x, ny );
				}

			}
			//还是回到“当前”起点
			ans = anstemp;
			for (int a = 0; a < H; a++)
			{
				for (int b = 0; b < W; b++)
				{
					map[b][a] = maptemp[b][a];

				}
			}

			
		}

	}

	
	
}



int main()
{
	fin >> W >> H;
	while (W&&H)
	{
		for (int i = 0; i < H; i++)
		{
			for (int j = 0; j < W; j++)
			{
				fin >> map[j][i];
			}
		}

		
		for (int i = 0; i < H; i++)
		{
			for (int j = 0; j < W; j++)
			{
				if (map[j][i] == '2')
				{//开始滑行！
					map[j][i] = '0';
					Curling(j, i);
				}
			}
		}
		
		if (result>10)
		{
			cout << -1 << endl;
		}
		else
		{
			cout << result << endl;
		}
		//为下一次初始化result和ans
		result = 100;
		ans = 0;
		fin >> W >> H;
	}

	system("pause");
	return 0;
}

