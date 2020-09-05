#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

vector < pair<int, pair<int, int>>> v; //����ġ, ���� ����, �� ���� 
int parent[1000001]; // �θ� ���� ����
int numv, nume;
void input(void)
{
	//������ ������ ������ ���� 
	cin >> numv >> nume;
	for (int i = 0; i < numv; i++)
		parent[i] = i;
	for (int i = 0; i < nume; i++)
	{
		int  s, e, w; // ����ġ, ó�� ����, ������
		cin >> s>> e >> w;
		v.push_back({ w, {s, e} });

	}
	sort(v.begin(), v.end()); //����ġ�� �������� ����
}

int find(int v)
{
	if (parent[v] == v) //�θ�� �ڽ��� ������
		return v;
	else
		return find(parent[v]); //�ٸ��� �θ��� �θ� ã��
}
void union_(int v1, int v2)
{
	int x, y;
	x = find(v1);  // �θ� ���� ã��
	y = find(v2);
	
	if (x < y)
		parent[y] = x;
	else
		parent[x] = y;
}
int main(void)
{
	input();
	int maxnum = v[0].first;
	int answer = 0;
	for (int i = 0; i< v.size(); i++)
	{
		if (find(v[i].second.first) != find(v[i].second.second)) //����Ŭ�� ������
		{
			union_(v[i].second.first, v[i].second.second);
			maxnum = max(maxnum, v[i].first);
			cout << v[i].first << '\n';
			answer += v[i].first;
		}
	}
	cout << answer - maxnum << '\n';
	return 0;
	
}