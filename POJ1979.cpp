// RedAndBlack.cpp : 定义控制台应用程序的入口点。
//

//#include "stdafx.h"
#include<iostream>
#include<fstream>
using namespace std;
//ifstream fin("D:\\test.in");
//ofstream fout("D:\\test.out");
//读入的数据列数和行数
int W, H;
int ans = 0;
char map[21][21];
int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };

void DFS(int x, int y)
{
	map[x][y] = 'X';
	ans++;
	for (int i = 0; i < 4; i++)
	{
		int nx = x + dx[i];
		int ny = y + dy[i];
		if (0<=nx && nx<W && 0<=ny && ny<H && map[nx][ny]=='.')
		{
			DFS(nx, ny);
		}
	}
	return;

}
int main()
{
	cin >> W >> H;
	while (W && H)
	{
		for (int i = 0; i < H; i++)
		{
			for (int j = 0; j < W; j++)
			{
				cin >> map[j][i];
			}
		}

		for (int i = 0; i < H; i++)
		{
			for (int j = 0; j < W; j++)
			{
				if (map[j][i] == '@')
				{
					DFS(j, i);
				}
			}
		}
		cout << ans << endl;
		ans = 0;
		cin >> W >> H;
		

	}
	
	
	
	//system("pause");
	return 0;
}

