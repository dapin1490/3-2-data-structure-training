#include <iostream>
#include <queue>
#include <map>
#include <vector>
using namespace std;

/*
BFS �˰���
- ��Ʈ���� ����
- �湮 ��� ǥ�� �� ť�� push
- ť�� ������� ������
  - ť���� �ϳ� pop
  - ��� pop�� ����� ������ ��忡 ���� �湮���� ���� �Ϳ� ���� ť�� push

DFS �˰���
- ��Ʈ �湮 �� �湮 ǥ��
- ������ ��� �� �湮���� ���� �Ϳ� ���� DFS ��� ȣ��
*/

class node {
public:
	int data;
	vector<node*> adj;
	int distance = 0; // ���� ����� station���κ����� �Ÿ�

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