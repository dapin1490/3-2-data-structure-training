// 수업에서 다룬 문제 풀이 코드로, 일부만 구현되어 있습니다.
// 수업 때 설명을 듣고, 마저 구현하세요.
#include <iostream>
#include <vector>
#include <climits>
#include <fstream>

using namespace std;

struct Edge {
	int src;
	int dst;
	int weight;
};

const int UNKOWN = INT_MAX;

bool ReadTestCase(string filename, int& N, vector<Edge>& edges) {
	ifstream infile(filename);

	if (!infile.is_open()) {
		cout << "error" << endl;
		return false;
	}

	infile >> N;

	for (int i = 0; i < N * N - 1; i++) {
		string directions;
		int power;

		infile >> directions >> power;

		int next = i;

		for (auto d : directions){
			switch (d) {
			case 'N': next = i - N; break;
			case 'E': next = i + 1; break;
			case 'S': next = i + N; break;
			case 'W': next = i - 1; break;
			}
			// edges.push_back(Edge{i, next, -directions}); // 내가 추가했음 확인 필요
		}
	}
	return true;
}

vector<int> BellmanFord(vector<Edge> edges, int V, int start) {
	vector<int> distance(V, UNKOWN);
	distance[start] = 0;
	for (int i = 0; i < V - 1; ++i) {
		for (auto& e : edges) {
			if (distance[e.src] == UNKOWN)
				continue;
			if (distance[e.dst] > distance[e.src] + e.weight)
				distance[e.dst] = distance[e.src] + e.weight;
		}
	}
	return distance;
}

int main() {
	int N;
	vector<Edge> edges;

	if (ReadTestCase("testcase1.txt", N, edges))
	{
		vector<int> distance = BellmanFord(edges, N * N, 0);

		if (distance.empty() || distance[N * N - 1] == UNKOWN)
			cout << "탐색 중단" << endl;
		else
			cout << -1 * distance[N * N - 1] << endl;
	}
}