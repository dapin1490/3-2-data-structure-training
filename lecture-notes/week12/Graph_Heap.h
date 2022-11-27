#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

const string root = "../../../github desktop/3-2-data-structure-training/lecture-notes/week12/";
const string intxt = root + "graph input.txt";
const string outtxt = root + "graph output.txt";

extern ifstream input{ intxt };
extern ofstream output{ outtxt };

enum class _error : int { shut_down, ValueErrorInt, ValueErrorChar, UnknownError };

// C++ 에러 메시지 참고 : https://learn.microsoft.com/ko-kr/cpp/error-messages/compiler-errors-1/c-cpp-build-errors?view=msvc-170
void error(_error code, string message = "") {
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

		while (i != 1 && is_left_min(e, get_parent(e))) { // 루트가 아니고 부모보다 키가 작으면
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