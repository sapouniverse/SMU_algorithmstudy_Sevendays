#include<iostream>
#include<ctime>
#include<vector>
#include<string>
#include<cstdio>
using namespace std;
int temp;
int insertion_count;
int merge_count;
int quick_ver01_count;
int quick_ver02_count;
int quick_ver03_count = 0;
static long holdrand = 1L;
/*
	�й� : 201910976
	�̸� : �ȼ���
	
	��ü���� �ҽ� ���� :
		insertion_sort : ���������� �����ϴ� ��ɰ� �ð�, �� Ƚ���� ���� ���ĵ� �迭�� ����ϴ� �Լ�
		heap_sort : �������� �����ϴ� ��ɰ� �ð�, �� Ƚ���� ���� ���ĵ� �迭�� ���
		merge_sort : �պ������� �����ϴ� ��ɰ� �ð�, �� Ƚ���� ���� ���ĵ� �迭�� ���
		quick_sort(ver01, ver02, ver03 ,ver04) : �������� �����ϴ� ��ɰ� �ð�, �� Ƚ���� ���� ���ĵ� �迭�� ���
		main : 1024���� ���� ���Ҹ� �����Ͽ� insertion_sort, heap_sort, merge_sort, quick_sort �Լ��� �����Ѵ�.
		
*/
//=====================================�����Լ�====================================================

void my_srand(unsigned int seed) {
	holdrand = (long)seed;
}

int my_rand() {
	return (((holdrand = holdrand * 214013L + 2531011L) >> 16) & 0x7fff);
}

//====================================��������========================================================
void insertion_sort(int arr[], int n)
{
	int j, i;
	clock_t start = clock();
	for (i = 1; i < n; i++) //1��° ��Ҵ� �̹� ���ĵǾ��ִٰ� �����ϰ� 2��° ���ں��� ������ �����Ѵ�.
	{
		temp = arr[i];
		for (j = i - 1; j >= 0; j--) //�ٷ� ���� ��Һ��� ��ó�� ��ұ��� ���Ͽ� ��ġ�� ã�´�. 
		{
			insertion_count++;
			if (temp < arr[j])
				arr[j + 1] = arr[j]; //���� ��ĭ�� �̷��.
			else
				break;
		}
			arr[j + 1] = temp;
	}

	//printf("insertion sort�� �ð�: %0.5f\n", (float)(clock() - start) / CLOCKS_PER_SEC);


}


//==================================�պ�����==============================================

void merge(int arr[], int left, int right, int mid) //�պ�����
{
	int first = left; //�պκ� �迭�� ù �ε���
	int second = mid + 1; //�޺κ� �迭�� ù �ε���
	vector <int> v;
	
	while (first <= mid && second <= right) 
	{
		merge_count++;
		if (arr[first] <= arr[second])
			v.push_back(arr[first++]);
		else 
			v.push_back(arr[second++]);
	}
	if (first > mid)
	{
		while (second <= right)
			v.push_back(arr[second++]);
	}
	else
	{
		while (first <= mid)
			v.push_back(arr[first++]);
	}
	for (int i = 0; i < v.size(); i++)
	{
		arr[i+left] = v[i];
	}
}

void merge_sort(int arr[], int left, int right) 
{
	if (left < right) //�迭�� ũ�Ⱑ 1�̻�
	{
		merge_sort(arr, left, (left + right) / 2); 
		merge_sort(arr, (left+right)/2+1, right);//�� �κ����� ������.

		merge(arr, left, right, (left+right) / 2); //��ģ��. 
	}
}


//======================�� ���� version1(first or last element as pivot)=======================

int partition_ver01(int arr[], int left, int right)
{
	int pivot = arr[left]; //first element as pivot
	int low = left + 1, high = right;
	while (low <= high)
	{
		while (pivot >= arr[low] && low <= right) {
			quick_ver01_count++;
			low++;
		}
		while (pivot <= arr[high] && high >= (left + 1)) {
			quick_ver01_count++;
			high--;
		}

		if (low <= high)
		{
			temp = arr[low];
			arr[low] = arr[high];
			arr[high] = temp;
		}
	}
	temp = arr[left];
	arr[left] = arr[high];
	arr[high] = temp; // �ǹ� ��ġ �ٲ�

	return high; //�ǹ� ��ġ 
}

void quick_sort_ver01(int arr[], int left, int right)
{
	if (left <= right)
	{
		int pivot = partition_ver01(arr, left, right);
		quick_sort_ver01(arr, left, pivot - 1);
		quick_sort_ver01(arr, pivot + 1, right);
	}

}

//=====================�� ���� version2========================
int partition_ver02(int arr[], int left, int right)
{
	my_srand((unsigned)time(NULL));
	int p = my_rand() % (right - left + 1) + left;
	int pivot = arr[p];

	int temp = arr[p]; //�Ǻ� ��ġ�� ���� �������� 
	arr[p] = arr[left];
	arr[left] = temp;

	int low = left + 1, high = right;
	while (low <= high)
	{

		while (pivot >= arr[low] && low <= right) {
			low++;
			quick_ver02_count++;
		}
		while (pivot <= arr[high] && high >= (left + 1)) {
			high--;
			quick_ver02_count++;
		}
		
		if (low <= high) 
		{
			int temp = arr[low];
			arr[low] = arr[high];
			arr[high] = temp;
		}
	}
	temp = arr[left];
	arr[left] = arr[high];
	arr[high] = temp; // �ǹ� ��ġ �ٲ�

	return high; //�ǹ� ��ġ 
}

void quick_sort_ver02(int arr[], int left, int right)
{	
	if (left <= right)
	{
		int pivot = partition_ver02(arr, left, right);
		quick_sort_ver01(arr, left, pivot - 1);
		quick_sort_ver01(arr, pivot + 1, right);
	}
}


//======================�� ���� version3(median of three partitioning as pivot.)=======================

int partition_ver03(int arr[], int left, int right)
{
	int p; //pivot index
	quick_ver03_count += 2;
	if (arr[left] < arr[right] && arr[right] < arr[(left + right) / 2])
		p = right;
	else if (arr[left] < arr[(left + right) / 2] && arr[(left + right) / 2] < arr[right])
		p = (left + right) / 2;
	else p = left;

	int pivot = arr[p];
	
	int temp = arr[p]; //�Ǻ� ��ġ�� ���� �������� 
	arr[p] = arr[left];
	arr[left] = temp; 

	int low = left + 1, high = right;
	while (low <= high)
	{
		while (pivot >= arr[low] && low <= right) {
			low++;
			quick_ver03_count++;
		}
		while (pivot <= arr[high] && high >= (left + 1)) {
			high--;
			quick_ver03_count++;
		}

		if (low <= high)
		{
			int temp = arr[low];
			arr[low] = arr[high];
			arr[high] = temp;
		}
	}
	temp = arr[left];
	arr[left] = arr[high];
	arr[high] = temp; // �ǹ� ��ġ �ٲ�

	return high; //�ǹ� ��ġ 
}

void quick_sort_ver03(int arr[], int left, int right)
{
	if (left <= right)
	{
		int pivot = partition_ver03(arr, left, right);
		quick_sort_ver01(arr, left, pivot - 1);
		quick_sort_ver01(arr, pivot + 1, right);
	}
}
//==================================main==================================================
int main(void)
{
	int arr[1024];
	my_srand((unsigned)time(NULL));
	for (int i = 0; i < 1024; i++)
	{
		arr[i] = my_rand()%1000;
		cout << arr[i] << " ";
	}
	int brr[1024], crr[1024], drr[1024], err[1024];
	memcpy(brr, arr, sizeof(arr));
	memcpy(drr, arr, sizeof(arr));
	memcpy(err, arr, sizeof(arr));
	memcpy(crr, arr, sizeof(arr));
	insertion_sort(arr, 1024);
	cout << "insertion_sort�� ��Ƚ��: " << insertion_count;
	merge_sort(brr, 0, 1023);
	cout << "merge_sort�� ��Ƚ��: " << merge_count << '\n';

	quick_sort_ver01(crr, 0, 1023);
	cout << "quicksort_ver01�� ��Ƚ��: " << quick_ver01_count;
	quick_sort_ver02(drr, 0, 1023);
	cout << "quicksort_ver02�� ��Ƚ��: " << quick_ver02_count << '\n';
	quick_sort_ver03(err, 0, 1023);
	cout << "quicksort_ver03�� ��Ƚ��: " << quick_ver03_count<<'\n';
}