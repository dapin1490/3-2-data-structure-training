#pragma once

#include <iostream>
#include <queue>
#include <vector>
#include <fstream>
#include <stack>
using namespace std;

struct Node {
	int to_station = INFINITY; // ���� ����� station������ �Ÿ�
	vector<int> adj; // ���� ���
	vector<int> d; // �� ���� �������� �Ÿ�
};

class Graph {
private:
	int vertices; // �� ��
	vector<Node> graph; // �� ����� Ű���� ������ �ε����� ��ü
	vector<bool> visited; // �湮 ����

	void print_route();

public:
	Graph(int vts); // ������

	void add_undir_edge(int key1, int key2, int d = 1);
	void add_dir_edge(int from, int to, int d = 1);

	void BFS(int start_key);
	void BFS(vector<int> starts);

	void DFS_by_iteration(int start_key);
	void DFS_by_iteration(vector<int> starts);

	void DFS_by_recursion(int start_key, bool is_start = true);
	void DFS_by_recursion(vector<int> starts, bool is_start = true);
};

const string in_file_route = "res/example_input.txt";
const string out_file_route = "res/example_output.txt";

extern ifstream input_file{ in_file_route };
extern ofstream output_file{ out_file_route };

Graph::Graph(int vts) { // ������
	vertices = vts;
	graph.resize(vts);
	visited.resize(vts, false);
}

void Graph::add_undir_edge(int key1, int key2, int d) {
	graph[key1].adj.push_back(key2);
	graph[key1].d.push_back(d);

	graph[key2].adj.push_back(key1);
	graph[key2].d.push_back(d);
}

void Graph::add_dir_edge(int from, int to, int d) {
	graph[from].adj.push_back(to);
	graph[from].d.push_back(d);
}

void Graph::print_route() {
	vector<Node>::iterator iter;
	int idx = 0;
	for (iter = graph.begin(); iter != graph.end(); iter++) {
		output_file << "Node #" << idx++ << " : " << (*iter).to_station << "\n";
	}
}

void Graph::BFS(int start_key) { // ��Ʈ(������)���� ����
	graph[start_key].to_station = 0; // �������� station�̹Ƿ� station������ �Ÿ��� 0
	visited[start_key] = true; // �湮 ǥ�� ��
	queue<int> que;
	que.push(start_key); // ť�� push

	output_file << "----------\nStation : " << start_key << "\nSearch by BFS\n\n";

	while (!que.empty()) { // ť�� ������� ������
		start_key = que.front(); // ť���� �ϳ� pop
		que.pop();

		int len = graph[start_key].adj.size();
		for (int i = 0; i < len; i++) { // ��� pop�� ����� ������ ��忡 ���� �湮���� ���� �Ϳ� ���� ť�� push
			int current = graph[start_key].adj[i];
			if (!visited[current]) {
				visited[current] = true;
				que.push(current);
				graph[current].to_station = graph[start_key].to_station + 1; // ���� �湮�� ���� station���κ��� ������ ���������� 1��ŭ �� ������ ����
			}
		}
	}

	// Ž���� ���� �� �湮 ���� ǥ�ø� ��� ����
	visited.assign(vertices, false);

	// Ž�� ��� ���
	this->print_route();
	output_file << "----------\n";
}

void Graph::BFS(vector<int> starts) {
	vector<int>::iterator iter;
	queue<int> que;
	int vert;

	output_file << "----------\nStations : ";
	for (iter = starts.begin(); iter != starts.end(); iter++) {
		graph[*iter].to_station = 0; // �������� station�̹Ƿ� station������ �Ÿ��� 0
		visited[*iter] = true;
		que.push(*iter);
		output_file << *iter << "  ";
	}
	output_file << "\nSearch by BFS\n\n";

	while (!que.empty()) {
		vert = que.front();
		que.pop();

		int len = graph[vert].adj.size();
		for (int i = 0; i < len; i++) { // ��� pop�� ����� ������ ��忡 ���� �湮���� ���� �Ϳ� ���� ť�� push
			int current = graph[vert].adj[i];
			if (!visited[current]) {
				visited[current] = true;
				que.push(current);
				graph[current].to_station = graph[vert].to_station + 1; // ���� �湮�� ���� station���κ��� ������ ���������� 1��ŭ �� ������ ����
			}
		}
	}

	// Ž���� ���� �� �湮 ���� ǥ�ø� ��� ����
	visited.assign(vertices, false);

	// Ž�� ��� ���
	this->print_route();
	output_file << "----------\n";
}

void Graph::DFS_by_iteration(int start_key) { // ��Ʈ(������)���� ����
	stack<pair<int, int>> s; // first�� �湮�ؾ� �� ���, second�� ������ �湮�� ���

	s.emplace(start_key, start_key);
	graph[start_key].to_station = -1; // �������� station�̹Ƿ� station������ �Ÿ��� 0�ε�, ������ while �ȿ��� �ѹ� �湮�ϰ� +1�� �ؾ� �ϱ� ������ -1�� �ʱ�ȭ

	output_file << "----------\nStation : " << start_key << "\nSearch by DFS(iteration)\n\n";

	while (!s.empty()) {
		pair<int, int> curr = s.top();
		s.pop();

		if (!visited[curr.first]) {
			visited[curr.first] = true;
			graph[curr.first].to_station = graph[curr.second].to_station + 1;
			output_file << "visit : " << curr.first << "\n";

			for (vector<int>::iterator i = graph[curr.first].adj.begin(); i != graph[curr.first].adj.end(); i++) {
				s.emplace(*i, curr.first);
			}
		}
	}

	// Ž���� ���� �� �湮 ���� ǥ�ø� ��� ����
	visited.assign(vertices, false);

	// Ž�� ��� ���
	this->print_route();
	output_file << "----------\n";
}

void Graph::DFS_by_iteration(vector<int> starts) {
	stack<pair<int, int>> s; // first�� �湮�ؾ� �� ���, second�� ������ �湮�� ���
	vector<int>::iterator i;

	output_file << "----------\nStations : ";
	for (i = starts.begin(); i != starts.end(); i++) {
		s.emplace(*i, *i);
		graph[*i].to_station = 0; // �������� station�̹Ƿ� station������ �Ÿ��� 0
		visited[*i] = true;
		output_file << *i << "  ";
	}
	output_file << "\nSearch by DFS(iteration)\n\n";

	for (i = starts.begin(); i != starts.end(); i++) {
		output_file << "visit : " << *i << "\n";
	}

	for (i = starts.begin(); i != starts.end(); i++) {
		for (vector<int>::iterator it = graph[*i].adj.begin(); it != graph[*i].adj.end(); it++) {
			s.emplace(*it, *i);
		}
	}

	while (!s.empty()) {
		pair<int, int> curr = s.top();
		s.pop();

		if (!visited[curr.first]) {
			visited[curr.first] = true;
			graph[curr.first].to_station = graph[curr.second].to_station + 1;
			output_file << "visit : " << curr.first << "\n";

			for (vector<int>::iterator i = graph[curr.first].adj.begin(); i != graph[curr.first].adj.end(); i++) {
				s.emplace(*i, curr.first);
			}
		}
	}

	// Ž���� ���� �� �湮 ���� ǥ�ø� ��� ����
	visited.assign(vertices, false);

	// Ž�� ��� ���
	this->print_route();
	output_file << "----------\n";
}

void Graph::DFS_by_recursion(int start_key, bool is_start) {
	vector<int>::iterator iter;

	if (is_start) {
		output_file << "Station : " << start_key << "\nSearch by DFS(recursion)\n\n";
		graph[start_key].to_station = 0; // �������� station�̹Ƿ� station������ �Ÿ��� 0
		visited[start_key] = true; // �湮 ǥ��
		output_file << "visit : " << start_key << "\n";
	}

	for (iter = graph[start_key].adj.begin(); iter != graph[start_key].adj.end(); iter++) {
		if (!visited[*iter]) {
			visited[*iter] = true;
			output_file << "visit : " << *iter << "\n";
			graph[*iter].to_station = graph[start_key].to_station + 1;
			DFS_by_recursion(*iter, false);
		}
	}

	if (is_start) {
		visited.assign(vertices, false);
		print_route();
	}
}

void Graph::DFS_by_recursion(vector<int> starts, bool is_start) {
	vector<int>::iterator iter;

	if (is_start) {
		output_file << "----------\nStation : ";
		for (vector<int>::iterator i = starts.begin(); i != starts.end(); i++) {
			output_file << *i << " ";
		}
		output_file << "\nSearch by DFS(recursion)\n\n";

		for (vector<int>::iterator i = starts.begin(); i != starts.end(); i++) {
			graph[*i].to_station = 0; // �������� station�̹Ƿ� station������ �Ÿ��� 0
			visited[*i] = true;
			output_file << "visit : " << *i << "\n";
		}
	}

	for (vector<int>::iterator i = starts.begin(); i != starts.end(); i++) {
		for (iter = graph[*i].adj.begin(); iter != graph[*i].adj.end(); iter++) {
			if (!visited[*iter]) {
				visited[*iter] = true;
				output_file << "visit : " << *iter << "\n";
				graph[*iter].to_station = graph[*i].to_station + 1;

				vector<int> next = { *iter };
				DFS_by_recursion(next, false);
			}
		}
	}

	if (is_start) {
		visited.assign(vertices, false);
		print_route();
		output_file << "----------\n";
	}
}