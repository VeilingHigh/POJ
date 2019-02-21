// POJ3009.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include<iostream>
#include<fstream>
#include <cstring>
using namespace std;
ifstream fin("D:\\test.in");
ofstream fout("D:\\test.out");
//�������������������
int W, H;
int ans = 0;
char map[21][21];
int result = 100;

int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };






void Curling(int x, int y)
{	//����������ٽ��ķ��򣬿��ܲ��ܻ�
	if (map[x][y]=='3')
	{//һֱȡ��С���Ǹ�ans
		if (ans<result)
		{
			result = ans;
		}
		return;
	}
	else if (x < 0 || x==W || y<0 || y==H || ans>10)
	{//���Ǳ߽����
		
		return;
	}
	
	

	for (int i = 0; i < 4; i++)
	{
		int nx = x + dx[i];
		int ny = y + dy[i];
		if (0 <= nx && nx<W && 0 <= ny && ny<H && map[nx][ny] != '1')
		{	//������Σ��϶�����һ��,������䣬���жϿɲ�����
			//��֮ǰ�Ȱ��ϴ��ۼƵĸ���¼����
			char maptemp[21][21];
			for (int a = 0; a < H; a++)
			{
				for (int b = 0; b < W; b++)
				{
					maptemp[b][a] = map[b][a];

				}
				
			}
			
		
			int anstemp = ans;
			//��ʼ��
			ans++;		
			//������4������ʼ��
			if (dx[i]==1)
			{//�����ƶ�
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
					//��Ա���ס�ģ����󷵻�һ��
					Curling(nx - 1, y);
				}
				else
				{//��Ե����յ��3�ͳ���������ans>10�����
					Curling(nx, y);
				}
				
				
			}

			if (dx[i]==-1)
			{//�����ƶ�
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
			{//�����ƶ�
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
			{//�����ƶ�
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
			//���ǻص�����ǰ�����
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
				{//��ʼ���У�
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
		//Ϊ��һ�γ�ʼ��result��ans
		result = 100;
		ans = 0;
		fin >> W >> H;
	}

	system("pause");
	return 0;
}

