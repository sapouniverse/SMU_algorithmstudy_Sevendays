#include<iostream>
using namespace std;
int N;
int ans[3];
short map[2200][2200];
int maski(int x, int y, int n);

void divide(int x, int y, int n)
{
	if (n < 3)
	{
		for (int i = x; i < x + n; i++)
		{
			for (int j = y; j < y + n; j++)
			{
				ans[map[i][j] + 1]++; //-1�� 0�ε���, 0�� 1�ε���, 1�� 2�ε����� �ִ´�. 
			}
		}
	}
	else {
		int c = maski(x, y, n);
		if (c != -10) // ������ ������ ���
			ans[c + 1]++;
		else {
			n = n / 3;
			divide(x, y, n);
			divide(x + n, y, n);
			divide(x + n + n, y, n);
			divide(x, y + n, n);
			divide(x + n, y + n, n);
			divide(x + n + n, y + n, n);
			divide(x, y + n + n, n);
			divide(x + n, y + n + n, n);
			divide(x + n + n, y + n + n, n);
		}
	}
}
int maski( int x, int y, int n)
{
	short a = map[x][y]; //ù ���� ����
	for (int i = x; i < x + n; i++)
	{
		for (int j = y; j < y + n; j++)
		{
			if (a != map[i][j]) //�ٸ���
				return -10;
		}
	}
	return a; //������ -1, 0, 1�߿� ����
}


int main(void)
{
	cin >> N;
	short k;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> k;
			map[i][j] = k;
		}
	}

	divide(0, 0, N);
	cout << ans[0] << '\n' << ans[1] << '\n' << ans[2] << '\n';
}
