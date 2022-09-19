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
	우선순위큐와 사용 시, p.first가 key가 되며, 모든 key값이 동일할 때 p.second가 key가 된다.
	2. tuple class
	pair가 두 객체라면, tuple은 세 객체를 하나의 객체로 만듭니다.
	헤더: tuple
	사용법
	tuple<[type 1], [type 2], [type 3]> 객체이름(값1, 값2, 값3);
	나머지 기능은 생략합니다.
	3. vector
	C++에서 제공하는 컨테이너(자료구조) 중 하나인 동적 배열
	동적 배열의 편리성으로 인해 매우 자주 쓰이는 클래스입니다.
	헤더: vector
	사용법
	vector<[type]> 객체이름; eg. vector<int> vec;
	vec.push_back(5);
	vec.pop_back();
	*/

	// C++의 우선순위큐는 기본적으로 Max heap을 사용합니다.
	// Min heap을 원할 경우 greater라는 키워드를 사용해 구성합니다.
	// 교재(현재 코드의 17줄 MinHeapSorting 함수)를 참조하세요.
	
	// 아래는 간단히 pair를 이용한 우선순위 큐 구현방법입니다.
	// key 값과 데이터를 구별해서 사용하는 경우가 많기 때문에, pair는 우선순위 큐 구현시 자주 사용합니다.
	// 꼭 익숙해 지세요.
	priority_queue<pair<int, string>> temp_data;// 원하는 자료형에 따라 우선순위큐의 형태를 만듭니다.
	temp_data.push({1, "첫번째 손님"});			// 우선순위큐에 첫번째 데이터를 넣습니다.
	temp_data.push({ 2, "두번째 손님" });		// 두번째 데이터를 넣습니다.
	cout << temp_data.top().first << endl;		// 이론 시간에 배우겠지만, 힙은 root를 출력하는 자료구조입니다. 첫 요소(key 값)을 확인합니다.
	cout << temp_data.top().second << endl;		// 두번째 요소를 확인합니다.
	temp_data.pop();							// Root를 반환(힙에서 제거)합니다.

	// 코딩 실력을 향상하려면 디버깅 하며 어떻게 힙이 구성되는지 확인해야 합니다.
	// 강의 시간에 잠시 함께 해 보겠지만, 꼭 직접 해보길 추천합니다.
	return 0;
}