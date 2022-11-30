#include <iostream>
#include <vector>
#include <climits>
using namespace std;

struct Edge {
	int src;
	int dst;
	int weight;
};

const int UNKNOWN = INT_MAX;

vector<int> BellmanFord(vector<Edge> edges, int V, int start) {
	vector<int> distance(V, UNKNOWN);
	distance[start] = 0;
	for (int i = 0; i < V - 1; ++i) {
		for (auto& e : edges) {
			if (distance[e.src] == UNKNOWN)
				continue;
			if (distance[e.dst] > distance[e.src] + e.weight)
				distance[e.dst] = distance[e.src] + e.weight;
		}
	}

	// 결과 반환하기 전에 음수 사이클 확인하는 코드 추가하기

	return distance;
}

int main(){
	int V = 5;
	vector<Edge> edges;
	vector<vector<int>> edge_map{
		{0, 1, -1},
		{0, 2, 4},
		{1, 2, 3},
		{3, 2, 5},
		{3, 1, 1},
		{1, 3, 2},
		{1, 4, 2},
		{4, 3, -3}
	};
	for (auto& e : edge_map)
		edges.emplace_back(Edge{ e[0], e[1], e[2] });

	int start = 0;
	vector<int> distance = BellmanFord(edges, V, start);

	cout << "Starting vertex : " << start << endl;
	for (int i = 0; i < distance.size(); ++i) {
		if (distance[i] == UNKNOWN)
			cout << "I have not visited the vertex " << i << "." << endl;
		else
			cout << "The vertex " << i << " : " << distance[i] << endl;
	}
	return 0;
}