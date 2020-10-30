#include<iostream>
#include<vector>
#include<string>
#include<ctime>
#include<chrono>
#include<cstdio>
using namespace std;
using namespace chrono;
int temp;
int insertion_count;
int heap_count;
int merge_count;
int quick_ver01_count;
int quick_ver02_count;
int quick_ver03_count;
static long hold = 1;

/*
	�й� : 201910976
	�̸� : �ȼ���
	
	��ü���� �ҽ� ���� :
		my_srand, my_rand : ������ �����ϴ� rand�Լ��� ������ ��, �� ������ ��� ������ �� �Լ��� �����ȴ�. 
		insertion_sort : ���������� �����ϰ� �� Ƚ���� ����. 
		heap_sort, heapify : �������� �����ϰ�, �� Ƚ���� ����. 
		merge_sort, merge : �պ������� �����ϰ�, �� Ƚ���� ����. 
		quick_sort(ver01, ver02, ver03 ,ver04), partition(ver01, ver02, ver03) : ������ (ver01, ver02, ver03)�� �����ϰ�, �� Ƚ���� ����. 
		main : 1024���� ���� ���Ҹ� �����Ͽ� insertion_sort, heap_sort, merge_sort, quick_sort �Լ��� �����ϰ�, �ð��� �����Ѵ�.
	
	���� ���� :
		temp : ���ĵ��� ���� ��ȯ�� �̷������ ���Ǵ� �����̴�. 
		insertion_count : ���������� �ϸ鼭 �����ϴ� key���� �� Ƚ���̴�.
		merge_count : �պ������� �ϸ鼭 �����ϴ� key���� �� Ƚ���̴�.
		heap_count : �������� �ϸ鼭 �����ϴ� key���� �� Ƚ���̴�.
		quick_ver01_count : ������ version1�� �ϸ鼭 �����ϴ� key���� �� Ƚ���̴�.
		quick_ver02_count : ������ version2�� �ϸ鼭 �����ϴ� key���� �� Ƚ���̴�.
		quick_ver03_count : ������ version3�� �ϸ鼭 �����ϴ� key���� �� Ƚ���̴�. 

	�ڵ� ���� ��� : �ϳ��� �迭 arr�� ������ ���� �����ϰ�, 6������ ������ ������ �迭�� ����Ͽ� �����ϱ� ����
	arr�� �̸� �����ϰ�, brr�� arr�� ���Ҹ� �� �����ϸ� ���� ������ �����Ѵ�. 
*/

//===========================================================�����Լ�====================================================

int my_rand()
{
	hold =(((hold * hold)+hold) & 0x7fff); //�����Ǹ��� �߾� �������� �ǻ� ������ ������� ��Ŀ� ��Ƽ�긦 �� ���� ��������
	return hold; 
}
void my_srand(unsigned int seed) {
	hold = (unsigned long)seed;
}

//=======================================================��������========================================================
void insertion_sort(int arr[], int n)
{
	int j, i;
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

}
//=====================================================������===========================================================

void heapify(int arr[], int n, int i) {
	int first = i;
	int left = 2*i+1; //node�� ���� �ڽĳ��
	int right = 2*i + 2; //������ �ڽĳ��

	if (left < n && arr[left] > arr[first]) {
		first = left;
		heap_count++; //Ű����
	}

	if (right < n && arr[right] > arr[first]) {
		first = right;
		heap_count++; //Ű����
	}

	if (first != i) { 
		temp = arr[i];
		arr[i] = arr[first];
		arr[first] = arr[i];
		heapify(arr, n, first);
	}
}

void heap_sort(int arr[], int n) {
	
	for (int i = n / 2 - 1; i >= 0; i--) //max_heap�� �����Ѵ�. 
		heapify(arr, n, i); //max_heap ���� ���� �Լ�


	for (int i = n - 1; i >= 0; i--) {
		temp = arr[0];
		arr[0] = arr[i];
		arr[i] = temp; //root node(max)�� extract�ϴ� ����
		heapify(arr, i, 0); //max_heap����
	}
}

//====================================================�պ�����===========================================================

void merge(int arr[], int left, int right, int mid) //�պ�����
{
	int first = left; //�պκ� �迭�� ù �ε���
	int second = mid + 1; //�޺κ� �迭�� ù �ε���
	int copy[1024];
	int i = 0;
	
	while (first <= mid && second <= right) 
	{
		merge_count++;
		if (arr[first] <= arr[second])
			copy[i++] = arr[first++];
		else
			copy[i++] = arr[second++];
	}
	if (first > mid)
	{
		while (second <= right)
			copy[i++] = arr[second++];
	}
	else
	{
		while (first <= mid)
			copy[i++] = arr[first++];
	}
	for (int k = 0; k < i; k++)
	{
		arr[k+left] = copy[k];
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


//====================================�� ���� version1(first or last element as pivot)========================================

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

//============================================�� ���� version2==============================================================
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
		quick_sort_ver02(arr, left, pivot - 1);
		quick_sort_ver02(arr, pivot + 1, right);
	}
}


//================================�� ���� version3(median of three partitioning as pivot.)=====================================

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
		quick_sort_ver03(arr, left, pivot - 1);
		quick_sort_ver03(arr, pivot + 1, right);
	}
}
//=====================================================main================================================================
int main(void)
{
	while(true){
		int n;
		int sort;
		cout << "�迭�� ũ��  (1024����, 0�Է½� ����): ";
		cin >> n;
		if (n == 0) break;
		int arr[1025];
		int brr[1025];
		cout << "sorted? (yes : 1, no : 0):";
		cin >> sort;

		if (sort == 0) {
			my_srand((unsigned)time(NULL));
			for (int i = 0; i < n; i++)
			{
				arr[i] = my_rand()%1000;
			}
		}
		else {
			for (int i = 0; i < n; i++)
				arr[i] = i;
		}
		cout << "\t\t��Ƚ��\t�����ð�\n";
		memcpy(brr, arr, sizeof(arr));
		system_clock::time_point tp1 = system_clock::now();
		insertion_sort(brr, n);
		system_clock::time_point tp2 = system_clock::now();
		nanoseconds t = tp2 - tp1;
		printf("insertion sort%10d%15d\n\n", insertion_count, (int)t.count());

		memcpy(brr, arr, sizeof(arr));
		tp1 = system_clock::now();
		heap_sort(brr, n);
		tp2 = system_clock::now();
		t = tp2 - tp1;
		printf("heap sort%15d%15d\n\n", heap_count, (int)t.count());

		memcpy(brr, arr, sizeof(arr));
		tp1 = system_clock::now();
		merge_sort(brr, 0, n - 1);
		tp2 = system_clock::now(); t = tp2 - tp1;
		for (int i = 0; i < n; i++)
			cout << brr[i] << ' ';
		printf("merge sort%14d%15d\n\n", merge_count, (int)t.count());

		memcpy(brr, arr, sizeof(arr));
		tp1 = system_clock::now();
		quick_sort_ver01(brr, 0, n - 1);
		tp2 = system_clock::now(); t = tp2 - tp1;
		printf("quick_ver01%13d%15d\n\n", quick_ver01_count, (int)t.count());

		memcpy(brr, arr, sizeof(arr));
		tp1 = system_clock::now();
		quick_sort_ver02(brr, 0, n - 1);
		tp2 = system_clock::now(); t = tp2 - tp1;
		printf("quick_ver02%13d%15d\n\n", quick_ver02_count, (int)t.count());

		memcpy(brr, arr, sizeof(arr));
		tp1 = system_clock::now();
		quick_sort_ver03(brr, 0, n - 1);
		tp2 = system_clock::now(); t = tp2 - tp1;
		printf("quick_ver03%13d%15d\n\n", quick_ver03_count, (int)t.count());


		insertion_count = 0;
		heap_count = 0;
		merge_count = 0;
		quick_ver01_count = 0;
		quick_ver02_count = 0;
		quick_ver03_count = 0;
		cout << "===========================================================\n";
	}

}