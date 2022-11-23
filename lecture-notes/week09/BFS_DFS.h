#pragma once

#include <iostream>
#include <queue>
#include <vector>
#include <fstream>
#include <stack>
#include <string>
#include <map>
using namespace std;

// const string in_file_route = "res/input.txt";
// const string out_file_route = "res/output.txt";

const string in_file_route = "../3-2-data-structure-training/lecture-notes/week09/input.txt";
const string out_file_route = "../3-2-data-structure-training/lecture-notes/week09/output.txt";

extern ifstream input{ in_file_route };
extern ofstream output{ out_file_route };

extern map<string, int> city_code = { {"MOSCOW", 0}, {"LONDON", 1}, {"SEOUL", 2}, {"SEATLE", 3}, {"DUBAI", 4}, {"SYDNEY", 5}};

struct Node {
	string name = "None";
	int to_station = -2; // 가장 가까운 station까지의 거리
	vector<int> adj; // 인접 노드
	vector<int> d; // 각 인접 노드까지의 거리
};

class Graph {
private:
	int vertices; // 정점 수
	vector<Node> graph; // 각 노드의 키값은 벡터의 인덱스로 대체
	vector<bool> visited; // 방문 여부

	void print_distance();

public:
	Graph(int vts); // 생성자

	void add_undir_edge(int key1, int key2, int d = 1);
	void add_dir_edge(int from, int to, int d = 1);

	void add_undir_edge(string key1, string key2, int d = 1);
	void add_dir_edge(string from, string to, int d = 1);

	void BFS(int start_key);
	void BFS(vector<int> starts);

	void DFS_by_iteration(int start_key);
	void DFS_by_iteration(vector<int> starts);

	void DFS_to_destination(int start, int dest);

	void DFS_by_recursion(int start_key, bool is_start = true);
	void DFS_by_recursion(vector<int> starts, bool is_start = true);
};

Graph::Graph(int vts) { // 생성자
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

// C++의 맵에 키가 있는지 확인 : https://www.techiedelight.com/ko/determine-if-a-key-exists-in-a-map-in-cpp/
void Graph::add_undir_edge(string key1, string key2, int d) {
	if (city_code.find(key1) == city_code.end())
		city_code.emplace(key1, city_code.size());

	if (city_code.find(key2) == city_code.end())
		city_code.emplace(key2, city_code.size());

	graph[city_code[key1]].name = key1;
	graph[city_code[key2]].name = key2;

	graph[city_code[key1]].adj.push_back(city_code[key2]);
	graph[city_code[key1]].d.push_back(d);

	graph[city_code[key2]].adj.push_back(city_code[key1]);
	graph[city_code[key2]].d.push_back(d);
}

void Graph::add_dir_edge(string from, string to, int d) {
	if (city_code.find(from) == city_code.end())
		city_code.emplace(from, city_code.size());

	if (city_code.find(to) == city_code.end())
		city_code.emplace(to, city_code.size());

	graph[city_code[from]].name = from;
	graph[city_code[to]].name = to;

	graph[city_code[from]].adj.push_back(city_code[to]);
	graph[city_code[from]].d.push_back(d);
}

void Graph::print_distance() {
	vector<Node>::iterator iter;
	int idx = 0;
	for (iter = graph.begin(); iter != graph.end(); iter++) {
		if ((*iter).name != "None")
			output << (*iter).name << " : " << (*iter).to_station << "\n";
		else
			output << "Node #" << idx++ << " : " << (*iter).to_station << "\n";
	}
}

void Graph::BFS(int start_key) { // 루트(시작점)에서 시작
	graph[start_key].to_station = 0; // 시작점은 station이므로 station까지의 거리가 0
	visited[start_key] = true; // 방문 표시 후
	queue<int> que;
	que.push(start_key); // 큐에 push

	output << "----------\nStation : " << (graph[start_key].name != "None" ? graph[start_key].name : to_string(start_key)) << "\nSearch by BFS\n\n";

	while (!que.empty()) { // 큐가 비어있을 때까지
		start_key = que.front(); // 큐에서 하나 pop
		que.pop();

		int len = graph[start_key].adj.size();
		for (int i = 0; i < len; i++) { // 방금 pop한 노드의 인접한 노드에 대해 방문하지 않은 것에 한해 큐에 push
			int current = graph[start_key].adj[i];
			if (!visited[current]) {
				visited[current] = true;
				que.push(current);
				graph[current].to_station = graph[start_key].to_station + graph[start_key].d[i]; // 지금 방문한 곳은 station으로부터 현재의 기준점보다 1만큼 더 떨어져 있음
			}
		}
	}

	// 탐색을 끝낸 후 방문 여부 표시를 모두 지움
	visited.assign(vertices, false);

	// 탐색 결과 출력
	this->print_distance();
	output << "----------\n";
}

void Graph::BFS(vector<int> starts) {
	vector<int>::iterator iter;
	queue<int> que;
	int vert;

	output << "----------\nStations : ";
	for (iter = starts.begin(); iter != starts.end(); iter++) {
		graph[*iter].to_station = 0; // 시작점은 station이므로 station까지의 거리가 0
		visited[*iter] = true;
		que.push(*iter);
		output << (graph[*iter].name != "None" ? graph[*iter].name : to_string(*iter)) << "  ";
	}
	output << "\nSearch by BFS\n\n";

	while (!que.empty()) {
		vert = que.front();
		que.pop();

		int len = graph[vert].adj.size();
		for (int i = 0; i < len; i++) { // 방금 pop한 노드의 인접한 노드에 대해 방문하지 않은 것에 한해 큐에 push
			int current = graph[vert].adj[i];
			if (!visited[current]) {
				visited[current] = true;
				que.push(current);
				graph[current].to_station = graph[vert].to_station + graph[vert].d[i]; // 지금 방문한 곳은 station으로부터 현재의 기준점보다 1만큼 더 떨어져 있음
			}
		}
	}

	// 탐색을 끝낸 후 방문 여부 표시를 모두 지움
	visited.assign(vertices, false);

	// 탐색 결과 출력
	this->print_distance();
	output << "----------\n";
}

void Graph::DFS_by_iteration(int start_key) { // 루트(시작점)에서 시작
	string route = "";
	stack<pair<int, int>> s; // first는 방문해야 할 노드, second는 직전에 방문한 노드

	s.emplace(start_key, start_key);
	
	output << "----------\nStation : " << (graph[start_key].name != "None" ? graph[start_key].name : to_string(start_key)) << "\nSearch by DFS(iteration)\n\n";

	while (!s.empty()) {
		pair<int, int> curr = s.top();
		s.pop();

		if (!visited[curr.first]) {
			visited[curr.first] = true;
			// output << "visit : " << curr.first << "\n";
			if (graph[curr.first].name != "None")
				route += (graph[curr.first].name + "   ");
			else
				route += (to_string(curr.first) + "   ");

			for (vector<int>::iterator i = graph[curr.first].adj.begin(); i != graph[curr.first].adj.end(); i++) {
				s.emplace(*i, curr.first);
			}
		}
	}

	// 탐색을 끝낸 후 방문 여부 표시를 모두 지움
	visited.assign(vertices, false);

	// 탐색 결과 출력
	output << "DFS route : " << route << "\n";
	output << "----------\n";
}

void Graph::DFS_by_iteration(vector<int> starts) {
	string route = "";
	stack<pair<int, int>> s; // first는 방문해야 할 노드, second는 직전에 방문한 노드
	vector<int>::iterator i;

	output << "----------\nStations : ";
	for (i = starts.begin(); i != starts.end(); i++) {
		s.emplace(*i, *i);
		visited[*i] = true;
		output << (graph[*i].name != "None" ? graph[*i].name : to_string(*i)) << "  ";
	}
	output << "\nSearch by DFS(iteration)\n\n";

	for (i = starts.begin(); i != starts.end(); i++) {
		// output << "visit : " << *i << "\n";
		route = route + (graph[*i].name != "None" ? graph[*i].name : to_string(*i)) + "   ";
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
			// output << "visit : " << curr.first << "\n";
			route = route + (graph[curr.first].name != "None" ? graph[curr.first].name : to_string(curr.first)) + "   ";

			for (vector<int>::iterator i = graph[curr.first].adj.begin(); i != graph[curr.first].adj.end(); i++) {
				s.emplace(*i, curr.first);
			}
		}
	}

	// 탐색을 끝낸 후 방문 여부 표시를 모두 지움
	visited.assign(vertices, false);

	// 탐색 결과 출력
	output << "DFS route : " << route << "\n";
	output << "----------\n";
}

void Graph::DFS_to_destination(int start, int dest) { // 루트(시작점)에서 시작
	string route = "";
	stack<pair<int, int>> s; // first는 방문해야 할 노드, second는 직전에 방문한 노드

	s.emplace(start, start);
	
	output << "----------\nStation : " << (graph[start].name != "None" ? graph[start].name : to_string(start)) << "\nDestination : " << (graph[dest].name != "None" ? graph[dest].name : to_string(dest)) << "\nSearch by DFS to destination\n\n";

	while (!s.empty()) {
		pair<int, int> curr = s.top();
		s.pop();

		if (curr.first == dest) {
			output << "found destination\n";
			route = route + (graph[curr.first].name != "None" ? graph[curr.first].name : to_string(curr.first)) + "   ";
			break;
		}

		if (!visited[curr.first]) {
			visited[curr.first] = true;
			// output << "visit : " << curr.first << "\n";
			route = route + (graph[curr.first].name != "None" ? graph[curr.first].name : to_string(curr.first)) + "   ";

			for (vector<int>::iterator i = graph[curr.first].adj.begin(); i != graph[curr.first].adj.end(); i++) {
				s.emplace(*i, curr.first);
			}
		}
	}

	// 탐색을 끝낸 후 방문 여부 표시를 모두 지움
	visited.assign(vertices, false);

	// 탐색 결과 출력
	output << "DFS route : " << route << "\n";
	output << "----------\n";
}

void Graph::DFS_by_recursion(int start_key, bool is_start) {
	vector<int>::iterator iter;

	if (is_start) {
		output << "----------\nStation : " << (graph[start_key].name != "None" ? graph[start_key].name : to_string(start_key)) << "\nSearch by DFS(recursion)\n\n";
		visited[start_key] = true; // 방문 표시
		output << "visit : " << (graph[start_key].name != "None" ? graph[start_key].name : to_string(start_key)) << "\n";
	}

	for (iter = graph[start_key].adj.begin(); iter != graph[start_key].adj.end(); iter++) {
		if (!visited[*iter]) {
			visited[*iter] = true;
			output << "visit : " << (graph[*iter].name != "None" ? graph[*iter].name : to_string(*iter)) << "\n";
			DFS_by_recursion(*iter, false);
		}
	}

	if (is_start) {
		visited.assign(vertices, false);
		output << "----------\n";
	}
}

void Graph::DFS_by_recursion(vector<int> starts, bool is_start) {
	vector<int>::iterator iter;

	if (is_start) {
		output << "----------\nStation : ";
		for (vector<int>::iterator i = starts.begin(); i != starts.end(); i++) {
			output << (graph[*i].name != "None" ? graph[*i].name : to_string(*i)) << " ";
		}
		output << "\nSearch by DFS(recursion)\n\n";

		for (vector<int>::iterator i = starts.begin(); i != starts.end(); i++) {
			visited[*i] = true;
			output << "visit : " << (graph[*i].name != "None" ? graph[*i].name : to_string(*i)) << "\n";
		}
	}

	for (vector<int>::iterator i = starts.begin(); i != starts.end(); i++) {
		for (iter = graph[*i].adj.begin(); iter != graph[*i].adj.end(); iter++) {
			if (!visited[*iter]) {
				visited[*iter] = true;
				output << "visit : " << (graph[*iter].name != "None" ? graph[*iter].name : to_string(*iter)) << "\n";

				vector<int> next = { *iter };
				DFS_by_recursion(next, false);
			}
		}
	}

	if (is_start) {
		visited.assign(vertices, false);
		output << "----------\n";
	}
}