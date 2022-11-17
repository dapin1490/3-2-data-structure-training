// 코드 참고 10주 강의자료 Class10_GraphBook.cpp

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <fstream>
#include <stack>
using namespace std;

const string in_file_route = "res/input.txt";
const string out_file_route = "res/output.txt";

int n; // 행렬 차원
vector<int> house;
vector<vector<int>> m; // 행렬 입력

bool isValid(int a, int b) {
	return (0 <= a && a < n) && (0 <= b && b < n);
}

void dfs_recur(int a, int b, int lb) {
	int x, y;
	m[a][b] = lb;
	house[lb - 2]++;

	for (int i = 0; i < 4; i++) {
		switch (i) {
		case 0: x = a - 1; y = b; break;
		case 1: x = a + 1; y = b; break;
		case 2: x = a; y = b - 1; break;
		case 3: x = a; y = b + 1; break;
		}
		if (isValid(x, y) && m[x][y] == 1)
			dfs_recur(x, y, lb);
	}

	return;
}

void dfs_iter(int a, int b, int label) {
	stack<pair<int, int>> st;
	int x = a, y = b;
	
	st.emplace(a, b);

	while (!st.empty()) {
		pair<int, int> curr = st.top();
		st.pop();
		a = curr.first; x = a;
		b = curr.second; y = b;

		if (m[x][y] == 1) {
			m[x][y] = label;
			house[label - 2]++;

			for (int i = 0; i < 4; i++) {
				switch (i) {
				case 0: x = a - 1; y = b; break;
				case 1: x = a + 1; y = b; break;
				case 2: x = a; y = b - 1; break;
				case 3: x = a; y = b + 1; break;
				}
				if (isValid(x, y) && m[x][y] == 1)
					st.emplace(x, y);
			}
		}
	}

	return;
}

int apt_number() {
	int count = 0; // cc 개수
	int lab = 1;

	for (int i = 0; i < n; i++) { // Connected Component 알고리즘
		for (int j = 0; j < n; j++) { // 맵을 탐색하면서 label 1인 부분은 dfs로
			if (m[i][j] == 1) {
				count++; // 새로운 CC를 찾을 때마다 증가
				house.push_back(0);
				// dfs_recur(i, j, ++lab); // 2부터 labeling
				dfs_iter(i, j, ++lab);
			}
		}
	}

	return count;
}


int main()
{
	ifstream input{ in_file_route };
	ofstream output{ out_file_route };

	string line;
	int cc;

	input >> n; // 지도 크기
	m.resize(n, vector<int>(n, 0)); // 참고 : https://velog.io/@kwt0124/2%EC%B0%A8%EC%9B%90-%EB%B2%A1%ED%84%B0-resize
	house.clear();

	// 지도 입력
	for (int i = 0; i < n; i++) {
		input >> line;
		for (int j = 0; j < n; j++)
			m[i][j] = int(line.at(j)) - int('0');
	}

	cc = apt_number();

	sort(house.begin(), house.end());

	output << cc << "\n";
	for (vector<int>::iterator i = house.begin(); i != house.end(); i++)
		output << *i << "\n";

	input.close();
	output.close();

	return 0;
}
