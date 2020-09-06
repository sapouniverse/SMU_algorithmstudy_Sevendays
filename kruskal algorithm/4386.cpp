#include<iostream>
#include<vector>
#include<queue>
#include<cmath>
using namespace std;

int c;

vector < pair<double, double>> vec;
vector <pair<double, pair<int, int>>> map;
int parent[101];


void input(void)
{
	cin >> c;  // ���� ����
	double x, y;
	for (int i = 0; i < c; i++)
	{
		parent[i + 1] = i + 1; //�θ� �ʱ�ȭ
		cin >> x >> y;
		vec.push_back({ x,y }); //���Ϳ� ��ǥ�� ����
		if (vec.size() == 1)
			continue;
		for (int j = 0; j < vec.size() - 1; j++) //�ֱٿ� ������ ��
		{
			int popx = vec[j].first, popy = vec[j].second;
			map.push_back({ sqrt((popx - x) * (popx - x) + (popy - y) * (popy - y)),{ i+1,j+1 }});
		}

	}
	sort(map.begin(), map.end());

}

int find(int v)
{
	if (parent[v] == v)
		return v;
	else
		return find(parent[v]);
}

void union_(int v1, int v2)
{
	int x, y;
	x = find(v1);
	y = find(v2);
	if (x < y)
		parent[y] = x;
	else parent[x] = y;
}

int main(void)
{
	input();
	//print();
	double answer = 0;
	for (int k = 0; k < map.size(); k++)
	{
		if (find(map[k].second.first) != find(map[k].second.second)) {
			union_(map[k].second.first, map[k].second.second);
			answer += map[k].first;
		}
	}
	printf("%.2f\n", answer);
	return 0;

}