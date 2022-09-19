#include <iostream>
#include <queue>
#include <tuple>
#include <string>
#include <fstream>

using namespace std;
void MaxHeapSorting(int a[], int n) {  // C++로 쉽게 풀어쓴 자료구조
	priority_queue <int> maxHeap;
	for (int i = 0; i < n; ++i)
		maxHeap.push(a[i]);
	for (int i = 0; i < n; i++) {
		a[i] = maxHeap.top();
		maxHeap.pop();
	}
}
void MinHeapSorting(int a[], int n) {  // C++로 쉽게 풀어쓴 자료구조
	priority_queue<int, vector<int>, greater<int>>minHeap;
	for (int i = 0; i < n; ++i)
		minHeap.push(a[i]);
	for (int i = 0; i < n; ++i) {
		a[i] = minHeap.top();
		minHeap.pop();
	}
}

int main() {
	/*
	1. pair class
	서로 다른 형태의 두 객체를 묶어 하나의 객체로 만듭니다.
	헤더: utility
	선언: pair<[type 1], [type 2]> 객체이름
	사용법
	make_pair(variable 1, variable 2): variable 1, 2의 pair 생성
	p.first: p 객체 첫번째 인자 반환
	p.second: p 객체 두번째 인자 반환
	나머지 기능은 생략합니다.
	2. tuple class
	pair가 두 객체라면, tuple은 세 객체를 하나의 객체로 만듭니다.
	헤더: tuple
	사용법
	tuple<[type 1], [type 2], [type 3]> 객체이름(값1, 값2, 값3);
	나머지 기능은 생략합니다.
	*/
	int num_test_cases;
	int N, M;				// 문서의 개수, 몇 번째로 놓여있는지 나타내는 정수
	//int priority;	 		// 중요도

	int temp_order, temp_priority; // printing 중 사용할 index와 value

	ifstream fin("Prob_1966.txt");

	fin >> num_test_cases;
	for (int i = 0; i < num_test_cases; ++i) {
		fin >> N >> M;
		priority_queue<pair<int, int>> priority_data;
		for (int j = 0; j < N; ++j) {
			fin >> temp_priority;
			priority_data.push({ temp_priority, j });
		}
		for (int j = 0; j < N; ++j) {
			temp_priority = priority_data.top().first;
			temp_order = priority_data.top().second;
			priority_data.pop();
			if (temp_order == M) {
				cout << j + 1 << endl;
				break;
			}
		}
	}
	fin.close();
	return 0;
}