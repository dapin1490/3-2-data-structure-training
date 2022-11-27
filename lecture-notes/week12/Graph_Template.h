#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <list>
#include <limits>
#include <algorithm>
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

struct cmp { // 다익스트라 우선순위 큐 비교 연산자 : 가중치가 적고 정점 번호가 적은 것을 우선으로 함
	bool operator()(pair<unsigned, unsigned> a, pair<unsigned, unsigned> b) {
		if (a.second == b.second)
			return a.first >= b.first;
		else
			return a.second > b.second;
	}
};

template <typename T>
struct Edge {
	T w; // 가중치
	unsigned from; // 시작점
	unsigned to; // 종점
};

template <typename T>
class TGraph {
private:
	unsigned v; // 정점 수
	vector<Edge<T>> edges; // 그래프가 갖는 간선들

public:
	// 생성자
	TGraph() { this->v = 0; }
	TGraph(unsigned v) { this->v = v; }

	// 함수 정의에 쓰인 const : 이 함수 안에서 쓰는 값들을 변경할 수 없다
	unsigned size() const { return v; } // 그래프가 갖는 정점의 수를 반환
	auto& edges_from() const { return this->edges; } // 그래프가 갖는 간선들을 반환
	// 특정 정점에 연결된 간선들만 반환
	auto edges_from(unsigned i) const { // 여기에 & 쓰면 결과가 제대로 반환이 안 됨. 근데 이유는 모름..
		vector<Edge<T>> edge_from_i;
		for (auto& e : edges) {
			if (e.from == i)
				edge_from_i.push_back(e);
		}
		/* // 이쪽 코드도 똑같은 기능을 함
		for (int idx = 0; idx < this->edges.size(); idx++) {
			if (this->edges[idx].from == i)
				edge_from_i.push_back(edges[idx]);
		}*/
		return edge_from_i;
	}

	void add(Edge<T>&& e) { // 방향 간선 추가
		if (e.from > 0 && e.from <= this->v && e.to > 0 && e.to <= this->v)
			this->edges.push_back(e);
		else
			error(_error::shut_down, "정점 범위 초과");

		return;
	}

	void add_undir(Edge<T>&& e) { // 무방향 간선 추가
		if (e.from > 0 && e.from <= this->v && e.to > 0 && e.to <= this->v) {
			this->edges.push_back(e);
			this->edges.push_back(Edge<T>{e.w, e.to, e.from});
		}
		else
			error(_error::shut_down, "정점 범위 초과");

		return;
	}

	void print() { // 그래프 출력
		for (int i = 1; i <= v; i++) {
			output << "# " << i << " : "; // 정점 번호
			vector<Edge<T>> edge = this->TGraph::edges_from(i); // 정점에 연결된 간선 가져오기
			for (auto& e : edge)
				output << "(" << e.to << ", " << e.w << ")  "; // 정점에 연결된 간선 출력
			output << "\n";
		}
		return;
	}

	// 기본 : 시작점으로부터의 최소 거리만 구하는 다익스트라
	auto dijkstra(unsigned s) { // s는 시작점
		vector<unsigned> d(v + 1, numeric_limits<unsigned>::max()); // 저장용 거리 벡터. 정점 번호가 1부터 시작함
		vector<bool> visited(v + 1, false); // 방문 여부 초기화

		unsigned vert = s; // 이제 방문할 정점 : 아직 시작하지 않았으므로 시작점으로 초기화
		visited[0] = true; // 안 쓰는 인덱스 방문할 일 없게 미리 표시
		/*
		1. 시작점 방문
		2. 거리 파악
		3. 가장 가까운 곳으로 이동
		4. 반복
		*/
		d[s] = 0; // 시작점은 거리 0

		while (find(visited.begin(), visited.end(), false) != visited.end()) { // 아직 방문하지 않은 정점이 남아있는 동안
			priority_queue<pair<unsigned, unsigned>, vector<pair<unsigned, unsigned>>, cmp> next_visit; // 다음에 방문할 정점 : (정점, 거리)

			visited[vert] = true; // 정점 방문
			vector<Edge<T>> v_edge = edges_from(vert); // 지금 방문한 정점에 연결된 간선들 가져오기

			for (auto& e : v_edge) {
				if (d[vert] + e.w < d[e.to]) { // 거리를 업데이트할 필요가 있을 때에만
					d[e.to] = d[vert] + e.w; // 거리 업데이트
				}
			}

			for (unsigned i = 1; i <= v; i++)
				if (!visited[i])
					next_visit.push(make_pair(i, d[i])); // 방문하지 않은 모든 정점을 우선순위 큐에 추가

			if (!next_visit.empty()) {
				pair<unsigned, unsigned> next = next_visit.top(); // (정점, 거리)
				vert = next.first;
			}
		}

		return d; // 거리 벡터 반환
	}

	// 응용 : 다익스트라 경로 탐색
	vector<pair<unsigned, unsigned>> dijkstra_path(unsigned s) { // s는 시작점
		vector<pair<unsigned, unsigned>> d(v + 1, make_pair(numeric_limits<unsigned>::max(), s)); // 저장용 거리 벡터. 정점 번호가 1부터 시작함. (최소 비용 거리, 직전 경로 정점)
		vector<bool> visited(v + 1, false); // 방문 여부 초기화
		unsigned vert = s; // 이제 방문할 정점 : 아직 시작하지 않았으므로 시작점으로 초기화
		visited[0] = true; // 안 쓰는 인덱스 방문할 일 없게 미리 표시
		d[s].first = 0; // 시작점은 거리 0

		while (find(visited.begin(), visited.end(), false) != visited.end()) { // 아직 방문하지 않은 정점이 남아있는 동안
			priority_queue<pair<unsigned, unsigned>, vector<pair<unsigned, unsigned>>, cmp> next_visit; // 다음에 방문할 정점 : (정점, 거리)

			visited[vert] = true; // 정점 방문
			vector<Edge<T>> v_edge = edges_from(vert); // 정점에 연결된 간선 가져오기

			for (auto& e : v_edge) {
				if (d[vert].first + e.w < d[e.to].first) { // 거리를 업데이트할 필요가 있을 때에만
					d[e.to].first = d[vert].first + e.w; // 거리 업데이트
					d[e.to].second = vert; // 직전 방문 정점 업데이트
				}
			}

			for (unsigned i = 1; i <= v; i++)
				if (!visited[i])
					next_visit.push(make_pair(i, d[i].first)); // 방문하지 않은 모든 정점을 우선순위 큐에 추가

			if (!next_visit.empty()) {
				pair<unsigned, unsigned> next = next_visit.top(); // (정점, 거리)
				vert = next.first;
			}
		}

		return d;
	}

	// 응용 : 다익스트라 경로 탐색 - 모든 경로 표시
	vector<pair<unsigned, list<unsigned>>> dijkstra_fullpath(unsigned s) { // s는 시작점
		vector<pair<unsigned, unsigned>> d(v + 1, make_pair(numeric_limits<unsigned>::max(), s)); // 저장용 거리 벡터. 정점 번호가 1부터 시작함. (최소 비용 거리, 직전 경로 정점)
		vector<bool> visited(v + 1, false); // 방문 여부 초기화
		vector<pair<unsigned, list<unsigned>>> full_path(v + 1); // 모든 경로 표시 벡터 : (거리, 경로)
		unsigned vert = s; // 이제 방문할 정점 : 아직 시작하지 않았으므로 시작점으로 초기화
		visited[0] = true; // 안 쓰는 인덱스 방문할 일 없게 미리 표시
		d[s].first = 0; // 시작점은 거리 0

		while (find(visited.begin(), visited.end(), false) != visited.end()) { // 아직 방문하지 않은 정점이 남아있는 동안
			priority_queue<pair<unsigned, unsigned>, vector<pair<unsigned, unsigned>>, cmp> next_visit; // 다음에 방문할 정점 : (정점, 거리)

			visited[vert] = true; // 정점 방문
			vector<Edge<T>> v_edge = edges_from(vert); // 정점에 연결된 간선 가져오기

			for (auto& e : v_edge) {
				if (d[vert].first + e.w < d[e.to].first) { // 거리를 업데이트할 필요가 있을 때에만
					d[e.to].first = d[vert].first + e.w; // 거리 업데이트
					d[e.to].second = vert; // 직전 방문 정점 업데이트
				}
			}

			for (unsigned i = 1; i <= v; i++)
				if (!visited[i])
					next_visit.push(make_pair(i, d[i].first)); // 방문하지 않은 모든 정점을 우선순위 큐에 추가

			if (!next_visit.empty()) {
				pair<unsigned, unsigned> next = next_visit.top(); // (정점, 거리)
				vert = next.first;
			}
		}

		// 위에서 알아낸 최소 비용 거리와 직전 방문 정점을 이용해 모든 경로 찾기
		// 도착점인 i로부터 시작점인 s까지 거슬러 올라가는 방식으로 탐색
		for (unsigned i = 1; i <= v; i++) {
			unsigned dest = d[i].second; // 시작점 s에서 정점 i를 찾아가는 경로상에서, i를 방문하기 직전의 정점
			full_path[i].first = d[i].first; // s에서 i로 가는 최소 비용
			full_path[i].second.push_front(i); // 도착점 i 먼저 리스트에 추가
			while (dest != s) { // 시작점 s에 도달하면 종료
				full_path[i].second.push_front(dest); // 지금 방문하는 점을 경로 맨 앞에 추가
				dest = d[dest].second; // 시작점에서 지금 방문한 점으로 오기까지, 직전 방문 정점을 다음 방문지로 지정
			}
			if (i != s) // 위의 반복문은 시작점 s를 다음 방문지로 지정하면 종료되기 때문에 경로에 추가되지 않으므로, 현재 도착점이 시작점과 다르다면 경로에 추가해야 함
				full_path[i].second.push_front(s);
		}

		return full_path;
	}
};