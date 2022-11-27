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

// C++ ���� �޽��� ���� : https://learn.microsoft.com/ko-kr/cpp/error-messages/compiler-errors-1/c-cpp-build-errors?view=msvc-170
void error(_error code, string message = "") {
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

		while (i != 1 && is_left_min(e, get_parent(e))) { // ��Ʈ�� �ƴϰ� �θ𺸴� Ű�� ������
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