// 코드 출처 10주 강의자료 Class10_GraphBook.cpp

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

int n; // 행렬 차원
vector<int> house;
vector<vector<int>> m; // 행렬 입력

bool isValid(int a, int b) {
	return (0 <= a && a < n) && (0 <= b && b < n);
}

void dfs(int a, int b, int lb) {
	int x, y;
	m[a][b] = lb;
	house[lb - 1]++;

	for (int i = 0; i < 4; i++) {
		switch (i)
		{
		case 0: x = a - 1; y = b; break;
		case 1: x = a + 1; y = b; break;
		case 2: x = a; y = b - 1; break;
		case 3: x = a; y = b + 1; break;
		}
		if (isValid(x, y) && m[x][y] == 1)
			dfs(x, y, lb);
	}
}

// bool isAllZero() {
// 	for (int i = 0; i < n; i++)
// 		for (int j = 0; j < n; j++)
// 			if (label[i][j] != 0) return false;
// 	return true;
// }

// int getMax(int a[], int n) {
// 	int max = -1;
// 	for (int i = 0; i < n; i++)
// 		if (max < a[i]) max = a[i];
// 	return max;
// }

// void safeArea(int n) {
// 	for (int h = 0; h < 100; h++) { // height h : 1~100
// 		int count = 0; // CC 개수 초기화
// 		for (int i = 0; i < n; i++) // label 배열을 0과 1로 표현
// 			for (int j = 0; j < n; j++)
// 				if (m[i][j] > h + 1) label[i][j] = 1; // 높이 h보다 큰 부분만 1로
// 				else label[i][j] = 0;

// 		if (isAllZero()) break; // 높이 h보다 큰 부분이 없으면(all zero) stop

// 		for (int i = 0; i < n; i++) { // test : 안전영역 출력
// 			for (int j = 0; j < n; j++)
// 				cout << label[i][j];
// 			cout << endl;
// 		}

// 		for (int i = 0; i < n; i++) // Connected Component 알고리즘
// 			for (int j = 0; j < n; j++) // 맵을 탐색하면서 label 1인 부분은 dfs로
// 				if (label[i][j] == 1) {
// 					count++; // 새로운 CC를 찾을 때마다 증가
// 					dfs(i, j, count + 1); // 2부터 labeling
// 				}
// 		countNum[h] = count; // 각 높이 h에서의 CC 개수 저장
// 		cout << "높이: " << h << "  안전영역 갯수: " << count << endl;
// 	}
// }

void apt_number() {
	int count = 0; // cc 개수
	int lab = 0; // 단지 번호인데 벡터 ㅇㄴ덱스로 사용해야 해서 0

	for (int i = 0; i < n; i++) { // Connected Component 알고리즘
		for (int j = 0; j < n; j++) { // 맵을 탐색하면서 label 1인 부분은 dfs로
			if (m[i][j] == 1) {
				count++; // 새로운 CC를 찾을 때마다 증가
				house.push_back(0);
				dfs(i, j, lab + 1); // 2부터 labeling
			}
		}
	}
}


int main()
{
	string line;

	cin >> n; // 지도 크기
	m.resize(n, vector<int>(n, 0)); // 참고 : https://velog.io/@kwt0124/2%EC%B0%A8%EC%9B%90-%EB%B2%A1%ED%84%B0-resize
	house.clear();

	// 지도 입력
	for (int i = 0; i < n; i++) {
		cin >> line;
		for (int j = 0; j < n; j++) {
			m[i][j] = int(line.at(j)) - int('0');
		}
	}

	apt_number();

	sort(house.begin(), house.end());

	for (vector<int>::iterator i = house.begin(); i != house.end(); i++) {
		cout << *i << "\n";
	}

	return 0;
}
