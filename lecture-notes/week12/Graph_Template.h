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
struct HeapNode { // 거리 벡터의 요소를 이용하는 것이므로 시작점은 정해져 있다
	unsigned to;
	T w;
};

template <typename T>
class Heap { // 0번 인덱스는 안 쓴다, 최소힙
private:
	vector<HeapNode<T>> heap; // 정렬 기준은 가중치 w, 탐색에 사용할 키는 시작점과 종점의 조합
	unsigned s; // size

public:
	Heap(unsigned s) { heap.resize(s + 1); this->s = 0; } // push한 것이 없기 때문에 size는 0

	bool is_empty() { return s == 0; };
	bool is_left_min(HeapNode<T> a, HeapNode<T> b) { // 왼쪽이 작은지 검사
		if (a.w == b.w)
			return a.to < b.to;
		return a.w < b.w;
	}
	bool is_in(HeapNode<T> e) { // 요소가 있는지 검사
		for (int i = 1; i <= s; i++) {
			if (heap[i].to == e.to && heap[i].w == e.w)
				return true;
		}
		return false;
	}
	bool has_left(HeapNode<T> e) { // 왼쪽 자식이 있는지 검사
		return find_index(e) * 2 <= s;
	}
	bool has_right(HeapNode<T> e) { // 오른쪽 자식이 있는지 검사
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

	void push(HeapNode<T> e) { // 삽입
		unsigned i = ++s; // 힙 크기를 증가시키고, 증가된 위치에서 시작
		heap[i] = e; // 시작 위치에 요소 넣기

		while(i != 1 && is_left_min(e, get_parent(e))) { // 루트가 아니고 부모보다 키가 작으면
			heap[i] = get_parent(e); // 부모를 자신의 위치로 끌어내리고
			i /= 2; // 자신이 올라감
		}

		heap[i] = e; // 마지막으로 올라간 자리에 안착

		output << "push (" << e.to << ", " << e.w << ")\n";
		print();

		return;
	}
	HeapNode<T>& pop() { // heapify가 제대로 안 됨
		if (is_empty())
			error(_error::shut_down, "힙이 비어있는데 삭제하려고 시도함");

		HeapNode<T> popped = heap[1]; // pop할 요소
		heap[1] = heap[s--]; // 마지막 요소를 루트로 옮기고 사이즈 감소
		unsigned i = 1; // 다시 heapify해야 할 요소의 인덱스

		while (i <= s) { // 힙 사이즈 내에서만 실행
			bool has_l = has_left(heap[i]);
			bool has_r = has_right(heap[i]);

			if (has_l && has_r) { // 양쪽 자식이 다 있음
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
			else if (has_r) { // 오른쪽 자식만 있음
				auto& right = get_right(heap[i]);

				if (is_left_min(right, heap[i])) {
					swap(heap[i], right);
					i = i * 2 + 1;
				}
				else
					break;
			}
			else if (has_l) { // 왼쪽 자식만 있음
				auto& left = get_left(heap[i]);

				if (is_left_min(left, heap[i])) {
					swap(heap[i], left);
					i = i * 2;
				}
				else
					break;
			}
			else { // 리프
				break;
			}
		}

		output << "popped (" << popped.to << ", " << popped.w << ")\n";
		print();

		return popped;
	}
	void edit(HeapNode<T> before, HeapNode<T> after) { // heapify가 제대로 안 됨
		int idx = find_index(before);
		heap[idx] = after;

		if (is_left_min(before, after)) { // 커짐 -> 아래로 내려가야 함
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
				else { // 자신이 리프라 내려갈 데가 없음
					break;
				}
			}
		}
		else { // 작아짐 -> 위로 올라가야 함
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
		Heap<unsigned> next_visit(v);

		unsigned vert = s; // 이제 방문할 정점 : 아직 시작하지 않았으므로 시작점으로 초기화
		visited[0] = true; // 안 쓰는 인덱스 방문할 일 없게 미리 표시

		for (unsigned i = 1; i <= v; i++)
			next_visit.push(HeapNode<unsigned>{i, d[i]});
		/*
		1. 시작점 방문
		2. 거리 파악
		3. 가장 가까운 곳으로 이동
		4. 반복
		*/
		d[s] = 0; // 시작점은 거리 0

		while (find(visited.begin(), visited.end(), false) != visited.end()) { // 아직 방문하지 않은 정점이 남아있는 동안
			visited[vert] = true; // 정점 방문
			vector<Edge<T>> v_edge = edges_from(vert); // 지금 방문한 정점에 연결된 간선들 가져오기

			for (auto& e : v_edge) {
				if (d[e.to] > d[vert] + e.w) {
					if (next_visit.is_in(HeapNode<unsigned>{e.to, d[e.to]})) // 다음 방문 정점 힙에 있는지 먼저 확인
						next_visit.edit(HeapNode<unsigned>{e.to, d[e.to]}, HeapNode<unsigned>{e.to, d[vert] + e.w}); // 있을 때만 업데이트
					d[e.to] = d[vert] + e.w;
				}
			}

			if (!next_visit.is_empty()) { // 비어있지 않을 때에만 pop
				HeapNode<unsigned> next = next_visit.pop(); // (정점, 거리)
				vert = next.to;
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