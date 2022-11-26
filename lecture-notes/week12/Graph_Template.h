#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <queue>
#include <list>
using namespace std;

const string root = "../../../github desktop/3-2-data-structure-training/lecture-notes/week12/";
const string intxt = root + "graph input.txt";
const string outtxt = root + "graph output.txt";

extern ifstream input{ intxt };
extern ofstream output{ outtxt };

enum class _error : int { shut_down, ValueErrorInt, ValueErrorChar, UnknownError };

// C++ ���� �޽��� ���� : https://learn.microsoft.com/ko-kr/cpp/error-messages/compiler-errors-1/c-cpp-build-errors?view=msvc-170
void error(_error code, string message="") {
	if (!message.empty())
		output << "error: " << message << "\n";

	switch (code) {
	case _error::shut_down:
		output << "���α׷� ������ ����\n";
		break;
	case _error::ValueErrorInt: // �߸��� �Է� - int
		output << "ValueErrorInt: int ���� �ԷµǾ�� �մϴ�.\n";
		break;
	case _error::ValueErrorChar: // �߸��� �Է� - char
		output << "ValueErrorChar: char ���� �ԷµǾ�� �մϴ�.\n";
		break;
	default:
		output << "UnknownError: �� �� ���� ����\n";
	}

	exit(1); // ���α׷� ������ ����
}

struct cmp { // ���ͽ�Ʈ�� �켱���� ť �� ������
	bool operator()(pair<unsigned, unsigned> a, pair<unsigned, unsigned> b) {
		if (a.second == b.second)
			return a.first >= b.first;
		else
			return a.second > b.second;
	}
};

template <typename T>
struct Edge {
	T w; // ����ġ
	unsigned from; // ������
	unsigned to; // ����
};

template <typename T>
class TGraph {
private:
	unsigned v; // ���� ��
	vector<Edge<T>> edges; // �׷����� ���� ������

public:
	// ������
	TGraph() { this->v = 0; }
	TGraph(unsigned v) { this->v = v; }

	// �Լ� ���ǿ� ���� const : �� �Լ� �ȿ��� ���� ������ ������ �� ����
	unsigned size() const { return v; } // �׷����� ���� ������ ���� ��ȯ
	auto& edges_from() const { return this->edges; } // �׷����� ���� �������� ��ȯ
	// Ư�� ������ ����� �����鸸 ��ȯ
	auto edges_from(unsigned i) const { // ���⿡ & ���� ����� ����� ��ȯ�� �� ��. �ٵ� ������ ��..
		vector<Edge<T>> edge_from_i;
		for (auto& e : edges) {
			if (e.from == i)
				edge_from_i.push_back(e);
		}
		/*for (int idx = 0; idx < this->edges.size(); idx++) {
			if (this->edges[idx].from == i)
				edge_from_i.push_back(edges[idx]);
		}*/
		return edge_from_i;
	}

	void add(Edge<T>&& e) { // ���� ���� �߰�
		if (e.from > 0 && e.from <= this->v && e.to > 0 && e.to <= this->v)
			this->edges.push_back(e);
		else
			error(_error::shut_down, "���� ���� �ʰ�");

		return;
	}

	void add_undir(Edge<T>&& e) { // ������ ���� �߰�
		if (e.from > 0 && e.from <= this->v && e.to > 0 && e.to <= this->v) {
			this->edges.push_back(e);
			this->edges.push_back(Edge<T>{e.w, e.to, e.from});
		}
		else
			error(_error::shut_down, "���� ���� �ʰ�");

		return;
	}

	void print() { // �׷��� ���
		for (int i = 1; i <= v; i++) {
			output << "# " << i << " : ";
			vector<Edge<T>> edge = this->TGraph::edges_from(i);
			for (auto& e : edge)
				output << "(" << e.to << ", " << e.w << ")  ";
			output << "\n";
		}
		return;
	}

	// �⺻ : ���������κ����� �ּ� �Ÿ��� ���ϴ� ���ͽ�Ʈ��
	vector<unsigned> dijkstra(unsigned s) { // s�� ������
		vector<unsigned> d(v + 1, numeric_limits<unsigned>::max()); // ����� �Ÿ� ����. ���� ��ȣ�� 1���� ������
		vector<bool> visited(v + 1, false); // �湮 ���� �ʱ�ȭ
		unsigned vert = s; // ���� �湮�� ���� : ���� �������� �ʾ����Ƿ� ���������� �ʱ�ȭ
		visited[0] = true; // �� ���� �ε��� �湮�� �� ���� �̸� ǥ��
		/*
		1. ������ �湮
		2. �Ÿ� �ľ�
		3. ���� ����� ������ �̵�
		4. �ݺ�
		*/
		d[s] = 0; // �������� �Ÿ� 0

		while (find(visited.begin(), visited.end(), false) != visited.end()) { // ���� �湮���� ���� ������ �����ִ� ����
			priority_queue<pair<unsigned, unsigned>, vector<pair<unsigned, unsigned>>, cmp> next_visit; // ������ �湮�� ���� : (����, �Ÿ�)

			visited[vert] = true; // ���� �湮
			vector<Edge<T>> v_edge = edges_from(vert); // ���� �湮�� ������ ����� ������ ��������

			for (auto& e : v_edge)
				d[e.to] = min(d[e.to], d[vert] + e.w); // �Ÿ� ������Ʈ

			for (unsigned i = 1; i <= v; i++)
				next_visit.push(make_pair(i, d[i])); // ��� ������ �켱���� ť�� �߰�

			while (!next_visit.empty()) { // ���� �湮 ���� ����
				pair<unsigned, unsigned> next = next_visit.top(); // (����, �Ÿ�)
				next_visit.pop();
				if (!visited[next.first]) { // �湮���� ���� ������ ���� �湮���� ���ϰ� break
					vert = next.first;
					break;
				}
			}
		}

		return d; // �Ÿ� ���� ��ȯ
	}

	// ���� : ���ͽ�Ʈ�� ��� Ž��
	vector<pair<unsigned, unsigned>> dijkstra_path(unsigned s) { // s�� ������
		vector<pair<unsigned, unsigned>> d(v + 1, make_pair(numeric_limits<unsigned>::max(), s)); // ����� �Ÿ� ����. ���� ��ȣ�� 1���� ������. (�ּ� ��� �Ÿ�, ���� ��� ����)
		vector<bool> visited(v + 1, false); // �湮 ���� �ʱ�ȭ
		unsigned vert = s; // ���� �湮�� ���� : ���� �������� �ʾ����Ƿ� ���������� �ʱ�ȭ
		visited[0] = true; // �� ���� �ε��� �湮�� �� ���� �̸� ǥ��
		/*
		1. ������ �湮
		2. �Ÿ� �ľ�
		3. ���� ����� ������ �̵�
		4. �ݺ�
		*/
		d[s].first = 0; // �������� �Ÿ� 0

		while (find(visited.begin(), visited.end(), false) != visited.end()) { // ���� �湮���� ���� ������ �����ִ� ����
			priority_queue<pair<unsigned, unsigned>, vector<pair<unsigned, unsigned>>, cmp> next_visit; // ������ �湮�� ���� : (����, �Ÿ�)

			visited[vert] = true; // ���� �湮
			vector<Edge<T>> v_edge = edges_from(vert);

			for (auto& e : v_edge) {
				if (d[vert].first + e.w < d[e.to].first) {
					d[e.to].first = d[vert].first + e.w;
					d[e.to].second = vert;
				}
			}

			for (unsigned i = 1; i <= v; i++)
				next_visit.push(make_pair(i, d[i].first));

			while (!next_visit.empty()) {
				pair<unsigned, unsigned> next = next_visit.top(); // (����, �Ÿ�)
				next_visit.pop();
				if (!visited[next.first]) {
					vert = next.first;
					break;
				}
			}
		}

		return d;
	}

	// ���� : ���ͽ�Ʈ�� ��� Ž�� - ��� ��� ǥ��
	vector<pair<unsigned, list<unsigned>>> dijkstra_fullpath(unsigned s) { // s�� ������
		vector<pair<unsigned, unsigned>> d(v + 1, make_pair(numeric_limits<unsigned>::max(), s)); // ����� �Ÿ� ����. ���� ��ȣ�� 1���� ������. (�ּ� ��� �Ÿ�, ���� ��� ����)
		vector<bool> visited(v + 1, false); // �湮 ���� �ʱ�ȭ
		vector<pair<unsigned, list<unsigned>>> full_path(v + 1); // ��� ��� ǥ�� ���� : (�Ÿ�, ���)
		unsigned vert = s; // ���� �湮�� ���� : ���� �������� �ʾ����Ƿ� ���������� �ʱ�ȭ
		visited[0] = true; // �� ���� �ε��� �湮�� �� ���� �̸� ǥ��
		/*
		1. ������ �湮
		2. �Ÿ� �ľ�
		3. ���� ����� ������ �̵�
		4. �ݺ�
		*/
		d[s].first = 0; // �������� �Ÿ� 0

		while (find(visited.begin(), visited.end(), false) != visited.end()) { // ���� �湮���� ���� ������ �����ִ� ����
			priority_queue<pair<unsigned, unsigned>, vector<pair<unsigned, unsigned>>, cmp> next_visit; // ������ �湮�� ���� : (����, �Ÿ�)

			visited[vert] = true; // ���� �湮
			vector<Edge<T>> v_edge = edges_from(vert);

			for (auto& e : v_edge) {
				if (d[vert].first + e.w < d[e.to].first) {
					d[e.to].first = d[vert].first + e.w;
					d[e.to].second = vert;
				}
			}

			for (unsigned i = 1; i <= v; i++)
				next_visit.push(make_pair(i, d[i].first));

			while (!next_visit.empty()) {
				pair<unsigned, unsigned> next = next_visit.top(); // (����, �Ÿ�)
				next_visit.pop();
				if (!visited[next.first]) {
					vert = next.first;
					break;
				}
			}
		}

		for (unsigned i = 1; i <= v; i++) {
			unsigned dest = d[i].second;
			full_path[i].first = d[i].first;
			full_path[i].second.push_front(i);
			while (dest != s) {
				full_path[i].second.push_front(dest);
				dest = d[dest].second;
			}
			if (i != s)
				full_path[i].second.push_front(s);
		}

		return full_path;
	}
};