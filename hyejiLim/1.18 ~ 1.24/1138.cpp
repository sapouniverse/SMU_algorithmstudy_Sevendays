#include <iostream>
using namespace std;

// �� �ٷ� ����
int main(void)
{
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	int N, left;
	int arr[10] = { 0, };

	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> left;
		for (int j = 0; j < N; j++) {
			if (left == 0 && arr[j] == 0) { // Ű ū ������� �����ư� ��ġ�ϰ��� �ϴ� �ڸ��� ����ִٸ�
				arr[j] = i + 1; // arr[j]�� �ڽ��� ��ġ, i+1�� Ű
				break;
			}
			else if (arr[j] == 0) { // Ű ū ����� �����ִٸ�
				left--;
			}
		}
	}
	for (int i = 0; i < N; i++)
		cout << arr[i] << ' ';
	return 0;
}
