#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <list>
#include <algorithm>
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

struct cmp { // ���ͽ�Ʈ�� �켱���� ť �� ������ : ����ġ�� ���� ���� ��ȣ�� ���� ���� �켱���� ��
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
struct HeapNode { // �Ÿ� ������ ��Ҹ� �̿��ϴ� ���̹Ƿ� �������� ������ �ִ�
	unsigned to;
	T w;
};

template <typename T>
class Heap { // 0�� �ε����� �� ����, �ּ���
private:
	vector<HeapNode<T>> heap; // ���� ������ ����ġ w, Ž���� ����� Ű�� �������� ������ ����
	unsigned s; // size

public:
	Heap(unsigned s) { heap.resize(s + 1); this->s = 0; } // push�� ���� ���� ������ size�� 0

	bool is_empty() { return s == 0; };
	bool is_left_min(HeapNode<T> a, HeapNode<T> b) { // ������ ������ �˻�
		if (a.w == b.w)
			return a.to < b.to;
		return a.w < b.w;
	}
	bool is_in(HeapNode<T> e) { // ��Ұ� �ִ��� �˻�
		for (int i = 1; i <= s; i++) {
			if (heap[i].to == e.to && heap[i].w == e.w)
				return true;
		}
		return false;
	}
	bool has_left(HeapNode<T> e) { // ���� �ڽ��� �ִ��� �˻�
		return find_index(e) * 2 <= s;
	}
	bool has_right(HeapNode<T> e) { // ������ �ڽ��� �ִ��� �˻�
		return find_index(e) * 2 + 1 <= s;
	}
	void swap(HeapNode<T>& a, HeapNode<T>& b) {
		HeapNode<T> tmp = a;
		a = b;
		b = tmp;
		return;
	}

	int find_index(HeapNode<T> key) { 
		for (int i = 1; i <= s; i++)
			if (heap[i].to == key.to && heap[i].w == key.w)
				return i;
	}
	HeapNode<T>& get_parent(HeapNode<T> key) { return heap[find_index(key) / 2]; }
	HeapNode<T>& get_left(HeapNode<T> key) { return heap[find_index(key) * 2]; }
	HeapNode<T>& get_right(HeapNode<T> key) { return heap[find_index(key) * 2 + 1]; }

	void push(HeapNode<T> e) { // ����
		unsigned i = ++s; // �� ũ�⸦ ������Ű��, ������ ��ġ���� ����
		heap[i] = e; // ���� ��ġ�� ��� �ֱ�

		while(i != 1 && is_left_min(e, get_parent(e))) { // ��Ʈ�� �ƴϰ� �θ𺸴� Ű�� ������
			heap[i] = get_parent(e); // �θ� �ڽ��� ��ġ�� �������
			i /= 2; // �ڽ��� �ö�
		}

		heap[i] = e; // ���������� �ö� �ڸ��� ����

		output << "push (" << e.to << ", " << e.w << ")\n";
		print();

		return;
	}
	HeapNode<T>& pop() { // heapify�� ����� �� ��
		if (is_empty())
			error(_error::shut_down, "���� ����ִµ� �����Ϸ��� �õ���");

		HeapNode<T> popped = heap[1]; // pop�� ���
		heap[1] = heap[s--]; // ������ ��Ҹ� ��Ʈ�� �ű�� ������ ����
		unsigned i = 1; // �ٽ� heapify�ؾ� �� ����� �ε���

		while (i <= s) { // �� ������ �������� ����
			bool has_l = has_left(heap[i]);
			bool has_r = has_right(heap[i]);

			if (has_l && has_r) { // ���� �ڽ��� �� ����
				auto& left = get_left(heap[i]);
				auto& right = get_right(heap[i]);

				if (is_left_min(left, heap[i]) || is_left_min(right, heap[i])) {
					if (is_left_min(left, right)) {
						swap(heap[i], right);
						i = i * 2 + 1;
					}
					else {
						swap(heap[i], left);
						i = i * 2;
					}
				}
				else
					break;
			}
			else if (has_r) { // ������ �ڽĸ� ����
				auto& right = get_right(heap[i]);

				if (is_left_min(right, heap[i])) {
					swap(heap[i], right);
					i = i * 2 + 1;
				}
				else
					break;
			}
			else if (has_l) { // ���� �ڽĸ� ����
				auto& left = get_left(heap[i]);

				if (is_left_min(left, heap[i])) {
					swap(heap[i], left);
					i = i * 2;
				}
				else
					break;
			}
			else { // ����
				break;
			}
		}

		output << "popped (" << popped.to << ", " << popped.w << ")\n";
		print();

		return popped;
	}
	void edit(HeapNode<T> before, HeapNode<T> after) { // heapify�� ����� �� ��
		int idx = find_index(before);
		heap[idx] = after;

		if (is_left_min(before, after)) { // Ŀ�� -> �Ʒ��� �������� ��
			while (idx <= s) {
				bool has_l = has_left(heap[idx]);
				bool has_r = has_right(heap[idx]);

				if (has_l && has_r) {
					auto& left = get_left(heap[idx]);
					auto& right = get_right(heap[idx]);

					if (is_left_min(left, heap[idx]) || is_left_min(right, heap[idx])) {
						if (is_left_min(right, heap[idx]) && is_left_min(left, right)) {
							swap(heap[idx], right);
							idx = idx * 2 + 1;
						}
						else {
							swap(heap[idx], left);
							idx = idx * 2;
						}
					}
					else
						break;
				}
				else if (has_r) {
					auto& right = get_right(heap[idx]);

					if (is_left_min(right, heap[idx])) {
						swap(heap[idx], right);
						idx = idx * 2 + 1;
					}
					else
						break;
				}
				else if (has_l) {
					auto& left = get_left(heap[idx]);

					if (is_left_min(left, heap[idx])) {
						swap(heap[idx], left);
						idx = idx * 2 + 1;
					}
					else
						break;
				}
				else { // �ڽ��� ������ ������ ���� ����
					break;
				}
			}
		}
		else { // �۾��� -> ���� �ö󰡾� ��
			while (idx >= 1 && is_left_min(heap[idx], get_parent(heap[idx]))) {
				swap(heap[idx], get_parent(heap[idx]));
				idx /= 2;
			}
		}

		output << "edited (" << before.to << ", " << before.w << ") -> (" << after.to << ", " << after.w << ")\n";
		print();
	}

	void print() {
		output << "print Edge heap\n";
		for (int i = 1; i <= s; i++)
			output << "(" << heap[i].to << ", " << heap[i].w << ")\n";
		output << "\n";
		return;
	}
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
		/* // ���� �ڵ嵵 �Ȱ��� ����� ��
		for (int idx = 0; idx < this->edges.size(); idx++) {
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
			output << "# " << i << " : "; // ���� ��ȣ
			vector<Edge<T>> edge = this->TGraph::edges_from(i); // ������ ����� ���� ��������
			for (auto& e : edge)
				output << "(" << e.to << ", " << e.w << ")  "; // ������ ����� ���� ���
			output << "\n";
		}
		return;
	}

	// �⺻ : ���������κ����� �ּ� �Ÿ��� ���ϴ� ���ͽ�Ʈ��
	auto dijkstra(unsigned s) { // s�� ������
		vector<unsigned> d(v + 1, numeric_limits<unsigned>::max()); // ����� �Ÿ� ����. ���� ��ȣ�� 1���� ������
		vector<bool> visited(v + 1, false); // �湮 ���� �ʱ�ȭ
		Heap<unsigned> next_visit(v);

		unsigned vert = s; // ���� �湮�� ���� : ���� �������� �ʾ����Ƿ� ���������� �ʱ�ȭ
		visited[0] = true; // �� ���� �ε��� �湮�� �� ���� �̸� ǥ��

		for (unsigned i = 1; i <= v; i++)
			next_visit.push(HeapNode<unsigned>{i, d[i]});
		/*
		1. ������ �湮
		2. �Ÿ� �ľ�
		3. ���� ����� ������ �̵�
		4. �ݺ�
		*/
		d[s] = 0; // �������� �Ÿ� 0

		while (find(visited.begin(), visited.end(), false) != visited.end()) { // ���� �湮���� ���� ������ �����ִ� ����
			visited[vert] = true; // ���� �湮
			vector<Edge<T>> v_edge = edges_from(vert); // ���� �湮�� ������ ����� ������ ��������

			for (auto& e : v_edge) {
				if (d[e.to] > d[vert] + e.w) {
					if (next_visit.is_in(HeapNode<unsigned>{e.to, d[e.to]})) // ���� �湮 ���� ���� �ִ��� ���� Ȯ��
						next_visit.edit(HeapNode<unsigned>{e.to, d[e.to]}, HeapNode<unsigned>{e.to, d[vert] + e.w}); // ���� ���� ������Ʈ
					d[e.to] = d[vert] + e.w;
				}
			}

			if (!next_visit.is_empty()) { // ������� ���� ������ pop
				HeapNode<unsigned> next = next_visit.pop(); // (����, �Ÿ�)
				vert = next.to;
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
		d[s].first = 0; // �������� �Ÿ� 0

		while (find(visited.begin(), visited.end(), false) != visited.end()) { // ���� �湮���� ���� ������ �����ִ� ����
			priority_queue<pair<unsigned, unsigned>, vector<pair<unsigned, unsigned>>, cmp> next_visit; // ������ �湮�� ���� : (����, �Ÿ�)

			visited[vert] = true; // ���� �湮
			vector<Edge<T>> v_edge = edges_from(vert); // ������ ����� ���� ��������

			for (auto& e : v_edge) {
				if (d[vert].first + e.w < d[e.to].first) { // �Ÿ��� ������Ʈ�� �ʿ䰡 ���� ������
					d[e.to].first = d[vert].first + e.w; // �Ÿ� ������Ʈ
					d[e.to].second = vert; // ���� �湮 ���� ������Ʈ
				}
			}

			for (unsigned i = 1; i <= v; i++)
				if (!visited[i])
					next_visit.push(make_pair(i, d[i].first)); // �湮���� ���� ��� ������ �켱���� ť�� �߰�

			if (!next_visit.empty()) {
				pair<unsigned, unsigned> next = next_visit.top(); // (����, �Ÿ�)
				vert = next.first;
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
		d[s].first = 0; // �������� �Ÿ� 0

		while (find(visited.begin(), visited.end(), false) != visited.end()) { // ���� �湮���� ���� ������ �����ִ� ����
			priority_queue<pair<unsigned, unsigned>, vector<pair<unsigned, unsigned>>, cmp> next_visit; // ������ �湮�� ���� : (����, �Ÿ�)

			visited[vert] = true; // ���� �湮
			vector<Edge<T>> v_edge = edges_from(vert); // ������ ����� ���� ��������

			for (auto& e : v_edge) {
				if (d[vert].first + e.w < d[e.to].first) { // �Ÿ��� ������Ʈ�� �ʿ䰡 ���� ������
					d[e.to].first = d[vert].first + e.w; // �Ÿ� ������Ʈ
					d[e.to].second = vert; // ���� �湮 ���� ������Ʈ
				}
			}

			for (unsigned i = 1; i <= v; i++)
				if (!visited[i])
					next_visit.push(make_pair(i, d[i].first)); // �湮���� ���� ��� ������ �켱���� ť�� �߰�

			if (!next_visit.empty()) {
				pair<unsigned, unsigned> next = next_visit.top(); // (����, �Ÿ�)
				vert = next.first;
			}
		}

		// ������ �˾Ƴ� �ּ� ��� �Ÿ��� ���� �湮 ������ �̿��� ��� ��� ã��
		// �������� i�κ��� �������� s���� �Ž��� �ö󰡴� ������� Ž��
		for (unsigned i = 1; i <= v; i++) {
			unsigned dest = d[i].second; // ������ s���� ���� i�� ã�ư��� ��λ󿡼�, i�� �湮�ϱ� ������ ����
			full_path[i].first = d[i].first; // s���� i�� ���� �ּ� ���
			full_path[i].second.push_front(i); // ������ i ���� ����Ʈ�� �߰�
			while (dest != s) { // ������ s�� �����ϸ� ����
				full_path[i].second.push_front(dest); // ���� �湮�ϴ� ���� ��� �� �տ� �߰�
				dest = d[dest].second; // ���������� ���� �湮�� ������ �������, ���� �湮 ������ ���� �湮���� ����
			}
			if (i != s) // ���� �ݺ����� ������ s�� ���� �湮���� �����ϸ� ����Ǳ� ������ ��ο� �߰����� �����Ƿ�, ���� �������� �������� �ٸ��ٸ� ��ο� �߰��ؾ� ��
				full_path[i].second.push_front(s);
		}

		return full_path;
	}
};