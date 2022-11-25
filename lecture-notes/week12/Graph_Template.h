#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
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

template <typename T>
struct Edge {
	T w; // ����ġ
	unsigned from;
	unsigned to;
};

template <typename T>
class TGraph {
private:
	unsigned v; // ���� ��
	vector<Edge<T>> edges;

public:
	TGraph() { this->v = 0; }
	TGraph(unsigned v) { this->v = v; }

	unsigned size() const { return v; } // const : �� �Լ� �ȿ��� ���� ������ ������ �� ����
	auto& edges_from() const { return this->edges; }
	auto& edges_from(unsigned i) const {
		vector<Edge<T>> edge_from_i;
		for (auto& e : edges) {
			if (e.from == i)
				edge_from_i.emplace_back(e);
		}
		/*for (int idx = 0; idx < this->edges.size(); idx++) {
			if (this->edges[idx].from == i)
				edge_from_i.push_back(edges[idx]);
		}*/
		return edge_from_i;
	}

	void add(Edge<T>&& e) {
		if (e.from > 0 && e.from <= this->v && e.to > 0 && e.to <= this->v)
			this->edges.push_back(e);
		else
			error(_error::shut_down, "���� ���� �ʰ�");

		return;
	}

	void add_undir(Edge<T>&& e) {
		if (e.from > 0 && e.from <= this->v && e.to > 0 && e.to <= this->v) {
			this->edges.push_back(e);
			this->edges.push_back(Edge<T>{e.w, e.to, e.from});
		}
		else
			error(_error::shut_down, "���� ���� �ʰ�");

		return;
	}

	void print() {
		for (int i = 1; i <= v; i++) {
			output << "# " << i << " : ";
			vector<Edge<T>> edge = this->TGraph::edges_from(i);
			for (auto& e : edge)
				output << "(" << e.to << ", " << e.w << ")  ";
			output << "\n";
		}
		return;
	}
};