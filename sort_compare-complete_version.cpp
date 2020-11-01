#include<iostream>
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
int quick_ver04_count;
static long hold = 1;

/*
	학번 : 201910976
	이름 : 안선정

	전체적인 소스 구성 :
		my_srand, my_rand : 난수를 생성하는 rand함수를 구현한 것, 이 파일의 모든 난수는 이 함수로 배정된다.
		insertion_sort : 삽입정렬을 수행하고 비교 횟수를 센다.
		heap_sort, heapify : 힙정렬을 수행하고, 비교 횟수를 센다.
		merge_sort, merge : 합병정렬을 수행하고, 비교 횟수를 센다.
		quick_sort(ver01, ver02, ver03 ,ver04), partition(ver01, ver02, ver03, ver04) : 퀵정렬 (ver01, ver02, ver03, ver04)을 수행하고, 비교 횟수를 센다.
		main : 1024개의 랜덤 원소를 배정하여 insertion_sort, heap_sort, merge_sort, quick_sort 함수를 수행하고, 시간을 측정한다.

	전역 변수 :
		temp : 정렬도중 값의 교환이 이루어질때 사용되는 변수이다.
		insertion_count : 삽입정렬을 하면서 실행하는 key값의 비교 횟수이다.
		merge_count : 합병정렬을 하면서 실행하는 key값의 비교 횟수이다.
		heap_count : 힙정렬을 하면서 실행하는 key값의 비교 횟수이다.
		quick_ver01_count : 퀵정렬 version1을 하면서 실행하는 key값의 비교 횟수이다.
		quick_ver02_count : 퀵정렬 version2를 하면서 실행하는 key값의 비교 횟수이다.
		quick_ver03_count : 퀵정렬 version3을 하면서 실행하는 key값의 비교 횟수이다.
		quick_ver04_count : 퀵정렬 version4를 하면서 실행하는 key값의 비교 횟수이다. 

	코드 진행 방식 : 하나의 배열 arr에 랜덤한 수를 배정하고, 6가지의 정렬을 동일한 배열을 사용하여 정렬하기 위해
	arr을 미리 설정하고, brr에 arr의 원소를 다 복사하며 각각 정렬을 수행한다.
*/

//===========================================================랜덤함수====================================================

int my_rand()
{
	hold = (((hold * hold) + hold) & 0x7fff); //폰노의만의 중앙 제곱법의 의사 난수가 만들어진 방식에 모티브를 얻어서 조금 변형했음
	return hold;
}
void my_srand(unsigned int seed) {
	hold = (unsigned long)seed;
}

//=======================================================삽입정렬========================================================
void insertion_sort(int arr[], int n)
{
	int j, i;
	for (i = 1; i < n; i++) //1번째 요소는 이미 정렬되어있다고 생각하고 2번째 인자부터 정렬을 시작한다.
	{
		temp = arr[i];
		for (j = i - 1; j >= 0; j--) //바로 전의 요소부터 맨처음 요소까지 비교하여 위치를 찾는다. 
		{
			insertion_count++; //key값 비교 부분
			if (temp < arr[j])
				arr[j + 1] = arr[j]; //값을 한칸씩 미룬다.
			else
				break;
		}
		arr[j + 1] = temp;
	}

}
//=====================================================힙정렬=============================================================
void heapify(int arr[], int n, int i) {

	int parent = i; //부모노드
	int left = 2 * i + 1; //자식노드 중 왼쪽
	int right = 2 * i + 2; // 자식노드 중 오른쪽

	if (left < n && arr[left] > arr[parent]) {
		heap_count++; //힙의 키값 비교부분
		parent = left;
	}

	if (right < n && arr[right] > arr[parent]) {
		parent = right;
		heap_count++; //힙의 키값 비교부분
	}

	if (parent != i) {
		temp = arr[parent];
		arr[parent] = arr[i];
		arr[i] = temp;
		heapify(arr, n, parent);
	}
}

void heap_sort(int arr[], int n) {
	//max_heap 만들기
	for (int i = n / 2 - 1; i >= 0; i--)
		heapify(arr, n, i); //힙의 조건 충족시키기 


	for (int i = n - 1; i >= 0; i--) { // 가장 큰 값 extract 과정
		temp = arr[0];
		arr[0] = arr[i];
		arr[i] = temp;

		heapify(arr, i, 0);
	}
}
//====================================================합병정렬===========================================================

void merge(int arr[], int left, int right, int mid) //합병과정
{
	int first = left; //앞부분 배열의 첫 인덱스
	int second = mid + 1; //뒷부분 배열의 첫 인덱스
	int copy[1024];
	int i = 0;

	while (first <= mid && second <= right)
	{
		merge_count++; //key값 비교 부분
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
		arr[k + left] = copy[k];
	}
}

void merge_sort(int arr[], int left, int right)
{
	if (left < right) //배열의 크기가 1이상
	{
		merge_sort(arr, left, (left + right) / 2);
		merge_sort(arr, (left + right) / 2 + 1, right);//두 부분으로 나눈다.

		merge(arr, left, right, (left + right) / 2); //합친다. 
	}
}


//====================================퀵 정렬 version1(first or last element as pivot)========================================

int partition_ver01(int arr[], int left, int right)
{
	int pivot = arr[left]; //first element as pivot
	int low = left + 1, high = right;
	while (low <= high)
	{
		while (pivot >= arr[low] && low <= right) {
			quick_ver01_count++; //key값 비교 부분
			low++;
		}
		while (pivot <= arr[high] && high >= (left + 1)) {
			quick_ver01_count++; //key값 비교 부분
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
	arr[high] = temp; // 피벗 위치 바꿈

	return high; //피벗 위치 
}

void quick_sort_ver01(int arr[], int left, int right)
{
	if (left <= right)
	{
		int pivot = partition_ver01(arr, left, right);
		quick_sort_ver01(arr, left, pivot - 1); //왼쪽 부분
		quick_sort_ver01(arr, pivot + 1, right); //오른쪽 부분
	}

}

//===================================퀵 정렬 version2(random number as a pivot)======================================================
int partition_ver02(int arr[], int left, int right)
{
	my_srand((unsigned)time(NULL)); //랜덤하게 pivot을 결정
	int p = my_rand() % (right - left + 1) + left;
	int pivot = arr[p];

	int temp = arr[p]; //피봇 위치를 가장 왼쪽으로 
	arr[p] = arr[left];
	arr[left] = temp;

	int low = left + 1, high = right;
	while (low <= high)
	{

		while (pivot >= arr[low] && low <= right) {
			low++;
			quick_ver02_count++; //key값 비교 부분
		}
		while (pivot <= arr[high] && high >= (left + 1)) {
			high--;
			quick_ver02_count++; //key값 비교 부분
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
	arr[high] = temp; // 피벗 위치 바꿈

	return high; //피벗 위치 
}

void quick_sort_ver02(int arr[], int left, int right)
{
	if (left <= right)
	{
		int pivot = partition_ver02(arr, left, right);
		quick_sort_ver02(arr, left, pivot - 1); //왼쪽 정렬부분
		quick_sort_ver02(arr, pivot + 1, right); //오른쪽 정렬
	}
}


//================================퀵 정렬 version3(median of three partitioning as pivot.)=====================================

int partition_ver03(int arr[], int left, int right)
{
	int p; //pivot index
	quick_ver03_count += 2; //pivot을 정하기 위해 매번 2번의 비교를 하게되어 추가적으로 count +=2
	if (arr[left] < arr[right] && arr[right] < arr[(left + right) / 2])
		p = right;
	else if (arr[left] < arr[(left + right) / 2] && arr[(left + right) / 2] < arr[right])
		p = (left + right) / 2;
	else p = left;

	int pivot = arr[p];

	int temp = arr[p]; //피봇 위치를 가장 왼쪽으로 
	arr[p] = arr[left];
	arr[left] = temp;

	int low = left + 1, high = right;
	while (low <= high)
	{
		while (pivot >= arr[low] && low <= right) {
			low++;
			quick_ver03_count++; //key값 비교 부분
		}
		while (pivot <= arr[high] && high >= (left + 1)) {
			high--;
			quick_ver03_count++; //key값 비교 부분
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
	arr[high] = temp; // 피벗 위치 바꿈

	return high; //피벗 위치 
}

void quick_sort_ver03(int arr[], int left, int right)
{
	if (left <= right)
	{
		int pivot = partition_ver03(arr, left, right);
		quick_sort_ver03(arr, left, pivot - 1); //왼쪽 부분 정렬
		quick_sort_ver03(arr, pivot + 1, right); //오른쪽 부분 정렬
	}
}

//============================퀵 정렬 version4(collaboration median of three quick sort & insertion sort)===========================
int partition_ver04(int arr[], int left, int right)
{
	int p; //pivot index
	quick_ver04_count += 2; //pivot을 정하기 위해 매번 2번의 비교를 하게되어 추가적으로 count +=2
	if (arr[left] < arr[right] && arr[right] < arr[(left + right) / 2])
		p = right;
	else if (arr[left] < arr[(left + right) / 2] && arr[(left + right) / 2] < arr[right])
		p = (left + right) / 2;
	else p = left;

	int pivot = arr[p];

	int temp = arr[p]; //피봇 위치를 가장 왼쪽으로 
	arr[p] = arr[left];
	arr[left] = temp;

	int low = left + 1, high = right;
	while (low <= high)
	{
		while (pivot >= arr[low] && low <= right) {
			low++;
			quick_ver04_count++; //key값 비교 부분
		}
		while (pivot <= arr[high] && high >= (left + 1)) {
			high--;
			quick_ver04_count++; //key값 비교 부분
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
	arr[high] = temp; // 피벗 위치 바꿈

	return high; //피벗 위치 
}

void quick_sort_ver04(int arr[], int left, int right, int n)
{
	//medain of three의 장점과 insertion sort의 장점을 혼합하여 30 이하의 길이인 배열은 삽입정렬하고, 아니면 퀵정렬을 진행한다. 
	if (n<=30)
	{
		int j, i;
		for (i = left; i <= right; i++) //1번째 요소는 이미 정렬되어있다고 생각하고 2번째 인자부터 정렬을 시작한다.
		{
			temp = arr[i];
			for (j = i - 1; j >= 0; j--) //바로 전의 요소부터 맨처음 요소까지 비교하여 위치를 찾는다. 
			{
				quick_ver04_count++;
				if (temp < arr[j])
					arr[j + 1] = arr[j]; //값을 한칸씩 미룬다.
				else
					break;
			}
			arr[j + 1] = temp;
		}
	}
	else if (left <= right)
	{
		int pivot = partition_ver04(arr, left, right);
		quick_sort_ver04(arr, left, pivot - 1, n); //왼쪽 부분 정렬
		quick_sort_ver04(arr, pivot + 1, right, n); //오른쪽 부분 정렬
	}
}
//=====================================================main================================================================
int main(void)
{
	while (true) {
		int n;
		int sort;
		cout << "배열의 크기  (1024이하, 0입력시 종료): ";
		cin >> n;
		if (n == 0) break;
		int arr[1025];
		int brr[1025];
		cout << "sorted? (yes : 1, no : 0):"; //정렬된 배열을 input하고 싶으면 1, 정렬되지 않은 배열을 input하고 싶으면 0
		cin >> sort;

		if (sort == 0) { //sort가 0이 입력되면 랜덤으로 input을 준다. 
			my_srand((unsigned)time(NULL));
			for (int i = 0; i < n; i++)
			{
				arr[i] = my_rand() % 1000; //0~999까지의 숫자를 랜덤하게 뽑아서 난수를 만듦 
			}
		}
		else { //sort가 1이 입력되면 그만큼 까지의 숫자를 순서대로 배정해준다. 
			for (int i = 0; i < n; i++)
				arr[i] = i;
		}
		cout << "Sorting algorithm     #of comparison\tActual measured time\n";
		cout << "---------------------------------------------------------------\n";
		memcpy(brr, arr, sizeof(arr));  //insertion sort성능 출력
		system_clock::time_point tp1 = system_clock::now(); //nanoseconds를 보기 위해 chorono 사용
		insertion_sort(brr, n); //실제 정렬할 brr을 arr로부터 원소를 복사
		system_clock::time_point tp2 = system_clock::now();
		nanoseconds t = tp2 - tp1;
		printf("insertion sort%20d%23d\n\n", insertion_count, (int)t.count());

		memcpy(brr, arr, sizeof(arr)); //heap sort 성능 출력
		tp1 = system_clock::now();
		heap_sort(brr, n);
		tp2 = system_clock::now();
		t = tp2 - tp1;
		printf("heap sort%25d%23d\n\n", heap_count, (int)t.count());

		memcpy(brr, arr, sizeof(arr));
		tp1 = system_clock::now();
		merge_sort(brr, 0, n - 1); //merge sort성능 출력
		tp2 = system_clock::now(); t = tp2 - tp1;
		printf("merge sort%24d%23d\n\n", merge_count, (int)t.count());

		memcpy(brr, arr, sizeof(arr));
		tp1 = system_clock::now();
		quick_sort_ver01(brr, 0, n - 1); //quick sort 성능 출력(version01)
		tp2 = system_clock::now(); t = tp2 - tp1;
		printf("quick_ver01%23d%23d\n\n", quick_ver01_count, (int)t.count());

		memcpy(brr, arr, sizeof(arr)); //quick sort 성능 출력(version02)
		tp1 = system_clock::now();
		quick_sort_ver02(brr, 0, n - 1);
		tp2 = system_clock::now(); t = tp2 - tp1;
		printf("quick_ver02%23d%23d\n\n", quick_ver02_count, (int)t.count());

		memcpy(brr, arr, sizeof(arr)); //quick sort 성능 출력(version03)
		tp1 = system_clock::now();
		quick_sort_ver03(brr, 0, n - 1);
		tp2 = system_clock::now(); t = tp2 - tp1;
		printf("quick_ver03%23d%23d\n\n", quick_ver03_count, (int)t.count());

		memcpy(brr, arr, sizeof(arr)); //quick sort 성능 출력(version04)
		tp1 = system_clock::now();
		quick_sort_ver04(brr, 0, n - 1, n);
		tp2 = system_clock::now(); t = tp2 - tp1;
		printf("quick_ver04%23d%23d\n\n", quick_ver04_count, (int)t.count());

		//반복문을 돌리기 위해 카운트 변수 초기화
		insertion_count = 0;
		heap_count = 0;
		merge_count = 0;
		quick_ver01_count = 0;
		quick_ver02_count = 0;
		quick_ver03_count = 0;
		quick_ver04_count = 0;
		cout << "===============================================================\n";
	}

}
