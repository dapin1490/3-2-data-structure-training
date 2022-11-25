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

// C++ 에러 메시지 참고 : https://learn.microsoft.com/ko-kr/cpp/error-messages/compiler-errors-1/c-cpp-build-errors?view=msvc-170
void error(_error code, string message="") {
	if (!message.empty())
		output << "error: " << message << "\n";

	switch (code) {
	case _error::shut_down:
		output << "프로그램 비정상 종료\n";
		break;
	case _error::ValueErrorInt: // 잘못된 입력 - int
		output << "ValueErrorInt: int 값이 입력되어야 합니다.\n";
		break;
	case _error::ValueErrorChar: // 잘못된 입력 - char
		output << "ValueErrorChar: char 값이 입력되어야 합니다.\n";
		break;
	default:
		output << "UnknownError: 알 수 없는 오류\n";
	}

	exit(1); // 프로그램 비정상 종료
}

template <typename T>
struct Edge {
	T w; // 가중치
	unsigned from;
	unsigned to;
};

template <typename T>
class TGraph {
private:
	unsigned v; // 정점 수
	vector<Edge<T>> edges;

public:
	TGraph() { this->v = 0; }
	TGraph(unsigned v) { this->v = v; }

	unsigned size() const { return v; } // const : 이 함수 안에서 쓰는 값들을 변경할 수 없다
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
			error(_error::shut_down, "정점 범위 초과");

		return;
	}

	void add_undir(Edge<T>&& e) {
		if (e.from > 0 && e.from <= this->v && e.to > 0 && e.to <= this->v) {
			this->edges.push_back(e);
			this->edges.push_back(Edge<T>{e.w, e.to, e.from});
		}
		else
			error(_error::shut_down, "정점 범위 초과");

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