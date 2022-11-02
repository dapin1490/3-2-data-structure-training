#include <iostream>
#include <queue>
#include <map>
#include <vector>
using namespace std;

/*
BFS 알고리즘
- 루트에서 시작
- 방문 노드 표시 후 큐에 push
- 큐가 비어있을 때까지
  - 큐에서 하나 pop
  - 방금 pop한 노드의 인접한 노드에 대해 방문하지 않은 것에 한해 큐에 push

DFS 알고리즘
- 루트 방문 후 방문 표시
- 인접한 노드 중 방문하지 않은 것에 대해 DFS 재귀 호출
*/

class node {
public:
	int data;
	vector<node*> adj;
	int distance = 0; // 가장 가까운 station으로부터의 거리

	node() { data = NULL; }
	node(int d) { data = d; }

	bool operator<(node* b) {
		return data < b->data;
	}
};

class garbage_station {
public:
	vector<node*> station;

	garbage_station() {}
	garbage_station(node* start) { station.push_back(start); }
	garbage_station(vector<node*> start) { station = start; }

	void add_station(node* st) { station.push_back(st); }

	void add_undir_edge(node* a, node* b) {
		a->adj.push_back(b);
		b->adj.push_back(a);
	}

	void add_dir_edge(node* from, node* to) {
		from->adj.push_back(to);
	}

	int bfs_route() {
		map<node*, bool> visited;
		queue<node*> que;
		node* current;

		for (auto i : station) {
			visited.emplace(i, true);
			que.push(i);
		}

		while (!que.empty()) {
			current = que.front();
			que.pop();

			for (vector<node*>::iterator i; i != current->adj.end(); i++) {
				if (visited.find(*i) != visited.end()) {
					que.push(*i);
					visited.emplace(*i, true);

					(*i)->distance = current->distance + 1;
				}
			}
		}
	}
};

int main()
{
	return 0;
}